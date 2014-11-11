#ifndef SOURCE_INC__
#define SOURCE_INC__

#include <algorithm>
#include <iostream>
#include <string>

#include "Aspects.hpp"
#include "biome.hpp"
#include "SourceClass.hpp"
#include "SourceType.hpp"
#include "SourceTypeList.hpp"

class Space;
class SourceList;

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
	 m_name = "None";
	 m_class = SOURCE_CLASS_NONE;
	 m_type = SOURCE_TYPE_NONE;
	 m_max_aspects = 0;
	 m_level = 0;
      };
      
      bool operator==(const Source &rhs) const
      {
	 if ((m_name != rhs.m_name)               ||
	     (m_class != rhs.m_class)             ||
	     (m_type != rhs.m_type)               ||
	     (m_level != rhs.m_level)             ||
	     !(m_base_yield == rhs.m_base_yield)  ||
	     (m_max_aspects != rhs.m_max_aspects) ||
	     (m_aspects.size() != rhs.m_aspects.size() ||
	     !(m_upgrades == rhs.m_upgrades)))
	    return false;

	 std::vector<Aspects::aspect_t> m_sorted_aspects(m_aspects);
	 std::vector<Aspects::aspect_t> rhs_sorted_aspects(rhs.m_aspects);

	 std::sort(m_sorted_aspects.begin(), m_sorted_aspects.end());
	 std::sort(rhs_sorted_aspects.begin(), rhs_sorted_aspects.end());

	 if (m_sorted_aspects != rhs_sorted_aspects)
	    return false;

	 return true;
      }

      source_class_t Class(void) const {return m_class;}
      source_type_t  Type(void)  const {return m_type; }
      unsigned Hash(void) const
      {
	 unsigned hash = m_class + (m_type << 2) + (m_level << 4);
	 hash += hash << 7;
	 hash += hash << 14;
	 hash += hash << 24;
	 for (unsigned i = 0; i < m_aspects.size(); i++)
	 {
	    hash += m_aspects[i];
	    hash += m_aspects[i] << 5;
	    hash += m_aspects[i] << 10;
	    hash += m_aspects[i] << 15;
	    hash += m_aspects[i] << 20;
	    hash += m_aspects[i] << 25;
	 }
	 return hash;
      }

      virtual void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) { yield.Reset(); }
      virtual void GetNatura(const std::vector<Space> &spaces, unsigned loc, Yield &yield) { yield.Reset(); }
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
	    return true;
	 }
	 return false;
      }
      void RemoveNewestAspect(void)
      {
	 if (m_aspects.size())
	    m_aspects.pop_back();
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

      virtual Source* Clone() const {return new Source(*this);}
      
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
      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3, bool once);

      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, true);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type2, true);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type1, type1, true);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type2, false);
      }
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddInRange(spaces, loc, yield, yield_adder, type1, type1, type1, false);
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = 1;
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, true);
	 yield.m_range = saved_range;
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddIfAdjacent(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddIfAdjacent(spaces, loc, yield, yield_adder, type1, type1, type1);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = 1;
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, false);
	 yield.m_range = saved_range;
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddAllAdjacent(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddAllAdjacent(spaces, loc, yield, yield_adder, type1, type1, type1);
      }

      // Same as above, but classes rather than types
      void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class, bool once);
      void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class)
      {
	 AddInRange(spaces, loc, yield, yield_adder, source_class, false);
      }
      void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class)
      {
	 AddInRange(spaces, loc, yield, yield_adder, source_class, true);
      }

      void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_class_t source_class)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = 1;
	 AddInRange(spaces, loc, yield, yield_adder, source_class, true);
	 yield.m_range = saved_range;
      }
      void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_class_t source_class)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = 1;
	 AddInRange(spaces, loc, yield, yield_adder, source_class, false);
	 yield.m_range = saved_range;
      }

      // 
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range, source_class_t source_class);
      bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_class_t source_class)
      {
	 return NotInRange(spaces, loc, 1, source_class);
      }
      bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
	              source_type_t type1, source_type_t type2, source_type_t type3); 
      bool NotAdjacent(const std::vector<Space> &spaces,
	              source_type_t type1, source_type_t type2, source_type_t type3); 
      {
	 return NotInRange(spaces, loc, 1, type1, type2, type3);
      }

      void AddUpgrade(source_type_t source_type, Aspects::aspect_t aspect1, Aspects::aspect_t aspect2 = Aspects::ASPECT_T_MAX)
      {
	 m_upgrades.push_back(Upgrade(source_type, aspect1, aspect2));
      }

      std::string                    m_name;
      source_class_t                 m_class;
      source_type_t                  m_type;
      unsigned                       m_level;
      Yield                          m_base_yield;
      unsigned                       m_max_aspects;
      std::vector<Aspects::aspect_t> m_aspects;
      std::vector<Upgrade>           m_upgrades;
};

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
	       m_sources.push_back(new Source());
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
