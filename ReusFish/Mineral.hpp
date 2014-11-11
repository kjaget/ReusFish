#ifndef MINERAL_INC__
#define MINERAL_INC__

#include <vector>

#include "Space.hpp"
#include "Source.hpp"

class Mineral : public Source
{
   public :
      Mineral() { m_class = MINERAL; }
      Mineral *Clone() const {return new Mineral(*this);}

      void GetUpgrades(biome_t biome, SourceList &upgrades) const
      {
	 Source::GetUpgrades(biome, upgrades);
	 bool changed;

	 do
	 {
	    changed = false;
	    for (SourceList::iterator it = upgrades.begin(); it != upgrades.end(); ++it)
	    {
	       if (!(*it)->IsValidForBiome(biome))
	       {
		  upgrades.erase(it);
		  changed = true;
		  break;
	       }
	    }
	 } while (changed);
	  }

   protected :
      typedef unsigned biome_mask_t;

	 static const biome_mask_t MASK_FOREST   = 1;
	 static const biome_mask_t MASK_DESERT   = 2;
	 static const biome_mask_t MASK_SWAMP    = 4;
	 static const biome_mask_t MASK_MOUNTAIN = 8;

     biome_mask_t m_biome_mask;

      bool IsValidForBiome(biome_t biome) const
      {
	 switch (biome)
	 {
	    case FOREST:
	       return m_biome_mask & MASK_FOREST ? true : false;
	    case DESERT:
	       return m_biome_mask & MASK_DESERT ? true : false;
	    case SWAMP:
	       return m_biome_mask & MASK_SWAMP  ? true : false;
	    case MOUNTAIN :
	       return m_biome_mask & MASK_MOUNTAIN ? true : false;
	 }
	 return false;
      }
};

class Agate: public Mineral
{
   public:
      Agate()
      {
	 Create();
      }

      Agate(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Agate";
	 m_type = AGATE;
	 m_base_yield.m_wealth = 8;
	 m_max_aspects = 1;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_SWAMP;
	 m_level = 1;
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
	 AddUpgrade(SALT, Aspects::LESSER_SEISMIC);
	 AddUpgrade(TOPAZ, Aspects::LESSER_NOBLE);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 GetYield(spaces, loc, yield, 10);
      }
      Agate* Clone() const {return new Agate(*this);}
};

class Great_Agate : public Agate
{
   public:
      Great_Agate()
      {
	 Create();
      }

      Great_Agate(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Agate";
	 m_type = AGATE;
	 m_base_yield.m_wealth = 15;
	 m_max_aspects = 2;
	 m_level = 2;
	 AddUpgrades();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 Agate::GetYield(spaces, loc, yield, 20);
      }
      Great_Agate* Clone() const {return new Great_Agate(*this);}
};

class Superior_Agate : public Agate
{
   public:
      Superior_Agate()
      {
	 Create();
      }

      Superior_Agate(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Agate";
	 m_type = AGATE;
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 3;
	 m_level = 3;
	 AddUpgrades();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 Agate::GetYield(spaces, loc, yield, 30);
      }
      Superior_Agate* Clone() const {return new Superior_Agate(*this);}
};

class Quartz : public Mineral
{
   public:
      Quartz()
      {
         Create();
      }

      Quartz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Quartz";
         m_type = QUARTZ;
	 m_base_yield.m_wealth = 10;
	 m_max_aspects = 1;
	 m_biome_mask = MASK_DESERT;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(TOPAZ, Aspects::LESSER_NOBLE);
         AddUpgrade(SALT, Aspects::LESSER_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 8, 8);
      }
      Quartz* Clone() const {return new Quartz(*this);}
};

class Great_Quartz : public Quartz
{
   public:
      Great_Quartz()
      {
         Create();
      }

      Great_Quartz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Quartz";
	 m_base_yield.m_wealth = 15;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Quartz::GetYield(spaces, loc, yield, 16, 16);
      }
      Great_Quartz* Clone() const {return new Great_Quartz(*this);}
};

class Superior_Quartz : public Quartz
{
   public:
      Superior_Quartz()
      {
         Create();
      }

      Superior_Quartz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Quartz";
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Quartz::GetYield(spaces, loc, yield, 30, 30);
      }
      Superior_Quartz* Clone() const {return new Superior_Quartz(*this);}
};

class Stone : public Mineral
{
   public:
      Stone()
      {
         Create();
      }

      Stone(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Stone";
         m_type = STONE;
	 m_base_yield.m_tech = 8;
	 m_max_aspects = 1;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SALT, Aspects::LESSER_CRYSTAL);
         AddUpgrade(COPPER, Aspects::LESSER_REACTION);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 10);
      }
      Stone* Clone() const {return new Stone(*this);}
};

class Great_Stone : public Stone
{
   public:
      Great_Stone()
      {
         Create();
      }

      Great_Stone(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Stone";
	 m_base_yield.m_tech = 15;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Stone::GetYield(spaces, loc, yield, 20);
      }
      Great_Stone* Clone() const {return new Great_Stone(*this);}
};

class Superior_Stone : public Stone
{
   public:
      Superior_Stone()
      {
         Create();
      }

      Superior_Stone(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Stone";
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Stone::GetYield(spaces, loc, yield, 40);
      }
      Superior_Stone* Clone() const {return new Superior_Stone(*this);}
};

class Marble : public Mineral
{
   public:
      Marble()
      {
         Create();
      }

      Marble(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Marble";
         m_type = MARBLE;
	 m_base_yield.m_tech = 10;
	 m_max_aspects = 1;
	 m_biome_mask = MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SALT, Aspects::LESSER_CRYSTAL);
         AddUpgrade(COPPER, Aspects::LESSER_REACTION, Aspects::LESSER_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 6, 6);
      }
      Marble* Clone() const {return new Marble(*this);}
};

class Great_Marble : public Marble
{
   public:
      Great_Marble()
      {
         Create();
      }

      Great_Marble(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Marble";
	 m_base_yield.m_tech = 15;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Marble::GetYield(spaces, loc, yield, 10, 15);
      }
      Great_Marble* Clone() const {return new Great_Marble(*this);}
};

class Superior_Marble : public Marble
{
   public:
      Superior_Marble()
      {
         Create();
      }

      Superior_Marble(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Marble";
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Marble::GetYield(spaces, loc, yield, 25, 25);
      }
      Superior_Marble* Clone() const {return new Superior_Marble(*this);}
};

class Topaz : public Mineral
{
   public:
      Topaz()
      {
         Create();
      }

      Topaz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Topaz";
         m_type = TOPAZ;
	 m_base_yield.m_wealth = 10;
	 m_max_aspects = 2;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ONYX, Aspects::POTENT_NOBLE);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 12, 5);
      }
      Topaz* Clone() const {return new Topaz(*this);}
};

class Great_Topaz : public Topaz
{
   public:
      Great_Topaz()
      {
         Create();
      }

      Great_Topaz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Topaz";
	 m_base_yield.m_wealth = 15;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Topaz::GetYield(spaces, loc, yield, 25, 10);
      }
      Great_Topaz* Clone() const {return new Great_Topaz(*this);}
};

class Superior_Topaz : public Topaz
{
   public:
      Superior_Topaz()
      {
         Create();
      }

      Superior_Topaz(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Topaz";
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Topaz::GetYield(spaces, loc, yield, 35, 15);
      }
      Superior_Topaz* Clone() const {return new Superior_Topaz(*this);}
};

class Salt : public Mineral
{
   public:
      Salt()
      {
         Create();
      }

      Salt(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Salt";
         m_type = SALT;
	 m_base_yield.m_food   = 5;
	 m_base_yield.m_tech   = 5;
	 m_base_yield.m_wealth = 5;
	 m_max_aspects = 2;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ONYX, Aspects::POTENT_CRYSTAL);
         AddUpgrade(IRON, Aspects::POTENT_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_tech_adder, unsigned m_awe_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 5, 5, 5);
      }
      Salt* Clone() const {return new Salt(*this);}
};

class Great_Salt : public Salt
{
   public:
      Great_Salt()
      {
         Create();
      }

      Great_Salt(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Salt";
	 m_base_yield.m_food   = 10;
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_wealth = 10;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Salt::GetYield(spaces, loc, yield, 10, 10, 10);
      }
      Great_Salt* Clone() const {return new Great_Salt(*this);}
};

class Superior_Salt : public Salt
{
   public:
      Superior_Salt()
      {
         Create();
      }

      Superior_Salt(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Salt";
	 m_base_yield.m_food   = 15;
	 m_base_yield.m_tech   = 15;
	 m_base_yield.m_wealth = 15;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Salt::GetYield(spaces, loc, yield, 20, 20, 15);
      }
      Superior_Salt* Clone() const {return new Superior_Salt(*this);}
};

class Onyx : public Mineral
{
   public:
      Onyx()
      {
         Create();
      }

      Onyx(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Onyx";
         m_type = ONYX;
	 m_base_yield.m_wealth = 14;
	 m_max_aspects = 3;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GOLD, Aspects::GREATER_NOBLE);
         AddUpgrade(SILVER, Aspects::GREATER_SEISMIC);
         AddUpgrade(PLATINUM, Aspects::GREATER_CRYSTAL);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_wealth_multiplier) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 1.5);
      }
      Onyx* Clone() const {return new Onyx(*this);}
};

class Great_Onyx : public Onyx
{
   public:
      Great_Onyx()
      {
         Create();
      }

      Great_Onyx(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Onyx";
	 m_base_yield.m_wealth = 16;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Onyx::GetYield(spaces, loc, yield, 2.0);
      }
      Great_Onyx* Clone() const {return new Great_Onyx(*this);}
};

class Superior_Onyx : public Onyx
{
   public:
      Superior_Onyx()
      {
         Create();
      }

      Superior_Onyx(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Onyx";
	 m_base_yield.m_wealth = 18;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Onyx::GetYield(spaces, loc, yield, 2.5);
      }
      Superior_Onyx* Clone() const {return new Superior_Onyx(*this);}
};

class Copper : public Mineral
{
   public:
      Copper()
      {
         Create();
      }

      Copper(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Copper";
         m_type = COPPER;
	 m_base_yield.m_tech = 10;
	 m_max_aspects = 2;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PHOSPHORUS, Aspects::POTENT_REACTION);
         AddUpgrade(IRON, Aspects::POTENT_REACTION);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_animal_tech_adder, unsigned m_mountain_tech_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 10, 10);
      }
      Copper* Clone() const {return new Copper(*this);}
};

class Great_Copper : public Copper
{
   public:
      Great_Copper()
      {
         Create();
      }

      Great_Copper(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Copper";
	 m_base_yield.m_tech = 15;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Copper::GetYield(spaces, loc, yield, 25, 20);
      }
      Great_Copper* Clone() const {return new Great_Copper(*this);}
};

class Superior_Copper : public Copper
{
   public:
      Superior_Copper()
      {
         Create();
      }

      Superior_Copper(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Copper";
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Copper::GetYield(spaces, loc, yield, 50, 30);
      }
      Superior_Copper* Clone() const {return new Superior_Copper(*this);}
};

class Phosphorus : public Mineral
{
   public:
      Phosphorus()
      {
         Create();
      }

      Phosphorus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Phosphorus";
         m_type = PHOSPHORUS;
	 m_base_yield.m_tech = 10;
	 m_max_aspects = 3;
	 m_biome_mask = MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SILVER, Aspects::GREATER_CRYSTAL);
         AddUpgrade(ALUMINIUM, Aspects::GREATER_REACTION);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_adder, unsigned m_awe_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 10, 5);
      }
      Phosphorus* Clone() const {return new Phosphorus(*this);}
};

class Great_Phosphorus : public Phosphorus
{
   public:
      Great_Phosphorus()
      {
         Create();
      }

      Great_Phosphorus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Phosphorus";
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Phosphorus::GetYield(spaces, loc, yield, 25, 10);
      }
      Great_Phosphorus* Clone() const {return new Great_Phosphorus(*this);}
};

class Superior_Phosphorus : public Phosphorus
{
   public:
      Superior_Phosphorus()
      {
         Create();
      }

      Superior_Phosphorus(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Phosphorus";
	 m_base_yield.m_tech = 25;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Phosphorus::GetYield(spaces, loc, yield, 40, 20);
      }
      Superior_Phosphorus* Clone() const {return new Superior_Phosphorus(*this);}
};

class Iron : public Mineral
{
   public:
      Iron()
      {
         Create();
      }

      Iron(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Iron";
         m_type = IRON;
	 m_base_yield.m_tech = 14;
	 m_max_aspects = 3;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SILVER, Aspects::GREATER_CRYSTAL);
         AddUpgrade(ALUMINIUM, Aspects::GREATER_REACTION);
         AddUpgrade(ZINC, Aspects::GREATER_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_tech_multiplier) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 5);
      }
      Iron* Clone() const {return new Iron(*this);}
};

class Great_Iron : public Iron
{
   public:
      Great_Iron()
      {
         Create();
      }

      Great_Iron(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Iron";
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Iron::GetYield(spaces, loc, yield, 7);
      }
      Great_Iron* Clone() const {return new Great_Iron(*this);}
};

class Superior_Iron : public Iron
{
   public:
      Superior_Iron()
      {
         Create();
      }

      Superior_Iron(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Iron";
	 m_base_yield.m_tech = 25;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Iron::GetYield(spaces, loc, yield, 10);
      }
      Superior_Iron* Clone() const {return new Superior_Iron(*this);}
};

class Gold : public Mineral
{
   public:
      Gold()
      {
         Create();
      }

      Gold(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Gold";
         m_type = GOLD;
	 m_base_yield.m_wealth = 25;
	 m_max_aspects = 5;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(RUBY, Aspects::SUBLIME_NOBLE);
         AddUpgrade(DIAMOND, Aspects::SUBLIME_NOBLE, Aspects::SUBLIME_CRYSTAL);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_rarity, unsigned m_rarity_subtract, unsigned m_wealth_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 60, 15, 15);
      }
      Gold* Clone() const {return new Gold(*this);}
};

class Great_Gold : public Gold
{
   public:
      Great_Gold()
      {
         Create();
      }

      Great_Gold(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Gold";
	 m_base_yield.m_tech = 30;
	 m_max_aspects = 6;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Gold::GetYield(spaces, loc, yield, 100, 20, 25);
      }
      Great_Gold* Clone() const {return new Great_Gold(*this);}
};

class Silver : public Mineral
{
   public:
      Silver()
      {
         Create();
      }

      Silver(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Silver";
         m_type = SILVER;
	 m_base_yield.m_tech  = 15;
	 m_base_yield.m_wealth = 15;
	 m_max_aspects = 5;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP | MASK_MOUNTAIN;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(DIAMOND, Aspects::SUBLIME_NOBLE, Aspects::SUBLIME_CRYSTAL);
         AddUpgrade(COAL, Aspects::SUBLIME_CRYSTAL);
         AddUpgrade(OIL, Aspects::SUBLIME_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_wealth_multiplier) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 0.6);
      }
      Silver* Clone() const {return new Silver(*this);}
};

class Great_Silver : public Silver
{
   public:
      Great_Silver()
      {
         Create();
      }

      Great_Silver(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Silver";
	 m_base_yield.m_tech  = 20;
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 6;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Silver::GetYield(spaces, loc, yield, 0.8);
      }
      Great_Silver* Clone() const {return new Great_Silver(*this);}
};

class Platinum : public Mineral
{
   public:
      Platinum()
      {
         Create();
      }

      Platinum(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Platinum";
         m_type = PLATINUM;
	 m_base_yield.m_wealth = 15;
	 m_base_yield.m_awe    = 5;
	 m_max_aspects = 5;
	 m_biome_mask = MASK_DESERT;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(COAL, Aspects::SUBLIME_CRYSTAL);
         AddUpgrade(OIL, Aspects::SUBLIME_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 15, 10);
      }
      Platinum* Clone() const {return new Platinum(*this);}
};

class Great_Platinum : public Platinum
{
   public:
      Great_Platinum()
      {
         Create();
      }

      Great_Platinum(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Platinum";
	 m_base_yield.m_wealth = 20;
	 m_base_yield.m_awe    = 8;
	 m_max_aspects = 6; // KCJ check
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Platinum::GetYield(spaces, loc, yield, 25, 15);
      }
      Great_Platinum* Clone() const {return new Great_Platinum(*this);}
};

class Aluminium : public Mineral
{
   public:
      Aluminium()
      {
         Create();
      }

      Aluminium(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Aluminium";
         m_type = ALUMINIUM;
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 1;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(URANIUM, Aspects::SUBLIME_REACTION);
         AddUpgrade(FLUORITE, Aspects::SUBLIME_REACTION, Aspects::SUBLIME_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_mineral_tech_adder, unsigned m_plant_tech_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 10, 15);
      }
      Aluminium* Clone() const {return new Aluminium(*this);}
};

class Great_Aluminium : public Aluminium
{
   public:
      Great_Aluminium()
      {
         Create();
      }

      Great_Aluminium(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Aluminium";
	 m_base_yield.m_tech = 25;
	 m_max_aspects = 6;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Aluminium::GetYield(spaces, loc, yield, 20, 30);
      }
      Great_Aluminium* Clone() const {return new Great_Aluminium(*this);}
};

class Zinc : public Mineral
{
   public:
      Zinc()
      {
         Create();
      }

      Zinc(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Zinc";
         m_type = ZINC;
	 m_base_yield.m_tech = 20;
	 m_max_aspects = 5;
	 m_biome_mask = MASK_MOUNTAIN;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(URANIUM, Aspects::SUBLIME_REACTION);
         AddUpgrade(FLUORITE, Aspects::SUBLIME_REACTION, Aspects::SUBLIME_SEISMIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_range, double m_tech_multiplier, unsigned m_awe_adder) const;
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         GetYield(spaces, loc, yield, 3, 0.4, 15);
      }
      Zinc* Clone() const {return new Zinc(*this);}
};

class Great_Zinc : public Zinc
{
   public:
      Great_Zinc()
      {
         Create();
      }

      Great_Zinc(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Zinc";
	 m_base_yield.m_tech = 25;
	 m_max_aspects = 6;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
         Zinc::GetYield(spaces, loc, yield, 5, 0.5, 25);
      }
      Great_Zinc* Clone() const {return new Great_Zinc(*this);}
};

class Ruby : public Mineral
{
   public:
      Ruby()
      {
         Create();
      }

      Ruby(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Ruby";
         m_type = RUBY;
	 m_base_yield.m_wealth = 30;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_DESERT;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Ruby* Clone() const {return new Ruby(*this);}
};

class Diamond : public Mineral
{
   public:
      Diamond()
      {
         Create();
      }

      Diamond(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Diamond";
         m_type = DIAMOND;
	 m_base_yield.m_wealth = 25;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Diamond* Clone() const {return new Diamond(*this);}
};

class Coal : public Mineral
{
   public:
      Coal()
      {
         Create();
      }

      Coal(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Coal";
         m_type = COAL;
	 m_base_yield.m_tech = 20;
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_FOREST | MASK_MOUNTAIN | MASK_DESERT | MASK_SWAMP;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Coal* Clone() const {return new Coal(*this);}
};

class Oil : public Mineral
{
   public:
      Oil()
      {
         Create();
      }

      Oil(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Oil";
         m_type = OIL;
	 m_base_yield.m_wealth = 15;
	 m_base_yield.m_wealth = 25;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_SWAMP;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Oil* Clone() const {return new Oil(*this);}
};

class Uranium : public Mineral
{
   public:
      Uranium()
      {
         Create();
      }

      Uranium(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Uranium";
         m_type = URANIUM;
	 m_base_yield.m_tech = 30;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_SWAMP;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Uranium* Clone() const {return new Uranium(*this);}
};

class Fluorite : public Mineral
{
   public:
      Fluorite()
      {
         Create();
      }

      Fluorite(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Fluorite";
         m_type = FLUORITE;
	 m_base_yield.m_tech = 30;
	 m_max_aspects = 8;
	 m_biome_mask = MASK_MOUNTAIN;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
      Fluorite* Clone() const {return new Fluorite(*this);}
};

#endif

