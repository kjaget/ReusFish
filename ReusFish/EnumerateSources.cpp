#include "Giants.hpp"
#include "Source.hpp"
#include "UsedList.hpp"

using namespace std;

// A single source on a given biometype
typedef pair<biome_t, const Source *> Tile;

static void permuteAspects(biome_t biome, 
					const Space &space,
					vector<Tile> &found_list,
					UsedList<size_t, Tile> &used_list);
static void generateUpgrades(vector<Tile> &found_list,
					  UsedList<size_t, Tile> &used_list);

static void permuteAspects(biome_t biome, const Space &space, 
					vector<Tile> &found_list, 
					UsedList<size_t, Tile> &used_list)
{
	Tile tile = make_pair(biome, space.m_source);

	if (used_list.Insert(tile))
		found_list.push_back(tile);

	//cout << "permuteAspects : " << endl;
	for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
	{
		// Skip lesser aspects
		// Use greater aspect instead of potent one if possible
		if ((aspect & 3) &&
			space.m_source->CanAddAspect((Aspects::aspect_t)aspect) &&
			aspects.IsValid((Aspects::aspect_t)aspect, space.m_source->Class()) &&
			!(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), space.m_source->Class()))) 
		{
			Space this_space(*space.m_source, aspect);
			//cout << "       permuteAspects seeing if used : " << endl;
			//landscape.Print();
			tile = make_pair(biome, this_space.m_source);
			if (used_list.Insert(tile))
			{
				found_list.push_back(tile);
				permuteAspects(biome, this_space, found_list, used_list);
			}
		}
	}
}

static void generateUpgrades(vector<Tile> &found_list, 
					  UsedList<size_t, Tile> &used_list)
{
	vector<Tile> new_found_list;
	SourceList upgrades;

	for (auto its = found_list.cbegin(); its != found_list.cend(); ++its)
	{
		its->second->GetUpgrades(its->first, upgrades);
		for (auto itu = upgrades.cbegin(); itu != upgrades.cend(); ++itu)
		{
			Tile biome_space_pair(its->first, *itu);
			if (used_list.Insert(biome_space_pair))
				new_found_list.push_back(biome_space_pair);
		}
	}
	found_list.insert(found_list.end(), new_found_list.begin(), new_found_list.end());
}

void enumerateSources(array<unsigned, SOURCE_TYPE_T_MAX> &best_source_level)
{
	for (size_t i = 0; i < SOURCE_TYPE_T_MAX; i++)
		best_source_level[i] = 0;

	Giants giants(true);
	BiomeList biome_types;
	biome_types.push_back(DESERT);
	biome_types.push_back(FOREST);
	biome_types.push_back(OCEAN);
	biome_types.push_back(SWAMP);
	biome_types.push_back(MOUNTAIN);

	UsedList<size_t, Tile> used_list;
	vector<Tile> found_list;

	SourceList source_list;
	for (auto itb = biome_types.cbegin(); itb != biome_types.cend(); ++itb)
	{
		giants.GetSources(*itb, source_list);
		for(auto its = source_list.cbegin(); its != source_list.cend(); ++its)
			permuteAspects(*itb, Space(**its), found_list, used_list);
	}

	size_t saved_size;
	do
	{
		saved_size = found_list.size();

		vector<pair<biome_t, const Source*>> new_found_list;
		for (auto it = found_list.cbegin(); it != found_list.cend(); ++it)
			permuteAspects(it->first, *(it->second), new_found_list, used_list);
		found_list.insert(found_list.end(), new_found_list.begin(), new_found_list.end());

		generateUpgrades(found_list, used_list);
	} 
	while (saved_size != found_list.size());

	for(auto its = found_list.cbegin(); its != found_list.cend(); ++its)
	{
		const source_type_t t = its->second->Type();
		const unsigned source_level = its->second->Level();
		if (source_level > best_source_level[t])
			best_source_level[t] = source_level;
	}
}
