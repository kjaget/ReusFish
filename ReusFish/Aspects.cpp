#include <string>
#include <iostream>

#include "Aspects.hpp"

Aspects::Aspects(void)
{
	m_aspects.resize(ASPECT_T_MAX);

	m_aspects[LESSER_LEAF] =  Aspect("L.Leaf", PLANT, Yield(0,2,0,0,0,1),  0, Yield());
	m_aspects[POTENT_LEAF] =  Aspect("P.Leaf", PLANT, Yield(0,4,0,0,0,2),  0, Yield());
	m_aspects[GREATER_LEAF] = Aspect("G.Leaf", PLANT, Yield(0,8,0,0,0,3),  0, Yield());
	m_aspects[SUBLIME_LEAF] = Aspect("S.Leaf", PLANT, Yield(0,12,0,0,0,4), 0, Yield());

	m_aspects[LESSER_HUNT] =  Aspect("L.Hunt", ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(1,0,0,0,0,0));
	m_aspects[POTENT_HUNT] =  Aspect("P.Hunt", ANIMAL, Yield(1,0,0,1,0,0), 7, Yield(2,0,0,1,0,0));
	m_aspects[GREATER_HUNT] = Aspect("G.Hunt", ANIMAL, Yield(2,0,0,2,0,0),14, Yield(3,0,0,2,0,0));
	m_aspects[SUBLIME_HUNT] = Aspect("S.Hunt", ANIMAL, Yield(3,0,0,2,0,0),30, Yield(4,0,0,2,0,0)); 

	m_aspects[LESSER_FRUIT] =  Aspect("L.Fruit", PLANT, Yield(3,0,0,0,0,0),  0, Yield());
	m_aspects[POTENT_FRUIT] =  Aspect("P.Fruit", PLANT, Yield(5,0,0,0,0,0),  7, Yield(7,0,0,0,0,0));
	m_aspects[GREATER_FRUIT] = Aspect("G.Fruit", PLANT, Yield(10,0,0,0,0,0),14, Yield(13,0,0,0,0,0));
	m_aspects[SUBLIME_FRUIT] = Aspect("S.Fruit", PLANT, Yield(15,0,0,0,0,0),30, Yield(20,0,0,0,0,0)); 

	m_aspects[LESSER_GROWTH] =  Aspect("L.Growth", PLANT, Yield(2,0,0,0,0,1), 0, Yield());
	m_aspects[POTENT_GROWTH] =  Aspect("P.Growth", PLANT, Yield(4,0,0,1,0,2), 0, Yield());
	m_aspects[GREATER_GROWTH] = Aspect("G.Growth", PLANT, Yield(8,0,0,2,0,3), 0, Yield());
	m_aspects[SUBLIME_GROWTH] = Aspect("S.Growth", PLANT, Yield(12,0,0,2,0,4),0, Yield()); 

	m_aspects[LESSER_HERD] =  Aspect("L.Herd", ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(1,0,0,0,0,0));
	m_aspects[POTENT_HERD] =  Aspect("P.Herd", ANIMAL, Yield(1,0,0,0,0,0), 7, Yield(2,0,0,0,0,0));
	m_aspects[GREATER_HERD] = Aspect("G.Herd", ANIMAL, Yield(2,0,0,0,0,0),14, Yield(3,0,0,0,0,0));
	m_aspects[SUBLIME_HERD] = Aspect("S.Herd", ANIMAL, Yield(3,0,0,0,0,0),30, Yield(4,0,0,0,0,0)); 

	m_aspects[LESSER_CRYSTAL] =  Aspect("L.Crystal", MINERAL, Yield(0,0,1,0,1,0),  0, Yield());
	m_aspects[POTENT_CRYSTAL] =  Aspect("P.Crystal", MINERAL, Yield(0,0,3,0,1,0),  7, Yield(0,0,6,0,2,0));
	m_aspects[GREATER_CRYSTAL] = Aspect("G.Crystal", MINERAL, Yield(0,0,6,0,2,0), 14, Yield(0,0,10,0,3,0));
	m_aspects[SUBLIME_CRYSTAL] = Aspect("S.Crystal", MINERAL, Yield(0,0,10,0,3,0),30, Yield(0,0,15,0,5,0)); 

	m_aspects[LESSER_EXOTIC] =  Aspect("L.Exotic", ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
	m_aspects[POTENT_EXOTIC] =  Aspect("P.Exotic", ANIMAL, Yield(0,0,1,0,0,0), 7, Yield(0,0,2,0,0,0));
	m_aspects[GREATER_EXOTIC] = Aspect("G.Exotic", ANIMAL, Yield(0,0,2,0,0,0),14, Yield(0,0,3,0,0,0));
	m_aspects[SUBLIME_EXOTIC] = Aspect("S.Exotic", ANIMAL, Yield(0,0,3,0,0,0),30, Yield(0,0,4,0,0,0)); 

	m_aspects[LESSER_NOBLE] =  Aspect("L.Noble", MINERAL, Yield(0,0,3,0,0,0), 0, Yield());
	m_aspects[POTENT_NOBLE] =  Aspect("P.Noble", MINERAL, Yield(0,0,5,0,0,0), 7, Yield(0,0,7,0,0,0));
	m_aspects[GREATER_NOBLE] = Aspect("G.Noble", MINERAL, Yield(0,0,10,0,0,0),14, Yield(0,0,13,0,0,0));
	m_aspects[SUBLIME_NOBLE] = Aspect("S.Noble", MINERAL, Yield(0,0,15,0,0,0),30, Yield(0,0,20,0,0,0)); 

	m_aspects[LESSER_SEISMIC] =  Aspect("L.Seismic", MINERAL, Yield(0,1,0,0,1,0),  0, Yield());
	m_aspects[POTENT_SEISMIC] =  Aspect("P.Seismic", MINERAL, Yield(0,3,0,0,1,0),  7, Yield(0, 6,0,0,2,0));
	m_aspects[GREATER_SEISMIC] = Aspect("G.Seismic", MINERAL, Yield(0,6,0,0,2,0), 14, Yield(0,10,0,0,3,0));
	m_aspects[SUBLIME_SEISMIC] = Aspect("S.Seismic", MINERAL, Yield(0,10,0,0,3,0),30, Yield(0,15,0,0,5,0)); 

	m_aspects[LESSER_TOXIC] =  Aspect("L.Toxic", PLANT, Yield(0,3,0,0,0,0),  0, Yield());
	m_aspects[POTENT_TOXIC] =  Aspect("P.Toxic", PLANT, Yield(0,5,0,0,0,0),  7, Yield(0, 7,0,0,0,0));
	m_aspects[GREATER_TOXIC] = Aspect("G.Toxic", PLANT, Yield(0,10,0,0,0,0),14, Yield(0,13,0,0,0,0));
	m_aspects[SUBLIME_TOXIC] = Aspect("S.Toxic", PLANT, Yield(0,15,0,0,0,0),30, Yield(0,20,0,0,0,0)); 

	m_aspects[LESSER_PREDATOR] =  Aspect("L.Predator", ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
	m_aspects[POTENT_PREDATOR] =  Aspect("P.Predator", ANIMAL, Yield(0,0,2,1,0,0), 7, Yield(0,0,2,1,0,0));
	m_aspects[GREATER_PREDATOR] = Aspect("G.Predator", ANIMAL, Yield(0,0,3,2,0,0),14, Yield(0,0,3,2,0,0));
	m_aspects[SUBLIME_PREDATOR] = Aspect("S.Predator", ANIMAL, Yield(0,0,4,2,0,0),30, Yield(0,0,4,2,0,0)); 

	m_aspects[LESSER_REACTION] =  Aspect("L.Reaction", MINERAL, Yield(0, 3,0,0,0,0), 0, Yield());
	m_aspects[POTENT_REACTION] =  Aspect("P.Reaction", MINERAL, Yield(0, 5,0,0,0,0), 7, Yield(0, 7,0,0,0,0));
	m_aspects[GREATER_REACTION] = Aspect("G.Reaction", MINERAL, Yield(0,10,0,0,0,0),14, Yield(0,13,0,0,0,0));
	m_aspects[SUBLIME_REACTION] = Aspect("S.Reaction", MINERAL, Yield(0,15,0,0,0,0),30, Yield(0,20,0,0,0,0)); 

	m_aspects[LESSER_EXOTIC] =  Aspect("L.Exotic", ANIMAL, Yield(0,0,0,0,0,0), 3, Yield(0,0,1,0,0,0));
	m_aspects[POTENT_EXOTIC] =  Aspect("P.Exotic", ANIMAL, Yield(0,0,1,0,0,0), 7, Yield(0,0,2,0,0,0));
	m_aspects[GREATER_EXOTIC] = Aspect("G.Exotic", ANIMAL, Yield(0,0,2,0,0,0),14, Yield(0,0,3,0,0,0));
	m_aspects[SUBLIME_EXOTIC] = Aspect("S.Exotic", ANIMAL, Yield(0,0,3,0,0,0),30, Yield(0,0,4,0,0,0)); 

	m_enabled.resize(ASPECT_T_MAX, false);
}

void Aspects::Enable(aspect_t base_type, unsigned level)
{
	if (level == 0)
		return;

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
