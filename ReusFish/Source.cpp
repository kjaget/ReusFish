#include "Source.hpp"
#include "SourceContainer.hpp"
#include "Space.hpp"

static SourceTypeList source_type_list;

Source::Source(void)
{
   	Create();
}

Source::Source(const Source &original) :
	m_class(original.m_class),
	m_type(original.m_type),
	m_level(original.m_level),
	m_max_aspects(original.m_max_aspects),
	m_upgrade_count(original.m_upgrade_count),
	m_name(original.m_name),
	m_base_yield(original.m_base_yield),
	m_aspects(original.m_aspects),
	m_upgrades(original.m_upgrades)
{
}

Source::Source(const std::vector<Aspects::aspect_t> &aspects)
{
	Create();
	m_aspects = aspects;
}

void Source::Create(void) 
{
	m_name  = "None";
	m_class = SOURCE_CLASS_NONE;
	m_type  = SOURCE_TYPE_NONE;
	m_max_aspects = 0;
	m_upgrade_count = 0;
	m_level = 0;
}

Source::~Source()
{
}

bool Source::operator==(const Source &rhs) const
{
	if (!strcmp(m_name,rhs.m_name) && (m_aspects == rhs.m_aspects) && (m_upgrade_count == rhs.m_upgrade_count))
		return true;
	return false;
}

source_class_t Source::Class(void) const
{
	return m_class;
}

source_type_t Source::Type(void) const
{
	return m_type;
}

unsigned char Source::Level(void) const
{
	return m_level;
}

unsigned char Source::UpgradeCount(void) const
{
	return m_upgrade_count;
}

size_t Source::Hash(void) const
{
	const size_t this_hash = (size_t)0x1234567812345678ULL + m_class + 
		((m_type + 1) << 2) + 
		((m_level + 1) << 4) + 
		((m_upgrade_count  + 1) << 6);
	size_t hash = this_hash;

	hash += this_hash << 7;
	hash += this_hash << 14;
	hash += this_hash << 24;
	for (size_t i = 0; i < m_aspects.size(); i++)
	{
		size_t aspect = m_aspects[i] + 1;
		hash += aspect;
		hash += aspect << 5;
		hash += aspect << 9;
		hash += aspect << 15;
		hash += aspect << 19;
		hash += aspect << 25;
	}
	return hash;
}

void Source::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const 
{
	(void)spaces;
	(void)loc;
	(void)mask;
	yield.Reset();
} 
void Source::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
{
	(void)spaces;
	(void)loc;
	yield.Reset();
}

unsigned Source::GetRange(std::vector<Space> &spaces, unsigned loc) const
{
	(void)spaces;
	(void)loc;
	return m_base_yield.m_range;
}

bool Source::PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield) 
{
	(void)spaces;
	(void)loc;
	(void)yield;
	(void)global_yield;
	return false;
}

void Source::ResetPostProcess(void)
{
}

void Source::GetAspects(unsigned natura, Yield &yield, unsigned mask) const
{
	for (size_t i = 0; i < m_aspects.size(); i++)
	{
		Yield this_yield;
		aspects.Bonus(m_aspects[i], natura, this_yield);
		yield.Add(this_yield, mask);
	}
}

bool Source::AddAspect(Aspects::aspect_t aspect)
{
	if (m_aspects.size() < m_max_aspects)
	{
		m_aspects.push_back(aspect);
		std::sort(m_aspects.begin(), m_aspects.end());
		return true;
	}
	return false;
}

bool Source::CanAddAspect(Aspects::aspect_t aspect) const
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

unsigned Source::CountAspects(Aspects::aspect_class_t aspect_class) const
{
	unsigned count = 0;
	for (size_t i = 0; i < m_aspects.size(); i++)
		if ((m_aspects[i] & 3U) == (aspect_class & 3U))
			count += 1;
	return count;
}

bool Source::IsValidForBiome(biome_t biome) const
{
   	(void)biome;
   	return true;
}

void Source::SetUpgradeCount(unsigned char upgrade_count)
{
	m_upgrade_count = upgrade_count;
}

Source* Source::Clone() const
{
	if (this)
	   	return new Source(*this);
   	return NULL;
}

void Source::Print(void) const
{
	std::cout << m_name << "(" << (unsigned)m_upgrade_count << "):";
	for (unsigned i = 0; i < m_aspects.size(); i++)
	{
		aspects.Print(m_aspects[i]);
		std::cout << ":";
	}
}




void Source::AddUpgrade(source_type_t source_type, Aspects::aspect_t aspect1, Aspects::aspect_t aspect2)
{
	m_upgrades.push_back(Upgrade(source_type, aspect1, aspect2));
}

void Source::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
	(void)biome;
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
			SourceFactory<source_type_t, unsigned char>::Builder builder;
			if (source_type_list.Get(m_upgrades[i].m_new_source, m_level, builder))
			{
				Source *new_source = builder();
				// Upgraded sources retain the aspects of the
				// pre-upgraded source. Copy those over here
				for (auto it = m_aspects.cbegin(); it != m_aspects.cend(); ++it)
					new_source->AddAspect(*it);
				new_source->SetUpgradeCount(UpgradeCount() + 1);

				upgrades.push_back(source_container.Add(new_source));
			}
		}
	}
}

// Add Yield if source types are in range
void Source::AddInRange(const std::vector<Space> &spaces, 
		unsigned loc, 
		Yield &yield,
		int start, 
		unsigned end,
		const Yield &yield_adder,
		unsigned mask,
		source_type_t type1,
		source_type_t type2,
		source_type_t type3,
		unsigned max_count) const
{
	unsigned adder_mask = yield_adder.GetMask();
	if ((adder_mask & mask) == 0)
		return;
	unsigned count = 0;
	for (unsigned i = std::max<int>(0, start);
		 (i <= end) && (i < spaces.size()) && (count < max_count);
		 i+= 1)
	{
		const source_type_t type = spaces[i].m_source->Type();
		if ((i != loc) && ((type == type1) || (type == type2) || (type == type3)) )
		{
			yield.Add(yield_adder, mask);
			count += 1;
		}
	}
}

// Add Yield if source classes are in range
void Source::AddInRange(const std::vector<Space> &spaces, 
		unsigned loc, 
		Yield &yield,
		int start, 
		unsigned end,
		const Yield &yield_adder,
		unsigned mask,
		source_class_t source_class,
		unsigned max_count) const
{
	unsigned adder_mask = yield_adder.GetMask();
	if ((adder_mask & mask) == 0)
		return;
	unsigned count = 0;
	for (unsigned i = std::max<int>(0, start); (i <= end) && (i < spaces.size()) && (count < max_count); i+= 1)
	{
		if ((i != loc) && (spaces[i].m_source->Class() == source_class))
		{
			yield.Add(yield_adder, mask);
			count += 1;
		}
	}
}

// Check whether or not a source class is in range
bool Source::NotInRange(const std::vector<Space> &spaces, 
		unsigned loc, 
		int start,
		unsigned end,
		source_class_t source_class) const
{
	for (unsigned i = std::max<int>(0, start); (i <= end) && (i < spaces.size()); i+= 1)
		if ((i != loc) && (spaces[i].m_source->Class() == source_class))
			return false;
	return true;
}

// Check whether or not a source type is in range
bool Source::NotInRange(const std::vector<Space> &spaces, 
		unsigned loc, 
		int start,
		unsigned end,
		source_type_t type1,
		source_type_t type2,
		source_type_t type3) const

{
	for (unsigned i = std::max<int>(0, start); (i <= end) && (i < spaces.size()); i+= 1)
	{
		if (i != loc)
		{
			const source_type_t type = spaces[i].m_source->Type();
			if ((type == type1) || (type == type2) || (type == type3)) 
				return false;
		}
	}
	return true;
}

void Source::GetFood(std::vector<Space> &spaces, unsigned loc, int start, int end,
		const Yield &yield, std::vector<unsigned> &food_yield) const
{
	food_yield.clear();
	food_yield.resize(spaces.size());

	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (i != loc)
		{
			unsigned range = spaces[i].m_source->GetRange(spaces, i);
			int this_start = std::max<int>(0, (int)i-range);
			int this_end = std::min<int>(i + range, spaces.size() - 1);

			if (!((this_start > end) || (this_end < start)))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_FOOD);
				for (unsigned j = std::max<int>(0, (int)i - this_yield.m_range); (j <= i + this_yield.m_range) && (j < spaces.size()); j++)
					food_yield[j] += this_yield.m_food;
			}
		}
	}
	// Use passed-in food from loc's space
	for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i++)
		food_yield[i] += yield.m_food;
}

void Source::AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3, unsigned max_count) const
{
	AddInRange(spaces, loc, yield, (int)loc - yield.m_range, loc + yield.m_range, 
			yield_adder, mask, type1, type2, type3, max_count);
}

void Source::AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type2, type3, 1);
}
void Source::AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type2, type2, 1);
}
void Source::AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type1, type1, 1);
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type2, type3, std::numeric_limits<unsigned>::max());
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type2, type2, std::numeric_limits<unsigned>::max());
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, type1, type1, type1, std::numeric_limits<unsigned>::max());
}

void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
{
	AddInRange(spaces, loc, yield, start, end, yield_adder, mask, type1, type2, type3, std::numeric_limits<unsigned>::max());
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
{
	AddAllInRange(spaces, loc, yield, start, end, yield_adder, mask, type1, type2, type2);
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
		const Yield &yield_adder, unsigned mask, source_type_t type1) const
{
	AddAllInRange(spaces, loc, yield, start, end, yield_adder, mask, type1, type1, type1);
}
void Source::AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
{
	AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, mask, type1, type2, type3, 1);
}
void Source::AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
{
	AddIfAdjacent(spaces, loc, yield, yield_adder, mask, type1, type2, type2);
}
void Source::AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1) const
{
	AddIfAdjacent(spaces, loc, yield, yield_adder, mask, type1, type1, type1);
}
void Source::AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
{
	AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, mask, type1, type2, type3, std::numeric_limits<unsigned>::max());
}
void Source::AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
{
	AddAllAdjacent(spaces, loc, yield, yield_adder, mask, type1, type2, type2);
}
void Source::AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_type_t type1) const
{
	AddAllAdjacent(spaces, loc, yield, yield_adder, mask, type1, type1, type1);
}

// Same as above, but classes rather than types
void Source::AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, 
		const Yield &yield_adder, unsigned mask, source_class_t source_class, unsigned max_count) const
{
	AddInRange(spaces, loc, yield, (int)loc - yield.m_range, loc + yield.m_range, yield_adder, mask, source_class, max_count);
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_class_t source_class) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, source_class, 1);
}
void Source::AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
		const Yield &yield_adder, unsigned mask, source_class_t source_class) const
{
	AddInRange(spaces, loc, yield, start, end, yield_adder, mask, source_class, std::numeric_limits<unsigned>::max());
}
void Source::AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_class_t source_class) const
{
	AddInRange(spaces, loc, yield, yield_adder, mask, source_class, 1);
}

void Source::AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_class_t source_class) const
{
	AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, mask, source_class, 1);
}
void Source::AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
		const Yield &yield_adder, unsigned mask, source_class_t source_class) const
{
	AddInRange(spaces, loc, yield, (int)loc - 1, loc + 1, yield_adder, mask, source_class, std::numeric_limits<unsigned>::max());
}

// 
bool Source::NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range, source_class_t source_class) const
{
	return NotInRange(spaces, loc, (int)loc - range, loc + range, source_class);
}
bool Source::NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_class_t source_class) const
{
	return NotInRange(spaces, loc, 1, source_class);
}
bool Source::NotInRange(const std::vector<Space> &spaces, unsigned loc, int start, unsigned end,
		source_type_t type1, source_type_t type2, source_type_t type3) const; 
bool Source::NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
		source_type_t type1, source_type_t type2, source_type_t type3) const 
{
	return NotInRange(spaces, loc, (int)loc - range, loc + range, type1, type2, type3);
}
bool Source::NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
		source_type_t type1, source_type_t type2) const
{
	return NotInRange(spaces, loc, range, type1, type2, type2);
}
bool Source::NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
		source_type_t type1) const
{
	return NotInRange(spaces, loc, range, type1, type1, type1);
}
bool Source::NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
		source_type_t type1, source_type_t type2, source_type_t type3)
{
	return NotInRange(spaces, loc, 1, type1, type2, type3);
}

bool Source::NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
		source_type_t type1, source_type_t type2) const
{
	return NotInRange(spaces, loc, 1, type1, type2);
}
bool Source::NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_type_t type1) const
{
	return NotInRange(spaces, loc, 1, type1);
}

void Source::GetTech(std::vector<Space> &spaces, unsigned loc, int start, int end,
		const Yield &yield, std::vector<unsigned> &tech_yield) const
{
	tech_yield.clear();
	tech_yield.resize(spaces.size());

	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (i != loc)
		{
			unsigned range = spaces[i].m_source->GetRange(spaces, i);
			int this_start = std::max<int>(0, (int)i-range);
			int this_end = std::min<int>(i + range, spaces.size() - 1);

			if (!((this_start > end) || (this_end < start)))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_TECH);
				for (unsigned j = std::max<int>(0, (int)i - this_yield.m_range); (j <= i + this_yield.m_range) && (j < spaces.size()); j++)
					tech_yield[j] += this_yield.m_tech;
			}
		}
	}
	// Use passed-in tech from loc's space
	for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i++)
		tech_yield[i] += yield.m_tech;
}

void Source::GetWealth(std::vector<Space> &spaces, unsigned loc, int start, int end,
		const Yield &yield, std::vector<unsigned> &wealth_yield) const
{
	wealth_yield.clear();
	wealth_yield.resize(spaces.size());

	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (i != loc)
		{
			unsigned range = spaces[i].m_source->GetRange(spaces, i);
			int this_start = std::max<int>(0, (int)i-range);
			int this_end = std::min<int>(i + range, spaces.size() - 1);

			if (!((this_start > end) || (this_end < start)))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_WEALTH);
				for (unsigned j = std::max<int>(0, (int)i - this_yield.m_range); (j <= i + this_yield.m_range) && (j < spaces.size()); j++)
					wealth_yield[j] += this_yield.m_wealth;
			}
		}
	}
	// Use passed-in wealth from loc's space
	for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i++)
		wealth_yield[i] += yield.m_wealth;
}

void Source::GetDanger(std::vector<Space> &spaces, unsigned loc, int start, int end,
		const Yield &yield, std::vector<unsigned> &danger_yield) const
{
	danger_yield.clear();
	danger_yield.resize(spaces.size());

	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (i != loc)
		{
			unsigned range = spaces[i].m_source->GetRange(spaces, i);
			int this_start = std::max<int>(0, (int)i-range);
			int this_end = std::min<int>(i + range, spaces.size() - 1);

			if (!((this_start > end) || (this_end < start)))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_DANGER);
				for (unsigned j = std::max<int>(0, (int)i - this_yield.m_range); (j <= i + this_yield.m_range) && (j < spaces.size()); j++)
					danger_yield[j] += this_yield.m_danger;
			}
		}
	}
	// Use passed-in danger from loc's space
	for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i++)
		danger_yield[i] += yield.m_danger;
}

void Source::GetAwe(std::vector<Space> &spaces, unsigned loc, int start, int end,
		const Yield &yield, std::vector<unsigned> &awe_yield) const
{
	awe_yield.clear();
	awe_yield.resize(spaces.size());

	for (unsigned i = 0; i < spaces.size(); i++)
	{
		if (i != loc)
		{
			unsigned range = spaces[i].m_source->GetRange(spaces, i);
			int this_start = std::max<int>(0, (int)i-range);
			int this_end = std::min<int>(i + range, spaces.size() - 1);

			if (!((this_start > end) || (this_end < start)))
			{
				Yield this_yield;
				spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_AWE);
				for (unsigned j = std::max<int>(0, (int)i - this_yield.m_range); (j <= i + this_yield.m_range) && (j < spaces.size()); j++)
					awe_yield[j] += this_yield.m_awe;
			}
		}
	}
	// Use passed-in awe from loc's space
	for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i++)
		awe_yield[i] += yield.m_awe;
}

void Source::GetFood(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &food_yield) const
{
	GetFood(spaces, loc, loc, loc, yield, food_yield);
}
void Source::GetTech(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &tech_yield) const
{
	GetTech(spaces, loc, loc, loc, yield, tech_yield);
}
void Source::GetWealth(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &wealth_yield) const
{
	GetWealth(spaces, loc, loc, loc, yield, wealth_yield);
}
void Source::GetDanger(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &danger_yield) const
{
	GetDanger(spaces, loc, loc, loc, yield, danger_yield);
}
void Source::GetAwe(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &awe_yield) const
{
	GetAwe(spaces, loc, loc, loc, yield, awe_yield);
}
