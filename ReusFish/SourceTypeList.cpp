#include "SourceTypeList.hpp"
#include "Animal.hpp"
#include "EnumerateSources.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"

SourceTypeList::SourceTypeList(void) :
	m_best_sources{0},
	m_init(0)
{
	Register(BLUEBERRY, 1, SourceBuilder<Blueberry>);
	Register(BLUEBERRY, 2, SourceBuilder<Great_Blueberry>);
	Register(BLUEBERRY, 3, SourceBuilder<Superior_Blueberry>);
	Register(DANDELION, 1, SourceBuilder<Dandelion>);
	Register(DANDELION, 2, SourceBuilder<Great_Dandelion>);
	Register(DANDELION, 3, SourceBuilder<Superior_Dandelion>);
	Register(APPLE_TREE, 1, SourceBuilder<AppleTree>);
	Register(APPLE_TREE, 2, SourceBuilder<Great_AppleTree>);
	Register(APPLE_TREE, 3, SourceBuilder<Superior_AppleTree>);
	Register(STRAWBERRY, 1, SourceBuilder<Strawberry>);
	Register(STRAWBERRY, 2, SourceBuilder<Great_Strawberry>);
	Register(STRAWBERRY, 3, SourceBuilder<Superior_Strawberry>);
	Register(NIGHTSHADE, 1, SourceBuilder<Nightshade>);
	Register(NIGHTSHADE, 2, SourceBuilder<Great_Nightshade>);
	Register(NIGHTSHADE, 3, SourceBuilder<Superior_Nightshade>);
	Register(PEAR_TREE, 1, SourceBuilder<PearTree>);
	Register(PEAR_TREE, 2, SourceBuilder<Great_PearTree>);
	Register(PEAR_TREE, 3, SourceBuilder<Superior_PearTree>);
	Register(FOXGLOVE, 1, SourceBuilder<Foxglove>);
	Register(FOXGLOVE, 2, SourceBuilder<Great_Foxglove>);
	Register(FOXGLOVE, 3, SourceBuilder<Superior_Foxglove>);
	Register(CHERRY_TREE, 2, SourceBuilder<CherryTree>);
	Register(CHERRY_TREE, 3, SourceBuilder<Great_CherryTree>);
	Register(PLUM_TREE, 2, SourceBuilder<PlumTree>);
	Register(PLUM_TREE, 3, SourceBuilder<Great_PlumTree>);
	Register(ORANGE_TREE, 3, SourceBuilder<OrangeTree>);
	Register(SUNFLOWER, 3, SourceBuilder<Sunflower>);
	Register(CHICKEN, 1, SourceBuilder<Chicken>);
	Register(CHICKEN, 2, SourceBuilder<Great_Chicken>);
	Register(CHICKEN, 3, SourceBuilder<Superior_Chicken>);
	Register(STOAT, 1, SourceBuilder<Stoat>);
	Register(STOAT, 2, SourceBuilder<Great_Stoat>);
	Register(STOAT, 3, SourceBuilder<Superior_Stoat>);
	Register(RABBIT, 1, SourceBuilder<Rabbit>);
	Register(RABBIT, 2, SourceBuilder<Great_Rabbit>);
	Register(RABBIT, 3, SourceBuilder<Superior_Rabbit>);
	Register(BEAVER, 1, SourceBuilder<Beaver>);
	Register(BEAVER, 2, SourceBuilder<Great_Beaver>);
	Register(BEAVER, 3, SourceBuilder<Superior_Beaver>);
	Register(FOX, 1, SourceBuilder<Fox>);
	Register(FOX, 2, SourceBuilder<Great_Fox>);
	Register(FOX, 3, SourceBuilder<Superior_Fox>);
	Register(DEER, 1, SourceBuilder<Deer>);
	Register(DEER, 2, SourceBuilder<Great_Deer>);
	Register(DEER, 3, SourceBuilder<Superior_Deer>);
	Register(BOAR, 1, SourceBuilder<Boar>);
	Register(BOAR, 2, SourceBuilder<Great_Boar>);
	Register(BOAR, 3, SourceBuilder<Superior_Boar>);
	Register(WISENT, 2, SourceBuilder<Wisent>);
	Register(WISENT, 3, SourceBuilder<Great_Wisent>);
	Register(WOLF, 2, SourceBuilder<Wolf>);
	Register(WOLF, 3, SourceBuilder<Great_Wolf>);
	Register(MOOSE, 3, SourceBuilder<Moose>);
	Register(BEAR, 3, SourceBuilder<Bear>);
	Register(WITHERED_SHRUB, 1, SourceBuilder<WitheredShrub>);
	Register(WITHERED_SHRUB, 2, SourceBuilder<Great_WitheredShrub>);
	Register(WITHERED_SHRUB, 3, SourceBuilder<Superior_WitheredShrub>);
	Register(AGAVE, 1, SourceBuilder<Agave>);
	Register(AGAVE, 2, SourceBuilder<Great_Agave>);
	Register(AGAVE, 3, SourceBuilder<Superior_Agave>);
	Register(BARREL_CACTUS, 1, SourceBuilder<BarrelCactus>);
	Register(BARREL_CACTUS, 2, SourceBuilder<Great_BarrelCactus>);
	Register(BARREL_CACTUS, 3, SourceBuilder<Superior_BarrelCactus>);
	Register(DATE_PALM, 1, SourceBuilder<DatePalm>);
	Register(DATE_PALM, 2, SourceBuilder<Great_DatePalm>);
	Register(DATE_PALM, 3, SourceBuilder<Superior_DatePalm>);
	Register(ALOE_VERA, 1, SourceBuilder<AloeVera>);
	Register(ALOE_VERA, 2, SourceBuilder<Great_AloeVera>);
	Register(ALOE_VERA, 3, SourceBuilder<Superior_AloeVera>);
	Register(DESERT_LIME, 2, SourceBuilder<DesertLime>);
	Register(DESERT_LIME, 3, SourceBuilder<Great_DesertLime>);
	Register(CHILLI_PEPPER, 2, SourceBuilder<ChilliPepper>);
	Register(CHILLI_PEPPER, 3, SourceBuilder<Great_ChilliPepper>);
	Register(CARDON_CACTUS, 3, SourceBuilder<CardonCactus>);
	Register(OPIUM_POPPY, 3, SourceBuilder<OpiumPoppy>);
	Register(KANGAROO_RAT, 1, SourceBuilder<KangarooRat>);
	Register(KANGAROO_RAT, 2, SourceBuilder<Great_KangarooRat>);
	Register(KANGAROO_RAT, 3, SourceBuilder<Superior_KangarooRat>);
	Register(DESERT_TORTOISE, 1, SourceBuilder<DesertTortoise>);
	Register(DESERT_TORTOISE, 2, SourceBuilder<Great_DesertTortoise>);
	Register(DESERT_TORTOISE, 3, SourceBuilder<Superior_DesertTortoise>);
	Register(GOAT, 1, SourceBuilder<Goat>);
	Register(GOAT, 2, SourceBuilder<Great_Goat>);
	Register(GOAT, 3, SourceBuilder<Superior_Goat>);
	Register(ARMADILLO, 1, SourceBuilder<Armadillo>);
	Register(ARMADILLO, 2, SourceBuilder<Great_Armadillo>);
	Register(ARMADILLO, 3, SourceBuilder<Superior_Armadillo>);
	Register(RATTLESNAKE, 1, SourceBuilder<Rattlesnake>);
	Register(RATTLESNAKE, 2, SourceBuilder<Great_Rattlesnake>);
	Register(RATTLESNAKE, 3, SourceBuilder<Superior_Rattlesnake>);
	Register(JAVELINA, 1, SourceBuilder<Javelina>);
	Register(JAVELINA, 2, SourceBuilder<Great_Javelina>);
	Register(JAVELINA, 3, SourceBuilder<Superior_Javelina>);
	Register(GREY_FOX, 1, SourceBuilder<GreyFox>);
	Register(GREY_FOX, 2, SourceBuilder<Great_GreyFox>);
	Register(GREY_FOX, 3, SourceBuilder<Superior_GreyFox>);
	Register(COYOTE, 2, SourceBuilder<Coyote>);
	Register(COYOTE, 3, SourceBuilder<Great_Coyote>);
	Register(GILA_MONSTER, 2, SourceBuilder<GilaMonster>);
	Register(GILA_MONSTER, 3, SourceBuilder<Great_GilaMonster>);
	Register(BIG_HORN, 3, SourceBuilder<BigHorn>);
	Register(BOBCAT, 3, SourceBuilder<Bobcat>);
	Register(ELDERBERRY, 1, SourceBuilder<Elderberry>);
	Register(ELDERBERRY, 2, SourceBuilder<Great_Elderberry>);
	Register(ELDERBERRY, 3, SourceBuilder<Superior_Elderberry>);
	Register(PEPPERMINT, 1, SourceBuilder<Peppermint>);
	Register(PEPPERMINT, 2, SourceBuilder<Great_Peppermint>);
	Register(PEPPERMINT, 3, SourceBuilder<Superior_Peppermint>);
	Register(TOMATO, 1, SourceBuilder<Tomato>);
	Register(TOMATO, 2, SourceBuilder<Great_Tomato>);
	Register(TOMATO, 3, SourceBuilder<Superior_Tomato>);
	Register(PINEAPPLE, 1, SourceBuilder<Pineapple>);
	Register(PINEAPPLE, 2, SourceBuilder<Great_Pineapple>);
	Register(PINEAPPLE, 3, SourceBuilder<Superior_Pineapple>);
	Register(MARSH_MALLOW, 1, SourceBuilder<Marshmallow>);
	Register(MARSH_MALLOW, 2, SourceBuilder<Great_Marshmallow>);
	Register(MARSH_MALLOW, 3, SourceBuilder<Superior_Marshmallow>);
	Register(PAPAYA, 1, SourceBuilder<Papaya>);
	Register(PAPAYA, 2, SourceBuilder<Great_Papaya>);
	Register(PAPAYA, 3, SourceBuilder<Superior_Papaya>);
	Register(WHITE_WILLOW, 1, SourceBuilder<WhiteWillow>);
	Register(WHITE_WILLOW, 2, SourceBuilder<Great_WhiteWillow>);
	Register(WHITE_WILLOW, 3, SourceBuilder<Superior_WhiteWillow>);
	Register(COFFEA, 2, SourceBuilder<Coffea>);
	Register(COFFEA, 3, SourceBuilder<Great_Coffea>);
	Register(HEMP, 2, SourceBuilder<Hemp>);
	Register(HEMP, 3, SourceBuilder<Great_Hemp>);
	Register(CACAO_TREE, 3, SourceBuilder<CacaoTree>);
	Register(RUBBER_TREE, 3, SourceBuilder<RubberTree>);
	Register(FROG, 1, SourceBuilder<Frog>);
	Register(FROG, 2, SourceBuilder<Great_Frog>);
	Register(FROG, 3, SourceBuilder<Superior_Frog>);
	Register(POISON_DART_FROG, 1, SourceBuilder<PoisonDartFrog>);
	Register(POISON_DART_FROG, 2, SourceBuilder<Great_PoisonDartFrog>);
	Register(POISON_DART_FROG, 3, SourceBuilder<Superior_PoisonDartFrog>);
	Register(OTTER, 1, SourceBuilder<Otter>);
	Register(OTTER, 2, SourceBuilder<Great_Otter>);
	Register(OTTER, 3, SourceBuilder<Superior_Otter>);
	Register(CRANE, 1, SourceBuilder<Crane>);
	Register(CRANE, 2, SourceBuilder<Great_Crane>);
	Register(CRANE, 3, SourceBuilder<Superior_Crane>);
	Register(IGUANA, 1, SourceBuilder<Iguana>);
	Register(IGUANA, 2, SourceBuilder<Great_Iguana>);
	Register(IGUANA, 3, SourceBuilder<Superior_Iguana>);
	Register(TAPIR, 1, SourceBuilder<Tapir>);
	Register(TAPIR, 2, SourceBuilder<Great_Tapir>);
	Register(TAPIR, 3, SourceBuilder<Superior_Tapir>);
	Register(BUFFALO, 2, SourceBuilder<Buffalo>);
	Register(BUFFALO, 3, SourceBuilder<Great_Buffalo>);
	Register(KOMODO_DRAGON, 2, SourceBuilder<KomodoDragon>);
	Register(KOMODO_DRAGON, 3, SourceBuilder<Great_KomodoDragon>);
	Register(ORANGUTAN, 3, SourceBuilder<Orangutan>);
	Register(CROCODILE, 3, SourceBuilder<Crocodile>);
	Register(KUMQUAT, 1, SourceBuilder<Kumquat>);
	Register(KUMQUAT, 2, SourceBuilder<Great_Kumquat>);
	Register(KUMQUAT, 3, SourceBuilder<Superior_Kumquat>);
	Register(GINGER, 1, SourceBuilder<Ginger>);
	Register(GINGER, 2, SourceBuilder<Great_Ginger>);
	Register(GINGER, 3, SourceBuilder<Superior_Ginger>);
	Register(DRAGONFRUIT, 1, SourceBuilder<Dragonfruit>);
	Register(DRAGONFRUIT, 2, SourceBuilder<Great_Dragonfruit>);
	Register(DRAGONFRUIT, 3, SourceBuilder<Superior_Dragonfruit>);
	Register(KIWIFRUIT, 1, SourceBuilder<Kiwifruit>);
	Register(KIWIFRUIT, 2, SourceBuilder<Great_Kiwifruit>);
	Register(KIWIFRUIT, 3, SourceBuilder<Superior_Kiwifruit>);
	Register(LYCHEE, 2, SourceBuilder<Lychee>);
	Register(LYCHEE, 3, SourceBuilder<Great_Lychee>);
	Register(CINNAMOMUM, 2, SourceBuilder<Cinnamomum>);
	Register(CINNAMOMUM, 3, SourceBuilder<Great_Cinnamomum>);
	Register(TEA_PLANT, 2, SourceBuilder<TeaPlant>);
	Register(TEA_PLANT, 3, SourceBuilder<Great_TeaPlant>);
	Register(GINKGO, 3, SourceBuilder<Ginkgo>);
	Register(BRAZILWOOD, 3, SourceBuilder<Brazilwood>);
	Register(OAK, 3, SourceBuilder<Oak>);
	Register(MARTEN, 1, SourceBuilder<Marten>);
	Register(MARTEN, 2, SourceBuilder<Great_Marten>);
	Register(MARTEN, 3, SourceBuilder<Superior_Marten>);
	Register(MONAL, 1, SourceBuilder<Monal>);
	Register(MONAL, 2, SourceBuilder<Great_Monal>);
	Register(MONAL, 3, SourceBuilder<Superior_Monal>);
	Register(MUSK_DEER, 1, SourceBuilder<MuskDeer>);
	Register(MUSK_DEER, 2, SourceBuilder<Great_MuskDeer>);
	Register(MUSK_DEER, 3, SourceBuilder<Superior_MuskDeer>);
	Register(PANGOLIN, 1, SourceBuilder<Pangolin>);
	Register(PANGOLIN, 2, SourceBuilder<Great_Pangolin>);
	Register(PANGOLIN, 3, SourceBuilder<Superior_Pangolin>);
	Register(SNOW_LEOPARD, 2, SourceBuilder<SnowLeopard>);
	Register(SNOW_LEOPARD, 3, SourceBuilder<Great_SnowLeopard>);
	Register(LANGUR_MONKEY, 2, SourceBuilder<LangurMonkey>);
	Register(LANGUR_MONKEY, 3, SourceBuilder<Great_LangurMonkey>);
	Register(YAK, 2, SourceBuilder<Yak>);
	Register(YAK, 3, SourceBuilder<Great_Yak>);
	Register(PANDA, 3, SourceBuilder<Panda>);
	Register(BULL, 3, SourceBuilder<Bull>);
	Register(MACKEREL, 1, SourceBuilder<Mackerel>);
	Register(MACKEREL, 2, SourceBuilder<Great_Mackerel>);
	Register(MACKEREL, 3, SourceBuilder<Superior_Mackerel>);
	Register(CLOWNFISH, 1, SourceBuilder<Clownfish>);
	Register(CLOWNFISH, 2, SourceBuilder<Great_Clownfish>);
	Register(CLOWNFISH, 3, SourceBuilder<Superior_Clownfish>);
	Register(SEABASS, 1, SourceBuilder<Seabass>);
	Register(SEABASS, 2, SourceBuilder<Great_Seabass>);
	Register(SEABASS, 3, SourceBuilder<Superior_Seabass>);
	Register(PARROTFISH, 1, SourceBuilder<Parrotfish>);
	Register(PARROTFISH, 2, SourceBuilder<Great_Parrotfish>);
	Register(PARROTFISH, 3, SourceBuilder<Superior_Parrotfish>);
	Register(MARLIN, 2, SourceBuilder<Marlin>);
	Register(MARLIN, 3, SourceBuilder<Great_Marlin>);
	Register(ANGLERFISH, 2, SourceBuilder<Anglerfish>);
	Register(ANGLERFISH, 3, SourceBuilder<Great_Anglerfish>);
	Register(TUNA, 2, SourceBuilder<Tuna>);
	Register(TUNA, 3, SourceBuilder<Great_Tuna>);
	Register(BLUE_WHALE, 3, SourceBuilder<BlueWhale>);
	Register(WHITE_SHARK, 3, SourceBuilder<WhiteShark>);
	Register(DOLPHIN, 3, SourceBuilder<Dolphin>);
	Register(AGATE, 1, SourceBuilder<Agate>);
	Register(AGATE, 2, SourceBuilder<Great_Agate>);
	Register(AGATE, 3, SourceBuilder<Superior_Agate>);
	Register(QUARTZ, 1, SourceBuilder<Quartz>);
	Register(QUARTZ, 2, SourceBuilder<Great_Quartz>);
	Register(QUARTZ, 3, SourceBuilder<Superior_Quartz>);
	Register(STONE, 1, SourceBuilder<Stone>);
	Register(STONE, 2, SourceBuilder<Great_Stone>);
	Register(STONE, 3, SourceBuilder<Superior_Stone>);
	Register(MARBLE, 1, SourceBuilder<Marble>);
	Register(MARBLE, 2, SourceBuilder<Great_Marble>);
	Register(MARBLE, 3, SourceBuilder<Superior_Marble>);
	Register(TOPAZ, 1, SourceBuilder<Topaz>);
	Register(TOPAZ, 2, SourceBuilder<Great_Topaz>);
	Register(TOPAZ, 3, SourceBuilder<Superior_Topaz>);
	Register(SALT, 1, SourceBuilder<Salt>);
	Register(SALT, 2, SourceBuilder<Great_Salt>);
	Register(SALT, 3, SourceBuilder<Superior_Salt>);
	Register(ONYX, 1, SourceBuilder<Onyx>);
	Register(ONYX, 2, SourceBuilder<Great_Onyx>);
	Register(ONYX, 3, SourceBuilder<Superior_Onyx>);
	Register(COPPER, 1, SourceBuilder<Copper>);
	Register(COPPER, 2, SourceBuilder<Great_Copper>);
	Register(COPPER, 3, SourceBuilder<Superior_Copper>);
	Register(PHOSPHORUS, 1, SourceBuilder<Phosphorus>);
	Register(PHOSPHORUS, 2, SourceBuilder<Great_Phosphorus>);
	Register(PHOSPHORUS, 3, SourceBuilder<Superior_Phosphorus>);
	Register(IRON, 1, SourceBuilder<Iron>);
	Register(IRON, 2, SourceBuilder<Great_Iron>);
	Register(IRON, 3, SourceBuilder<Superior_Iron>);
	Register(GOLD, 2, SourceBuilder<Gold>);
	Register(GOLD, 3, SourceBuilder<Great_Gold>);
	Register(SILVER, 2, SourceBuilder<Silver>);
	Register(SILVER, 3, SourceBuilder<Great_Silver>);
	Register(PLATINUM, 2, SourceBuilder<Platinum>);
	Register(PLATINUM, 3, SourceBuilder<Great_Platinum>);
	Register(ALUMINIUM, 2, SourceBuilder<Aluminium>);
	Register(ALUMINIUM, 3, SourceBuilder<Great_Aluminium>);
	Register(ZINC, 2, SourceBuilder<Zinc>);
	Register(ZINC, 3, SourceBuilder<Great_Zinc>);
	Register(RUBY, 3, SourceBuilder<Ruby>);
	Register(DIAMOND, 3, SourceBuilder<Diamond>);
	Register(COAL, 3, SourceBuilder<Coal>);
	Register(OIL, 3, SourceBuilder<Oil>);
	Register(URANIUM, 3, SourceBuilder<Uranium>);
	Register(FLUORITE, 3, SourceBuilder<Fluorite>);
	Register(NATURAL_GAS, 3, SourceBuilder<NaturalGas>);
}

unsigned SourceTypeList::GetBestSourceLevel(source_type_t t)
{
	if (m_init < 2)
	{
		// Get list of highest source level for
		// each type. This is used to filter out cases
		// where 2 giants can create types at different levels
		// and the program wastes time processing the lower
		// level one
		if (m_init == 0)
		{
			m_init = 1;
			std::cout << "Starting init" << std::endl;
			enumerateSources(m_best_sources);
			std::cout << "Ended init" << std::endl;
			m_init = 2;
		}
		else if (m_init == 1)
			return 0;
	}
	if (t > SOURCE_TYPE_T_MAX)
		return 0;
	return m_best_sources[t];
}

