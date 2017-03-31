#include "Animal.hpp"
#include "Aspects.hpp"
#include "Giants.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"
#include "SourceContainer.hpp"

Giant::Giant():
	m_domestic_level(0),
	m_domestic_level2(0)
{
}

void Giant::GetSources(biome_t biome, std::vector<const Source *>&sources) const
{
	SourceFactory<biome_t, unsigned>::Builder builder;
	if (m_source_factory.Get(biome, m_domestic_level, builder))
		sources.push_back(source_container.Add(builder()));
	if (m_source_factory2.Get(biome, m_domestic_level2, builder))
		sources.push_back(source_container.Add(builder()));
}

Ocean_Giant::Ocean_Giant() {}
Ocean_Giant::Ocean_Giant(unsigned domestic_level,
		unsigned growth_level,
		unsigned herd_level,
		unsigned crystal_level)
{
	m_domestic_level = domestic_level;
	m_domestic_level2 = 0;
	Init();
	aspects.Enable(Aspects::LESSER_GROWTH,  growth_level);
	aspects.Enable(Aspects::LESSER_HERD,    herd_level);
	aspects.Enable(Aspects::LESSER_CRYSTAL, crystal_level);
}

void Ocean_Giant::Init(void)
{
	m_source_factory.Register(OCEAN, 1, SourceBuilder<Mackerel>);
	m_source_factory.Register(OCEAN, 2, SourceBuilder<Great_Mackerel>);
	m_source_factory.Register(OCEAN, 3, SourceBuilder<Superior_Mackerel>);

	m_source_factory.Register(FOREST, 1, SourceBuilder<Chicken>);
	m_source_factory.Register(FOREST, 2, SourceBuilder<Great_Chicken>);
	m_source_factory.Register(FOREST, 3, SourceBuilder<Superior_Chicken>);

	m_source_factory.Register(DESERT, 1, SourceBuilder<KangarooRat>);
	m_source_factory.Register(DESERT, 2, SourceBuilder<Great_KangarooRat>);
	m_source_factory.Register(DESERT, 3, SourceBuilder<Superior_KangarooRat>);

	m_source_factory.Register(SWAMP, 1, SourceBuilder<Frog>);
	m_source_factory.Register(SWAMP, 2, SourceBuilder<Great_Frog>);
	m_source_factory.Register(SWAMP, 3, SourceBuilder<Superior_Frog>);

	m_source_factory.Register(MOUNTAIN, 1, SourceBuilder<Marten>);
	m_source_factory.Register(MOUNTAIN, 2, SourceBuilder<Great_Marten>);
	m_source_factory.Register(MOUNTAIN, 3, SourceBuilder<Superior_Marten>);
}

Forest_Giant::Forest_Giant() {}
Forest_Giant::Forest_Giant(unsigned domestic_level,
		unsigned leaf_level,
		unsigned fruit_level,
		unsigned hunt_level)
{
	m_domestic_level = domestic_level;
	m_domestic_level2 = 0;
	Init();
	aspects.Enable(Aspects::LESSER_LEAF,  leaf_level);
	aspects.Enable(Aspects::LESSER_FRUIT, fruit_level);
	aspects.Enable(Aspects::LESSER_HUNT,  hunt_level);
}

void Forest_Giant::Init(void)
{
	m_source_factory.Register(FOREST, 1, SourceBuilder<Blueberry>);
	m_source_factory.Register(FOREST, 2, SourceBuilder<Great_Blueberry>);
	m_source_factory.Register(FOREST, 3, SourceBuilder<Superior_Blueberry>);

	m_source_factory.Register(DESERT, 1, SourceBuilder<WitheredShrub>);
	m_source_factory.Register(DESERT, 2, SourceBuilder<Great_WitheredShrub>);
	m_source_factory.Register(DESERT, 3, SourceBuilder<Superior_WitheredShrub>);

	m_source_factory.Register(SWAMP, 1, SourceBuilder<Elderberry>);
	m_source_factory.Register(SWAMP, 2, SourceBuilder<Great_Elderberry>);
	m_source_factory.Register(SWAMP, 3, SourceBuilder<Superior_Elderberry>);

	m_source_factory.Register(MOUNTAIN, 1, SourceBuilder<Kumquat>);
	m_source_factory.Register(MOUNTAIN, 2, SourceBuilder<Great_Kumquat>);
	m_source_factory.Register(MOUNTAIN, 3, SourceBuilder<Superior_Kumquat>);
}

Stone_Giant::Stone_Giant() {}
Stone_Giant::Stone_Giant(unsigned domestic_level,
		unsigned domestic_level2,
		unsigned exotic_level,
		unsigned noble_level,
		unsigned seismic_level)	 
{
	m_domestic_level = domestic_level;
	m_domestic_level2 = domestic_level2;
	Init();
	aspects.Enable(Aspects::LESSER_EXOTIC,  exotic_level);
	aspects.Enable(Aspects::LESSER_NOBLE,   noble_level);
	aspects.Enable(Aspects::LESSER_SEISMIC, seismic_level);
}

void Stone_Giant::Init(void)
{
	m_source_factory.Register(FOREST, 1, SourceBuilder<Agate>);
	m_source_factory.Register(FOREST, 2, SourceBuilder<Great_Agate>);
	m_source_factory.Register(FOREST, 3, SourceBuilder<Superior_Agate>);

	m_source_factory.Register(MOUNTAIN, 1, SourceBuilder<Agate>);
	m_source_factory.Register(MOUNTAIN, 2, SourceBuilder<Great_Agate>);
	m_source_factory.Register(MOUNTAIN, 3, SourceBuilder<Superior_Agate>);

	m_source_factory.Register(SWAMP, 1, SourceBuilder<Agate>);
	m_source_factory.Register(SWAMP, 2, SourceBuilder<Great_Agate>);
	m_source_factory.Register(SWAMP, 3, SourceBuilder<Superior_Agate>);

	m_source_factory.Register(DESERT, 1, SourceBuilder<Quartz>);
	m_source_factory.Register(DESERT, 2, SourceBuilder<Great_Quartz>);
	m_source_factory.Register(DESERT, 3, SourceBuilder<Superior_Quartz>);

	m_source_factory2.Register(FOREST, 1, SourceBuilder<Stone>);
	m_source_factory2.Register(FOREST, 2, SourceBuilder<Great_Stone>);
	m_source_factory2.Register(FOREST, 3, SourceBuilder<Superior_Stone>);

	m_source_factory2.Register(MOUNTAIN, 1, SourceBuilder<Stone>);
	m_source_factory2.Register(MOUNTAIN, 2, SourceBuilder<Great_Stone>);
	m_source_factory2.Register(MOUNTAIN, 3, SourceBuilder<Superior_Stone>);

	m_source_factory2.Register(SWAMP, 1, SourceBuilder<Stone>);
	m_source_factory2.Register(SWAMP, 2, SourceBuilder<Great_Stone>);
	m_source_factory2.Register(SWAMP, 3, SourceBuilder<Superior_Stone>);

	m_source_factory2.Register(DESERT, 1, SourceBuilder<Marble>);
	m_source_factory2.Register(DESERT, 2, SourceBuilder<Great_Marble>);
	m_source_factory2.Register(DESERT, 3, SourceBuilder<Superior_Marble>);

}

Swamp_Giant::Swamp_Giant() {}
Swamp_Giant::Swamp_Giant(unsigned domestic_level,
		unsigned domestic_level2,
		unsigned toxic_level,
		unsigned predator_level,
		unsigned reaction_level) 	 
{
	m_domestic_level = domestic_level;
	m_domestic_level2 = domestic_level2;
	Init();
	aspects.Enable(Aspects::LESSER_TOXIC,    toxic_level);
	aspects.Enable(Aspects::LESSER_PREDATOR, predator_level);
	aspects.Enable(Aspects::LESSER_REACTION, reaction_level);
}

void Swamp_Giant::Init(void)
{
	m_source_factory.Register(FOREST, 1, SourceBuilder<Dandelion>);
	m_source_factory.Register(FOREST, 2, SourceBuilder<Great_Dandelion>);
	m_source_factory.Register(FOREST, 3, SourceBuilder<Superior_Dandelion>);

	m_source_factory.Register(DESERT, 1, SourceBuilder<WitheredShrub>);
	m_source_factory.Register(DESERT, 2, SourceBuilder<Great_WitheredShrub>);
	m_source_factory.Register(DESERT, 3, SourceBuilder<Superior_WitheredShrub>);

	m_source_factory.Register(SWAMP, 1, SourceBuilder<Peppermint>);
	m_source_factory.Register(SWAMP, 2, SourceBuilder<Great_Peppermint>);
	m_source_factory.Register(SWAMP, 3, SourceBuilder<Superior_Peppermint>);

	m_source_factory.Register(MOUNTAIN, 1, SourceBuilder<Ginger>);
	m_source_factory.Register(MOUNTAIN, 2, SourceBuilder<Great_Ginger>);
	m_source_factory.Register(MOUNTAIN, 3, SourceBuilder<Superior_Ginger>);

	m_source_factory2.Register(OCEAN, 1, SourceBuilder<Clownfish>);
	m_source_factory2.Register(OCEAN, 2, SourceBuilder<Great_Clownfish>);
	m_source_factory2.Register(OCEAN, 3, SourceBuilder<Superior_Clownfish>);

	m_source_factory2.Register(FOREST, 1, SourceBuilder<Stoat>);
	m_source_factory2.Register(FOREST, 2, SourceBuilder<Great_Stoat>);
	m_source_factory2.Register(FOREST, 3, SourceBuilder<Superior_Stoat>);

	m_source_factory2.Register(DESERT, 1, SourceBuilder<DesertTortoise>);
	m_source_factory2.Register(DESERT, 2, SourceBuilder<Great_DesertTortoise>);
	m_source_factory2.Register(DESERT, 3, SourceBuilder<Superior_DesertTortoise>);

	m_source_factory2.Register(SWAMP, 1, SourceBuilder<PoisonDartFrog>);
	m_source_factory2.Register(SWAMP, 2, SourceBuilder<Great_PoisonDartFrog>);
	m_source_factory2.Register(SWAMP, 3, SourceBuilder<Superior_PoisonDartFrog>);

	m_source_factory.Register(MOUNTAIN, 1, SourceBuilder<Monal>);
	m_source_factory.Register(MOUNTAIN, 2, SourceBuilder<Great_Monal>);
	m_source_factory.Register(MOUNTAIN, 3, SourceBuilder<Superior_Monal>);
}

Giants::Giants() :
	m_ocean_giant (Ocean_Giant (1,1,1,1)),
	m_forest_giant(Forest_Giant(1,1,1,0)),
	m_stone_giant (Stone_Giant (1,1,1,1,0)),
	m_swamp_giant (Swamp_Giant (1,1,1,0,0))
{
}

SourceList Giants::GetSources(biome_t biome) const
{
	SourceList sources;

	sources.push_back(source_container.Add(new Source()));
	m_ocean_giant.GetSources(biome, sources);
	m_forest_giant.GetSources(biome, sources);
	m_stone_giant.GetSources(biome, sources);
	m_swamp_giant.GetSources(biome, sources);
	return sources;
}
