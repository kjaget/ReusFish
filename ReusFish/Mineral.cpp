#include "Mineral.hpp"


void Agate::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), ANIMAL);
}

void Quartz::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_wealth_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), STONE);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), QUARTZ);
}

void Stone::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), PLANT);
}

void Marble::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,m_wealth_adder,0,0,0), MINERAL);
}

void Topaz::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,m_awe_adder,0), PLANT);
}

void Salt::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,m_wealth_adder,0,0,0), MINERAL);
	AddAllAdjacent(spaces, loc, yield, Yield(0,-m_tech_adder,-m_wealth_adder,0,0,0), SALT);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), ANIMAL);
}

void Onyx::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_wealth_multiplier, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	yield.m_wealth += int(spaces[loc].m_yield.m_natura * m_wealth_multiplier);
}

void Copper::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_animal_tech_adder, unsigned m_mountain_tech_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_animal_tech_adder,0,0,0,0), ANIMAL);
	if (biome_list[loc] == MOUNTAIN)
		yield.m_tech += m_mountain_tech_adder;
}

void Phosphorus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), PLANT);
}

void Iron::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	if (mask & YIELD_MASK_TECH)
	{
		std::vector<unsigned> danger;
		GetDanger(spaces, loc, yield, danger);
		yield.m_tech += m_tech_multiplier * danger[loc];
	}
}

void Gold::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_rarity, unsigned m_rarity_subtract, unsigned m_wealth_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	unsigned gold_count = 0;
	for (unsigned i = 0; i < spaces.size(); i++)
		if (spaces[i].m_source && (spaces[i].m_source->Type() == GOLD))
			gold_count += 1;

	int rarity_adder = m_rarity;
	rarity_adder -= (int)(m_rarity_subtract * gold_count);
	if (rarity_adder > 0)
		yield.m_wealth += rarity_adder;
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), MINERAL);
}

void Silver::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_wealth_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	if (mask & YIELD_MASK_WEALTH)
	{
		for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_source &&
				((spaces[i].m_source->Type() == TOPAZ) ||
				 (spaces[i].m_source->Type() == ONYX) ||
				 (spaces[i].m_source->Type() == GOLD) ||
				 (spaces[i].m_source->Type() == PLATINUM) ))
			{
				Yield wealth_yield;
				spaces[i].m_source->GetYield(spaces, loc, wealth_yield, YIELD_MASK_WEALTH);
				yield.m_wealth += int(m_tech_wealth_multiplier * wealth_yield.m_wealth);
			}
	}

	if (mask & YIELD_MASK_TECH)
	{
		for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_source &&
				((spaces[i].m_source->Type() == COPPER) ||
				 (spaces[i].m_source->Type() == IRON) ||
				 (spaces[i].m_source->Type() == ALUMINIUM) ))
			{
				Yield tech_yield;
				spaces[i].m_source->GetYield(spaces, loc, tech_yield, YIELD_MASK_TECH);
				yield.m_tech += int(m_tech_wealth_multiplier * tech_yield.m_tech);
			}
	}
}

void Platinum::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,m_awe_adder,0), COYOTE, GREY_FOX);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), ANIMAL);
}

void Aluminium::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_mineral_tech_adder, unsigned m_plant_tech_adder, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	unsigned mine_count = 0;
	for (unsigned i = 0; (i < spaces.size()) && (mine_count < 5); i++)
		if (spaces[i].m_source && 
				((spaces[i].m_source->Type() == IRON) ||
				 (spaces[i].m_source->Type() == COPPER)) )
			mine_count += 1;

	yield.m_tech += m_mineral_tech_adder * mine_count;
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_plant_tech_adder,0,0,0,0), PLANT);
}

void Zinc::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_range, double m_tech_multiplier, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	if (mask == YIELD_MASK_ALL)
	{
		std::vector<unsigned> tech;
		GetTech(spaces, loc, std::max<int>(0, (int)loc - m_range), loc + m_range, yield, tech);
		for (unsigned i = std::max<int>(0, (int)loc - m_range); (i <= loc + m_range) && (i < spaces.size()); i+= 1)
			if ((spaces[i].m_source->Type() == COPPER)   ||
	 			(spaces[i].m_source->Type() == IRON)     ||
				(spaces[i].m_source->Type() == ALUMINIUM) )
				spaces[i].m_yield.m_tech += int (m_tech_multiplier * tech[i]);
	}
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), COPPER);
}

void Ruby::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source && (spaces[i].m_source->Class() == PLANT))
			spaces[i].m_yield.m_natura += 15;
}

void Ruby::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	unsigned ruby_count = 0;
	for (unsigned i = 0; i < spaces.size(); i++)
		if (spaces[i].m_source && (spaces[i].m_source->Type() == RUBY))
			ruby_count += 1;

	int rarity_adder = 150;
	rarity_adder -= (int)(25 * ruby_count);
	if (rarity_adder > 0)
		yield.m_wealth += rarity_adder;

	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
	{
		if (spaces[i].m_source)
		{
			if (spaces[i].m_source->Class() != MINERAL)
				yield.m_wealth += 30;
			if (mask == YIELD_MASK_ALL)
			{
				if (spaces[i].m_source->Class() == ANIMAL)
					spaces[i].m_yield.m_awe += 5;
				if (spaces[i].m_source->Class() == PLANT)
				{
					spaces[i].m_yield.m_food += 30;
					spaces[i].m_yield.m_tech += 30;
				}
			}
		}
	}
}

void Diamond::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	unsigned plant_count = 0;
	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source && (spaces[i].m_source->Class() == PLANT))
			plant_count += 1;

	if (plant_count == 2)
		yield.m_wealth += 100;

	unsigned mineral_count = 0;
	for (unsigned i = std::max<int>(0, (int)loc - 2); (i <= loc + 2) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source && (spaces[i].m_source->Class() == MINERAL))
			mineral_count += 1;

	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source &&(spaces[i].m_source->Class() == ANIMAL))
		{
			Yield animal_yield;
			spaces[i].m_source->GetYield(spaces, loc, animal_yield, YIELD_MASK_WEALTH);
			yield.m_wealth += int(2.5 * animal_yield.m_wealth);
		}
}

void Coal::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	if (mask == YIELD_MASK_ALL)
	{
		for (unsigned i = 0; i < spaces.size(); i++)
			if (spaces[i].m_source && 
					((spaces[i].m_source->Type() == COPPER) ||
					 (spaces[i].m_source->Type() == IRON)) )
			{
				spaces[i].m_yield.m_tech   += 10;
				spaces[i].m_yield.m_wealth += 10;
			}
	}
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,50,0,0,0), COPPER, IRON);

	if (mask & (YIELD_MASK_TECH | YIELD_MASK_WEALTH | YIELD_MASK_AWE))
	{
		std::vector<unsigned> awe_yield;
		GetAwe(spaces, loc, std::max<int>(0, (int)loc - 2), loc + 2, yield, awe_yield);
		unsigned awe = 0;
		for (unsigned i = std::max<int>(0, (int)loc - 2); (i <= loc + 2) && (i < spaces.size()); i+= 1)
			if (i != loc)
				awe += awe_yield[i];
		yield.m_tech   += 2 * awe;
		yield.m_wealth += 2 * awe;
		yield.m_awe    -=     awe;
	}
}

void Oil::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	yield.m_wealth += 100;

	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source && (spaces[i].m_source->Class() == PLANT))
		{
			Yield plant_yield;
			spaces[i].m_source->GetYield(spaces, loc, plant_yield, YIELD_MASK_FOOD);
			yield.m_wealth += plant_yield.m_food;
		}

	unsigned plant_count = 0;
	unsigned animal_count = 0;
	unsigned mineral_count = 0;
	for (unsigned i = 0; i < spaces.size(); i++)
		if (spaces[i].m_source)
		{
			if (spaces[i].m_source->Class() == PLANT)
				plant_count += 1;
			else if (spaces[i].m_source->Class() == ANIMAL)
				animal_count += 1;
			else if (spaces[i].m_source->Class() == MINERAL)
				mineral_count += 1;
		}
	yield.m_tech += 5 * plant_count;
	yield.m_wealth += 5 * mineral_count;
	yield.m_food += 5 * animal_count;
}

void Uranium::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	unsigned uranium_count = 0;
	for (unsigned i = 0; i < spaces.size(); i++)
		if (spaces[i].m_source && (spaces[i].m_source->Type() == URANIUM))
		{
			uranium_count += 1;
			break;
		}
	if (!uranium_count)
		yield.m_tech += 250;

	for (unsigned i = std::max<int>(0, (int)loc - 2); (i <= loc + 2) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source &&
			((spaces[i].m_source->Class() == PLANT) ||
			 (spaces[i].m_source->Class() == ANIMAL) ||
			 (spaces[i].m_source->Class() == MINERAL)))
		{
			Yield tech_yield;
			spaces[i].m_source->GetYield(spaces, loc, tech_yield, YIELD_MASK_TECH);
			yield.m_tech += tech_yield.m_tech / 2;
		}
}

void Fluorite::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield);

	yield.m_range = 2;
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), ANIMAL);
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), PLANT);
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), MINERAL);
	yield.m_range = 0;
}

