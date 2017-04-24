#include "Giants.hpp"
#include "Source.hpp"
#include "UsedList.hpp"

using namespace std;

void permuteAspects(biome_t biome, 
		const Space &space, 
		std::vector<std::pair<biome_t, const Source *>> &found_list, 
		UsedList<size_t, Landscape> &used_list);
void generateUpgrades(std::vector<pair<biome_t, 
		const Source *>> &found_list, 
		UsedList<size_t, Landscape> &used_list);

void permuteAspects(biome_t biome, const Space &space, vector<pair<biome_t, const Source *>> &found_list, UsedList<size_t, Landscape> &used_list)
{
	Landscape landscape(1);
	biome_list[0] = biome;
	landscape[0] = Space(*space.m_source);

	if (used_list.Insert(landscape))
		found_list.push_back(make_pair(biome, space.m_source));

	//cout << "permuteAspects : " << endl;
	//landscape.Print();
	for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
	{
		// Skip lesser aspects
		// Use greater aspect instead of potent one if possible
		if ((aspect & 3) &&
			space.m_source->CanAddAspect((Aspects::aspect_t)aspect) &&
			aspects.IsValid((Aspects::aspect_t)aspect, space.m_source->Class()) &&
			!(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), space.m_source->Class()))) 
		{
			biome_list[0] = biome;
			landscape[0] = Space(*space.m_source, aspect);
			//cout << "       permuteAspects seeing if used : " << endl;
			//landscape.Print();

			if (used_list.Insert(landscape))
			{
				//cout << "     permuteAspects : added" << endl;
				found_list.push_back(make_pair(biome, landscape[0].m_source));
				permuteAspects(biome, landscape[0], found_list, used_list);
			}
		}
	}
}

void generateUpgrades(vector<pair<biome_t, const Source *>> &found_list, UsedList<size_t, Landscape> &used_list)
{
	vector<pair<biome_t, const Source *>> new_found_list;
	Landscape landscape(1);
	SourceList upgrades;

	for (auto its = found_list.cbegin(); its != found_list.cend(); ++its)
	{
		biome_list[0] = its->first;
		//cout << "Checking upgrades for ";
		//biome_list.Print(0);
		//cout << ":";
		//its->second->Print();
		//cout << endl;
		its->second->GetUpgrades(its->first, upgrades);
		for (auto itu = upgrades.cbegin(); itu != upgrades.cend(); ++itu)
		{
		//	(*itu)->Print();
		//	cout << endl;
			landscape[0] = Space(**itu);
			if (used_list.Insert(landscape))
			{
		//		cout << "Adding ";
		//		landscape.Print();
		//		cout << "to new found list" << endl;
				new_found_list.push_back(make_pair(its->first, landscape[0].m_source));
			}
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

	Landscape landscape(biome_types.size());
	UsedList<size_t, Landscape> used_list;
	vector<pair<biome_t, const Source*>> found_list;

	SourceList source_list;
	for (auto itb = biome_types.cbegin(); itb != biome_types.cend(); ++itb)
	{
		giants.GetSources(*itb, source_list);
		for(auto its = source_list.cbegin(); its != source_list.cend(); ++its)
			permuteAspects(*itb, Source(**its), found_list, used_list);
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
#if 0
		Landscape landscape(1);
		biome_list[0] = its->first;
		landscape[0] = Space(*its->second);
		cout << " ** " << endl;
		landscape.Print();
#endif

		const source_type_t t = its->second->Type();
		const unsigned source_level = its->second->Level();
		if (source_level > best_source_level[t])
			best_source_level[t] = source_level;
	}
	biome_list.clear();
}

