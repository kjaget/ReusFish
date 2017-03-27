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
UsedList<unsigned, Landscape> used_list;

void remaining_moves(unsigned initial_pos)
{
	Landscape landscape;
	int best_score = std::numeric_limits<int>::min();
	bool logging = false;
	unsigned upgrades_added = 0;
	unsigned aspects_added = 0;
	unsigned landspaces_processed = 0;

	while (!priority_queue.empty())
	{
		landscape = priority_queue.top();
		priority_queue.pop();
		if (priority_queue.size() > 100000000)
			logging = true;

		if (!used_list.Insert(landscape))
			continue;
		if (landscape.Score() > best_score)
		{
			std::cout << "***************************************************" << std::endl;
			std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landspaces_processed << std::endl;

			if (landscape.BeatsGoal())
			{
				std::cout << "Beats goal" << std::endl;
				used_list.Print();
			}
			landscape.PrintAll();
			best_score = landscape.Score();
		}
		if ((++landspaces_processed % 100000) == 0)
			std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landspaces_processed << std::endl;

		SourceList upgrades;
		for (int pos = (int)initial_pos; pos >= 0; pos--)
		{
			landscape[pos].m_source->GetUpgrades(biome_list[pos], upgrades);
			for (unsigned i = 0; i < upgrades.size(); i++)
			{
				Space saved_space = landscape[pos];
				landscape[pos] = Space(upgrades[i]);
				landscape.SetYield();
				if (logging)
				{
					std::cout << "***************************************************" << std::endl;
					std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << std::endl;
					landscape.Print();
				}

				//if (used_list.Insert(landscape))
				{
					upgrades_added += 1;
					priority_queue.push(landscape);
				}
				landscape[pos] = saved_space;
			}

			for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
			{
				// Skip lesser aspects
				// Use greater aspect instead of potent one if possible
				if ((aspect & 3) && 
						!(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), landscape[pos].m_source->Class())) &&
						aspects.IsValid((Aspects::aspect_t)aspect, landscape[pos].m_source->Class()) &&
						landscape[pos].m_source->CanAddAspect((Aspects::aspect_t)aspect))
				{
					Space saved_space = landscape[pos];
					landscape[pos] = Space(landscape[pos], aspect);
					landscape.SetYield();
					if (logging)
					{
						std::cout << "***************************************************" << std::endl;
						landscape.Print();
					}
					//if (used_list.Insert(landscape))
					{
						aspects_added+=1;
						priority_queue.push(landscape);
					}
					landscape[pos] = saved_space;
				}
			}
		}
	}
}

void initial_moves(Landscape &spaces, int pos, const Giants &giants)
{
	if (pos < 0)
	{
		static int best_score = std::numeric_limits<int>::min();

		spaces.SetYield();
		int score = spaces.Score();
		//if (used_list.Insert(spaces))
		{
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
			//if (used_list.Insert(spaces))
			priority_queue.push(spaces);
		}
		return;
	}

	// For each space which isn't a building, grab the 
	// list of possible starting sources
	// for this biome.
	if (spaces[pos].m_source->Class() != NON_NATURAL)
	{
		SourceList source_list = giants.GetSources(biome_list[pos]);
		for (unsigned i = 0; i < source_list.size(); i++)
		{
			spaces[pos] = Space(source_list[i]);
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

	spaces.SetGoal(Yield(15, 0, 15, 0, 0, 0));
	spaces.StartCity();
	spaces.AddSpace(DESERT,new Quartz());
	spaces.AddSpace(DESERT,new Source());
	spaces.AddSpace(DESERT,new City());
	spaces.AddSpace(DESERT,new City());
	spaces.AddSpace(DESERT,new City());
	spaces.AddSpace(DESERT,new City());
	spaces.AddSpace(DESERT,new Shrine());
	spaces.AddSpace(DESERT,new Source());
	spaces.EndCity();


	initial_moves(spaces,spaces.size()-1,giants);
	remaining_moves(spaces.size()-1);

	return 0;
}
