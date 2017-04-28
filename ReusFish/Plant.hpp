#pragma once

#include <vector>

#include "Space.hpp"
#include "Source.hpp"

class Plant : public Source
{
	public :
		Plant() { m_class = PLANT; m_base_yield.m_natura_range = 2; }
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const 
		{ 
			(void)spaces;
			(void)loc;
			yield = m_base_yield;
			GetAspects(0, yield, YIELD_MASK_NATURA);
		}
		Plant *Clone() const {return new Plant(*this);}
	protected:

		void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3, unsigned max_count = std::numeric_limits<unsigned>::max()) const
		{
			AddInRange(spaces, loc, yield, (int)loc - yield.m_natura_range, loc + yield.m_natura_range,
					yield_adder, mask, type1, type2, type3, type3, type3, type3, type3, max_count);
		}
		void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, unsigned max_count = std::numeric_limits<unsigned>::max()) const
		{
			AddAllInNaturaRange(spaces, loc, yield, yield_adder, mask, type1, type2, type2, max_count);
		}
		void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, unsigned max_count = std::numeric_limits<unsigned>::max()) const
		{
			AddAllInNaturaRange(spaces, loc, yield, yield_adder, mask, type1, type1, type1, max_count);
		}

		void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const
		{
			AddAllInNaturaRange(spaces, loc, yield, yield_adder, mask, type1, type2, type3, 1);
		}
		void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const
		{
			AddIfInNaturaRange(spaces, loc, yield, yield_adder, mask, type1, type2, type2);
		}
		void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const
		{
			AddIfInNaturaRange(spaces, loc, yield, yield_adder, mask, type1, type1, type1);
		}


		// Source class options
		void AddAllInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class, unsigned max_count = std::numeric_limits<unsigned>::max()) const
		{
			AddInRange(spaces, loc, yield, (int)loc - yield.m_natura_range, loc + yield.m_natura_range, yield_adder, mask, source_class, max_count);
		}

		void AddIfInNaturaRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const
		{
			AddAllInNaturaRange(spaces, loc, yield, yield_adder, mask, source_class, 1);
		}
};

class Blueberry : public Plant
{
	public:
		Blueberry()
		{
			Create();
		}

		Blueberry(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 10, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		Blueberry* Clone() const {return new Blueberry(*this);}
};

class Great_Blueberry : public Blueberry
{
	public:
		Great_Blueberry()
		{
			Create();
		}

		Great_Blueberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Blueberry";
			m_base_yield.m_food = 10;
			m_base_yield.m_natura = 2;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Blueberry::GetYield(spaces, loc, yield, 20, mask);
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

		Superior_Blueberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Blueberry";
			m_base_yield.m_food = 20;
			m_base_yield.m_natura = 3;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Blueberry::GetYield(spaces, loc, yield, 40, mask);
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

		Strawberry(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 3, 5, mask);
		}
		Strawberry* Clone() const {return new Strawberry(*this);}
};

class Great_Strawberry : public Strawberry
{
	public:
		Great_Strawberry()
		{
			Create();
		}

		Great_Strawberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Strawberry";
			m_base_yield.m_food = 10;
			m_base_yield.m_tech = 6;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Strawberry::GetYield(spaces, loc, yield, 15, 10, mask);
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

		Superior_Strawberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Strawberry";
			m_base_yield.m_food = 20;
			m_base_yield.m_tech = 8;
			m_base_yield.m_natura = 9;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Strawberry::GetYield(spaces, loc, yield, 30, 25, mask);
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

		AppleTree(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			GetNatura(spaces, loc, yield, 2);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 8, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		AppleTree* Clone() const {return new AppleTree(*this);}
};

class Great_AppleTree : public AppleTree
{
	public:
		Great_AppleTree()
		{
			Create();
		}

		Great_AppleTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.AppleTree";
			m_base_yield.m_food = 10;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			AppleTree::GetNatura(spaces, loc, yield, 4);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			AppleTree::GetYield(spaces, loc, yield, 16, mask);
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

		Superior_AppleTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.AppleTree";
			m_base_yield.m_food = 20;
			m_base_yield.m_natura = 8;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			AppleTree::GetNatura(spaces, loc, yield, 8);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			AppleTree::GetYield(spaces, loc, yield, 32, mask);
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

		PearTree(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 10, 5, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		PearTree* Clone() const {return new PearTree(*this);}
};

class Great_PearTree : public PearTree
{
	public:
		Great_PearTree()
		{
			Create();
		}

		Great_PearTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.PearTree";
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			PearTree::GetYield(spaces, loc, yield, 20, 10, mask);
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

		Superior_PearTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.PearTree";
			m_base_yield.m_food = 20;
			m_base_yield.m_natura = 4;
			m_max_aspects = 5;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			PearTree::GetYield(spaces, loc, yield, 40, 15, mask);
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

		CherryTree(const std::vector<Aspects::aspect_t>  &aspects)
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
			AddUpgrade(OAK, Aspects::SUBLIME_GROWTH);
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 15, 10, 20, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
				unsigned m_mineral_food_adder, unsigned m_silver_food_adder, unsigned m_gold_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		CherryTree* Clone() const {return new CherryTree(*this);}
};

class Great_CherryTree : public CherryTree
{
	public:
		Great_CherryTree()
		{
			Create();
		}

		Great_CherryTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.CherryTree";
			m_base_yield.m_food = 20;
			m_base_yield.m_natura = 2;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			CherryTree::GetYield(spaces, loc, yield, 30, 25, 50, mask);
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

		PlumTree(const std::vector<Aspects::aspect_t>  &aspects)
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
			AddUpgrade(OAK, Aspects::SUBLIME_GROWTH, Aspects::SUBLIME_GROWTH);
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			GetNatura(spaces, loc, yield, 12);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 10, 20, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;

		PlumTree* Clone() const {return new PlumTree(*this);}
};

class Great_PlumTree : public PlumTree
{
	public:
		Great_PlumTree()
		{
			Create();
		}

		Great_PlumTree(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.PlumTree";
			m_base_yield.m_food = 30;
			m_base_yield.m_tech = 30;
			m_base_yield.m_natura = 10;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			PlumTree::GetNatura(spaces, loc, yield, 25);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			PlumTree::GetYield(spaces, loc, yield, 24, 50, mask);
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

		OrangeTree(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		OrangeTree* Clone() const {return new OrangeTree(*this);}
};

class Dandelion : public Plant
{
	public:
		Dandelion()
		{
			Create();
		}

		Dandelion(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			GetNatura(spaces, loc, yield, 4);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 8, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		Dandelion* Clone() const {return new Dandelion(*this);}
};

class Great_Dandelion : public Dandelion
{
	public:
		Great_Dandelion()
		{
			Create();
		}

		Great_Dandelion(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Dandelion";
			m_base_yield.m_tech = 10;
			m_base_yield.m_natura = 4;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Dandelion::GetNatura(spaces, loc, yield, 8);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Dandelion::GetYield(spaces, loc, yield, 16, mask);
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

		Superior_Dandelion(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Dandelion";
			m_base_yield.m_tech = 20;
			m_base_yield.m_natura = 8;
			m_max_aspects = 3;
			m_level = 3;
		}


		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Dandelion::GetNatura(spaces, loc, yield, 16);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Dandelion::GetYield(spaces, loc, yield, 28, mask);
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

		Nightshade(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			GetNatura(spaces, loc, yield, 7);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 15, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		Nightshade* Clone() const {return new Nightshade(*this);}
};

class Great_Nightshade : public Nightshade
{
	public:
		Great_Nightshade()
		{
			Create();
		}

		Great_Nightshade(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Nightshade";
			m_base_yield.m_tech = 10;
			m_base_yield.m_natura = 4;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Nightshade::GetNatura(spaces, loc, yield, 10);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Nightshade::GetYield(spaces, loc, yield, 25, mask);
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

		Superior_Nightshade(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Nightshade";
			m_base_yield.m_tech = 20;
			m_base_yield.m_natura = 8;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Nightshade::GetNatura(spaces, loc, yield, 16);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Nightshade::GetYield(spaces, loc, yield, 50, mask);
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

		Foxglove(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 2.0, mask);
		}
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned mask = YIELD_MASK_ALL) const;
		Foxglove* Clone() const {return new Foxglove(*this);}
};

class Great_Foxglove : public Foxglove
{
	public:
		Great_Foxglove()
		{
			Create();
		}

		Great_Foxglove(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Foxglove";
			m_base_yield.m_tech = 12;
			m_base_yield.m_natura = 2;
			m_max_aspects = 4;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Foxglove::GetYield(spaces, loc, yield, 2.5, mask);
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

		Superior_Foxglove(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Foxglove";
			m_base_yield.m_tech = 24;
			m_base_yield.m_natura = 3;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Foxglove::GetYield(spaces, loc, yield, 3.0, mask);
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

		Sunflower(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Sunflower* Clone() const {return new Sunflower(*this);}
};

class WitheredShrub : public Plant
{
	public:
		WitheredShrub()
		{
			Create();
		}

		WitheredShrub(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_WitheredShrub(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Withered Shrub";
			m_base_yield.m_natura = 5;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Superior_WitheredShrub(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Withered Shrub";
			m_base_yield.m_natura = 10;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Agave(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 10, mask);
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

		Great_Agave(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Agave";
			m_base_yield.m_food = 10;
			m_base_yield.m_natura = 4;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Agave::GetYield(spaces, loc, yield, 20, mask);
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

		Superior_Agave(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Agave";
			m_base_yield.m_food = 20;
			m_base_yield.m_natura = 8;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Agave::GetYield(spaces, loc, yield, 40, mask);
		}
		Superior_Agave* Clone() const {return new Superior_Agave(*this);}
};

class BarrelCactus : public Plant
{
	public:
		BarrelCactus() :
			m_post_processed(false)
		{
			Create();
		}

		BarrelCactus(const std::vector<Aspects::aspect_t>  &aspects) :
			m_post_processed(false)
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
			m_post_processed = false;
		}

		void AddUpgrades(void)
		{
			m_upgrades.clear();
			AddUpgrade(ALOE_VERA, Aspects::POTENT_LEAF);
			AddUpgrade(CHILLI_PEPPER, Aspects::GREATER_TOXIC);
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		BarrelCactus* Clone() const {return new BarrelCactus(*this);}

		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
		{
			return PostProcess(spaces, loc, yield, global_yield, 5, 8);
		}
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield, unsigned m_wealth_limit, unsigned m_tech_adder)
		{
			yield.Reset();
			for (auto it = global_yield.begin(); it != global_yield.end(); ++it)
				it->Reset();

			// Only add extra tech once
			if (!m_post_processed && (spaces[loc].m_yield.m_wealth >= m_wealth_limit))
			{
				yield.m_tech += m_tech_adder;
				m_post_processed = true;
				return true; // indicate changed values
			}
			return false; // nothing changed during this call
		}
	protected:
		bool m_post_processed;
};

class Great_BarrelCactus : public BarrelCactus
{
	public:
		Great_BarrelCactus()
		{
			Create();
		}

		Great_BarrelCactus(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Barrel Cactus";
			m_base_yield.m_tech   = 10;
			m_base_yield.m_natura = 8;
			m_max_aspects = 3;
			m_level = 2;
		}

		Great_BarrelCactus* Clone() const {return new Great_BarrelCactus(*this);}
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
		{
			return BarrelCactus::PostProcess(spaces, loc, yield, global_yield, 10, 20);
		}
};

class Superior_BarrelCactus : public BarrelCactus
{
	public:
		Superior_BarrelCactus()
		{
			Create();
		}

		Superior_BarrelCactus(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Barrel Cactus";
			m_base_yield.m_tech   = 20;
			m_base_yield.m_natura = 16;
			m_max_aspects = 4;
			m_level = 3;
		}

		Superior_BarrelCactus* Clone() const {return new Superior_BarrelCactus(*this);}
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield)
		{
			return BarrelCactus::PostProcess(spaces, loc, yield, global_yield, 15, 40);
		}
};

class DatePalm : public Plant
{
	public:
		DatePalm()
		{
			Create();
		}

		DatePalm(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 8, mask);
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

		Great_DatePalm(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Date Palm";
			m_base_yield.m_food   = 12;
			m_base_yield.m_natura = 7;
			m_max_aspects = 4;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			DatePalm::GetYield(spaces, loc, yield, 16, mask);
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

		Superior_DatePalm(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Date Palm";
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 12;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			DatePalm::GetYield(spaces, loc, yield, 32, mask);
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

		AloeVera(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 5, 5, mask);
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

		Great_AloeVera(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Aloe Vera";
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 6;
			m_max_aspects = 4;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			AloeVera::GetYield(spaces, loc, yield, 10, 8, mask);
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

		Superior_AloeVera(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Aloe Vera";
			m_base_yield.m_food   = 40;
			m_base_yield.m_natura = 12;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			AloeVera::GetYield(spaces, loc, yield, 20, 12, mask);
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

		DesertLime(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 35, 15, 15, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_DesertLime(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Desert Lime";
			m_base_yield.m_food   = 30;
			m_base_yield.m_natura = 8;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			DesertLime::GetYield(spaces, loc, yield, 50, 25, 30, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		ChilliPepper(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 20, 20, mask);
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

		Great_ChilliPepper(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Chilli Pepper";
			m_base_yield.m_food   = 16;
			m_base_yield.m_tech   = 16;
			m_base_yield.m_natura = 8;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			ChilliPepper::GetYield(spaces, loc, yield, 40, 40, mask);
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

		CardonCactus(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		CardonCactus* Clone() const {return new CardonCactus(*this);}
};

class OpiumPoppy : public Plant
{
	public:
		OpiumPoppy()
		{
			Create();
		}

		OpiumPoppy(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		OpiumPoppy* Clone() const {return new OpiumPoppy(*this);}
};

class Elderberry : public Plant
{
	public:
		Elderberry()
		{
			Create();
		}

		Elderberry(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 7, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_Elderberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Elderberry";
			m_base_yield.m_food   = 10;
			m_base_yield.m_natura = 4;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Elderberry::GetYield(spaces, loc, yield, 15, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Superior_Elderberry(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Elderberry";
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Elderberry::GetYield(spaces, loc, yield, 30, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Peppermint(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 7, mask);
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

		Great_Peppermint(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Peppermint";
			m_base_yield.m_tech   = 12;
			m_base_yield.m_natura = 3;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Peppermint::GetYield(spaces, loc, yield, 14, mask);
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

		Superior_Peppermint(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Peppermint";
			m_base_yield.m_tech   = 24;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Peppermint::GetYield(spaces, loc, yield, 28, mask);
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

		Tomato(const std::vector<Aspects::aspect_t>  &aspects)
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
			AddUpgrade(BRAZILWOOD, Aspects::SUBLIME_GROWTH);
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 0.5, mask);
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

		Great_Tomato(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Tomato";
			m_base_yield.m_food   = 10;
			m_base_yield.m_tech   = 2;
			m_base_yield.m_natura = 3;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Tomato::GetYield(spaces, loc, yield, 1.0, mask);
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

		Superior_Tomato(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Tomato";
			m_base_yield.m_food   = 20;
			m_base_yield.m_tech   = 4;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Tomato::GetYield(spaces, loc, yield, 1.5, mask);
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

		Pineapple(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 14, mask);
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

		Great_Pineapple(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Pineapple";
			m_base_yield.m_food   = 14;
			m_base_yield.m_natura = 2;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Pineapple::GetYield(spaces, loc, yield, 28, mask);
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

		Superior_Pineapple(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Pineapple";
			m_base_yield.m_food   = 28;
			m_base_yield.m_natura = 4;
			m_max_aspects = 2;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Pineapple::GetYield(spaces, loc, yield, 42, mask);
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

		Marshmallow(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 15, 10, mask);
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

		Great_Marshmallow(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Marshmallow";
			m_base_yield.m_tech   = 8;
			m_base_yield.m_natura = 6;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Marshmallow::GetYield(spaces, loc, yield, 30, 20, mask);
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

		Superior_Marshmallow(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Marshmallow";
			m_base_yield.m_tech   = 16;
			m_base_yield.m_natura = 14;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Marshmallow::GetYield(spaces, loc, yield, 60, 40, mask);
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

		Papaya(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, int m_natura_limit, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 15, 5, 8, mask);
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

		Great_Papaya(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Papaya";
			m_base_yield.m_food   = 12;
			m_base_yield.m_natura = 6;
			m_max_aspects = 4;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Papaya::GetYield(spaces, loc, yield, 30, 10, 14, mask);
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

		Superior_Papaya(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Papaya";
			m_base_yield.m_food   = 24;
			m_base_yield.m_natura = 12;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Papaya::GetYield(spaces, loc, yield, 60, 15, 22, mask);
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

		WhiteWillow(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 6, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_WhiteWillow(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.White Willow";
			m_base_yield.m_tech   = 12;
			m_base_yield.m_natura = 3;
			m_max_aspects = 4;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			WhiteWillow::GetYield(spaces, loc, yield, 16, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Superior_WhiteWillow(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.White Willow";
			m_base_yield.m_tech   = 24;
			m_base_yield.m_natura = 6;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			WhiteWillow::GetYield(spaces, loc, yield, 32, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		Superior_WhiteWillow* Clone() const {return new Superior_WhiteWillow(*this);}
};

class Coffea : public Plant
{
	public:
		Coffea()
		{
			Create();
		}

		Coffea(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_food_adder, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 1, 10, 10, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_Coffea(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Coffea";
			m_base_yield.m_food   = 30;
			m_base_yield.m_tech   = 16;
			m_base_yield.m_natura = 10;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Coffea::GetYield(spaces, loc, yield, 2, 20, 20, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Hemp(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier, unsigned m_tech_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 1, 15, 10, mask);
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

		Great_Hemp(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Hemp";
			m_base_yield.m_tech   = 16;
			m_base_yield.m_natura = 8;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Hemp::GetYield(spaces, loc, yield, 2, 25, 12, mask);
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

		CacaoTree(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		CacaoTree* Clone() const {return new CacaoTree(*this);}
};

class RubberTree : public Plant
{
	public:
		RubberTree()
		{
			Create();
		}

		RubberTree(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		RubberTree* Clone() const {return new RubberTree(*this);}
};

class Kumquat : public Plant
{
	public:
		Kumquat()
		{
			Create();
		}

		Kumquat(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 8, 3, mask);
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

		Great_Kumquat(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Kumquat";
			m_base_yield.m_food   = 10;
			m_base_yield.m_natura = 2;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Kumquat::GetYield(spaces, loc, yield, 10, 7, mask);
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

		Superior_Kumquat(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Kumquat";
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 4;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Kumquat::GetYield(spaces, loc, yield, 20, 14, mask);
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

		Ginger(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 10, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_Ginger(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Ginger";
			m_base_yield.m_tech   = 10;
			m_base_yield.m_natura = 6;
			m_max_aspects = 2;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Ginger::GetYield(spaces, loc, yield, 20, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Superior_Ginger(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Ginger";
			m_base_yield.m_tech   = 20;
			m_base_yield.m_natura = 5;
			m_max_aspects = 3;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Ginger::GetYield(spaces, loc, yield, 40, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Dragonfruit(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, double m_awe_multiplier, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 1.0, 0.5, mask);
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

		Great_Dragonfruit(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Dragonfruit";
			m_base_yield.m_food   = 8;
			m_base_yield.m_tech   = 20;
			m_base_yield.m_natura = 2;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Dragonfruit::GetYield(spaces, loc, yield, 1.5, 0.75, mask);
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

		Superior_Dragonfruit(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Dragonfruit";
			m_base_yield.m_food   = 16;
			m_base_yield.m_tech   = 40;
			m_base_yield.m_natura = 4;
			m_max_aspects = 4;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Dragonfruit::GetYield(spaces, loc, yield, 2.0, 1.0, mask);
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

		Kiwifruit(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_tech_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, int m_natura_adder) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 5, 10, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
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

		Great_Kiwifruit(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Kiwifruit";
			m_base_yield.m_food   = 15;
			m_base_yield.m_tech   = 10;
			m_base_yield.m_natura = 3;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Kiwifruit::GetYield(spaces, loc, yield, 10, 20, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Kiwifruit::GetNatura(spaces, loc, yield, -5);
		}
		Great_Kiwifruit* Clone() const {return new Great_Kiwifruit(*this);}
};

class Superior_Kiwifruit : public Kiwifruit
{
	public:
		Superior_Kiwifruit()
		{
			Create();
		}

		Superior_Kiwifruit(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "S.Kiwifruit";
			m_base_yield.m_food   = 15;
			m_base_yield.m_tech   = 10;
			m_base_yield.m_natura = 3;
			m_max_aspects = 3;
			m_level = 2;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Kiwifruit::GetYield(spaces, loc, yield, 20, 40, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			Kiwifruit::GetNatura(spaces, loc, yield, -7);
		}
		// KCJ Need to add Miner's Fruit
		Superior_Kiwifruit* Clone() const {return new Superior_Kiwifruit(*this);}
};

class Lychee : public Plant
{
	public:
		Lychee()
		{
			Create();
		}

		Lychee(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_animal_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 18, 2, mask);
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

		Great_Lychee(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Lychee";
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 8;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Lychee::GetYield(spaces, loc, yield, 27, 4, mask);
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

		Cinnamomum(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_wealth_multiplier, unsigned m_plant_food_adder, unsigned m_plant_adjacent_food_adder, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 0.6, 5, 20, mask);
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

		Great_Cinnamomum(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Cinnamomum";
			m_base_yield.m_food   = 30;
			m_base_yield.m_wealth = 30;
			m_base_yield.m_natura = 2;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			Cinnamomum::GetYield(spaces, loc, yield, 0.75, 8, 40, mask);
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

		TeaPlant(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_awe_adder, unsigned m_tech_adder, int m_natura_limit, unsigned mask = YIELD_MASK_ALL) const;
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			GetYield(spaces, loc, yield, 12, 35, 15, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			GetNatura(spaces, loc, yield, 15);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, int m_natura_limit) const;
		TeaPlant* Clone() const {return new TeaPlant(*this);}
};

class Great_TeaPlant : public TeaPlant
{
	public:
		Great_TeaPlant()
		{
			Create();
		}

		Great_TeaPlant(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "G.Tea Plant";
			m_base_yield.m_tech   = 20;
			m_base_yield.m_awe    = 10;
			m_base_yield.m_natura = 14;
			m_max_aspects = 5;
			m_level = 3;
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			TeaPlant::GetYield(spaces, loc, yield, 25, 70, 25, mask);
		}
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
		{
			TeaPlant::GetNatura(spaces, loc, yield, 25);
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

		Ginkgo(const std::vector<Aspects::aspect_t>  &aspects)
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		Ginkgo* Clone() const {return new Ginkgo(*this);}
};

class Brazilwood : public Plant
{
	public:
		Brazilwood()
		{
			Create();
		}

		Brazilwood(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "Brazilwood";
			m_type = BRAZILWOOD;
			m_base_yield.m_tech   = 20;
			m_base_yield.m_wealth = 15;
			m_base_yield.m_natura = 8;
			m_max_aspects = 6;
			m_level = 3;
			AddUpgrades();
		}

		void AddUpgrades(void)
		{
			m_upgrades.clear();
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		Brazilwood* Clone() const {return new Brazilwood(*this);}
};

class Oak : public Plant
{
	public:
		Oak()
		{
			Create();
		}

		Oak(const std::vector<Aspects::aspect_t>  &aspects)
		{
			Create();
			m_aspects = aspects;
		}

		void Create(void)
		{
			m_name = "Oak";
			m_type = OAK;
			m_base_yield.m_food   = 20;
			m_base_yield.m_natura = 5;
			m_max_aspects = 7;
			m_level = 3;
			AddUpgrades();
		}

		void AddUpgrades(void)
		{
			m_upgrades.clear();
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Oak* Clone() const {return new Oak(*this);}
};
