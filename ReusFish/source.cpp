#include "Source.hpp"
#include "Space.hpp"

void Source::GetUpgrades (biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   for (unsigned i = 0; i < m_upgrades.size(); i++)
   {
      unsigned required_count;
      unsigned count = 0;
      if (m_level > 2)
	 required_count = 2;
      else if (m_upgrades[i].m_aspect1 == m_upgrades[i].m_aspect2)
	 required_count = 2;
      else
	 required_count = 1;
      for (unsigned j = 0; j < m_aspects.size(); j++)
      {
	 if (aspects.CanUpgrade(m_upgrades[i].m_aspect1, m_aspects[j]) ||
	       ((m_upgrades[i].m_aspect2 != Aspects::ASPECT_T_MAX) &&
		(aspects.CanUpgrade(m_upgrades[i].m_aspect2, m_aspects[j])) ) )
	 {
	    count += 1;
	 }
      }
      if (count >= required_count)
      {
	 SourceFactory<source_type_t, unsigned>::Builder builder;
	 if (source_type_list.Get(m_upgrades[i].m_new_source, m_level, builder))
	    upgrades.push_back(builder());
      }
   }
}

void Source::AddInRange(const std::vector<Space> &spaces, 
                        unsigned loc, 
                        Yield &yield,
                        const Yield &yield_adder,
                        source_type_t type1,
                        source_type_t type2,
                        source_type_t type3,
			bool once)
{
   unsigned range = m_base_yield.m_range;

   for (unsigned i = std::max<int>(0, (int)loc - range); i <= loc + range && (i < spaces.size()); i+= 1)
   {
      const source_type_t type = spaces[i].m_source->Type();
      if ((i != loc) && ((type == type1) || (type == type2) || (type == type3)) )
      {
	 yield += yield_adder;
	 if (once)
	    break;
      }
   }
}

void Source::AddInRange(const std::vector<Space> &spaces, 
                        unsigned loc, 
                        Yield &yield,
                        const Yield &yield_adder,
                        source_class_t source_class,
			bool once)
{
   unsigned range = m_base_yield.m_range;

   for (unsigned i = std::max<int>(0, (int)loc - range); i <= loc + range && (i < spaces.size()); i+= 1)
   {
      if ((i != loc) && ((spaces[i].m_source->Class() == source_class) || 
	                 ((source_class == ANIMAL) && (spaces[i].m_source->Class() == FISH))))
      {
	 yield += yield_adder;
	 if (once)
	    break;
      }
   }
}

bool Source::NotInRange(const std::vector<Space> &spaces, 
                        unsigned loc, 
                        unsigned range,
                        source_class_t source_class)
{
   for (unsigned i = std::max<int>(0, (int)loc - range); i <= loc + range && (i < spaces.size()); i+= 1)
      if ((i != loc) && ((spaces[i].m_source->Class() == source_class) || 
	                 ((source_class == ANIMAL) && (spaces[i].m_source->Class() == FISH))))
	 return false;
   return true;
}

bool Source::NotInRange(const std::vector<Space> &spaces, 
                        unsigned loc, 
                        unsigned range,
                        source_type_t type1,
                        source_type_t type2,
                        source_type_t type3)
                        
{
   for (unsigned i = std::max<int>(0, (int)loc - range); i <= loc + range && (i < spaces.size()); i+= 1)
   {
      if ((i != loc) && 
	  ((spaces[i].m_source->Type() == type1) || (spaces[i].m_source->Type() == type2) || (spaces[i].m_source->Type() == type3)) )
	 return false;
   }
   return true;
}
