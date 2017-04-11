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

static std::priority_queue<Landscape, std::deque<Landscape> > priority_queue;
static UsedList<unsigned, Landscape> used_list;

bool process_landscape_score(const Landscape &landscape, int &best_score, unsigned upgrades_added, unsigned aspects_added, unsigned &landscapes_processed)
{
	bool rc = false;
	int score = landscape.Score();

	// If the score is better than the previous
	// best, print it out
	if (score > best_score)
	{
		std::cout << "***************************************************" << std::endl;
		std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landscapes_processed << std::endl;

		if (landscape.BeatsGoal())
		{
			std::cout << "Beats goal" << std::endl;
			used_list.Print();
		}
		landscape.PrintAll();
		best_score = score;
		rc = true;
	}
	if ((++landscapes_processed % 250000) == 0)
		std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landscapes_processed << std::endl;
	return rc;
}


static void remaining_moves(unsigned initial_pos)
{
	int best_score = std::numeric_limits<int>::min();
	unsigned upgrades_added = 0;
	unsigned aspects_added = 0;
	unsigned landscapes_processed = 0;

	while (!priority_queue.empty())
	{
		// Grab the top scoring landscape off the queue
		// of those not yet processed
		Landscape landscape(priority_queue.top());
		priority_queue.pop();

		// If this has already been tested,
		// skip it
		if (!used_list.Insert(landscape))
			continue;

		SourceList upgrades;
		for (int pos = (int)initial_pos; pos >= 0; pos--)
		{
			// Save current space
			Space saved_space(landscape[pos]);

			for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
			{
				// Skip lesser aspects
				// Use greater aspect instead of potent one if possible
				if ((aspect & 3) && 
					!(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), saved_space.m_source->Class())) &&
						aspects.IsValid((Aspects::aspect_t)aspect, saved_space.m_source->Class()) &&
						saved_space.m_source->CanAddAspect((Aspects::aspect_t)aspect))
				{
					landscape[pos] = Space(saved_space, aspect);
					landscape.SetYield();
					aspects_added += 1;
					priority_queue.push(landscape);
					process_landscape_score(landscape, best_score, upgrades_added, aspects_added, landscapes_processed);

					// Get list of possible upgrades for current
					// space
					landscape[pos].m_source->GetUpgrades(biome_list[pos], upgrades);
					for (auto it = upgrades.cbegin(); it != upgrades.cend(); ++it)
					{
						landscape[pos] = Space(**it);
						landscape.SetYield();

						upgrades_added += 1;
						priority_queue.push(landscape);
						process_landscape_score(landscape, best_score, upgrades_added, aspects_added, landscapes_processed);
					}
				}
			}
			landscape[pos] = saved_space;
		}
	}
}

// Generate all the initial permutations of 
// starting configs for the landscape.  
void initial_moves(Landscape &spaces, int pos, const Giants &giants)
{
	if (pos < 0)
	{
		spaces.SetYield();
		int score = spaces.Score();
		// Doesn't have enough of a required class
		if (score == std::numeric_limits<int>::min())
			return;
		static int best_score = std::numeric_limits<int>::min();
		if (score > best_score)
		{
			std::cout << "***************************************************" << std::endl;
			if (spaces.BeatsGoal())
			{
				std::cout << "Beats goal" << std::endl;
				used_list.Print();
			}
			spaces.PrintAll();
			best_score = score;
		}
		priority_queue.push(spaces);
		if ((priority_queue.size() % 250000) == 0)
			std::cout << priority_queue.size() << " initial configs" << std::endl;
		return;
	}

	// For each space which isn't a building, grab the 
	// list of possible starting sources
	// for this biome.
	if (spaces[pos].m_source->Class() != NON_NATURAL)
	{
		SourceList source_list(giants.GetSources(biome_list[pos]));
		for (size_t i = 0; i < source_list.size(); i++)
		{
			spaces[pos] = Space(*source_list[i]);
			initial_moves(spaces, pos - 1, giants);
		}
	}
	else
		initial_moves(spaces, pos - 1, giants);
}

int main (int argc, char **argv)
{                               
	(void)argc;                 
	(void)argv;                 
	Landscape spaces;
	Giants giants;
	
	spaces.SetGoal(Opera().GetCompletionRequirements());
	spaces.AddSpace(OCEAN);
	spaces.StartCity();
	spaces.AddSpace(OCEAN);
	spaces.AddSpace(OCEAN);
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST,City());
	spaces.AddSpace(FOREST,City());
	spaces.AddSpace(FOREST,City());
	spaces.AddSpace(FOREST,City());
	spaces.AddSpace(FOREST,Temple());
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST);
	spaces.AddSpace(FOREST, Opera());
	spaces.AddSpace(FOREST);
	spaces.EndCity();

	initial_moves(spaces,spaces.size()-1,giants);
	remaining_moves(spaces.size()-1);

	return 0;
}
