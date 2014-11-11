#include <string>
#include <iostream>

#include "aspects.hpp"

Aspects::Aspects()
{
   m_aspects.resize(ASPECT_T_MAX);
   
   m_aspects[LESSER_LEAF] =  Aspect("Lesser Leaf",  PLANT, Yield(0,2,0,0,0,1),  0, Yield());
   m_aspects[POTENT_LEAF] =  Aspect("Potent Leaf",  PLANT, Yield(0,4,0,0,0,2),  0, Yield());
   m_aspects[GREATER_LEAF] = Aspect("Greater Leaf", PLANT, Yield(0,8,0,0,0,3),  0, Yield());
   m_aspects[SUBLIME_LEAF] = Aspect("Sublime Leaf", PLANT, Yield(0,12,0,0,0,4), 0, Yield());

   m_aspects[LESSER_HUNT] =  Aspect("Lesser Hunt",  ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(1,0,0,0,0,0));
   m_aspects[POTENT_HUNT] =  Aspect("Potent Hunt",  ANIMAL, Yield(1,0,0,1,0,0), 7, Yield(2,0,0,1,0,0));
   m_aspects[GREATER_HUNT] = Aspect("Greater Hunt", ANIMAL, Yield(2,0,0,2,0,0),14, Yield(3,0,0,2,0,0));
   m_aspects[SUBLIME_HUNT] = Aspect("Sublime Hunt", ANIMAL, Yield(3,0,0,2,0,0),30, Yield(4,0,0,2,0,0)); 

   m_aspects[LESSER_FRUIT] =  Aspect("Lesser Fruit",  PLANT, Yield(3,0,0,0,0,0),  0, Yield());
   m_aspects[POTENT_FRUIT] =  Aspect("Potent Fruit",  PLANT, Yield(5,0,0,0,0,0),  7, Yield(7,0,0,0,0,0));
   m_aspects[GREATER_FRUIT] = Aspect("Greater Fruit", PLANT, Yield(10,0,0,0,0,0),14, Yield(13,0,0,0,0,0));
   m_aspects[SUBLIME_FRUIT] = Aspect("Sublime Fruit", PLANT, Yield(15,0,0,0,0,0),30, Yield(20,0,0,0,0,0)); 

   m_aspects[LESSER_GROWTH] =  Aspect("Lesser Growth",  PLANT, Yield(2,0,0,0,0,1), 0, Yield());
   m_aspects[POTENT_GROWTH] =  Aspect("Potent Growth",  PLANT, Yield(4,0,0,1,0,2), 0, Yield());
   m_aspects[GREATER_GROWTH] = Aspect("Greater Growth", PLANT, Yield(8,0,0,2,0,3), 0, Yield());
   m_aspects[SUBLIME_GROWTH] = Aspect("Sublime Growth", PLANT, Yield(12,0,0,2,0,4),0, Yield()); 

   m_aspects[LESSER_HERD] =  Aspect("Lesser Herd",  ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(1,0,0,0,0,0));
   m_aspects[POTENT_HERD] =  Aspect("Potent Herd",  ANIMAL, Yield(1,0,0,0,0,0), 7, Yield(2,0,0,0,0,0));
   m_aspects[GREATER_HERD] = Aspect("Greater Herd", ANIMAL, Yield(2,0,0,0,0,0),14, Yield(3,0,0,0,0,0));
   m_aspects[SUBLIME_HERD] = Aspect("Sublime Herd", ANIMAL, Yield(3,0,0,0,0,0),30, Yield(4,0,0,0,0,0)); 

   m_aspects[LESSER_CRYSTAL] =  Aspect("Lesser Crystal",  MINERAL, Yield(0,0,1,0,1,0),  0, Yield());
   m_aspects[POTENT_CRYSTAL] =  Aspect("Potent Crystal",  MINERAL, Yield(0,0,3,0,1,0),  7, Yield(0,0,6,0,2,0));
   m_aspects[GREATER_CRYSTAL] = Aspect("Greater Crystal", MINERAL, Yield(0,0,6,0,2,0), 14, Yield(0,0,10,0,3,0));
   m_aspects[SUBLIME_CRYSTAL] = Aspect("Sublime Crystal", MINERAL, Yield(0,0,10,0,3,0),30, Yield(0,0,15,0,5,0)); 

   m_aspects[LESSER_EXOTIC] =  Aspect("Lesser Exotic",  ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
   m_aspects[POTENT_EXOTIC] =  Aspect("Potent Exotic",  ANIMAL, Yield(0,0,1,0,0,0), 7, Yield(0,0,2,0,0,0));
   m_aspects[GREATER_EXOTIC] = Aspect("Greater Exotic", ANIMAL, Yield(0,0,2,0,0,0),14, Yield(0,0,3,0,0,0));
   m_aspects[SUBLIME_EXOTIC] = Aspect("Sublime Exotic", ANIMAL, Yield(0,0,3,0,0,0),30, Yield(0,0,4,0,0,0)); 

   m_aspects[LESSER_NOBLE] =  Aspect("Lesser Noble",  MINERAL, Yield(0,0,3,0,0,0), 0, Yield());
   m_aspects[POTENT_NOBLE] =  Aspect("Potent Noble",  MINERAL, Yield(0,0,5,0,0,0), 7, Yield(0,0,7,0,0,0));
   m_aspects[GREATER_NOBLE] = Aspect("Greater Noble", MINERAL, Yield(0,0,10,0,0,0),14, Yield(0,0,13,0,0,0));
   m_aspects[SUBLIME_NOBLE] = Aspect("Sublime Noble", MINERAL, Yield(0,0,15,0,0,0),30, Yield(0,0,20,0,0,0)); 

   m_aspects[LESSER_SEISMIC] =  Aspect("Lesser Seismic",  MINERAL, Yield(0,1,0,0,1,0),  0, Yield());
   m_aspects[POTENT_SEISMIC] =  Aspect("Potent Seismic",  MINERAL, Yield(0,3,0,0,1,0),  7, Yield(0, 6,0,0,2,0));
   m_aspects[GREATER_SEISMIC] = Aspect("Greater Seismic", MINERAL, Yield(0,6,0,0,2,0), 14, Yield(0,10,0,0,3,0));
   m_aspects[SUBLIME_SEISMIC] = Aspect("Sublime Seismic", MINERAL, Yield(0,10,0,0,3,0),30, Yield(0,15,0,0,5,0)); 

   m_aspects[LESSER_TOXIC] =  Aspect("Lesser Toxic",  PLANT, Yield(0,3,0,0,0,0),  0, Yield());
   m_aspects[POTENT_TOXIC] =  Aspect("Potent Toxic",  PLANT, Yield(0,5,0,0,0,0),  7, Yield(0, 7,0,0,0,0));
   m_aspects[GREATER_TOXIC] = Aspect("Greater Toxic", PLANT, Yield(0,10,0,0,0,0),14, Yield(0,13,0,0,0,0));
   m_aspects[SUBLIME_TOXIC] = Aspect("Sublime Toxic", PLANT, Yield(0,15,0,0,0,0),30, Yield(0,20,0,0,0,0)); 

   m_aspects[LESSER_PREDATOR] =  Aspect("Lesser Predator",  ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
   m_aspects[POTENT_PREDATOR] =  Aspect("Potent Predator",  ANIMAL, Yield(0,0,2,1,0,0), 7, Yield(0,0,2,1,0,0));
   m_aspects[GREATER_PREDATOR] = Aspect("Greater Predator", ANIMAL, Yield(0,0,3,2,0,0),14, Yield(0,0,3,2,0,0));
   m_aspects[SUBLIME_PREDATOR] = Aspect("Sublime Predator", ANIMAL, Yield(0,0,4,2,0,0),30, Yield(0,0,4,2,0,0)); 

   m_aspects[LESSER_REACTION] =  Aspect("Lesser Reaction",  MINERAL, Yield(0, 3,0,0,0,0), 0, Yield());
   m_aspects[POTENT_REACTION] =  Aspect("Potent Reaction",  MINERAL, Yield(0, 5,0,0,0,0), 7, Yield(0, 7,0,0,0,0));
   m_aspects[GREATER_REACTION] = Aspect("Greater Reaction", MINERAL, Yield(0,10,0,0,0,0),14, Yield(0,13,0,0,0,0));
   m_aspects[SUBLIME_REACTION] = Aspect("Sublime Reaction", MINERAL, Yield(0,15,0,0,0,0),30, Yield(0,20,0,0,0,0)); 

   m_aspects[LESSER_EXOTIC] =  Aspect("Lesser Exotic",  ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
   m_aspects[POTENT_EXOTIC] =  Aspect("Potent Exotic",  ANIMAL, Yield(0,0,1,0,0,0), 7, Yield(0,0,2,0,0,0));
   m_aspects[GREATER_EXOTIC] = Aspect("Greater Exotic", ANIMAL, Yield(0,0,2,0,0,0),14, Yield(0,0,3,0,0,0));
   m_aspects[SUBLIME_EXOTIC] = Aspect("Sublime Exotic", ANIMAL, Yield(0,0,3,0,0,0),30, Yield(0,0,4,0,0,0)); 

   m_enabled.resize(ASPECT_T_MAX, false);
}

void Aspects::Enable(aspect_t base_type, unsigned level)
{
   if (level == 0) return;

   if (base_type & 3U)
      std::cerr << "Aspects::Enable : base_type " << base_type << " not multiple of 4 " << std::endl;
   if (level > 3)
   {
      std::cerr << "Aspects::Enable : level " << level << " > 3 " << std::endl;
      level = 3;
   }
   unsigned i = (unsigned)base_type & ~3U;
   for (unsigned j = 0; j <= level; j++)
      m_enabled[(aspect_t)(i+j)] = true;
}

bool Aspects::IsEnabled(aspect_t type) const
{
   return m_enabled[type];
}

bool Aspects::IsValid(aspect_t type, source_class_t source_class) const
{
   if (!m_enabled[type])
      return false;
   if (source_class == m_aspects[type].m_resource)
      return true;
   return false;
}

void Aspects::Bonus(aspect_t type, unsigned natura, Yield &yield) const
{
   const Aspect &this_aspect = m_aspects[type];

   if ((this_aspect.m_natura_threshold > 0) && (natura >= this_aspect.m_natura_threshold))
      yield = this_aspect.m_natura_bonus;
   else
      yield = this_aspect.m_bonus;
}

bool Aspects::CanUpgrade(aspect_t requirement, aspect_t source_aspect) const
{
   if ((source_aspect >= requirement) && (source_aspect <= (requirement | 3)))
      return true;
   return false;
}

void Aspects::Print(aspect_t type) const
{
   m_aspects[type].Print();
}

Aspects aspects;
