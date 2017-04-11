#pragma once

#include <vector>

#include "Biome.hpp"
#include "Source.hpp"
#include "SourceFactory.hpp"

class Giant
{
	public:
		Giant();
		void GetSources(biome_t biome, std::vector<const Source *> &sources) const;

	protected:
		unsigned      m_domestic_level;
		unsigned      m_domestic_level2;
		SourceFactory<biome_t, unsigned char> m_source_factory;
		SourceFactory<biome_t, unsigned char> m_source_factory2;
};

class Ocean_Giant : public Giant
{
	public:
		Ocean_Giant();
		Ocean_Giant(unsigned domestic_level,
				unsigned growth_level,
				unsigned herd_level,
				unsigned crystal_level);
		void Init(void);
};

class Forest_Giant : public Giant
{
	public:
		Forest_Giant();
		Forest_Giant(unsigned domestic_level,
				unsigned leaf_level,
				unsigned fruit_level,
				unsigned hunt_level);
		void Init(void);
};

class Stone_Giant : public Giant
{
	public:
		Stone_Giant();
		Stone_Giant(unsigned domestic_level,
				unsigned domestic_level2,
				unsigned exotic_level,
				unsigned noble_level,
				unsigned seismic_level);
		void Init(void);
};

class Swamp_Giant : public Giant
{
	public:
		Swamp_Giant();
		Swamp_Giant(unsigned domestic_level,
				unsigned domestic_level2,
				unsigned toxic_level,
				unsigned predator_level,
				unsigned reaction_level);
		void Init(void);
};


class Giants
{
	public:
		Giants();
		SourceList GetSources(biome_t biome) const;

	private:
		Ocean_Giant  m_ocean_giant;
		Forest_Giant m_forest_giant;
		Stone_Giant  m_stone_giant;
		Swamp_Giant  m_swamp_giant;

};
