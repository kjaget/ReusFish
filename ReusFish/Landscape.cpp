#include <climits>
#include "Building.hpp"
#include "Landscape.hpp"

unsigned char Landscape::m_start = 0;
unsigned char Landscape::m_end = 0;
Yield Landscape::m_goal;

Landscape::Landscape(void)
{
}

Landscape::Landscape(unsigned size) : 
	m_spaces(size)
{
}

bool Landscape::operator<(const Landscape &rhs) const
{
	return Score() < rhs.Score();
}

Space &Landscape::operator [] (const unsigned i)
{
	return m_spaces[i];
}

const Space &Landscape::operator [] (const unsigned i) const
{
	return m_spaces[i];
}

bool Landscape::operator==(const Landscape &rhs) const
{
	return m_spaces == rhs.m_spaces;
}

size_t Landscape::Hash(void) const
{
	size_t hash = (size_t)0x600DF00D600DF00DULL;

	for (unsigned i = 0; i < m_spaces.size(); i++)
	{
		const unsigned size_t_bits = CHAR_BIT * sizeof(size_t);
		size_t this_hash = m_spaces[i].Hash();
		hash += this_hash << (i%size_t_bits);
		hash += (this_hash & ~((size_t)1 << (size_t_bits - 1))) >> (size_t_bits - (i%size_t_bits));
	}
	return hash;
}

size_t Landscape::size(void) const
{
	return m_spaces.size();
}

unsigned Landscape::Food(unsigned start_pos, unsigned end_pos) const
{
	unsigned food = 0;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		food += m_spaces[i].m_yield.m_food;
	return food;
}

unsigned Landscape::Tech(unsigned start_pos, unsigned end_pos) const
{
	unsigned tech = 0;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		tech += m_spaces[i].m_yield.m_tech;
	return tech;
}

unsigned Landscape::Wealth(unsigned start_pos, unsigned end_pos) const
{
	unsigned wealth = 0;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		wealth += m_spaces[i].m_yield.m_wealth;
	return wealth;
}

int Landscape::Awe(unsigned start_pos, unsigned end_pos) const
{
	int awe = 0;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		awe += m_spaces[i].m_yield.m_awe;
	return awe;
}

unsigned Landscape::Danger(unsigned start_pos, unsigned end_pos) const
{
	unsigned danger = 0;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		danger += m_spaces[i].m_yield.m_danger;
	return danger;
}

void Landscape::GetYield(Yield &yield, unsigned start_pos, unsigned end_pos) const
{
	yield.Reset();
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
		yield += m_spaces[i].m_yield;
}

void Landscape::GetYield(Yield &yield) const
{
	GetYield(yield, m_start, m_end);
}

void Landscape::Reset(void)
{
	for (unsigned i = 0; i < m_spaces.size(); i++)
		m_spaces[i].m_yield.Reset();
}

void Landscape::AddSpace(biome_t biome, const Source &source)
{
	biome_list.push_back(biome);
	m_spaces.push_back(Space(source));
}

void Landscape::AddSpace(biome_t biome)
{
	biome_list.push_back(biome);
	m_spaces.push_back(Space());
}

void Landscape::StartCity(void)
{
	m_start = m_spaces.size();
}

void Landscape::EndCity(void)
{
	m_end = m_spaces.size() - 1;
	for (auto it = m_spaces.begin(); it != m_spaces.end(); ++it)
		if (it->m_source->Type() == BUILDING)
		{
			Source *new_building = it->m_source->Clone();
			dynamic_cast<Building *>(new_building)->SetStartEnd(m_start, m_end);
			*it = Space(*new_building);
		}
}

void Landscape::SetGoal(const Yield &goal)
{
	m_goal = goal;
}

void Landscape::SetYield(void)
{
	Reset();

	// Since some plants can modify natura of other
	// spaces so accumulate chages across all of m_spaces
	for (size_t i = 0; i < m_spaces.size(); i++)
	{
		if (m_spaces[i].m_source)
		{
			Yield yield;
			m_spaces[i].m_source->GetNatura(m_spaces, i, yield);
			m_spaces[i].m_yield.m_natura += yield.m_natura;
			m_spaces[i].m_yield.m_natura_range = yield.m_natura_range;
		}
	}

	// Calculate natura first since it controls the rest of the
	// yield of each space
	std::vector<Yield> natura_yield(m_spaces.size());

	for (size_t i = 0; i < m_spaces.size(); i++)
		natura_yield[i] = m_spaces[i].m_yield;

	// Natura is the max of all sources in range
	for (size_t i = 0; i < m_spaces.size(); i++)
	{
		const unsigned this_natura = natura_yield[i].m_natura;
		const unsigned this_range  = natura_yield[i].m_natura_range;
		for (unsigned j = std::max<int>(0, (int)i - this_range); (j <= i + this_range) && (j < m_spaces.size()); j++)
			m_spaces[j].m_yield.m_natura = std::max<int>(m_spaces[j].m_yield.m_natura, this_natura);
	}

	for (unsigned i = 0; i < m_spaces.size(); i++)
	{
		Yield yield;
		m_spaces[i].m_source->GetYield(m_spaces, i, yield);
		yield.m_natura = 0;

		for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < m_spaces.size()); j++)
			m_spaces[j].m_yield += yield;

	}

	// Need a temp non-const copy of Spaces to run post-processing on
	// Can't use m_spaces since those pointers are consts and point to
	// a global pool of shared sources.  That doesn't guaratee that each
	// entry in the array will be unique so one Source might be shared
	// by two or more entries in m_spaces.
	//
	std::vector <Source *> sources;

	for (unsigned i = 0; i < m_spaces.size(); i++)
		sources.push_back(m_spaces[i].m_source->Clone());

	bool changed;
	Yield yield;
	std::vector<Yield> global_yield(m_spaces.size());
	do
	{
		changed = false;
		for (size_t i = 0; i < m_spaces.size(); i++)
		{
			if (sources[i]->PostProcess(m_spaces, i, yield, global_yield))
			{
				changed = true;
				for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < m_spaces.size()); j++)
					m_spaces[j].m_yield += yield;
				for (size_t j = 0; j < m_spaces.size(); j++)
					m_spaces[j].m_yield += global_yield[j];
			}
		}
	}
	while (changed);

	for (unsigned i = 0; i < m_spaces.size(); i++)
		delete sources[i];
}

std::array<unsigned char, SOURCE_CLASS_T_MAX> Landscape::CountClasses(void) const
{
	std::array<unsigned char, SOURCE_CLASS_T_MAX> class_count{};
	for (unsigned i = m_start; (i <= m_end) && (i < size()); i++)
		if (m_spaces[i].m_source)
			class_count[m_spaces[i].m_source->Class()] += 1;
	return class_count;
}

bool Landscape::BeatsGoal(void) const
{
	Yield yield;
	for (unsigned i = m_start; (i <= m_end) && (i < size()); i++)
		yield += m_spaces[i].m_yield;
	if (yield > m_goal)
		return true;
	return false;
}

int Landscape::ScoreHelper(unsigned goal, unsigned val, double multiplier) const
{
	int score = 0;
	if (goal)
	{
		// Give linear improvement until goal is hit. At that point,
		// additional yield doesn't matter that much
		if (val > goal)
		{
			score = (int)multiplier;
			if (val > (1.5*goal))
				val = (int)(1.5*goal);
			score += int((double(val - goal) / goal) * (multiplier / 75.0));
		}
		else
			score = int((double)val / goal * multiplier);
	}
	return score;
}
int Landscape::Score(const Yield &goal, unsigned start_pos, unsigned end_pos) const
{
	int score = 0;
	//unsigned superior_count = 0;
	//unsigned greater_count = 0;
	Yield yield;
	auto class_count = CountClasses();

	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	{
		if (m_spaces[i].m_source)
		{
			yield += m_spaces[i].m_yield;
			if (m_spaces[i].m_source && (m_spaces[i].m_source->Type() == BUILDING))
				if (!dynamic_cast<const Building *>(m_spaces[i].m_source)->CheckClassCompletion(class_count))
					return std::numeric_limits<int>::min();
			//      superior_count += m_spaces[i].m_source->CountAspects(Aspects::SUBLIME);
			//      greater_count  += m_spaces[i].m_source->CountAspects(Aspects::GREATER);
		}
	}

	score += ScoreHelper(goal.m_food, yield.m_food, 5000.0);
	score += ScoreHelper(goal.m_tech, yield.m_tech, 5000.0);
	score += ScoreHelper(goal.m_wealth, yield.m_wealth, 5000.0);
	score += ScoreHelper(goal.m_danger, yield.m_danger, 5000.0);
	score += ScoreHelper(goal.m_awe, yield.m_awe, 5000.0);
	score += ScoreHelper(goal.m_natura, yield.m_natura, 5000.0);
#if 0
	if (yield.m_awe > (yield.m_danger + 20))
		score /= 1.5;
#endif

#if 0
	score -= greater_count * 5000/100;
	int delta = score - INT_MIN;

	delta = (int)((double)delta * (1. - 0.01 * superior_count - 0.005 * greater_count));
	score = delta - INT_MIN;
#endif
	return score;
}

int Landscape::Score(const Yield &goal) const
{
	return Score(goal, m_start, m_end);
}

int Landscape::Score(void) const
{
	return Score(m_goal, m_start, m_end);
}

void Landscape::Print(void) const
{
	for (unsigned i = 0; i < m_spaces.size(); i++)
	{
		if (i == m_start)
			std::cout << "--------" << std::endl;
		m_spaces[i].Print();
		std::cout << std::endl;
		if (i == m_end)
			std::cout << "--------" << std::endl;
	}
}
void Landscape::PrintAll(void) const
{
	std::cout << "S:" << Score();
	std::cout << " F:" << Food(m_start, m_end);
	std::cout << " T:" << Tech(m_start, m_end);
	std::cout << " W:" << Wealth(m_start, m_end);
	std::cout << " D:" << Danger(m_start, m_end);
	std::cout << " A:" << Awe(m_start, m_end);
	std::cout << " H:" << Hash() << std::endl;
	for (unsigned i = 0; i < m_spaces.size(); i++)
	{
		if (i == m_start)
			std::cout << "--------" << std::endl;
		biome_list.Print(i);
		m_spaces[i].Print();
		if (m_spaces[i].m_source)
		{
			std::cout << " :: " ;
			Yield yield;
			// Need just the yield for this space, but 
			// this space can change others. We don't want
			// to modify the actual yield. Operate on
			// a dummy copy of spaces so global
			// changes get thrown away
			std::vector<Space> spaces(m_spaces);
			spaces[i].m_source->GetNatura(spaces, i, yield);
			unsigned natura = yield.m_natura;
			spaces[i].m_source->GetYield(spaces, i, yield);
			yield.m_natura = natura;
			yield.Print();
		}
		std::cout << std::endl;
		if (i == m_end)
			std::cout << "--------" << std::endl;
	}
}

