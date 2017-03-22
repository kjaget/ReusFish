#include <algorithm>

#include "Plant.hpp"

void Blueberry::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, APPLE_TREE, DANDELION, STRAWBERRY);
}

void Strawberry::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, BLUEBERRY, STRAWBERRY);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), mask, DANDELION, STRAWBERRY);
}


void AppleTree::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, ANIMAL);
}

void AppleTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder, 0,0,0,0,0), mask, ANIMAL);
}

void PearTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,m_awe_adder,0), mask, PLANT);
}

void CherryTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
		unsigned m_mineral_food_adder, unsigned m_silver_food_adder, unsigned m_gold_food_adder, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllInNaturaRange(spaces, loc, yield, Yield(m_mineral_food_adder,0,0,0,0,0), mask, MINERAL);
	AddIfAdjacent(spaces, loc, yield, Yield(m_silver_food_adder,0,0,0,0,0), mask, SILVER);
	AddIfAdjacent(spaces, loc, yield, Yield(m_gold_food_adder,0,0,0,0,0), mask, GOLD);
}

void PlumTree::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	if (NotInRange(spaces, loc, m_base_yield.m_natura_range, PLANT))
		yield.m_natura += m_natura_adder;
}

void PlumTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_food_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), mask, MINERAL);
	if ((mask & YIELD_MASK_FOOD) && NotInRange(spaces, loc, m_base_yield.m_natura_range, PLANT))
		yield.m_food += m_food_adder;
}

void OrangeTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.AddFood(3 * spaces[loc].m_yield.m_natura, mask);

	AddIfInNaturaRange(spaces, loc, yield, Yield(27,0,0,0,0,0), mask, MINERAL);
	AddIfInNaturaRange(spaces, loc, yield, Yield(27,0,0,0,0,0), mask, ANIMAL);
	AddIfInNaturaRange(spaces, loc, yield, Yield(27,0,0,0,0,0), mask, PLANT);
}

void Dandelion::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const
{
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, PLANT);
}

void Dandelion::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, PLANT);
}

void Nightshade::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const
{
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, MINERAL);
}

void Nightshade::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, PLANT);
}

void Foxglove::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.AddTech(spaces[loc].m_yield.m_natura * m_tech_multiplier, mask);
}

void Sunflower::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);

	unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};
	for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
	{
		if (!seen_flag[spaces[i].m_source->Type()] &&
			(spaces[i].m_source->Class() == PLANT) &&
			(biome_list[i] == FOREST)  )
		{
			seen_flag[spaces[i].m_source->Type()] = 1;
			yield.m_natura += 8;
		}
	}
}

void Sunflower::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & (YIELD_MASK_TECH | YIELD_MASK_AWE))
	{
		std::vector<unsigned> food_yield;
		GetFood(spaces, loc, loc - 1, loc + 1, yield, food_yield);
		unsigned food = 0;
		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
			food += food_yield[i];

		yield.AddTech(food / 5, mask);
		yield.AddAwe(food / 5, mask);
	}
}

void WitheredShrub::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, MINERAL);
}

void WitheredShrub::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
}

void Agave::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, PLANT);
}

void BarrelCactus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
}

void DatePalm::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllInNaturaRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, ANIMAL);
}

void AloeVera::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllInNaturaRange(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), mask, ANIMAL);
}

void DesertLime::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, PLANT);
}

void DesertLime::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_AWE))
	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
	{
		if ((i != loc) && 
			((spaces[i].m_source->Class() != ANIMAL) && (spaces[i].m_source->Class() != PLANT)  && (spaces[i].m_source->Class() != MINERAL) ))
		{
			yield.AddFood(m_food_adder, mask);
			yield.AddAwe(m_awe_adder, mask);
		}
	}
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, PLANT);
}

void ChilliPepper::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_tech_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, COPPER, IRON);
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, SALT, ALUMINIUM);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, TOPAZ, ONYX);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, PLATINUM, GOLD);
}

void CardonCactus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllInNaturaRange(spaces, loc, yield, Yield(25,0,0,0,0,0), mask, MINERAL);

	if (mask & YIELD_MASK_WEALTH)
	{
		std::vector<unsigned> wealth_yield;
		GetWealth(spaces,std::max<int>(0, (int)loc - m_base_yield.m_natura_range), loc + m_base_yield.m_natura_range, loc, yield, wealth_yield);

		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
			if (spaces[i].m_source->Class() == MINERAL)
				yield.m_wealth += wealth_yield[i]/2;
	}
}

void OpiumPoppy::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	AddAllAdjacent(spaces, loc, yield, Yield(0,50,50,0,-15,0), mask, PLANT);
	unsigned plant_count = 0;
	if (mask & YIELD_MASK_TECH)
	{
		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
			if (spaces[i].m_source->Class() == PLANT)
				plant_count += 1;
		if (plant_count >= 2)
			yield.m_tech += 100;
	}
}

void Elderberry::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, ANIMAL);
}

void Elderberry::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder, 0,0,0,0,0), mask, ANIMAL);
}

void Peppermint::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, MINERAL);
}

void Tomato::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_TECH)
	{
		std::vector<unsigned> food_yield;
		GetFood(spaces, loc, yield, food_yield);
		yield.m_tech += int(m_tech_multiplier * food_yield[loc]);
	}
}

void Pineapple::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, MINERAL);
}

void Marshmallow::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), mask, ANIMAL);
}
void Papaya::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, int m_natura_limit, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	if (spaces[loc].m_yield.m_natura >= m_natura_limit)
	{
		yield.AddFood(m_food_adder, mask);
		yield.AddAwe(m_awe_adder, mask);
	}
}

void WhiteWillow::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddAllInNaturaRange(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, PLANT);
}

void WhiteWillow::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllInNaturaRange(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, PLANT);
}

void Superior_WhiteWillow::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
{
	WhiteWillow::GetNatura(spaces, loc, yield, 4);
	AddAllInNaturaRange(spaces, loc, yield, Yield(0,0,0,0,0,4), YIELD_MASK_NATURA, WHITE_WILLOW);
}

void Coffea::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i += 1)
		if ((i != loc) && (spaces[i].m_source->Class() == PLANT))
			spaces[i].m_yield.m_natura += m_natura_adder;
}

void Coffea::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_food_adder, unsigned m_tech_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_TECH)
	{
		std::vector<unsigned> food_yield;
		GetFood(spaces, loc, loc - 1, loc + 1, yield, food_yield);
		for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i += 1)
			if ((i != loc) && (spaces[i].m_source->Class() == PLANT))
			{
				unsigned food = food_yield[i] / 2;
				yield.m_tech += food * m_tech_multiplier;
			}
	}

	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,m_tech_adder,0,0,0,0), mask, PLANT);
}

void Hemp::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, YIELD_MASK_NATURA);

	if (mask & YIELD_MASK_TECH)
	{
		std::vector<unsigned> awe_yield;
		GetAwe(spaces, loc, std::max<int>(0, (int)loc - m_base_yield.m_natura_range), loc + m_base_yield.m_natura_range, yield, awe_yield);
		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
			if (i != loc)
				yield.m_tech = awe_yield[i] * m_tech_multiplier;
	}

	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), mask, IRON, PHOSPHORUS);
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,m_awe_adder,0), mask, SALT, ALUMINIUM);
}

void CacaoTree::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,25), YIELD_MASK_NATURA, MINERAL);
}

void CacaoTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,25,0), mask, PLANT);
	AddIfAdjacent(spaces, loc, yield, Yield(50,0,0,0,0,0), mask, ANIMAL);

	if (mask & YIELD_MASK_FOOD)
	{
		std::vector<unsigned> awe_yield;
		GetAwe(spaces, loc, std::max<int>(0, (int)loc - m_base_yield.m_natura_range), loc + m_base_yield.m_natura_range, yield, awe_yield);
		unsigned awe = 0;
		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
			awe += awe_yield[i];
		if (awe >= 150)
			yield.m_food += 80;
	}
}

void RubberTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{ 
	yield = m_base_yield;
	const unsigned natura = spaces[loc].m_yield.m_natura;
	GetAspects(natura, yield, mask);

	if (natura >= 30)
	{
		yield.AddTech(80, mask);
		yield.AddAwe(30, mask);
	}
	else if (natura >= 24)
	{
		yield.AddTech(40, mask);
		yield.AddAwe(20, mask);
	}
	else if (natura >= 18)
	{
		yield.AddTech(20, mask);
		yield.AddAwe(10, mask);
	}
	AddAllAdjacent(spaces, loc, yield, Yield(0,55,0,0,10,0), mask, OIL, ALUMINIUM, URANIUM);
}

void Kumquat::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,m_awe_adder,0), mask, PLANT);
}

void Ginger::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), YIELD_MASK_NATURA, ANIMAL);
}

void Ginger::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), mask, ANIMAL);
}

void Dragonfruit::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, double m_awe_multiplier, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	yield.AddFood(m_food_multiplier * (spaces[loc].m_yield.m_natura / 2), mask);
	yield.AddAwe(m_awe_multiplier * (spaces[loc].m_yield.m_natura / 2), mask);
}

void Kiwifruit::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, int m_natura_adder) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
		if ((i != loc) && (spaces[i].m_source->Class() == PLANT))
			spaces[i].m_yield.m_natura += m_natura_adder;
}

void Kiwifruit::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_tech_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder, 0,0,0,0,0), mask, ANIMAL);
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_TECH))
	{
	for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
		if ((i != loc) && (spaces[i].m_source->Class() == PLANT))
		{
			spaces[i].m_yield.AddFood(m_food_adder, mask);
			spaces[i].m_yield.AddTech(m_tech_adder, mask);
		}
	}
}

void Lychee::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_animal_food_adder, unsigned mask) const 
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), mask, ANIMAL);

	// KCJ - const yield adder
	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (spaces[i].m_source->Class() == ANIMAL)
			for (unsigned j = std::max<int>(0, (int)loc - yield.m_natura_range); (j <= loc + yield.m_natura_range) && (j < spaces.size()); j+= 1)
				spaces[i].m_yield.m_food += m_animal_food_adder;
	}
}

void Cinnamomum::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
		double m_wealth_multiplier, unsigned m_plant_food_adder, unsigned m_plant_adjacent_food_adder, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (mask & YIELD_MASK_WEALTH)
	{
		std::vector<unsigned>wealth_yield;
		GetWealth(spaces, loc, std::max<int>(0, (int)loc - m_base_yield.m_natura_range), loc + m_base_yield.m_natura_range, yield, wealth_yield);

		for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
			if ((i != loc) && (spaces[i].m_source->Class() == MINERAL))
				yield.m_wealth += int(m_wealth_multiplier * wealth_yield[i]);
	}

	AddAllInNaturaRange(spaces, loc, yield, Yield(m_plant_food_adder, 0,0,0,0,0), mask, PLANT);
	AddIfAdjacent(spaces, loc, yield, Yield(m_plant_adjacent_food_adder, 0,0,0,0,0), mask, PLANT);
}

void TeaPlant::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, int m_natura_limit) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);
	if (spaces[loc].m_yield.m_natura >= m_natura_limit)
		yield.m_natura_range += 1;
}

void TeaPlant::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
		unsigned m_awe_adder, unsigned m_tech_adder, int m_natura_limit, unsigned mask) const
{
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);

	if (spaces[loc].m_yield.m_natura >= m_natura_limit)
	{
		yield.m_natura_range += 1;
		yield.AddTech(m_tech_adder, mask);
	}

	AddAllInNaturaRange(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), mask, TEA_PLANT);
}

void Ginkgo::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const 
{ 
	yield = m_base_yield;
	GetAspects(0, yield, YIELD_MASK_NATURA);

	if ((loc > 0) && (spaces[loc-1].m_source->Type() == LANGUR_MONKEY) && 
			((loc+1) < spaces.size()) &&(spaces[loc+1].m_source->Type() == LANGUR_MONKEY))
		yield.m_natura += 15;
}

void Ginkgo::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{ 
	yield = m_base_yield;
	GetAspects(spaces[loc].m_yield.m_natura, yield, mask);
	if ((mask & YIELD_MASK_FOOD) && 
			((loc > 0) && (spaces[loc-1].m_source->Type() == LANGUR_MONKEY) && 
			((loc+1) < spaces.size()) &&(spaces[loc+1].m_source->Type() == LANGUR_MONKEY)))
		yield.m_food += 100;
	AddAllInNaturaRange(spaces, loc, yield, Yield(20,20,0,0,0,0), mask, PLANT);
}

