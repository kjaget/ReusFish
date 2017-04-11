#pragma once

#include <iostream>
#include <vector>

typedef enum BIOME_T
{
	BIOME_NONE,
	DESERT,
	FOREST,
	OCEAN,
	SWAMP,
	MOUNTAIN,
	BIOME_T_MAX
} biome_t;

class BiomeList : public std::vector<biome_t>
{
	public:
		biome_t &operator [] (size_t i)
		{
			if (i >= size())
				resize(i + 1);

			return at(i);
		}
		void Print(size_t i) const
		{
			if (i >= size())
				std::cout << "Undef:";
			else
			{
				switch(at(i))
				{
					case DESERT:
						std::cout << "Desert:";
						break;
					case FOREST:
						std::cout << "Forest:";
						break;
					case OCEAN:
						std::cout << "Ocean:";
						break;
					case SWAMP:
						std::cout << "Swamp:";
						break;
					case MOUNTAIN:
						std::cout << "Mountain:";
						break;
					default:
						std::cout << "None:";
						break;
				}
			}
		}
};

extern BiomeList biome_list;
