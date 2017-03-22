#include "Source.hpp"
#include "SourceContainer.hpp"
#include "Space.hpp"

static SourceTypeList source_type_list;

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
			SourceFactory<source_type_t, unsigned>::Builder builder;
			if (source_type_list.Get(m_upgrades[i].m_new_source, m_level, builder))
				upgrades.push_back(source_container.Add(builder()));
		}
	}
}

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
	for (unsigned i = std::max<int>(0, start); (i <= end) && (i < spaces.size()) && (count < max_count); i+= 1)
	{
		const source_type_t type = spaces[i].m_source->Type();
		if ((i != loc) && ((type == type1) || (type == type2) || (type == type3)) )
		{
			yield.Add(yield_adder, mask);
			count += 1;
		}
	}
}

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
		if ((i != loc) && 
				((spaces[i].m_source->Type() == type1) || (spaces[i].m_source->Type() == type2) || (spaces[i].m_source->Type() == type3)) )
			return false;
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
