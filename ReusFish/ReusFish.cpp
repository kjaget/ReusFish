#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <limits>

#include "Aspects.hpp"
#include "Animal.hpp"
#include "Biome.hpp"
#include "Building.hpp"
#include "Giants.hpp"
#include "Landscape.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"
#include "Source.hpp"
#include "Space.hpp"
#include "UsedList.hpp"
#include "Yield.hpp"

//#define VERBOSE

class RunState
{
	public:
		RunState(void) :
			m_best_score(std::numeric_limits<int>::min()),
			m_base(0),
			m_initials(0),
			m_aspects(0),
			m_upgrades(0),
			m_landscapes_processed(0),
			m_early_out(0),
			m_not_enough(0)
		{
		}
		bool AddNewAspect(Landscape &landscape)
		{
			if (!AddCommon(landscape))
				return false;
			m_aspects += 1;
			return CheckScore(landscape);
		}

		bool AddNewUpgrade(Landscape &landscape)
		{
			if (!AddCommon(landscape))
				return false;
			m_upgrades += 1;
			return CheckScore(landscape);
		}

		bool AddNewInitial(Landscape &landscape)
		{
			if (!AddCommon(landscape))
				return false;
			m_initials += 1;
			return CheckScore(landscape);
		}
		bool AddNewBase(Landscape &landscape)
		{
			if (!AddCommon(landscape))
				return false;
			m_base += 1;
			return CheckScore(landscape);
		}

		bool GetBest(Landscape &landscape)
		{
			if (m_priority_queue.empty())
				return false;

			// Grab the top scoring landscape off the queue
			// of those not yet processed
			landscape = m_priority_queue.top();
			m_priority_queue.pop();
			return true;
		}

		bool CheckScore(const Landscape &landscape)
		{
			bool rc = false;
			const int score = landscape.Score();
			m_landscapes_processed += 1;

			// If the score is better than the previous
			// best, print it out
			if (score > m_best_score)
			{
				std::cout << "***************************************************" << std::endl;
				if (landscape.BeatsGoal())
					std::cout << "!!!!!! Beats goal" << std::endl;

				landscape.PrintAll();
				m_best_score = score;
				rc = true;
			}

			if ((score > m_best_score) || ((m_landscapes_processed % 250000) == 0))
			{
				Print();
				m_used_list.Print();
				std::cout << "Priority Queue Size = " << m_priority_queue.size() << std::endl;
			}
			return rc;
		}
		void Print(void) const
		{
			std::cout << "Upgrades=" << m_upgrades;
			std::cout << " Aspects=" << m_aspects;
			std::cout << " Initials=" << m_initials;
			std::cout << " Base=" << m_base;
			std::cout << " Landscapes=" << m_landscapes_processed;
			std::cout << " Early Out=" << m_early_out << std::endl;
			std::cout << " Not Enough=" << m_not_enough<< std::endl;
		}

	private:
		bool AddCommon(Landscape &landscape)
		{
			if (!m_used_list.Insert(landscape))
			{
				m_early_out += 1;
				return false;
			}
			landscape.SetYield();
#ifdef VERBOSE
			landscape.PrintAll();
#endif
			if (landscape.Score() == std::numeric_limits<int>::min())
			{
				m_not_enough += 1;
				return false;
			}
			m_priority_queue.push(landscape);
			return true;
		}
		int      m_best_score;
		unsigned m_base;
		unsigned m_initials;
		unsigned m_aspects;
		unsigned m_upgrades;
		unsigned m_landscapes_processed;
		unsigned m_early_out;
		unsigned m_not_enough;

		std::priority_queue<Landscape, std::deque<Landscape>> m_priority_queue;
		UsedList<size_t, Landscape> m_used_list;
};

static void remaining_moves(unsigned initial_pos, const Giants &giants, RunState &run_state)
{
#ifdef VERBOSE
	std::cout << "remaining_moves(" << initial_pos<< ")" << std::endl;
#endif

	Landscape landscape;
	// Grab the top scoring landscape off the queue
	// of those not yet processed
	while (run_state.GetBest(landscape))
	{
#ifdef VERBOSE
		std::cout << "Popped new landscape : " << std::endl;
		landscape.Print();
#endif

		SourceList upgrades;
		for (int pos = (int)initial_pos; pos >= 0; pos--)
		{
			// Save current space
			Space saved_space(landscape[pos]);
#ifdef VERBOSE
			std::cout << "Checking pos " << pos << " = ";
			saved_space.m_source->Print();
			std::cout << std::endl;
#endif

			for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
			{
#ifdef VERBOSE
				std::cout << "Testing aspect ";
				aspects.Print((Aspects::aspect_t)aspect);
				std::cout << std::endl;
#endif

				// Skip lesser aspects
				// Use greater aspect instead of potent one if possible
				if ((aspect & 3) &&
					aspects.IsValid((Aspects::aspect_t)aspect, saved_space.m_source->Class()) &&
					saved_space.m_source->CanAddAspect((Aspects::aspect_t)aspect) &&
					!(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), saved_space.m_source->Class())) )
				{
					landscape[pos] = Space(saved_space, aspect);
					if (run_state.AddNewAspect(landscape))
						remaining_moves(initial_pos, giants, run_state);

					// Get list of possible upgrades for current
					// space
					landscape[pos].m_source->GetUpgrades(biome_list[pos], upgrades);
					for (auto it = upgrades.cbegin(); it != upgrades.cend(); ++it)
					{
						landscape[pos] = Space(**it);

						if (run_state.AddNewUpgrade(landscape))
							remaining_moves(initial_pos, giants, run_state);

						const unsigned range = 2;
						for (size_t i = std::max<int>((int)pos - range, 0); (i < (pos + range)) && (i < landscape.size()); i++)
						{
							Space another_space(landscape[i]);
							if ((i != (unsigned)pos) && (landscape[i].m_source->Class() != NON_NATURAL))
							{
								SourceList source_list(giants.GetSources(biome_list[i]));
								for (auto its = source_list.cbegin(); its != source_list.cend(); ++its)
								{
#if 0
									std::cout << "Setting landscape[" << i <<"]=";
									(*its)->Print();
									std::cout << std::endl;
#endif
									landscape[i] = Space(**its);
									if (run_state.AddNewInitial(landscape))
										remaining_moves(initial_pos, giants, run_state);

								}
							}
							landscape[i] = another_space;
						}
					}
				}
			}
			landscape[pos] = saved_space;
		}
	}
	std::cout << "Returing from remaining_moves()" << std::endl;
	run_state.Print();
}

// Generate all the initial permutations of 
// starting configs for the landscape.  
void initial_moves(Landscape &spaces, int pos, const Giants &giants, RunState &run_state)
{
	if (pos < 0)
	{
		// All spaces filled with something so add them
		// to the list of base states to check
		run_state.AddNewBase(spaces);
		return;
	}

	// For each space which isn't a building, grab the 
	// list of possible starting sources
	// for this biome.
	if (spaces[pos].m_source->Class() != NON_NATURAL)
	{
		SourceList source_list(giants.GetSources(biome_list[pos]));
		for(auto it = source_list.cbegin(); it != source_list.cend(); ++it)
		{
			spaces[pos] = Space(**it);
			initial_moves(spaces, pos - 1, giants, run_state);
		}
	}
	else
		initial_moves(spaces, pos - 1, giants, run_state);
}

int main (int argc, char **argv)
{                               
	(void)argc;                 
	(void)argv;                 
	Landscape spaces;
	Giants giants;
	RunState run_state;


	spaces.SetGoal(Market().GetCompletionRequirements());
	//spaces.AddSpace(MOUNTAIN);
	spaces.StartCity();
#if 1
	//spaces.AddSpace(MOUNTAIN);
	//spaces.AddSpace(DESERT);
	spaces.AddSpace(DESERT);
	spaces.AddSpace(DESERT, Market());
	spaces.AddSpace(DESERT,City());
	spaces.AddSpace(DESERT,City());
	spaces.AddSpace(DESERT,City());
	spaces.AddSpace(DESERT,City());
	spaces.AddSpace(DESERT);
	spaces.AddSpace(DESERT);
	spaces.AddSpace(MOUNTAIN);
	//spaces.AddSpace(MOUNTAIN);
	spaces.EndCity();
	//spaces.AddSpace(MOUNTAIN);
	//spaces.AddSpace(MOUNTAIN);
#endif
	//
#if 0
	std::vector<Aspects::aspect_t> a;
	a.push_back(Aspects::POTENT_PREDATOR);
	spaces.AddSpace(DESERT, Rattlesnake(a));
	priority_queue.push(spaces);
	remaining_moves(0, giants);
	return 0;
#endif

	initial_moves(spaces,spaces.size()-1, giants, run_state);
	remaining_moves(spaces.size()-1, giants, run_state);

	return 0;
}
