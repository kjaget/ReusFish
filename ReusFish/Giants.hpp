#pragma once

#include <array>
#include <vector>

#include "Biome.hpp"
#include "Source.hpp"
#include "SourceFactory.hpp"

class Giant
{
	public:
		Giant(void);
		void GetSources(biome_t biome, const std::array<unsigned, SOURCE_TYPE_T_MAX> &best_source_level, SourceList &sources) const;

	protected:
		unsigned                              m_domestic_level;
		unsigned                              m_domestic_level2;
		SourceFactory<biome_t, unsigned char> m_source_factory;
		SourceFactory<biome_t, unsigned char> m_source_factory2;

	private:
		void AddSource(Source *source, const std::array<unsigned, SOURCE_TYPE_T_MAX> &best_sources, SourceList &sources) const;
};

class Ocean_Giant : public Giant
{
	public:
		Ocean_Giant(unsigned domestic_level,
					unsigned growth_level,
					unsigned herd_level,
					unsigned crystal_level);
		void Init(void);
};

class Forest_Giant : public Giant
{
	public:
		Forest_Giant(unsigned domestic_level,
					 unsigned leaf_level,
					 unsigned fruit_level,
					 unsigned hunt_level);
		void Init(void);
};

class Stone_Giant : public Giant
{
	public:
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
		Giants(bool skip_lower_level_sources = false);
		void GetSources(biome_t biome, SourceList &list) const;

	private:
		Ocean_Giant  m_ocean_giant;
		Forest_Giant m_forest_giant;
		Stone_Giant  m_stone_giant;
		Swamp_Giant  m_swamp_giant;

		std::array<SourceList, BIOME_T_MAX> m_source_lists;
};
