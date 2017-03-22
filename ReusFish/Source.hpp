#ifndef SOURCE_INC__
#define SOURCE_INC__

#include <algorithm>
#include <iostream>
#include <cstring>

#include "Aspects.hpp"
#include "biome.hpp"
#include "SourceClass.hpp"
#include "SourceType.hpp"
#include "SourceTypeList.hpp"

class Space;
typedef std::vector<const Source *> SourceList;

// This source upgrades to <new_source> with <aspect1> or <aspect2>
class Upgrade
{
   public:
      Upgrade() : 
	 m_new_source(SOURCE_TYPE_NONE), 
	 m_aspect1(Aspects::ASPECT_T_MAX),
	 m_aspect2(Aspects::ASPECT_T_MAX) 
      {}
      Upgrade(source_type_t source_type,
	    Aspects::aspect_t aspect1,
	    Aspects::aspect_t aspect2) : 
	 m_new_source(source_type), 
	 m_aspect1(aspect1), 
	 m_aspect2(aspect2) 
      {}

      bool operator==(const Upgrade &rhs) const
      {
	 return ((m_new_source == rhs.m_new_source) &&
	       (m_aspect1 == rhs.m_aspect1) &&
	       (m_aspect2 == rhs.m_aspect2));
      }
      source_type_t m_new_source;
      Aspects::aspect_t m_aspect1;
      Aspects::aspect_t m_aspect2;
};

class Source
{
   public :
      Source() { Create(); }
      Source(const Source &original) :
	 m_name(original.m_name),
	 m_class(original.m_class),
	 m_type(original.m_type),
	 m_level(original.m_level),
	 m_base_yield(original.m_base_yield),
	 m_max_aspects(original.m_max_aspects),
	 m_aspects(original.m_aspects),
	 m_upgrades(original.m_upgrades)
      {}
      Source(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }
      virtual void Create(void) 
      {
	 m_name  = "None";
	 m_class = SOURCE_CLASS_NONE;
	 m_type  = SOURCE_TYPE_NONE;
	 m_max_aspects = 0;
	 m_level = 0;
      };
      
      bool operator==(const Source &rhs) const
      {
	 if (!strcmp(m_name,rhs.m_name) && (m_aspects == rhs.m_aspects))
	    return true;
	 return false;
#if 0
	 if (strcmp(m_name,rhs.m_name)               ||
	     (m_class != rhs.m_class)             ||
	     (m_type != rhs.m_type)               ||
	     (m_level != rhs.m_level)             ||
	     !(m_base_yield == rhs.m_base_yield)  ||
	     (m_max_aspects != rhs.m_max_aspects) ||
	     !(m_aspects == rhs.m_aspects)        ||
	     !(m_upgrades == rhs.m_upgrades))
	    return false;
	 return true;
#endif
      }

      source_class_t Class(void) const {return m_class;}
      source_type_t  Type(void)  const {return m_type; }
      unsigned Hash(void) const
      {
	 unsigned this_hash = 0x12345678 + m_class + ((m_type +1)<< 2) + ((m_level +1)<< 4);
	 unsigned hash = this_hash;
	 
	 hash += this_hash << 7;
	 hash += this_hash << 14;
	 hash += this_hash << 24;
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	 {
	    unsigned aspect = m_aspects[i] + 1;
	    hash += aspect;
	    hash += aspect << 5;
	    hash += aspect << 9;
	    hash += aspect << 15;
	    hash += aspect << 19;
	    hash += aspect << 25;
	 }
	 return hash;
      }

      static const unsigned YIELD_MASK_FOOD   = 0x1;
      static const unsigned YIELD_MASK_TECH   = 0x2;
      static const unsigned YIELD_MASK_WEALTH = 0x4;
      static const unsigned YIELD_MASK_DANGER = 0x8;
      static const unsigned YIELD_MASK_AWE    = 0x10;
      static const unsigned YIELD_MASK_ALL    = 0xFF;

      virtual void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const { yield.Reset(); } 
      virtual void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const { yield.Reset(); }
      virtual unsigned GetRange(std::vector<Space> &spaces, unsigned loc) const { return m_base_yield.m_range; }
      virtual bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield) { return false; }
      virtual void ResetPostProcess(void) { }
      void GetAspects(unsigned natura, Yield &yield) const
      {
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	 {
	    Yield this_yield;
	    aspects.Bonus(m_aspects[i], natura, this_yield);
	    yield += this_yield;
	 }
      }
      bool AddAspect(Aspects::aspect_t aspect)
      {
	 if (m_aspects.size() < m_max_aspects)
	 {
	    m_aspects.push_back(aspect);
	    std::sort(m_aspects.begin(), m_aspects.end());
	    return true;
	 }
	 return false;
      }
      bool CanAddAspect(Aspects::aspect_t aspect) const
      {
	 if (m_aspects.size() >= std::min<unsigned>(3, m_max_aspects))
	    return false;
	 if (CountAspects(Aspects::SUBLIME) >= std::max<unsigned>(2, m_max_aspects/2))
	       return false;
	 unsigned count = 0;
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	    if (m_aspects[i] == aspect)
	       count += 1;
	 if (count >= 2)
	    return false;

	 return true;
      }
      unsigned CountAspects(Aspects::aspect_class_t aspect_class) const
      {
	 unsigned count = 0;
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	    if ((m_aspects[i] & 3U) == (aspect_class & 3U))
	       count += 1;
	 return count;
      }
      virtual void GetUpgrades (biome_t biome, SourceList &upgrades) const;
      virtual bool IsValidForBiome(biome_t biome) const { return true; }

      virtual Source* Clone() const {if (this) return new Source(*this); else return NULL;}
      
      void Print(void) const
      {
	 std::cout << m_name << ":";
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	 {
	    aspects.Print(m_aspects[i]);
	    std::cout << ":";
	 }
      }

   protected:
      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3, bool once) const;

      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3, bool once) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - yield.m_range, loc + yield.m_range, 
	       yield_adder, type1, type2, type3, once);
      }

      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, true);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type2, true);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type1, type1, true);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type2, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type1, type1, false);
      }

      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3) const
      {
	 AddInRange(spaces, loc, yield, start, end, yield_adder, type1, type2, type3, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2) const
      {
	 AddAllInRange(spaces, loc, yield, start, end, yield_adder, type1, type2, type2);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
	    const Yield &yield_adder, source_type_t type1) const
      {
	 AddAllInRange(spaces, loc, yield, start, end, yield_adder, type1, type1, type1);
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, type1, type2, type3, true);
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2) const
      {
	 AddIfAdjacent(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1) const
      {
	 AddIfAdjacent(spaces, loc, yield, yield_adder, type1, type1, type1);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, type1, type2, type3, false);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2) const
      {
	 AddAllAdjacent(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1) const
      {
	 AddAllAdjacent(spaces, loc, yield, yield_adder, type1, type1, type1);
      }

      // Same as above, but classes rather than types
      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
			      const Yield &yield_adder, source_class_t source_class, bool once) const;
      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, 
			      const Yield &yield_adder, source_class_t source_class, bool once) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - yield.m_range, loc + yield.m_range, yield_adder, source_class, once);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, source_class, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
			      const Yield &yield_adder, source_class_t source_class) const
      {
	 AddInRange(spaces, loc, yield, start, end, yield_adder, source_class, false);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class) const
      {
	 AddInRange(spaces, loc, yield, yield_adder, source_class, true);
      }

      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_class_t source_class) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, source_class, true);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_class_t source_class) const
      {
	 AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, source_class, false);
      }

      // 
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, int start, unsigned end, source_class_t source_class) const;
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range, source_class_t source_class) const
      {
	 return NotInRange(spaces, loc, (int)loc - range, loc + range, source_class);
      }
      bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_class_t source_class) const
      {
	 return NotInRange(spaces, loc, 1, source_class);
      }
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, int start, unsigned end,
	              source_type_t type1, source_type_t type2, source_type_t type3) const; 
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
	              source_type_t type1, source_type_t type2, source_type_t type3) const 
      {
	 return NotInRange(spaces, loc, (int)loc - range, loc + range, type1, type2, type3);
      }
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
	              source_type_t type1, source_type_t type2) const
      {
	 return NotInRange(spaces, loc, range, type1, type2, type2);
      }
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
	              source_type_t type1) const
      {
	 return NotInRange(spaces, loc, range, type1, type1, type1);
      }
      bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
	              source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 return NotInRange(spaces, loc, 1, type1, type2, type3);
      }

      bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
	              source_type_t type1, source_type_t type2) const
      {
	 return NotInRange(spaces, loc, 1, type1, type2);
      }
      bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_type_t type1) const
      {
	 return NotInRange(spaces, loc, 1, type1);
      }


      void GetFood(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &food_yield) const
      {
	 GetFood(spaces, loc, loc, loc, yield, food_yield);
      }
      void GetFood(std::vector<Space> &spaces, unsigned loc, int start, unsigned end, const Yield &yield, std::vector<unsigned> &food_yield) const;
      void GetTech(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &tech_yield) const
      {
	 GetTech(spaces, loc, loc, loc, yield, tech_yield);
      }
      void GetTech(std::vector<Space> &spaces, unsigned loc, int start, unsigned end, const Yield &yield, std::vector<unsigned> &tech_yield) const;
      void GetWealth(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &wealth_yield) const
      {
	 GetWealth(spaces, loc, loc, loc, yield, wealth_yield);
      }
      void GetWealth(std::vector<Space> &spaces, unsigned loc, int start, unsigned end, const Yield &yield, std::vector<unsigned> &wealth_yield) const;
      void GetDanger(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &danger_yield) const
      {
	 GetDanger(spaces, loc, loc, loc, yield, danger_yield);
      }
      void GetDanger(std::vector<Space> &spaces, unsigned loc, int start, unsigned end, const Yield &yield, std::vector<unsigned> &danger_yield) const;
      void GetAwe(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &awe_yield) const
      {
	 GetAwe(spaces, loc, loc, loc, yield, awe_yield);
      }
      void GetAwe(std::vector<Space> &spaces, unsigned loc, int start, unsigned end, const Yield &yield, std::vector<unsigned> &awe_yield) const;
      

      void AddUpgrade(source_type_t source_type, Aspects::aspect_t aspect1, Aspects::aspect_t aspect2 = Aspects::ASPECT_T_MAX)
      {
	 m_upgrades.push_back(Upgrade(source_type, aspect1, aspect2));
      }

      source_class_t                 m_class;
      source_type_t                  m_type;
      unsigned char                  m_level;
      unsigned char                  m_max_aspects;
      const char                    *m_name;
      Yield                          m_base_yield;
      std::vector<Aspects::aspect_t> m_aspects;
      std::vector<Upgrade>           m_upgrades;
};


#if 0
class SourceList
{
   public:
      SourceList() {}
      SourceList(const SourceList &orig)
      {
	 DeepCopy(orig);
      }
      SourceList& operator=(const SourceList &orig)
      {
	 for (unsigned i = 0; i < m_sources.size(); i++)
	    if (m_sources[i])
	       delete m_sources[i];
	 m_sources.clear();
	 DeepCopy(orig);
      }
      void DeepCopy(const SourceList &orig)
      {
	 for (unsigned i = 0; i < orig.m_sources.size(); i++)
	    if (orig.m_sources[i])
	       m_sources.push_back(orig.m_sources[i]->Clone());
	    else
	       m_sources.push_back(NULL);
      }
      ~SourceList()
      {
	 for (unsigned i = 0; i < m_sources.size(); i++)
	    if (m_sources[i])
	       delete m_sources[i];
      }
      const Source *operator[] (const unsigned i) const
      {
	 return m_sources[i];
      }
      Source *operator[] (const unsigned i)
      {
	 return m_sources[i];
      }
      size_t size(void) const
      {
	 return m_sources.size();
      }

      void clear(void)
      {
	 m_sources.clear();
      }

      void push_back(Source *elem)
      {
	 m_sources.push_back(elem);
      }

      std::vector<Source *> m_sources;
};
#endif

#endif
