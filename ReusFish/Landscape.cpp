#include <climits>
#include "Building.hpp"
#include "Landscape.hpp"

unsigned char Landscape::m_start = 0;
unsigned char Landscape::m_end = 0;
Yield Landscape::m_goal;

Landscape::Landscape(void) :
	m_score_dirty(true)
{
}

Landscape::Landscape(unsigned size) : 
	m_spaces(size),
	m_score_dirty(true)
{
}

bool Landscape::operator<(const Landscape &rhs) const
{
	if (m_score_dirty || rhs.m_score_dirty)
		std::cout << "!!!!===== Landscape score dirty in operator < " << std::endl;
	return m_score < rhs.m_score;
}

Space &Landscape::operator [] (const unsigned i)
{
	m_score_dirty = true;
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

	for (size_t i = 0; i < m_spaces.size(); i++)
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
	m_score_dirty = true;
	for (unsigned i = 0; i < m_spaces.size(); i++)
		m_spaces[i].m_yield.Reset();
}

void Landscape::AddSpace(biome_t biome, const Source &source)
{
	m_score_dirty = true;
	biome_list.push_back(biome);
	m_spaces.push_back(Space(source));
}

void Landscape::AddSpace(biome_t biome)
{
	m_score_dirty = true;
	biome_list.push_back(biome);
	m_spaces.push_back(Space());
}

void Landscape::StartCity(void)
{
	m_score_dirty = true;
	m_start = m_spaces.size();
}

void Landscape::EndCity(void)
{
	m_score_dirty = true;
	m_end = m_spaces.size() - 1;
	for (auto it = m_spaces.begin(); it != m_spaces.end(); ++it)
		if (it->m_source->Type() == BUILDING)
		{
			Source *new_building = it->m_source->Clone();
			dynamic_cast<Building *>(new_building)->SetStartEnd(m_start, m_end);
			it->m_source = new_building;
		}
}

void Landscape::SetGoal(const Yield &goal)
{
	m_score_dirty = true;
	m_goal = goal;
}

void Landscape::SetYield(void)
{
	if (!m_score_dirty)
		return;
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

	Score();
}

std::array<unsigned char, SOURCE_CLASS_T_MAX> Landscape::CountClasses(void) const
{
	std::array<unsigned char, SOURCE_CLASS_T_MAX> class_count{0};
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

#if 0
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
#endif

int Landscape::ScoreHelper(unsigned goal, unsigned val, double multiplier) const
{
	int score = 0;
	const float goal_threshold = 1.5;
	if (goal)
	{
		// Give linear improvement until goal is hit. At that point,
		// additional yield doesn't matter that much
		if (val > (goal * 2. * goal_threshold))
		{
		}
		else if (val > (goal * goal_threshold))
		{
			// Penalize going too far over the goal
			double delta = (goal * 2. * goal_threshold - val) / (goal * goal_threshold);
			score = int(multiplier * pow(delta, 0.5));
		}
		else if (val > goal)
			score = multiplier + (val-goal)*.1;
		else
			score = int(multiplier * pow((double)val / goal, 1./3.));
	}
	else
		score = multiplier * val * 0.25;
	return score;
}

int Landscape::Score(const Yield &goal, unsigned start_pos, unsigned end_pos)
{
	if (!m_score_dirty)
		return m_score;

	int score = 0;
	unsigned sublime_count = 0;
	unsigned greater_count = 0;
	Yield yield;
	std::array<unsigned char, SOURCE_CLASS_T_MAX> class_count;
	bool class_count_valid = false;
	for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	{
		if (m_spaces[i].m_source)
		{
			yield += m_spaces[i].m_yield;
			if (m_spaces[i].m_source && (m_spaces[i].m_source->Type() == BUILDING))
			{
				const Building *building = dynamic_cast<const Building *>(m_spaces[i].m_source);
				if (building->NeedsClassCount())
				{
					if (!class_count_valid)
					{
						class_count = CountClasses();
						class_count_valid = true;
					}
					if (!dynamic_cast<const Building *>(m_spaces[i].m_source)->CheckClassCompletion(class_count))
						return std::numeric_limits<int>::min();

					sublime_count += m_spaces[i].m_source->CountAspects(Aspects::SUBLIME);
					greater_count  += m_spaces[i].m_source->CountAspects(Aspects::GREATER);
				}
			}
		}
	}

	unsigned total_goal = goal.m_food + goal.m_tech + goal.m_wealth + goal.m_danger + goal.m_awe + goal.m_natura;

	const double scale = 100000;
	score += ScoreHelper(goal.m_food, yield.m_food, scale) * (double)goal.m_food/total_goal;
	score += ScoreHelper(goal.m_tech, yield.m_tech, scale) * (double)goal.m_tech/total_goal;
	score += ScoreHelper(goal.m_wealth, yield.m_wealth, scale) * (double)goal.m_wealth/total_goal;
	score += ScoreHelper(goal.m_danger, yield.m_danger, scale) * (double)goal.m_danger/total_goal;
	score += ScoreHelper(goal.m_awe, yield.m_awe, scale) * (double)goal.m_awe/total_goal;
	score += ScoreHelper(goal.m_natura, yield.m_natura, scale) * (double)goal.m_natura/total_goal;
#if 1
	if (yield.m_danger > (yield.m_awe + 30))
		score /= 1.25;
#endif

	score -= (sublime_count) * (scale / 5000);
	score -= (greater_count) * (scale / 15000);
	m_score_dirty = false;
	m_score = score;
	return score;
}

int Landscape::Score(const Yield &goal)
{
	return Score(goal, m_start, m_end);
}

int Landscape::Score(void)
{
	return Score(m_goal, m_start, m_end);
}

void Landscape::Print(void) const
{
	for (unsigned i = 0; i < m_spaces.size(); i++)
	{
		if (i == m_start)
			std::cout << "--------" << std::endl;
		biome_list.Print(i);
		m_spaces[i].Print();
		std::cout << std::endl;
		if (i == m_end)
			std::cout << "--------" << std::endl;
	}
}
void Landscape::PrintAll(void) const
{
	std::cout << "S:" << m_score;
	if (m_score_dirty)
		std::cout << "!" << std::endl;
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

