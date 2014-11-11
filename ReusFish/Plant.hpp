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
   protected:
      void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = yield.m_natura_range;
	 AddInRange(spaces, loc, yield, yield_adder, type1, type2, type3, true);
	 yield.m_range = saved_range;
      }
      void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddIfInNaturaRange(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddIfInNaturaRange(spaces, loc, yield, yield_adder, type1, type1, type1);
      }
      void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2, source_type_t type3)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = yield.m_natura_range;
	 AddIfInNaturaRange(spaces, loc, yield, yield_adder, type1, type2, type3);
	 yield.m_range = saved_range;
      }
      void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1, source_type_t type2)
      {
	 AddAllInNaturaRange(spaces, loc, yield, yield_adder, type1, type2, type2);
      }
      void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    const Yield &yield_adder, source_type_t type1)
      {
	 AddAllInNaturaRange(spaces, loc, yield, yield_adder, type1, type1, type1);
      }
      void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = yield.m_natura_range;
	 AddInRange(spaces, loc, yield, yield_adder, source_class, false);
	 yield.m_range = saved_range;
      }
      void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
			      const Yield &yield_adder, source_class_t source_class)
      {
	 unsigned saved_range = yield.m_range;
	 yield.m_range = yield.m_natura_range;
	 AddInRange(spaces, loc, yield, yield_adder, source_class, true);
	 yield.m_range = saved_range;
      }
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(APPLE_TREE, Aspects::LESSER_FRUIT);
         AddUpgrade(STRAWBERRY, Aspects::LESSER_LEAF);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 10);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PEAR_TREE, Aspects::POTENT_FRUIT);
         AddUpgrade(CHERRY_TREE, Aspects::GREATER_GROWTH);
         AddUpgrade(PLUM_TREE, Aspects::GREATER_LEAF);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 3, 5);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PEAR_TREE, Aspects::POTENT_FRUIT);
         AddUpgrade(CHERRY_TREE, Aspects::GREATER_GROWTH);
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
      Great_AppleTree* Clone() const {return new Great_AppleTree(*this);}
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
	 AddUpgrades();
      }

	        void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGE_TREE, Aspects::SUBLIME_FRUIT);
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

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGE_TREE, Aspects::SUBLIME_FRUIT);
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
	 AddUpgrades();
      }
	  
      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGE_TREE, Aspects::SUBLIME_FRUIT);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGE_TREE, Aspects::SUBLIME_FRUIT);
         AddUpgrade(SUNFLOWER, Aspects::SUBLIME_TOXIC);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(STRAWBERRY, Aspects::LESSER_GROWTH);
         AddUpgrade(NIGHTSHADE, Aspects::LESSER_TOXIC);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(FOXGLOVE, Aspects::POTENT_TOXIC);
         AddUpgrade(PLUM_TREE, Aspects::GREATER_LEAF);
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SUNFLOWER, Aspects::SUBLIME_TOXIC);
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
      Superior_Foxglove* Clone() const {return new Superior_Foxglove(*this);}
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
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Sunflower* Clone() const {return new Sunflower(*this);}
};

class WitheredShrub : public Plant
{
   public:
      WitheredShrub()
      {
         Create();
      }

      WitheredShrub(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Withered Shrub";
         m_type = WITHERED_SHRUB;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(AGAVE, Aspects::LESSER_GROWTH, Aspects::LESSER_FRUIT);
         AddUpgrade(BARREL_CACTUS, Aspects::LESSER_LEAF, Aspects::LESSER_TOXIC);
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 1);
      }
      WitheredShrub* Clone() const {return new WitheredShrub(*this);}
};

class Great_WitheredShrub : public WitheredShrub
{
   public:
      Great_WitheredShrub()
      {
         Create();
      }

      Great_WitheredShrub(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Withered Shrub";
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WitheredShrub::GetNatura(spaces, loc, yield, 9);
      }
      Great_WitheredShrub* Clone() const {return new Great_WitheredShrub(*this);}
};

class Superior_WitheredShrub : public WitheredShrub
{
   public:
      Superior_WitheredShrub()
      {
         Create();
      }

      Superior_WitheredShrub(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Withered Shrub";
         m_level = 3;
      }

      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WitheredShrub::GetNatura(spaces, loc, yield, 18);
      }
      Superior_WitheredShrub* Clone() const {return new Superior_WitheredShrub(*this);}
};

class Agave : public Plant
{
   public:
      Agave()
      {
         Create();
      }

      Agave(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Agave";
         m_type = AGAVE;
	 m_base_yield.m_food = 5;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(DATE_PALM, Aspects::POTENT_FRUIT);
         AddUpgrade(DESERT_LIME, Aspects::GREATER_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 10);
      }
      Agave* Clone() const {return new Agave(*this);}
};

class Great_Agave : public Agave
{
   public:
      Great_Agave()
      {
         Create();
      }

      Great_Agave(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Agave";
	 m_base_yield.m_food = 10;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Agave::GetYield(spaces, loc, yield, 20);
      }
      Great_Agave* Clone() const {return new Great_Agave(*this);}
};

class Superior_Agave : public Agave
{
   public:
      Superior_Agave()
      {
         Create();
      }

      Superior_Agave(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Agave";
	 m_base_yield.m_food = 20;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Agave::GetYield(spaces, loc, yield, 40);
      }
      Superior_Agave* Clone() const {return new Superior_Agave(*this);}
};

class BarrelCactus : public Plant
{
   public:
      BarrelCactus()
      {
         Create();
      }

      BarrelCactus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Barrel Cactus";
         m_type = BARREL_CACTUS;
	 m_base_yield.m_tech   = 2;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ALOE_VERA, Aspects::POTENT_LEAF);
         AddUpgrade(CHILLI_PEPPER, Aspects::GREATER_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_wealth_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 8, 5);
      }
      BarrelCactus* Clone() const {return new BarrelCactus(*this);}
};

class Great_BarrelCactus : public BarrelCactus
{
   public:
      Great_BarrelCactus()
      {
         Create();
      }

      Great_BarrelCactus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Barrel Cactus";
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         BarrelCactus::GetYield(spaces, loc, yield, 20, 10);
      }
      Great_BarrelCactus* Clone() const {return new Great_BarrelCactus(*this);}
};

class Superior_BarrelCactus : public BarrelCactus
{
   public:
      Superior_BarrelCactus()
      {
         Create();
      }

      Superior_BarrelCactus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Barrel Cactus";
	 m_base_yield.m_tech   = 20;
	 m_base_yield.m_natura = 16;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         BarrelCactus::GetYield(spaces, loc, yield, 40, 15);
      }
      Superior_BarrelCactus* Clone() const {return new Superior_BarrelCactus(*this);}
};

class DatePalm : public Plant
{
   public:
      DatePalm()
      {
         Create();
      }

      DatePalm(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Date Palm";
         m_type = DATE_PALM;
	 m_base_yield.m_food   = 5;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(CARDON_CACTUS, Aspects::SUBLIME_GROWTH, Aspects::SUBLIME_FRUIT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 8);
      }
      DatePalm* Clone() const {return new DatePalm(*this);}
};

class Great_DatePalm : public DatePalm
{
   public:
      Great_DatePalm()
      {
         Create();
      }

      Great_DatePalm(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Date Palm";
	 m_base_yield.m_food   = 12;
	 m_base_yield.m_natura = 7;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DatePalm::GetYield(spaces, loc, yield, 16);
      }
      Great_DatePalm* Clone() const {return new Great_DatePalm(*this);}
};

class Superior_DatePalm : public DatePalm
{
   public:
      Superior_DatePalm()
      {
         Create();
      }

      Superior_DatePalm(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Date Palm";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_natura = 12;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DatePalm::GetYield(spaces, loc, yield, 32);
      }
      Superior_DatePalm* Clone() const {return new Superior_DatePalm(*this);}
};

class AloeVera : public Plant
{
   public:
      AloeVera()
      {
         Create();
      }

      AloeVera(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Aloe Vera";
         m_type = ALOE_VERA;
	 m_base_yield.m_tech   = 5;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(OPIUM_POPPY, Aspects::SUBLIME_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 5, 5);
      }
      AloeVera* Clone() const {return new AloeVera(*this);}
};

class Great_AloeVera : public AloeVera
{
   public:
      Great_AloeVera()
      {
         Create();
      }

      Great_AloeVera(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Aloe Vera";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         AloeVera::GetYield(spaces, loc, yield, 10, 8);
      }
      Great_AloeVera* Clone() const {return new Great_AloeVera(*this);}
};

class Superior_AloeVera : public AloeVera
{
   public:
      Superior_AloeVera()
      {
         Create();
      }

      Superior_AloeVera(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Aloe Vera";
	 m_base_yield.m_food   = 40;
	 m_base_yield.m_natura = 12;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         AloeVera::GetYield(spaces, loc, yield, 20, 12);
      }
      Superior_AloeVera* Clone() const {return new Superior_AloeVera(*this);}
};

class DesertLime : public Plant
{
   public:
      DesertLime()
      {
         Create();
      }

      DesertLime(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Desert Lime";
         m_type = DESERT_LIME;
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(CARDON_CACTUS, Aspects::SUBLIME_GROWTH, Aspects::SUBLIME_FRUIT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned m_tech_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 35, 15, 15);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 5);
      }
      DesertLime* Clone() const {return new DesertLime(*this);}
};

class Great_DesertLime : public DesertLime
{
   public:
      Great_DesertLime()
      {
         Create();
      }

      Great_DesertLime(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Desert Lime";
	 m_base_yield.m_food   = 30;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DesertLime::GetYield(spaces, loc, yield, 50, 25, 30);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DesertLime::GetNatura(spaces, loc, yield, 8);
      }
      Great_DesertLime* Clone() const {return new Great_DesertLime(*this);}
};

class ChilliPepper : public Plant
{
   public:
      ChilliPepper()
      {
         Create();
      }

      ChilliPepper(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Chilli Pepper";
         m_type = CHILLI_PEPPER;
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_tech   = 8;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(OPIUM_POPPY, Aspects::SUBLIME_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 20, 20);
      }
      ChilliPepper* Clone() const {return new ChilliPepper(*this);}
};

class Great_ChilliPepper : public ChilliPepper
{
   public:
      Great_ChilliPepper()
      {
         Create();
      }

      Great_ChilliPepper(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Chilli Pepper";
	 m_base_yield.m_food   = 16;
	 m_base_yield.m_tech   = 16;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         ChilliPepper::GetYield(spaces, loc, yield, 40, 40);
      }
      Great_ChilliPepper* Clone() const {return new Great_ChilliPepper(*this);}
};

class CardonCactus : public Plant
{
   public:
      CardonCactus()
      {
         Create();
      }

      CardonCactus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Cardon Cactus";
         m_type = CARDON_CACTUS;
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      CardonCactus* Clone() const {return new CardonCactus(*this);}
};

class OpiumPoppy : public Plant
{
   public:
      OpiumPoppy()
      {
         Create();
      }

      OpiumPoppy(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Opium Poppy";
         m_type = OPIUM_POPPY;
	 m_base_yield.m_tech   = 30;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      OpiumPoppy* Clone() const {return new OpiumPoppy(*this);}
};

class Elderberry : public Plant
{
   public:
      Elderberry()
      {
         Create();
      }

      Elderberry(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Elderberry";
         m_type = ELDERBERRY;
	 m_base_yield.m_food   = 5;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(TOMATO, Aspects::LESSER_LEAF);
         AddUpgrade(PINEAPPLE, Aspects::LESSER_FRUIT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 7);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 3);
      }
      Elderberry* Clone() const {return new Elderberry(*this);}
};

class Great_Elderberry : public Elderberry
{
   public:
      Great_Elderberry()
      {
         Create();
      }

      Great_Elderberry(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Elderberry";
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Elderberry::GetYield(spaces, loc, yield, 15);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Elderberry::GetNatura(spaces, loc, yield, 8);
      }
      Great_Elderberry* Clone() const {return new Great_Elderberry(*this);}
};

class Superior_Elderberry : public Elderberry
{
   public:
      Superior_Elderberry()
      {
         Create();
      }

      Superior_Elderberry(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Elderberry";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Elderberry::GetYield(spaces, loc, yield, 30);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Elderberry::GetNatura(spaces, loc, yield, 12);
      }
      Superior_Elderberry* Clone() const {return new Superior_Elderberry(*this);}
};

class Peppermint : public Plant
{
   public:
      Peppermint()
      {
         Create();
      }

      Peppermint(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Peppermint";
         m_type = PEPPERMINT;
	 m_base_yield.m_tech   = 7;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(TOMATO, Aspects::LESSER_GROWTH);
         AddUpgrade(MARSH_MALLOW, Aspects::LESSER_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 7);
      }
      Peppermint* Clone() const {return new Peppermint(*this);}
};

class Great_Peppermint : public Peppermint
{
   public:
      Great_Peppermint()
      {
         Create();
      }

      Great_Peppermint(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Peppermint";
	 m_base_yield.m_tech   = 12;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Peppermint::GetYield(spaces, loc, yield, 14);
      }
      Great_Peppermint* Clone() const {return new Great_Peppermint(*this);}
};

class Superior_Peppermint : public Peppermint
{
   public:
      Superior_Peppermint()
      {
         Create();
      }

      Superior_Peppermint(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Peppermint";
	 m_base_yield.m_tech   = 24;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Peppermint::GetYield(spaces, loc, yield, 28);
      }
      Superior_Peppermint* Clone() const {return new Superior_Peppermint(*this);}
};

class Tomato : public Plant
{
   public:
      Tomato()
      {
         Create();
      }

      Tomato(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Tomato";
         m_type = TOMATO;
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_tech   = 2;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(WHITE_WILLOW, Aspects::POTENT_LEAF);
         AddUpgrade(COFFEA, Aspects::GREATER_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 0.5);
      }
      Tomato* Clone() const {return new Tomato(*this);}
};

class Great_Tomato : public Tomato
{
   public:
      Great_Tomato()
      {
         Create();
      }

      Great_Tomato(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Tomato";
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_tech   = 2;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Tomato::GetYield(spaces, loc, yield, 1.0);
      }
      Great_Tomato* Clone() const {return new Great_Tomato(*this);}
};

class Superior_Tomato : public Tomato
{
   public:
      Superior_Tomato()
      {
         Create();
      }

      Superior_Tomato(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Tomato";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_tech   = 4;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Tomato::GetYield(spaces, loc, yield, 1.5);
      }
      Superior_Tomato* Clone() const {return new Superior_Tomato(*this);}
};

class Pineapple : public Plant
{
   public:
      Pineapple()
      {
         Create();
      }

      Pineapple(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Pineapple";
         m_type = PINEAPPLE;
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PAPAYA, Aspects::POTENT_FRUIT);
         AddUpgrade(COFFEA, Aspects::GREATER_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 14);
      }
      Pineapple* Clone() const {return new Pineapple(*this);}
};

class Great_Pineapple : public Pineapple
{
   public:
      Great_Pineapple()
      {
         Create();
      }

      Great_Pineapple(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Pineapple";
	 m_base_yield.m_food   = 14;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Pineapple::GetYield(spaces, loc, yield, 28);
      }
      Great_Pineapple* Clone() const {return new Great_Pineapple(*this);}
};

class Superior_Pineapple : public Pineapple
{
   public:
      Superior_Pineapple()
      {
         Create();
      }

      Superior_Pineapple(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Pineapple";
	 m_base_yield.m_food   = 28;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Pineapple::GetYield(spaces, loc, yield, 42);
      }
      Superior_Pineapple* Clone() const {return new Superior_Pineapple(*this);}
};

class Marshmallow : public Plant
{
   public:
      Marshmallow()
      {
         Create();
      }

      Marshmallow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Marshmallow";
         m_type = MARSH_MALLOW;
	 m_base_yield.m_tech   = 4;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(WHITE_WILLOW, Aspects::POTENT_LEAF);
         AddUpgrade(HEMP, Aspects::GREATER_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 15, 10);
      }
      Marshmallow* Clone() const {return new Marshmallow(*this);}
};

class Great_Marshmallow : public Marshmallow
{
   public:
      Great_Marshmallow()
      {
         Create();
      }

      Great_Marshmallow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Marshmallow";
	 m_base_yield.m_tech   = 8;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Marshmallow::GetYield(spaces, loc, yield, 30, 20);
      }
      Great_Marshmallow* Clone() const {return new Great_Marshmallow(*this);}
};

class Superior_Marshmallow : public Marshmallow
{
   public:
      Superior_Marshmallow()
      {
         Create();
      }

      Superior_Marshmallow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Marshmallow";
	 m_base_yield.m_tech   = 16;
	 m_base_yield.m_natura = 14;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Marshmallow::GetYield(spaces, loc, yield, 60, 40);
      }
      Superior_Marshmallow* Clone() const {return new Superior_Marshmallow(*this);}
};

class Papaya : public Plant
{
   public:
      Papaya()
      {
         Create();
      }

      Papaya(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Papaya";
         m_type = PAPAYA;
	 m_base_yield.m_food   = 6;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(CACAO_TREE, Aspects::SUBLIME_GROWTH, Aspects::SUBLIME_FRUIT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, int m_natura_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 15, 5, 8);
      }
      Papaya* Clone() const {return new Papaya(*this);}
};

class Great_Papaya : public Papaya
{
   public:
      Great_Papaya()
      {
         Create();
      }

      Great_Papaya(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Papaya";
	 m_base_yield.m_food   = 12;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Papaya::GetYield(spaces, loc, yield, 30, 10, 14);
      }
      Great_Papaya* Clone() const {return new Great_Papaya(*this);}
};

class Superior_Papaya : public Papaya
{
   public:
      Superior_Papaya()
      {
         Create();
      }

      Superior_Papaya(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Papaya";
	 m_base_yield.m_food   = 24;
	 m_base_yield.m_natura = 12;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Papaya::GetYield(spaces, loc, yield, 60, 15, 22);
      }
      Superior_Papaya* Clone() const {return new Superior_Papaya(*this);}
};

class WhiteWillow : public Plant
{
   public:
      WhiteWillow()
      {
         Create();
      }

      WhiteWillow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "White Willow";
         m_type = WHITE_WILLOW;
	 m_base_yield.m_tech   = 8;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(RUBBER_TREE, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 6);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 2);
      }
      WhiteWillow* Clone() const {return new WhiteWillow(*this);}
};

class Great_WhiteWillow : public WhiteWillow
{
   public:
      Great_WhiteWillow()
      {
         Create();
      }

      Great_WhiteWillow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great White Willow";
	 m_base_yield.m_tech   = 12;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WhiteWillow::GetYield(spaces, loc, yield, 16);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WhiteWillow::GetNatura(spaces, loc, yield, 3);
      }
      Great_WhiteWillow* Clone() const {return new Great_WhiteWillow(*this);}
};

class Superior_WhiteWillow : public WhiteWillow
{
   public:
      Superior_WhiteWillow()
      {
         Create();
      }

      Superior_WhiteWillow(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior White Willow";
	 m_base_yield.m_tech   = 24;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WhiteWillow::GetYield(spaces, loc, yield, 32);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         WhiteWillow::GetNatura(spaces, loc, yield, 4);
	 AddAllInNaturaRange(spaces, loc, yield, Yield(0,0,0,0,0,4), WHITE_WILLOW);
      }
      Superior_WhiteWillow* Clone() const {return new Superior_WhiteWillow(*this);}
};

class Coffea : public Plant
{
   public:
      Coffea()
      {
         Create();
      }

      Coffea(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Coffea";
         m_type = COFFEA;
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_tech   = 8;
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(CACAO_TREE, Aspects::SUBLIME_GROWTH, Aspects::SUBLIME_FRUIT);
         AddUpgrade(RUBBER_TREE, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_food_adder, unsigned m_tech_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 1, 10, 10);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 5);
      }
      Coffea* Clone() const {return new Coffea(*this);}
};

class Great_Coffea : public Coffea
{
   public:
      Great_Coffea()
      {
         Create();
      }

      Great_Coffea(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Coffea";
	 m_base_yield.m_food   = 30;
	 m_base_yield.m_tech   = 16;
	 m_base_yield.m_natura = 10;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Coffea::GetYield(spaces, loc, yield, 2, 20, 20);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Coffea::GetNatura(spaces, loc, yield, 10);
      }
      Great_Coffea* Clone() const {return new Great_Coffea(*this);}
};

class Hemp : public Plant
{
   public:
      Hemp()
      {
         Create();
      }

      Hemp(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Hemp";
         m_type = HEMP;
	 m_base_yield.m_tech   = 8;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(RUBBER_TREE, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_tech_adder, unsigned m_awe_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 1, 15, 10);
      }
      Hemp* Clone() const {return new Hemp(*this);}
};

class Great_Hemp : public Hemp
{
   public:
      Great_Hemp()
      {
         Create();
      }

      Great_Hemp(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Hemp";
	 m_base_yield.m_tech   = 16;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Hemp::GetYield(spaces, loc, yield, 2, 25, 12);
      }
      Great_Hemp* Clone() const {return new Great_Hemp(*this);}
};

class CacaoTree : public Plant
{
   public:
      CacaoTree()
      {
         Create();
      }

      CacaoTree(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Cacao Tree";
         m_type = CACAO_TREE;
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_natura = 12;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      CacaoTree* Clone() const {return new CacaoTree(*this);}
};

class RubberTree : public Plant
{
   public:
      RubberTree()
      {
         Create();
      }

      RubberTree(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Rubber Tree";
         m_type = RUBBER_TREE;
	 m_base_yield.m_tech   = 25;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      RubberTree* Clone() const {return new RubberTree(*this);}
};

class Kumquat : public Plant
{
   public:
      Kumquat()
      {
         Create();
      }

      Kumquat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Kumquat";
         m_type = KUMQUAT;
	 m_base_yield.m_food   = 5;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(DRAGONFRUIT, Aspects::LESSER_FRUIT, Aspects::LESSER_TOXIC);
         AddUpgrade(KIWIFRUIT, Aspects::POTENT_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 8, 3);
      }
      Kumquat* Clone() const {return new Kumquat(*this);}
};

class Great_Kumquat : public Kumquat
{
   public:
      Great_Kumquat()
      {
         Create();
      }

      Great_Kumquat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Kumquat";
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Kumquat::GetYield(spaces, loc, yield, 10, 7);
      }
      Great_Kumquat* Clone() const {return new Great_Kumquat(*this);}
};

class Superior_Kumquat : public Kumquat
{
   public:
      Superior_Kumquat()
      {
         Create();
      }

      Superior_Kumquat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Kumquat";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Kumquat::GetYield(spaces, loc, yield, 20, 14);
      }
      Superior_Kumquat* Clone() const {return new Superior_Kumquat(*this);}
};

class Ginger : public Plant
{
   public:
      Ginger()
      {
         Create();
      }

      Ginger(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Ginger";
         m_type = GINGER;
	 m_base_yield.m_tech   = 5;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(DRAGONFRUIT, Aspects::LESSER_FRUIT, Aspects::LESSER_TOXIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 10);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, 5);
      }
      Ginger* Clone() const {return new Ginger(*this);}
};

class Great_Ginger : public Ginger
{
   public:
      Great_Ginger()
      {
         Create();
      }

      Great_Ginger(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Ginger";
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_natura = 6;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Ginger::GetYield(spaces, loc, yield, 20);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Ginger::GetNatura(spaces, loc, yield, 9);
      }
      Great_Ginger* Clone() const {return new Great_Ginger(*this);}
};

class Superior_Ginger : public Ginger
{
   public:
      Superior_Ginger()
      {
         Create();
      }

      Superior_Ginger(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Ginger";
	 m_base_yield.m_tech   = 20;
	 m_base_yield.m_natura = 5;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Ginger::GetYield(spaces, loc, yield, 40);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Ginger::GetNatura(spaces, loc, yield, 12);
      }
      Superior_Ginger* Clone() const {return new Superior_Ginger(*this);}
};

class Dragonfruit : public Plant
{
   public:
      Dragonfruit()
      {
         Create();
      }

      Dragonfruit(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Dragonfruit";
         m_type = DRAGONFRUIT;
	 m_base_yield.m_food   = 4;
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(LYCHEE, Aspects::GREATER_FRUIT);
         AddUpgrade(CINNAMOMUM, Aspects::GREATER_GROWTH);
         AddUpgrade(TEA_PLANT, Aspects::GREATER_LEAF);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, double m_awe_multiplier);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 2.0, 1.0);
      }
      Dragonfruit* Clone() const {return new Dragonfruit(*this);}
};

class Great_Dragonfruit : public Dragonfruit
{
   public:
      Great_Dragonfruit()
      {
         Create();
      }

      Great_Dragonfruit(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Dragonfruit";
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_tech   = 20;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Dragonfruit::GetYield(spaces, loc, yield, 3.0, 1.5);
      }
      Great_Dragonfruit* Clone() const {return new Great_Dragonfruit(*this);}
};

class Superior_Dragonfruit : public Dragonfruit
{
   public:
      Superior_Dragonfruit()
      {
         Create();
      }

      Superior_Dragonfruit(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Dragonfruit";
	 m_base_yield.m_food   = 16;
	 m_base_yield.m_tech   = 40;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 2;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Dragonfruit::GetYield(spaces, loc, yield, 4.0, 2.0);
      }
      Superior_Dragonfruit* Clone() const {return new Superior_Dragonfruit(*this);}
};

class Kiwifruit : public Plant
{
   public:
      Kiwifruit()
      {
         Create();
      }

      Kiwifruit(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Kiwifruit";
         m_type = KIWIFRUIT;
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_tech   = 5;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(LYCHEE, Aspects::GREATER_FRUIT);
         AddUpgrade(TEA_PLANT, Aspects::GREATER_LEAF);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_tech_adder);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, int m_natura_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 5, 10);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetNatura(spaces, loc, yield, -3);
      }
      Kiwifruit* Clone() const {return new Kiwifruit(*this);}
};

class Great_Kiwifruit : public Kiwifruit
{
   public:
      Great_Kiwifruit()
      {
         Create();
      }

      Great_Kiwifruit(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Kiwifruit";
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_natura = 3;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Kiwifruit::GetYield(spaces, loc, yield, 10, 20);
      }
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Kiwifruit::GetNatura(spaces, loc, yield, -5);
      }
      Great_Kiwifruit* Clone() const {return new Great_Kiwifruit(*this);}
};

class Lychee : public Plant
{
   public:
      Lychee()
      {
         Create();
      }

      Lychee(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Lychee";
         m_type = LYCHEE;
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_natura = 4;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GINKGO, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_animal_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 18, 2);
      }
      Lychee* Clone() const {return new Lychee(*this);}
};

class Great_Lychee : public Lychee
{
   public:
      Great_Lychee()
      {
         Create();
      }

      Great_Lychee(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Lychee";
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_natura = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Lychee::GetYield(spaces, loc, yield, 27, 4);
      }
      Great_Lychee* Clone() const {return new Great_Lychee(*this);}
};

class Cinnamomum : public Plant
{
   public:
      Cinnamomum()
      {
         Create();
      }

      Cinnamomum(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Cinnamomum";
         m_type = CINNAMOMUM;
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_wealth = 15;
	 m_base_yield.m_natura = 1;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GINKGO, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_wealth_multiplier, unsigned m_plant_food_adder, unsigned m_plant_adjacent_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 0.6, 5, 20);
      }
      Cinnamomum* Clone() const {return new Cinnamomum(*this);}
};

class Great_Cinnamomum : public Cinnamomum
{
   public:
      Great_Cinnamomum()
      {
         Create();
      }

      Great_Cinnamomum(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Cinnamomum";
	 m_base_yield.m_food   = 30;
	 m_base_yield.m_wealth = 30;
	 m_base_yield.m_natura = 2;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Cinnamomum::GetYield(spaces, loc, yield, 0.75, 8, 40);
      }
      Great_Cinnamomum* Clone() const {return new Great_Cinnamomum(*this);}
};

class TeaPlant : public Plant
{
   public:
      TeaPlant()
      {
         Create();
      }

      TeaPlant(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Tea Plant";
         m_type = TEA_PLANT;
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_awe    = 5;
	 m_base_yield.m_natura = 7;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GINKGO, Aspects::SUBLIME_LEAF, Aspects::SUBLIME_GROWTH);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_tech_adder, int m_natura_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 12, 35, 15);
      }
      TeaPlant* Clone() const {return new TeaPlant(*this);}
};

class Great_TeaPlant : public TeaPlant
{
   public:
      Great_TeaPlant()
      {
         Create();
      }

      Great_TeaPlant(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Tea Plant";
	 m_base_yield.m_tech   = 20;
	 m_base_yield.m_awe    = 10;
	 m_base_yield.m_natura = 14;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         TeaPlant::GetYield(spaces, loc, yield, 25, 70, 25);
      }
      Great_TeaPlant* Clone() const {return new Great_TeaPlant(*this);}
};

class Ginkgo : public Plant
{
   public:
      Ginkgo()
      {
         Create();
      }

      Ginkgo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Ginkgo";
         m_type = GINKGO;
	 m_base_yield.m_food   = 20;
	 m_base_yield.m_tech   = 20;
	 m_base_yield.m_natura = 13;
	 m_base_yield.m_natura_range = 3;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Ginkgo* Clone() const {return new Ginkgo(*this);}
};

#endif
