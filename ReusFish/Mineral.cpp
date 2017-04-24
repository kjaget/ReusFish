#include "Mineral.hpp"


void Agate::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), mask, ANIMAL);
}

void Quartz::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_wealth_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, STONE);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), mask, QUARTZ);
}

void Stone::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, PLANT);
}

void Marble::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,m_wealth_adder,0,0,0), mask, MINERAL);
}

void Topaz::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,m_awe_adder,0), mask, PLANT);
}

void Salt::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,m_wealth_adder,0,0,0), mask, MINERAL);
	AddAllAdjacent(spaces, loc, yield, Yield(0,-m_tech_adder,-m_wealth_adder,0,0,0), mask, SALT);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), mask, ANIMAL);
}

void Onyx::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_wealth_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.AddWealth(spaces[loc].m_yield.m_natura * m_wealth_multiplier, mask);
}

void Copper::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_animal_tech_adder, unsigned m_mountain_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(0,m_animal_tech_adder,0,0,0,0), mask, ANIMAL);
	if (biome_list[loc] == MOUNTAIN)
		yield.AddTech(m_mountain_tech_adder, mask);
}

void Phosphorus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), mask, PLANT);
}

void Iron::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_TECH)
	{
		std::vector<unsigned> danger;
		GetDanger(spaces, loc, yield, danger);
		yield.m_tech += m_tech_multiplier * danger[loc];
	}
}

void Gold::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_rarity, unsigned m_rarity_subtract, unsigned m_wealth_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_WEALTH)
	{
		unsigned gold_count = 0;
		for (unsigned i = 0; i < spaces.size(); i++)
			if (spaces[i].m_source && (spaces[i].m_source->Type() == GOLD))
				gold_count += 1;

		int rarity_adder = m_rarity;
		rarity_adder -= (int)(m_rarity_subtract * gold_count);
		if (rarity_adder > 0)
			yield.m_wealth += rarity_adder;
		AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), mask, MINERAL);
	}
}

void Silver::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_wealth_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	// KCJ - postprocessing?
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
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,m_awe_adder,0), mask, COYOTE, GREY_FOX);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), mask, ANIMAL);
}

void Aluminium::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_mineral_tech_adder, unsigned m_plant_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_TECH)
	{
		unsigned mine_count = 0;
		for (unsigned i = 0; (i < spaces.size()) && (mine_count < 5); i++)
			if (spaces[i].m_source &&
				((spaces[i].m_source->Type() == IRON) ||
				 (spaces[i].m_source->Type() == COPPER)) )
				mine_count += 1;

		yield.m_tech += m_mineral_tech_adder * mine_count;
		AddAllAdjacent(spaces, loc, yield, Yield(0,m_plant_tech_adder,0,0,0,0), mask, PLANT);
	}
}

void Zinc::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_range, double m_tech_multiplier, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask == YIELD_MASK_ALL)
	{
		std::vector<unsigned> tech;
		GetTech(spaces, loc, std::max<int>(0, (int)loc - m_range), loc + m_range, yield, tech);
		for (unsigned i = std::max<int>(0, (int)loc - m_range); (i <= loc + m_range) && (i < spaces.size()); i+= 1)
			if ((spaces[i].m_source->Type() == COPPER)   ||
	 			(spaces[i].m_source->Type() == IRON)     ||
				(spaces[i].m_source->Type() == ALUMINIUM) )
				spaces[i].m_yield.AddTech(m_tech_multiplier * tech[i], mask);
	}
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), mask, COPPER);
}

void Ruby::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, YIELD_MASK_NATURA);

	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
		if (spaces[i].m_source && (spaces[i].m_source->Class() == PLANT))
			spaces[i].m_yield.m_natura += 15;
}

void Ruby::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_WEALTH)
	{
		unsigned ruby_count = 0;
		for (unsigned i = 0; i < spaces.size(); i++)
			if (spaces[i].m_source && (spaces[i].m_source->Type() == RUBY))
				ruby_count += 1;

		int rarity_adder = 150;
		rarity_adder -= (int)(25 * ruby_count);
		if (rarity_adder > 0)
			yield.m_wealth += rarity_adder;
	}

	// KCJ - postprocess?
	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
	{
		if (spaces[i].m_source)
		{
			if (spaces[i].m_source->Class() != MINERAL)
				yield.AddWealth(30, mask);
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
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_WEALTH)
	{
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
}

void Coal::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	// KCJ - do +10 to copper/iron as postprocessing

	AddAllAdjacent(spaces, loc, yield, Yield(0,0,50,0,0,0), mask, COPPER, IRON);

	if (mask & (YIELD_MASK_TECH | YIELD_MASK_WEALTH | YIELD_MASK_AWE))
	{
		std::vector<unsigned> awe_yield;
		const unsigned start = std::max<int>(0, (int)loc - 2);
		const unsigned end   = loc + 2;
		GetAwe(spaces, loc, start, end, yield, awe_yield);
		unsigned awe = 0;
		for (unsigned i = start; (i <= end) && (i < spaces.size()); i+= 1)
			if (i != loc)
				awe += awe_yield[i];
		yield.AddTech(2 * awe, mask);
		yield.AddWealth(2 * awe, mask);
		yield.AddWealth(-awe, mask);
	}
}

bool Coal::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
	(void)loc;
	yield.Reset();
	for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
		it->Reset();

	if (m_post_processed)
		return false;

	for (size_t i = 0; i < spaces.size(); ++i)
	{
		source_type_t type = spaces[i].m_source->Type();
		if ((type == COPPER) || (type == IRON))
		{
			global_yield[i].m_wealth += 10;
			global_yield[i].m_tech   += 10;
		}
	}

	m_post_processed = true;
	return true;
}

void Oil::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	// KCJ - Only if active?
	yield.AddWealth(100, mask);

	if (mask & YIELD_MASK_TECH)
	{
		for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
			if ((i != loc) && spaces[i].m_source && (spaces[i].m_source->Class() == PLANT))
			{
				Yield plant_yield;
				spaces[i].m_source->GetYield(spaces, loc, plant_yield, YIELD_MASK_FOOD);
				yield.m_tech += plant_yield.m_food;
			}
	}

	if (mask & (YIELD_MASK_TECH | YIELD_MASK_WEALTH | YIELD_MASK_FOOD))
	{
		unsigned plant_count = 0;
		unsigned animal_count = 0;
		unsigned mineral_count = 0;
		for (unsigned i = 0; i < spaces.size(); i++)
			if (spaces[i].m_source)
			{
				source_class_t cl = spaces[i].m_source->Class();
				if (cl == PLANT)
					plant_count += 1;
				else if (cl == ANIMAL)
					animal_count += 1;
				else if (cl == MINERAL)
					mineral_count += 1;
			}
		yield.AddTech(5 * plant_count, mask);
		yield.AddWealth(5 * mineral_count, mask);
		yield.AddFood(5 * animal_count, mask);
	}
}

void Uranium::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	// KCJ - check for activation?
	//
	if (mask & YIELD_MASK_TECH)
	{
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
			if ((i != loc) && spaces[i].m_source &&
					((spaces[i].m_source->Class() == PLANT) ||
					 (spaces[i].m_source->Class() == ANIMAL) ||
					 (spaces[i].m_source->Class() == MINERAL)))
			{
				Yield tech_yield;
				spaces[i].m_source->GetYield(spaces, loc, tech_yield, YIELD_MASK_TECH);
				yield.m_tech += tech_yield.m_tech / 2;
			}
	}
}

void Fluorite::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.m_range = 2;
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), mask, ANIMAL);
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), mask, PLANT);
	AddIfInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), mask, MINERAL);
	yield.m_range = 0;
}

bool Fluorite::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
	unsigned save_post_processed = m_post_processed; 

	yield.Reset();
	for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
		it->Reset();

	if (!(M_POST_PROCESSED_TECH & m_post_processed) && (spaces[loc].m_yield.m_tech >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_TECH;
	}
	if (!(M_POST_PROCESSED_FOOD & m_post_processed) && (spaces[loc].m_yield.m_food >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_FOOD;
	}
	if (!(M_POST_PROCESSED_WEALTH & m_post_processed) && (spaces[loc].m_yield.m_wealth >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_WEALTH;
	}
	if (!(M_POST_PROCESSED_DANGER & m_post_processed) && (spaces[loc].m_yield.m_danger >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_DANGER;
	}
	if (!(M_POST_PROCESSED_AWE & m_post_processed) && (spaces[loc].m_yield.m_awe >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_AWE;
	}
	if (!(M_POST_PROCESSED_NATURA & m_post_processed) && (spaces[loc].m_yield.m_natura >= 10))
	{
		yield.m_tech += 25;
		m_post_processed |= M_POST_PROCESSED_NATURA;
	}
	if (save_post_processed == m_post_processed)
		return false;
	return true;

}

void NaturalGas::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.m_range = 3;
	AddIfInRange(spaces, loc, yield, Yield(0,-100,-100,0,0,0), mask, NATURAL_GAS);
	AddAllInRange(spaces, loc, yield, Yield(0,0,50,0,0,0), mask, ANIMAL);
	AddAllInRange(spaces, loc, yield, Yield(0,50,0,0,0,0), mask, PLANT);

	yield.m_range = 0;
}
