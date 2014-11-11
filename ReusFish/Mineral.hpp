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

   protected :
      typedef unsigned biome_mask_t;

	 static const biome_mask_t MASK_FOREST   = 1;
	 static const biome_mask_t MASK_DESERT   = 2;
	 static const biome_mask_t MASK_SWAMP    = 4;
	 static const biome_mask_t MASK_MOUNTAIN = 8;

     biome_mask_t m_biome_mask;

      bool IsValidForBiome(biome_t biome)
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
	 m_base_yield.m_wealth = 10;
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
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 10);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
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
	 m_base_yield.m_food = 20;
	 m_max_aspects = 3;
	 m_level = 3;
	 AddUpgrades();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Agate::GetYield(spaces, loc, yield, 30);
      }
      Superior_Agate* Clone() const {return new Superior_Agate(*this);}
};


#endif

