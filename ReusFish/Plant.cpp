#include <algorithm>

#include "Plant.hpp"

void Blueberry::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0),APPLE_TREE, DANDELION, STRAWBERRY);
}

void Blueberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_LEAF, m_aspects[i]))
      {
	 upgrades.push_back(new Strawberry(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new AppleTree(m_aspects));
	 break;
      }
   }
}

void Great_Blueberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_LEAF, m_aspects[i]))
      {
	 upgrades.push_back(new Great_Strawberry(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_AppleTree(m_aspects));
	 break;
      }
   }
}

void Superior_Blueberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_LEAF, m_aspects[i]))
      {
	 upgrades.push_back(new Superior_Strawberry(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Superior_AppleTree(m_aspects));
	 break;
      }
   }
}

void Strawberry::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), BLUEBERRY, STRAWBERRY);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), DANDELION, STRAWBERRY);
}

void Strawberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new PearTree(m_aspects));
	 break;
      }
   }
}

void Great_Strawberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_PearTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_GROWTH, m_aspects[i])) 
      {
	 upgrades.push_back(new CherryTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new PlumTree(m_aspects));
	 break;
      }
   }
}

void Superior_Strawberry::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Superior_PearTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_GROWTH, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_CherryTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_PlumTree(m_aspects));
	 break;
      }
   }
}


void AppleTree::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) 
{ 
   yield = m_base_yield;
   GetAspects(0, yield);
   AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), ANIMAL);
}

void AppleTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder) 
{ 
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder, 0,0,0,0,0), ANIMAL);
}

void AppleTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new PearTree(m_aspects));
	 break;
      }
   }
}

void Great_AppleTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_PearTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new CherryTree(m_aspects));
	 break;
      }
   }
}

void Superior_AppleTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new Superior_PearTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_CherryTree(m_aspects));
	 break;
      }
   }
}

void PearTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder) 
{ 
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,m_awe_adder,0), PLANT);
}

void Superior_PearTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::SUBLIME_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new OrangeTree(m_aspects));
	 break;
      }
   }
}

void CherryTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, 
	    unsigned m_mineral_food_adder, unsigned m_silver_food_adder, unsigned m_gold_food_adder)
{ 
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(m_mineral_food_adder,0,0,0,0,0), MINERAL);
   AddIfAdjacent(spaces, loc, yield, Yield(m_silver_food_adder,0,0,0,0,0), SILVER);
   AddIfAdjacent(spaces, loc, yield, Yield(m_gold_food_adder,0,0,0,0,0), GOLD);
}

void Great_CherryTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::SUBLIME_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new OrangeTree(m_aspects));
	 break;
      }
   }
}

void PlumTree::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) 
{ 
   yield = m_base_yield;
   GetAspects(0, yield);
   if (NotInRange(spaces, loc, m_base_yield.m_natura_range, PLANT))
      yield.m_natura += m_natura_adder;
}

void PlumTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_food_adder) 
{ 
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllAdjacent(spaces, loc, yield, Yield(0,0,0,0,m_awe_adder,0), MINERAL);
   if (NotInRange(spaces, loc, m_base_yield.m_natura_range, PLANT))
      yield.m_food += m_food_adder;
}

void Great_PlumTree::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::SUBLIME_FRUIT, m_aspects[i])) 
      {
	 upgrades.push_back(new OrangeTree(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if ((aspects.CanUpgrade(Aspects::SUBLIME_TOXIC, m_aspects[i])) ||
          (aspects.CanUpgrade(Aspects::SUBLIME_LEAF , m_aspects[i])) )
      {
	 upgrades.push_back(new Sunflower(m_aspects));
	 break;
      }
   }
}

void OrangeTree::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) 
{ 
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_food += 3 * spaces[loc].m_yield.m_natura;

   unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};
   for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i+= 1)
   {
      if ((i != loc) && !seen_flag[spaces[i].m_source->Type()] &&
	  ((spaces[i].m_source->Class() == ANIMAL) || (spaces[i].m_source->Class() == FISH)   || 
	   (spaces[i].m_source->Class() == PLANT)  || (spaces[i].m_source->Class() == MINERAL) ))
      {
	 seen_flag[spaces[i].m_source->Type()] = 1;
	 yield.m_food += 27;
      }
   }
}

void Dandelion::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder)
{
   yield = m_base_yield;
   GetAspects(0, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), PLANT);
}

void Dandelion::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), PLANT);
}

void Dandelion::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Nightshade(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_GROWTH, m_aspects[i])) 
      {
	 upgrades.push_back(new Strawberry(m_aspects));
	 break;
      }
   }
}

void Great_Dandelion::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Great_Nightshade(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_GROWTH, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_Strawberry(m_aspects));
	 break;
      }
   }
}

void Superior_Dandelion::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Superior_Nightshade(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::LESSER_GROWTH, m_aspects[i])) 
      {
	 upgrades.push_back(new Superior_Strawberry(m_aspects));
	 break;
      }
   }
}

void Nightshade::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder)
{
   yield = m_base_yield;
   GetAspects(0, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,0,m_natura_adder), MINERAL);
}

void Nightshade::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), PLANT);
}

void Nightshade::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Foxglove(m_aspects));
	 break;
      }
   }
}

void Great_Nightshade::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Great_Foxglove(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new PlumTree(m_aspects));
	 break;
      }
   }
}

void Superior_Nightshade::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::POTENT_TOXIC, m_aspects[i]))
      {
	 upgrades.push_back(new Superior_Foxglove(m_aspects));
	 break;
      }
   }
   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::GREATER_LEAF, m_aspects[i])) 
      {
	 upgrades.push_back(new Great_PlumTree(m_aspects));
	 break;
      }
   }
}

void Foxglove::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_tech = int(spaces[loc].m_yield.m_natura * m_tech_multiplier);
}

void Superior_Foxglove::GetUpgrades(biome_t biome, SourceList &upgrades) const
{
   upgrades.clear();
   unsigned i;

   for (i = 0; i < m_aspects.size(); i++)
   {
      if (aspects.CanUpgrade(Aspects::SUBLIME_TOXIC, m_aspects[i]) ||
          aspects.CanUpgrade(Aspects::SUBLIME_LEAF , m_aspects[i]))
      {
	 upgrades.push_back(new Sunflower(m_aspects));
	 break;
      }
   }
}

void Sunflower::GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) 
{ 
   yield = m_base_yield;
   GetAspects(0, yield);

   unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};
   for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
   {
      if (!seen_flag[spaces[i].m_source->Type()] &&
	  (spaces[i].m_source->Class() == PLANT) &&
	  (spaces[i].Biome() == FOREST)  )
      {
	 seen_flag[spaces[i].m_source->Type()] = 1;
	 yield.m_natura += 8;
      }
   }
}

void Sunflower::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   std::vector<Yield> temp_yield(spaces.size());

   for (unsigned i = 0; i < spaces.size(); i++)
   {
      if (spaces[i].m_source)
      {
	 Yield yield;
	 spaces[i].m_source->GetYield(spaces, i, yield);
	 yield.m_natura = 0;
	 for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < spaces.size()); j++)
	    temp_yield[i] += yield;
      }
   }

   unsigned food = 0;
   for (unsigned i = std::max<int>(0, (int)loc - m_base_yield.m_natura_range); (i <= loc + m_base_yield.m_natura_range) && (i < spaces.size()); i += 1)
      food += temp_yield[i].m_food;

   yield.m_tech += food / 5;
   yield.m_awe  += food / 5;
}

