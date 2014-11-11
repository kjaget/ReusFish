#ifndef PLANT_INC__
#define PLANT_INC__

#include <vector>

#include "Space.hpp"
#include "Source.hpp"

class Plant : public Source
{
   public :
      Plant() { m_class = PLANT; m_base_yield.m_natura_range = 2; }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) 
      { 
	 yield = m_base_yield;
	 GetAspects(0, yield);
      }
      Plant *Clone() const {return new Plant(*this);}
};

class Blueberry : public Plant
{
   public:
      Blueberry()
      {
	 Create();
      }

      Blueberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Blueberry";
	 m_type = BLUEBERRY;
	 m_base_yield.m_food = 5;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 1;
	 m_level = 1;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 10);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Blueberry* Clone() const {return new Blueberry(*this);}
};

class Great_Blueberry : public Blueberry
{
   public:
      Great_Blueberry()
      {
	 Create();
      }

      Great_Blueberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Blueberry";
	 m_type = BLUEBERRY;
	 m_base_yield.m_food = 10;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 2;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Blueberry::GetYield(spaces, loc, yield, 20);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_Blueberry* Clone() const {return new Great_Blueberry(*this);}
};

class Superior_Blueberry : public Blueberry
{
   public:
      Superior_Blueberry()
      {
	 Create();
      }

      Superior_Blueberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Blueberry";
	 m_type = BLUEBERRY;
	 m_base_yield.m_food = 20;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 3;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Blueberry::GetYield(spaces, loc, yield, 40);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_Blueberry* Clone() const {return new Superior_Blueberry(*this);}
};

class Strawberry : public Plant
{
   public:
      Strawberry()
      {
	 Create();
      }

      Strawberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Strawberry";
	 m_type = STRAWBERRY;
	 m_base_yield.m_food = 5;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
	 m_level = 1;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 3, 5);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder);
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Strawberry* Clone() const {return new Strawberry(*this);}
};

class Great_Strawberry : public Strawberry
{
   public:
      Great_Strawberry()
      {
	 Create();
      }

      Great_Strawberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Strawberry";
	 m_type = STRAWBERRY;
	 m_base_yield.m_food = 10;
	 m_base_yield.m_tech = 6;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Strawberry::GetYield(spaces, loc, yield, 15, 10);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_Strawberry* Clone() const {return new Great_Strawberry(*this);}
};

class Superior_Strawberry : public Strawberry
{
   public:
      Superior_Strawberry()
      {
	 Create();
      }

      Superior_Strawberry(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Strawberry";
	 m_type = STRAWBERRY;
	 m_base_yield.m_food = 20;
	 m_base_yield.m_tech = 8;
	 m_base_yield.m_natura = 9;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Strawberry::GetYield(spaces, loc, yield, 30, 25);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_Strawberry* Clone() const {return new Superior_Strawberry(*this);}
};

class AppleTree : public Plant
{
   public:
      AppleTree()
      {
	 Create();
      }

      AppleTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "AppleTree";
	 m_type = APPLE_TREE;
	 m_base_yield.m_food = 6;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
	 m_level = 1;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetNatura(spaces, loc, yield, 2);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 8);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      AppleTree* Clone() const {return new AppleTree(*this);}
};

class Great_AppleTree : public AppleTree
{
   public:
      Great_AppleTree()
      {
	 Create();
      }

      Great_AppleTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great AppleTree";
	 m_type = APPLE_TREE;
	 m_base_yield.m_food = 10;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 AppleTree::GetNatura(spaces, loc, yield, 4);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 AppleTree::GetYield(spaces, loc, yield, 16);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_AppleTree* Clone() const {return new Great_AppleTree(*this);}
     
   protected:
      static const unsigned m_food_adder = 16;
      static const unsigned m_natura_adder = 4;
};

class Superior_AppleTree : public AppleTree
{
   public:
      Superior_AppleTree()
      {
	 Create();
      }

      Superior_AppleTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior AppleTree";
	 m_type = APPLE_TREE;
	 m_base_yield.m_food = 20;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 AppleTree::GetNatura(spaces, loc, yield, 8);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 AppleTree::GetYield(spaces, loc, yield, 32);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_AppleTree* Clone() const {return new Superior_AppleTree(*this);}
};

class PearTree : public Plant
{
   public:
      PearTree()
      {
	 Create();
      }

      PearTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "PearTree";
	 m_type = PEAR_TREE;
	 m_base_yield.m_food = 5;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 3;
	 m_level = 1;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 10,5);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder);
      PearTree* Clone() const {return new PearTree(*this);}
};

class Great_PearTree : public PearTree
{
   public:
      Great_PearTree()
      {
	 Create();
      }

      Great_PearTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great PearTree";
	 m_type = PEAR_TREE;
	 m_base_yield.m_food = 10;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 4;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 PearTree::GetYield(spaces, loc, yield, 20, 10);
      }
      Great_PearTree* Clone() const {return new Great_PearTree(*this);}
};

class Superior_PearTree : public PearTree
{
   public:
      Superior_PearTree()
      {
	 Create();
      }

      Superior_PearTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior PearTree";
	 m_type = PEAR_TREE;
	 m_base_yield.m_food = 20;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 5;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 PearTree::GetYield(spaces, loc, yield, 40, 15);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_PearTree* Clone() const {return new Superior_PearTree(*this);}
};

class CherryTree : public Plant
{
   public:
      CherryTree()
      {
	 Create();
      }

      CherryTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "CherryTree";
	 m_type = CHERRY_TREE;
	 m_base_yield.m_food = 10;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 4;
	 m_level = 2;
      }
	  
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 15, 10, 20);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    unsigned m_mineral_food_adder, unsigned m_silver_food_adder, unsigned m_gold_food_adder);
      CherryTree* Clone() const {return new CherryTree(*this);}
};

class Great_CherryTree : public CherryTree
{
   public:
      Great_CherryTree()
      {
	 Create();
      }

      Great_CherryTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great CherryTree";
	 m_type = CHERRY_TREE;
	 m_base_yield.m_food = 20;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 CherryTree::GetYield(spaces, loc, yield, 30, 25, 50);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_CherryTree* Clone() const {return new Great_CherryTree(*this);}
};

class PlumTree : public Plant
{
   public:
      PlumTree()
      {
	 Create();
      }

      PlumTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "PlumTree";
	 m_type = PLUM_TREE;
	 m_base_yield.m_food = 15;
	 m_base_yield.m_tech = 15;
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 4;
	 m_level = 2;
      }


      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetNatura(spaces, loc, yield, 12);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 10, 20);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_food_adder);

      PlumTree* Clone() const {return new PlumTree(*this);}
};

class Great_PlumTree : public PlumTree
{
   public:
      Great_PlumTree()
      {
	 Create();
      }

      Great_PlumTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great PlumTree";
	 m_type = PLUM_TREE;
	 m_base_yield.m_food = 30;
	 m_base_yield.m_tech = 30;
	 m_base_yield.m_natura = 10;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 PlumTree::GetNatura(spaces, loc, yield, 25);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 PlumTree::GetYield(spaces, loc, yield, 24, 50);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_PlumTree* Clone() const {return new Great_PlumTree(*this);}
};

class OrangeTree : public Plant
{
   public:
      OrangeTree()
      {
	 Create();
      }

      OrangeTree(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "OrangeTree";
	 m_type = ORANGE_TREE;
	 m_base_yield.m_food = 25;
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      OrangeTree* Clone() const {return new OrangeTree(*this);}
};

class Dandelion : public Plant
{
   public:
      Dandelion()
      {
	 Create();
      }

      Dandelion(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Dandelion";
	 m_type = DANDELION;
	 m_base_yield.m_tech = 5;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 1;
	 m_level = 1;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetNatura(spaces, loc, yield, 4);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 8);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder);
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Dandelion* Clone() const {return new Dandelion(*this);}
};

class Great_Dandelion : public Dandelion
{
   public:
      Great_Dandelion()
      {
	 Create();
      }

      Great_Dandelion(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Dandelion";
	 m_type = DANDELION;
	 m_base_yield.m_tech = 10;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
	 m_level = 2;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Dandelion::GetNatura(spaces, loc, yield, 8);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Dandelion::GetYield(spaces, loc, yield, 16);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_Dandelion* Clone() const {return new Great_Dandelion(*this);}
};

class Superior_Dandelion : public Dandelion
{
   public:
      Superior_Dandelion()
      {
	 Create();
      }

      Superior_Dandelion(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Dandelion";
	 m_type = DANDELION;
	 m_base_yield.m_tech = 20;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 3;
	 m_level = 3;
      }

     
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Dandelion::GetNatura(spaces, loc, yield, 16);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Dandelion::GetYield(spaces, loc, yield, 28);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_Dandelion* Clone() const {return new Superior_Dandelion(*this);}
};

class Nightshade : public Plant
{
   public:
      Nightshade()
      {
	 Create();
      }

      Nightshade(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Nightshade";
	 m_type = NIGHTSHADE;
	 m_base_yield.m_tech = 5;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 2;
	 m_level = 1;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetNatura(spaces, loc, yield, 7);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 15);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder);
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Nightshade* Clone() const {return new Nightshade(*this);}
};

class Great_Nightshade : public Nightshade
{
   public:
      Great_Nightshade()
      {
	 Create();
      }

      Great_Nightshade(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Nightshade";
	 m_type = NIGHTSHADE;
	 m_base_yield.m_tech = 10;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Nightshade::GetNatura(spaces, loc, yield, 10);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Nightshade::GetYield(spaces, loc, yield, 25);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Great_Nightshade* Clone() const {return new Great_Nightshade(*this);}
};

class Superior_Nightshade : public Nightshade
{
   public:
      Superior_Nightshade()
      {
	 Create();
      }

      Superior_Nightshade(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Nightshade";
	 m_type = NIGHTSHADE;
	 m_base_yield.m_tech = 20;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Nightshade::GetNatura(spaces, loc, yield, 16);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Nightshade::GetYield(spaces, loc, yield, 50);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_Nightshade* Clone() const {return new Superior_Nightshade(*this);}
};

class Foxglove : public Plant
{
   public:
      Foxglove()
      {
	 Create();
      }

      Foxglove(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Foxglove";
	 m_type = FOXGLOVE;
	 m_base_yield.m_tech = 6;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 3;
	 m_level = 1;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2.0);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier);
      Foxglove* Clone() const {return new Foxglove(*this);}
};

class Great_Foxglove : public Foxglove
{
   public:
      Great_Foxglove()
      {
	 Create();
      }

      Great_Foxglove(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Foxglove";
	 m_type = FOXGLOVE;
	 m_base_yield.m_tech = 12;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 4;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Foxglove::GetYield(spaces, loc, yield, 2.5);
      }
      Great_Foxglove* Clone() const {return new Great_Foxglove(*this);}
};

class Superior_Foxglove : public Foxglove
{
   public:
      Superior_Foxglove()
      {
	 Create();
      }

      Superior_Foxglove(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Foxglove";
	 m_type = FOXGLOVE;
	 m_base_yield.m_tech = 24;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Foxglove::GetYield(spaces, loc, yield, 3.0);
      }
      void GetUpgrades(biome_t biome, SourceList &upgrades) const;
      Superior_Foxglove* Clone() const {return new Superior_Foxglove(*this);}
   protected:
      static const double m_tech_multiplier;
};

class Sunflower : public Plant
{
   public:
      Sunflower()
      {
	 Create();
      }

      Sunflower(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Sunflower";
	 m_type = SUNFLOWER;
	 m_base_yield.m_tech = 22;
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 7;
	 m_level = 3;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Sunflower* Clone() const {return new Sunflower(*this);}
};
#endif
