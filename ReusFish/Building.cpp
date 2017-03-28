
#include "Building.hpp"
#include "SourceType.hpp"

Building::Building(void) 
{
	m_class = NON_NATURAL; 
	m_type = BUILDING; 
	m_start = 0; 
	m_end = 0;
}

Building *Building::Clone(void) const
{
	return new Building(*this);
}

void Building::SetStartEnd(unsigned start, unsigned end)
{
	m_start = start;
	m_end = end;
}

City::City(void)
{
	m_name = "City";
}

City *City::Clone(void) const
{
	return new City(*this);
}

Mill::Mill(void)
{
	m_name = "Mill";
}

void Mill::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	AddInRange(spaces, loc, yield, m_start, m_end, Yield(15,0,0,0,0,0), mask, ANIMAL, 3);
	AddInRange(spaces, loc, yield, m_start, m_end, Yield(35,0,0,0,0,0), mask, FOXGLOVE, DANDELION, DANDELION, 2);

#if 0
	if (mask & YIELD_MASK_TECH)
	{
		unsigned animal_count = 0;
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
			if ((spaces[i].m_source->Type() == BOAR) ||
					(spaces[i].m_source->Type() == RABBIT))
				animal_count += 1;

		if (animal_count == 1)
			yield.m_tech += 100;
		else if (animal_count == 2)
			yield.m_tech += 50;
	}
#endif
}

Mill *Mill::Clone(void) const
{
	return new Mill(*this);
}

Druid::Druid(void)
{
	m_name = "Druid";
}

void Druid::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	AddInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, MINERAL, 3);
}

Druid *Druid::Clone(void) const
{
	return new Druid(*this);
}

Shrine::Shrine(void)
{
	m_name = "Shrine";
}

void Shrine::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	AddInRange(spaces, loc, yield, m_start, m_end, Yield(10,0,5,0,0,0), mask, ANIMAL, 3);
}

Shrine *Shrine::Clone(void) const
{
	return new Shrine(*this);
}

Circus::Circus(void)
{
	m_name = "Circus";
}

void Circus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_TECH | YIELD_MASK_WEALTH))
	{
		bool seen_flag[BIOME_T_MAX] = {0};

		seen_flag[BIOME_NONE] = true;

		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
		{
			if ((spaces[i].m_source->Class() == ANIMAL) && !seen_flag[biome_list[i]])
			{
				seen_flag[biome_list[i]] = true;
				yield.AddFood(30, mask);
				yield.AddTech(10, mask);
				yield.AddWealth(30, mask);
			}
		}
	}
}

Circus *Circus::Clone(void) const
{
	return new Circus(*this);
}

Market::Market(void)
{
	m_name = "Market";
}

void Market::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	// Animal market
	if (mask & YIELD_MASK_WEALTH)
	{
		bool seen_flag[SOURCE_TYPE_T_MAX] = {0};
		seen_flag[BIOME_NONE] = true;

		for (unsigned i = std::max((int)loc - 2,0); (i <= loc + 2) && (i < spaces.size()); i+= 1)
		{
			if ((biome_list[i] = DESERT) && (spaces[i].m_source->Class() == ANIMAL) && !seen_flag[i])
			{
				seen_flag[i] = true;
				yield.m_wealth += 25;
			}
		}
	}
	AddInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,25,0,5,0), mask, GREY_FOX, RATTLESNAKE, RATTLESNAKE, 3);

	if (mask & YIELD_MASK_WEALTH)
	{
		unsigned topaz_count = 0;
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_source->Type() == TOPAZ)
				topaz_count += 1;
		if (topaz_count <= 3)
			yield.m_wealth += 40 * topaz_count;
	}

	// Salt Merchants
	if (mask & YIELD_MASK_WEALTH)
	{
		unsigned salt_count = 0;
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_source->Type() == SALT)
				salt_count += 1;
		if (salt_count > 0)
			yield.m_wealth += 35;
		if (salt_count > 1)
			yield.m_wealth += 25;
		if (salt_count > 2)
			yield.m_wealth += 15;
	}

	if (mask & YIELD_MASK_WEALTH)
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_yield.m_danger >= 2)
				yield.m_wealth += 10;
}

Market *Market::Clone(void) const
{
	return new Market(*this);
}

Bank::Bank(void)
{
	m_name = "Bank";
}

void Bank::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(25,0,25,0,0,0), mask, LYCHEE, TOPAZ, CHILLI_PEPPER);

	if (mask & YIELD_MASK_WEALTH)
	{
		std::vector<unsigned> wealth_yield;
		GetWealth(spaces, loc, (int)loc - 1, loc + 1, yield, wealth_yield);
		for (unsigned i = loc - 1; i <= loc + 1; i++)
			if (i != loc)
				yield.m_wealth += wealth_yield[i];
	}
}
Bank *Bank::Clone(void) const
{
	return new Bank(*this);
}

Lighthouse::Lighthouse()
{
	m_name = "Lighthouse";
}

void Lighthouse::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const 
{
	(void)loc;
	yield.Reset();

	// hard coded city extents for now...
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH | YIELD_MASK_TECH))
	{
		unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};
		for (unsigned i = 4; i < 9; i+= 1)
		{
			if ((biome_list[i] == OCEAN) && 
					(spaces[i].m_source->Class() == ANIMAL) && 
					(spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
			{
				yield.AddTech(5, mask);
				yield.AddWealth(5, mask);
				if (spaces[i].m_source->Type() == ANGLERFISH)
					yield.AddWealth(50, mask);
				if (!seen_flag[spaces[i].m_source->Type()])
				{
					seen_flag[spaces[i].m_source->Type()] = 1;
					yield.AddFood(35, mask);
				}
			}
		}
	}
}

Lighthouse* Lighthouse::Clone(void) const 
{
	return new Lighthouse(*this);
}

Harbor::Harbor(void)
{
	m_name = "Harbor";
}

void Harbor::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	yield.Reset();

	// hard coded city extents for now...
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH))
	{
		for (unsigned i = 4; i < 9; i+= 1)
		{
			if ((biome_list[i] == OCEAN) && (spaces[i].m_source->Class() == ANIMAL) && (spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
			{
				yield.AddFood(5, mask);
				yield.AddWealth(5, mask);
				if (i >= 7)
					yield.AddFood(10, mask);
			}
		}
		for (unsigned i = 0; i < spaces.size(); i+= 1)
		{
			if (spaces[i].m_source->Type() == SEABASS)
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, yield);
				for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j < (i + yield.m_range)) && (j < spaces.size()); j++)
					if ((j >= 4) && (j <= 17))
						yield.AddFood(yield.m_food * 0.5, mask);
			}
		}
	}
}
Harbor* Harbor::Clone(void) const
{
	return new Harbor(*this);
}
