
#include "Building.hpp"
#include "SourceType.hpp"

Building::Building(void) :
	m_needs_class_count(false),
	m_completion_class_count(std::array<unsigned char, SOURCE_TYPE_T_MAX>{0})
{
	m_class = NON_NATURAL;
	m_type = BUILDING;
	m_start = 0;
	m_end = 0;
}

Building::Building(const Yield &completion_requirements) :
	m_completion_requirements(completion_requirements),
	m_needs_class_count(false),
	m_completion_class_count(std::array<unsigned char, SOURCE_TYPE_T_MAX>{0})
{
	m_class = NON_NATURAL;
	m_type = BUILDING;
	m_start = 0;
	m_end = 0;
}

Building::Building(const Building &other) :
	Source(other),
	m_start(other.m_start),
	m_end(other.m_end),
	m_completion_requirements(other.m_completion_requirements),
	m_needs_class_count(other.m_needs_class_count),
	m_completion_class_count(other.m_completion_class_count)
{
}

Building *Building::Clone(void) const
{
	return new Building(*this);
}

void Building::SetStartEnd(unsigned char start, unsigned char end)
{
	m_start = start;
	m_end = end;
}

const Yield &Building::GetCompletionRequirements(void) const
{
	return m_completion_requirements;
}

bool Building::CheckClassCompletion(const std::array<unsigned char, SOURCE_CLASS_T_MAX> &class_count) const
{
	for (int i = 0; i < SOURCE_CLASS_T_MAX; i++)
		if (class_count[i] < m_completion_class_count[i])
			return false;
	return true;
}

void Building::SetClassCompletionCount(source_class_t source_class, unsigned char count)
{
	if (source_class < SOURCE_CLASS_T_MAX)
	{
		m_needs_class_count = true;
		m_completion_class_count[source_class] = count;
	}
}

bool Building::NeedsClassCount(void) const
{
	return m_needs_class_count;
}

City::City(void)
{
	m_name = "City";
}

City *City::Clone(void) const
{
	return new City(*this);
}

Mill::Mill(void) :
	Building(Yield(100,40,0,0,0,0))
{
	m_name = "Mill";
}

void Mill::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(15,0,0,0,0,0), mask, ANIMAL, 3);
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(15,0,0,0,0,0), mask, PLANT, 3);

	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(35,0,0,0,0,0), mask, DEER, WISENT, 2);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(35,0,0,0,0,0), mask, FOXGLOVE, DANDELION, 2);

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

Druid::Druid(void) :
	Building(Yield(0,30,0,0,0,0))
{
	m_name = "Druid";
}

void Druid::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	// Herbalist
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, PLANT, 3);
	// Cook
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), mask, TOMATO, SALT, MARSH_MALLOW, 1);
	// Hermit
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, MINERAL, 3);
	// Inventor
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), mask, COPPER, IRON, IRON, 1);
}

Druid *Druid::Clone(void) const
{
	return new Druid(*this);
}

Shrine::Shrine(void) :
	Building(Yield(15,0,15,0,0,0))
{
	m_name = "Shrine";
}

void Shrine::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(10,0,5,0,0,0), mask, ANIMAL, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(5,0,10,0,0,0), mask, ANIMAL, 3);
}

Shrine *Shrine::Clone(void) const
{
	return new Shrine(*this);
}

Circus::Circus(void) :
	Building(Yield(200, 0, 200, 0, 0, 0))
{
	m_name = "Circus";
	SetClassCompletionCount(ANIMAL, 5);
}

void Circus::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(5,0,25,0,5,0), mask, DEER, GOAT, BOAR, 3);
#if 1
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
				yield.AddWealth(30, mask);
				yield.AddAwe(10, mask);
			}
		}
	}
#endif
}
bool Circus::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
	yield.Reset();
	for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
		it->Reset();
	if (m_post_processed.size() != spaces.size())
	{
		m_post_processed.resize(spaces.size());
		m_total_danger.resize(spaces.size());
		for (size_t i = 0; i < spaces.size(); i++)
		{
			m_post_processed[i] = false;
			m_total_danger[i] = 0;
		}
	}
			
	bool rc = false;
	//
	for (unsigned i = m_start; i <= m_end; i++)
	{
		
		int delta = (int)spaces[i].m_yield.m_danger - m_total_danger[i];
		if (delta)
		{
			yield.m_food   += 2*delta;
			yield.m_danger += delta;
			m_total_danger[i] = spaces[i].m_yield.m_danger;
			rc = true;
		}

		if (!m_post_processed[i] && spaces[i].m_source)
		{
			if (spaces[i].m_yield.m_danger >= 2)
			{
				global_yield[i].m_danger += 1;
				m_post_processed[i] = true;
				rc = true;
			}
		}
	}

	return rc;
}

Circus *Circus::Clone(void) const
{
	return new Circus(*this);
}

Market::Market(void) :
	Building(Yield(0,0,120,0,0,0))
{
	m_name = "Market";
}

void Market::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	// Pelt Traders
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,15,0,0,0), mask, ANIMAL, 3);

#if 0
	// Animal market
	if (mask & YIELD_MASK_WEALTH)
	{
		std::array<bool,SOURCE_TYPE_T_MAX> seen_flag = {0};
		seen_flag[BIOME_NONE] = true;

		for (unsigned i = std::max((int)loc - 2,0); (i <= loc + 2) && (i < spaces.size()); i+= 1)
		{
			if ((i != loc) && (biome_list[i] = DESERT) && spaces[i].m_source && (spaces[i].m_source->Class() == ANIMAL) && !seen_flag[i])
			{
				seen_flag[i] = true;
				yield.m_wealth += 25;
			}
		}
	}
	// Exotic Pet
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,25,0,5,0), mask, GREY_FOX, RATTLESNAKE, RATTLESNAKE, 3);

#endif
	if (mask & YIELD_MASK_WEALTH)
	{
#if 0
		// Salt Merchants
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
		//Exotic Topaz Trinkets
		{
			Yield temp_yield;
			AddAllInRange(spaces, loc, temp_yield, m_start, m_end, Yield(0,0,40,0,0,0), mask, TOPAZ);
			if (temp_yield.m_wealth <= 120)
				yield += temp_yield;
		}
#endif

		// Prized Preys - KCJ redo as post processing?
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
			if (spaces[i].m_yield.m_danger >= 2)
				yield.m_wealth += 10;
	}

} 

Market *Market::Clone(void) const
{
	return new Market(*this);
}

Bank::Bank(void) :
	Building(Yield(75,75,300,0,0,0)),
	m_post_processed(false)
{
	m_name = "Bank";
}

void Bank::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)mask;

#if 0
	// Protectionism
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,50,0,0,0), mask, GOLD, MUSK_DEER, COYOTE, 3);
	for (unsigned i = m_start; (mask & YIELD_MASK_WEALTH) && (i <= m_end) && (i < spaces.size()); i+= 1)
	{
		if (spaces[i].m_source)
		{
			const source_class_t c = spaces[i].m_source->Class();
			if ((c == ANIMAL) || (c == PLANT) || (c == MINERAL))
				yield.m_wealth += 5;
		}

	}

#endif
#if 1
	// Development Aid
	yield.AddWealth(60,mask);
	for (unsigned i = m_start; (mask & (YIELD_MASK_WEALTH | YIELD_MASK_FOOD | YIELD_MASK_TECH | YIELD_MASK_AWE) && (i <= m_end)) && (i < spaces.size()); i+= 1)
	{
		if (spaces[i].m_source)
		{
			const source_type_t t = spaces[i].m_source->Type();
			if (t == DESERT_LIME)
			{
				yield.AddFood(45, mask);
				yield.AddWealth(-15, mask);
			}
			else if (t == SILVER)
			{
				yield.AddTech(45, mask);
				yield.AddWealth(-15, mask);
			}
			else if (t == COYOTE)
			{
				yield.AddWealth(75-15, mask);
			}
			else if (t == PLATINUM)
			{
				yield.AddWealth(-15, mask);
				yield.AddAwe(15, mask);
			}
		}
	}
#endif
	// Local investment - see also PostProcess
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(25,0,25,0,0,0), mask, LYCHEE, TOPAZ, CHILLI_PEPPER);
}

bool Bank::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
#if 0
	yield.Reset();
	for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
		it->Reset();
	if (!m_post_processed)
	{
		// Local investment - see also Yield
		for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i++)
			if (i != loc)
				yield.m_wealth += spaces[i].m_yield.m_wealth;
		m_post_processed = true;
		return true; // indicate changed values
	}
#endif
	return false; // nothing changed during this call
}
Bank *Bank::Clone(void) const
{
	return new Bank(*this);
}

Lighthouse::Lighthouse(void) :
	Building(Yield(300, 50, 200, 0, 0,0))
{
	m_name = "Lighthouse";
}

void Lighthouse::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const 
{
	yield.Reset();

	// Clear Blue - verify limit is broken?
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(35,0,0,0,5,0), mask, TUNA, PARROTFISH);

	Yield temp_yield;
	temp_yield.m_range = 2;
	AddAllInRange(spaces, loc, yield, Yield(0,0,0,0,20,0), mask, CLOWNFISH,2);
	yield.Add(temp_yield, mask);

#if 0
	// hard coded city extents for now...
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH | YIELD_MASK_TECH))
	{
		unsigned marlin_seabass_count = 0;
		for (unsigned i = m_start; i < m_end; i+= 1)
		{
			if ((biome_list[i] == OCEAN) && 
				spaces[i].m_source &&
				(spaces[i].m_source->Class() == ANIMAL))
			{
				const source_type_t t = spaces[i].m_source->Type();
				// Deep Sea
				if (t != SOURCE_TYPE_NONE)
				{
					yield.AddTech(5, mask);
					yield.AddWealth(5, mask);
				}
				if (t == ANGLERFISH)
					yield.AddWealth(50, mask);
				else if ((t == MARLIN) || (t == SEABASS))
					marlin_seabass_count += 1;
			}
		}
		// Fishing Sport
		if (marlin_seabass_count <= 2)
		{
			yield.AddFood(50, mask);
			yield.AddWealth(100, mask);
		}
		else if (marlin_seabass_count <= 4)
		{
			yield.AddFood(100, mask);
			yield.AddWealth(50, mask);
		}
	}
#endif
}

Lighthouse* Lighthouse::Clone(void) const 
{
	return new Lighthouse(*this);
}

Harbor::Harbor(void) :
	Building(Yield(90, 0, 50, 0, 0, 0))
{
	m_name = "Harbor";
}

void Harbor::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	yield.Reset();

	// Fishing Trade
	for (unsigned i = m_start; i < m_end; i+= 1)
	{
		if (spaces[i].m_source)
		{
			const source_class_t c = spaces[i].m_source->Class();
			if ((c == ANIMAL) || (c == PLANT) || (c == MINERAL))
				yield.AddWealth(5, mask);
		}
	}
}

bool Harbor::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
	(void)loc;
	yield.Reset();
	if (!m_post_processed)
	{
		for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
			it->Reset();
		for (size_t i = 0; i < spaces.size(); i++)
			if (spaces[i].m_source && 
				(spaces[i].m_source->Type() == SEABASS))
			{
				const unsigned range = spaces[i].m_yield.m_range;
				for (unsigned j = std::max<int>(0, (int)i - range); (j < (i + range)) && (j < spaces.size()); j++)
					global_yield[j].m_food += spaces[i].m_source->Level() + 1;
				Yield this_yield;
				std::vector<Space> s(spaces);
				spaces[i].m_source->GetYield(s, i, this_yield, YIELD_MASK_FOOD);
				this_yield.m_food += spaces[i].m_source->Level() + 1;
				yield.m_food += this_yield.m_food / 2;
			}
		m_post_processed = true;
		return true; // indicate changed values
	}
	return false; // nothing changed during this call
}

Harbor* Harbor::Clone(void) const
{
	return new Harbor(*this);
}

University::University(void)
{
	m_name = "University";
}

void University::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(10,5,0,0,0,0), mask, PLANT, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, ANIMAL);
}
University* University::Clone(void) const
{
	return new University(*this);
}

Geologist::Geologist(void)
{
	m_name = "Geologist";
}

void Geologist::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,10,5,0,0,0), mask, MINERAL, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,35,0,0,0), mask, ONYX, TOPAZ, 2);
}
Geologist* Geologist::Clone(void) const
{
	return new Geologist(*this);
}

Alchemist::Alchemist(void)
{
	m_name = "Alchemist";
}

void Alchemist::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, MINERAL, 3);
	for (unsigned i = std::min<int>((int)loc - 2, 0); (i <= (loc + 2)) && (i < spaces.size()); i+= 1)
		if ((i != loc) && (spaces[i].m_source->Class() == MINERAL))
		{
			spaces[i].m_yield.m_wealth = 3 * spaces[i].m_yield.m_tech;
			spaces[i].m_yield.m_tech = 0;
		}
}
Alchemist* Alchemist::Clone(void) const
{
	return new Alchemist(*this);
}

Apothecary::Apothecary(void) :
	Building(Yield(200, 200, 50, 0, 0, 0))
{
	m_name = "Apothecary";
}

void Apothecary::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_TECH | YIELD_MASK_AWE))
	{
		for (unsigned i = std::max<int>((int)loc - 2, 0); (i <= (loc + 2)) && (i < spaces.size()); i+= 1)
		{
			if ((i != loc) && (spaces[i].m_source->Class() == PLANT))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, loc, this_yield, YIELD_MASK_FOOD | YIELD_MASK_TECH);
				this_yield.m_food *= 1.5;
				this_yield.m_tech *= 1.5;
				this_yield.m_awe   = 15;
				yield += this_yield;
			}
		}
	}
}
Apothecary* Apothecary::Clone(void) const
{
	return new Apothecary(*this);
}
Workshop::Workshop(void) :
	Building(Yield(25, 70, 70, 0, 0, 0))
{
	m_name = "Workshop";
}

void Workshop::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,5,10,0,0,0), mask, MINERAL, 3);
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,20,10,0,0,0), mask, MINERAL, 3);
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,10,5,0,0,0), mask, MINERAL, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,25,0,0,0), mask, IRON, COPPER, 2);
}
Workshop* Workshop::Clone(void) const
{
	return new Workshop(*this);
}

CustomsHouse::CustomsHouse(void) :
	Building(Yield(40, 0, 100, 0, 0, 0))
{
	m_name = "CustomsHouse";
}

void CustomsHouse::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,15,0,0,0), mask, MINERAL, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,30,0,0,0), mask, COYOTE, RATTLESNAKE, GREY_FOX, 2);
}
CustomsHouse* CustomsHouse::Clone(void) const
{
	return new CustomsHouse(*this);
}
Temple::Temple(void) :
	Building(Yield(70, 0, 70, 0, 0, 0))
{
	m_name = "Temple";
}

void Temple::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(10,0,5,0,0,0), mask, ANIMAL, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(30,0,10,0,0,0), mask, BOAR, RABBIT, GOAT, MUSK_DEER, JAVELINA, 3);
#if 0
	yield.m_range = 2;
	AddAllInRange(spaces, loc, yield, Yield(20,0,20,0,0,0), mask, ANIMAL, 2);
	yield.m_range = 0;
#endif
}
Temple* Temple::Clone(void) const
{
	return new Temple(*this);
}

Cathedral::Cathedral(void) :
	Building(Yield(120, 0, 120, 0, 25, 0))
{
	m_name = "Cathedral";
}

void Cathedral::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(5,10,0,0,0,0), mask, ANIMAL, 3);
	// relics stuff
}
Cathedral* Cathedral::Clone(void) const
{
	return new Cathedral(*this);
}

BlastFurnace::BlastFurnace(void) :
	Building(Yield(50, 175, 175, 0, 0, 0))
{
	m_name = "BlastFurnace";
	SetClassCompletionCount(MINERAL, 5);
}

void BlastFurnace::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,50,50,0,0,0), mask, IGUANA, BUFFALO,KOMODO_DRAGON, RATTLESNAKE, COYOTE, GILA_MONSTER, 4);
}
BlastFurnace* BlastFurnace::Clone(void) const
{
	return new BlastFurnace(*this);
}

Hamlet::Hamlet(void) :
	Building(Yield(300,60,60,0,0,0))
{
	m_name = "Hamlet";
}

void Hamlet::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,0,0,5,0), mask, ANIMAL, 4);
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(75,25,0,0,0,0), mask, WOLF, WISENT, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(45,0,30,0,0,0), mask, TUNA, MARLIN, 3);
}
Hamlet* Hamlet::Clone(void) const
{
	return new Hamlet(*this);
}

Barracks::Barracks(void) :
	Building(Yield(0,0,0,0,0,0))
{
	m_name = "Barracks";
}

void Barracks::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(5,10,0,0,0,0), mask, PLANT, 3);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(30,0,0,0,-10,0), mask, COPPER, IRON, WHITE_WILLOW, SALT, 3);
}

Barracks* Barracks::Clone(void) const
{
	return new Barracks(*this);
}

InventorsTower::InventorsTower(void)
{
	m_name = "InventorsTower";
}

void InventorsTower::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,15,0,-10,0), mask, MINERAL);
}
InventorsTower* InventorsTower::Clone(void) const
{
	return new InventorsTower(*this);
}

Observatory::Observatory(void) :
	Building(Yield(50,300,75,0,0,0)),
	m_post_processed(false)
{
	m_name = "Observatory";
}

void Observatory::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	// Licensed Breakthrough
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,45,0,0,0), mask, WHITE_WILLOW, NIGHTSHADE, BARREL_CACTUS, 4);

	// Advanced Equipment
	bool zinc_seen = false;
	bool aluminium_seen = false;
	bool iron_seen = false;
	for (unsigned i = m_start; (mask & YIELD_MASK_TECH) && (i < m_end); i++)
	{
		if (spaces[i].m_source)
		{
			source_type_t t = spaces[i].m_source->Type();
			if (!zinc_seen && (t == ZINC))
			{
				yield.m_tech += 30;
				zinc_seen = true;
			}
			if (!aluminium_seen && (t == ALUMINIUM))
			{
				yield.m_tech += 30;
				aluminium_seen = true;
			}
			if (!iron_seen && (t == IRON))
			{
				yield.m_tech += 30;
				iron_seen = true;
			}
		}
	}
	AddIfAdjacent(spaces, loc, yield, Yield(0,30,0,0,0,0), ZINC, ALUMINIUM, IRON);
	// Active Researchers
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), mask, COFFEA, TEA_PLANT);
}

bool Observatory::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
{
	yield.Reset();
	for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
		it->Reset();
	if (!m_post_processed)
	{
		for (unsigned i = std::max<int>(0, (int)loc - 2); (i <= loc + 2) && (i < spaces.size()); i++)
			if ((i != loc) && spaces[i].m_source && (spaces[i].m_source->Type() != BUILDING))
				yield.m_tech += spaces[i].m_yield.m_tech/2;
		m_post_processed = true;
		return true; // indicate changed values
	}
	return false; // nothing changed during this call
}

Observatory* Observatory::Clone(void) const
{
	return new Observatory(*this);
}

Opera::Opera(void) :
	Building(Yield(850,0,850,0,0,0))
{
	m_name = "Opera";
}

void Opera::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();

	// Diverse show
#if 1
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
				yield.AddWealth(30, mask);
				yield.AddAwe(10, mask);
			}
		}
	}
#endif

#if 0
	// Fables
	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH))
	{
		unsigned animal_count = 0;
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
		{
			if (spaces[i].m_source)
			{
				source_type_t t = spaces[i].m_source->Type();
				if ((t == BEAVER) || (t == ARMADILLO) || (t == FOX) || (t == GREY_FOX) || (t == LANGUR_MONKEY) || (t == RABBIT) || (t == GOAT))
					animal_count += 1;
			}
		}
		if (animal_count > 0)
		{
			yield.AddFood(75, mask);
			yield.AddWealth(75, mask);
		}
		if (animal_count > 1)
		{
			yield.AddFood(50, mask);
			yield.AddWealth(50, mask);
		}
		if (animal_count > 2)
		{
			yield.AddFood(25, mask);
			yield.AddWealth(25, mask);
		}
	}
#endif
	// Genesis story
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,75,0,0,0), mask, BLUEBERRY, APPLE_TREE, STRAWBERRY, AGAVE, DATE_PALM, 4);
	
#if 0
	// Heroics of the Titan Slayer
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(75,0,0,0,0,0), mask, ANIMAL, 4);
	yield.AddAwe(-20, mask);

	// Inspired Piece
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(100,0,100,0,0,0), mask, CARDON_CACTUS, ORANGE_TREE, MOOSE, BEAR, BIG_HORN, PANDA, BOBCAT, 2);
	// Peculiar Adventures of Maarten
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,0,0,60,0), mask, MARTEN, MARTEN, MARTEN, 1);
#endif

	// Epic of Bas
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,150,0,0,0), mask, WOLF, COYOTE, SNOW_LEOPARD, BEAR, 1);
}

Opera* Opera::Clone(void) const
{
	return new Opera(*this);
}

Tradepost::Tradepost(void) :
	Building(Yield(0, 0, 30, 0, 0, 0))
{
	m_name = "Tradepost";
}

void Tradepost::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,15,0,0,0), mask, ANIMAL, 3);
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(30,0,10,0,0,0), mask, BOAR, RABBIT, GOAT, MUSK_DEER, JAVELINA, 3);
#if 0
	yield.m_range = 2;
	AddAllInRange(spaces, loc, yield, Yield(20,0,20,0,0,0), mask, ANIMAL, 2);
	yield.m_range = 0;
#endif
}
Tradepost* Tradepost::Clone(void) const
{
	return new Tradepost(*this);
}

Multinational::Multinational(void) :
	Building(Yield(200, 1250, 200, 0, 0, 0))
{
	m_name = "Multinational";
}

void Multinational::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();
	// Development Aid
	yield.AddWealth(60,mask);
	for (unsigned i = m_start; (mask & (YIELD_MASK_WEALTH | YIELD_MASK_FOOD | YIELD_MASK_TECH | YIELD_MASK_AWE) && (i <= m_end)) && (i < spaces.size()); i+= 1)
	{
		if (spaces[i].m_source)
		{
			const source_type_t t = spaces[i].m_source->Type();
			if (t == DESERT_LIME)
			{
				yield.AddFood(45, mask);
				yield.AddWealth(-15, mask);
			}
			else if (t == SILVER)
			{
				yield.AddTech(45, mask);
				yield.AddWealth(-15, mask);
			}
			else if (t == COYOTE)
			{
				yield.AddWealth(75-15, mask);
			}
			else if (t == PLATINUM)
			{
				yield.AddWealth(-15, mask);
				yield.AddAwe(15, mask);
			}
		}
	}
	unsigned pyramid_count = 0;
	yield.AddAwe(-20, mask);
	for (size_t i = 0; (mask & YIELD_MASK_WEALTH) && (i < spaces.size()); i+= 1)
		if ((i != loc) && (spaces[i].m_source->Class() == MINERAL))
		{
			spaces[i].m_yield.AddWealth(-10, mask);
			if (++pyramid_count < 8)
				yield.m_wealth += 50;

		}
}
Multinational* Multinational::Clone(void) const
{
	return new Multinational(*this);
}

Castle::Castle(void) :
	Building(Yield(1250, 100, 300, 0, 0, 0))
{
	m_name = "Castle";
}

void Castle::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();

	// Rappresentante
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(45,0,30,0,0,0), mask, TUNA, MARLIN, 2);

	Yield temp_yield;
	AddAllInRange(spaces, loc, temp_yield, m_start, m_end, Yield(1,0,0,0,0,0), mask, STOAT, BEAR, WOLF, 3);
	if (temp_yield.m_food > 0)
	{
		yield.AddFood(100,mask);
		yield.AddWealth(50, mask);
	}
	if (temp_yield.m_food > 1)
	{
		yield.AddFood(75,mask);
		yield.AddWealth(25, mask);
	}
	if (temp_yield.m_food > 2)
	{
		yield.AddFood(50,mask);
		yield.AddWealth(15, mask);
	}

	// Prince of Orange
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(150,0,50,0,0,0), mask, ORANGE_TREE, 1);

}
Castle* Castle::Clone(void) const
{
	return new Castle(*this);
}

Hospital::Hospital(void) :
	Building(Yield(750, 750, 200, 0, 150, 0))
{
	m_name = "Hospital";
	SetClassCompletionCount(PLANT,3);
}

void Hospital::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();

	Yield temp_yield;
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,0,0,0,0), mask, STOAT, BEAR, WOLF, 3);

	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_TECH))
	{
		unsigned plant_count = 0;
		std::array<bool, SOURCE_TYPE_T_MAX> sources_seen{false};
		for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
		{
			if (spaces[i].m_source)
			{
				source_type_t t = spaces[i].m_source->Type();
				if (((biome_list[i] == FOREST) || (biome_list[i]== SWAMP)) &&
					(spaces[i].m_source->Class() == PLANT) && !sources_seen[t])
				{
					sources_seen[t] = true;
					plant_count += 1;
				}
				if ((t == PLUM_TREE) || (t == CHERRY_TREE) || (t == HEMP) || (t == COFFEA))
				{
					spaces[i].m_yield.AddNatura(10, mask);
					spaces[i].m_yield.AddAwe(5, mask);
				}
			}
		}
		yield.AddFood(30 * plant_count, mask);
		yield.AddTech(30 * plant_count, mask);
	}

	// Medical Equipment
	//AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(75,75,0,0,0,0), mask, SALT, ALUMINIUM, ZINC, URANIUM, FLUORITE, 3);
	//AddIfAdjacent(spaces, loc, yield, Yield(75,75,0,0,0,0), SALT, ALUMINIUM, ZINC, URANIUM, FLUORITE);

}
Hospital* Hospital::Clone(void) const
{
	return new Hospital(*this);
}

CanalTown::CanalTown(void) :
	Building(Yield(750, 750, 200, 0, 150, 0))
{
	m_name = "CanalTown";
}

void CanalTown::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();

	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(45,0,30,0,0,0), mask, TUNA, MARLIN, 3);

	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(50,0,50,0,0,0), mask, FOX, GREY_FOX, WOLF, SNOW_LEOPARD, LANGUR_MONKEY, BOBCAT, BEAR, 6);

}
CanalTown* CanalTown::Clone(void) const
{
	return new CanalTown(*this);
}

Plantation::Plantation(void)
{
	m_name = "Plantation";
}

void Plantation::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	yield.Reset();


	Yield temp_yield;
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(15,0,0,0,0,0), mask, ANIMAL, 3);

	if (mask & (YIELD_MASK_FOOD | YIELD_MASK_AWE))
	{
		Yield temp_yield;
		AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(1,0,0,0,0,0), mask, APPLE_TREE, 1);
		AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(1,0,0,0,0,0), mask, STRAWBERRY, 1);
		AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(1,0,0,0,0,0), mask, PEAR_TREE, 1);
		if (temp_yield.m_food >= 2)
		{
			yield.m_food += 20;
			yield.m_awe += 10;
		}
		if (temp_yield.m_food >= 3)
		{
			yield.m_food += 40;
			yield.m_awe += 20;
		}
	}
}
Plantation* Plantation::Clone(void) const
{
	return new Plantation(*this);
}
NaturePark::NaturePark(void)
{
	m_name = "NaturePark";
}

void NaturePark::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
	(void)loc;
	yield.AddWealth(90, mask);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), mask, KUMQUAT, DRAGONFRUIT);
	AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,0,0,5,0), mask, KUMQUAT, DRAGONFRUIT, LYCHEE);
}

NaturePark *NaturePark::Clone(void) const
{
	return new NaturePark(*this);
}
