#ifndef ANIMAL_INC__
#define ANIMAL_INC__

#include <vector>

#include "Space.hpp"
#include "Source.hpp"

class Animal : public Source
{
   public :
      Animal() { m_class = ANIMAL; m_base_yield.m_range = 2; }
      Animal *Clone() const {return new Animal(*this);}
};

class Fish : public Animal 
{
   public :
      Fish() { m_class = FISH; }
      Fish* Clone() const {return new Fish(*this);}
};

class Mackerel : public Fish
{
   public:
      Mackerel()
      {
	 Create();
      }

      Mackerel(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Mackerel";
	 m_type = MACKEREL;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 1;
	 m_level = 1;
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
	 m_upgrades.clear();
	 AddUpgrade(SEABASS, Aspects::LESSER_HUNT, Aspects::LESSER_PREDATOR);
	 AddUpgrade(PARROTFISH, Aspects::LESSER_HERD, Aspects::LESSER_EXOTIC);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Mackerel* Clone() const {return new Mackerel(*this);}
};

class Great_Mackerel : public Mackerel
{
   public:
      Great_Mackerel()
      {
	 Create();
      }

      Great_Mackerel(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Mackerel";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 1;
	 m_level = 2;
      }
      Great_Mackerel* Clone() const {return new Great_Mackerel(*this);}
};

class Superior_Mackerel : public Mackerel
{
   public:
      Superior_Mackerel() 
      {
	 Create();
      }

      Superior_Mackerel(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Mackerel";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 2;
	 m_level = 3;
      }
      Superior_Mackerel* Clone() const {return new Superior_Mackerel(*this);}
};

class Clownfish : public Fish
{
   public:
      Clownfish()
      {
	 Create();
      }

      Clownfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Clownfish";
	 m_type = CLOWNFISH;
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 1;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SEABASS, Aspects::LESSER_HUNT, Aspects::LESSER_PREDATOR);
         AddUpgrade(PARROTFISH, Aspects::LESSER_EXOTIC, Aspects::LESSER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2);
      }
      Clownfish* Clone() const {return new Clownfish(*this);}
};
class Great_Clownfish : public Clownfish 
{
   public:
      Great_Clownfish()
      {
	 Create();
      }

      Great_Clownfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Clownfish";
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 2;
	 m_level = 2;
      }

      Great_Clownfish* Clone() const {return new Great_Clownfish(*this);}
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Clownfish::GetYield(spaces, loc, yield, 4);
      }
};

class Superior_Clownfish : public Clownfish 
{
   public:
      Superior_Clownfish()
      {
	 Create();
      }

      Superior_Clownfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Clownfish";
	 m_base_yield.m_wealth = 8;
	 m_max_aspects = 3;
	 m_level = 3;
      }

      Superior_Clownfish* Clone() const {return new Superior_Clownfish(*this);}
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Clownfish::GetYield(spaces, loc, yield, 6);
      }
   protected:
      static const unsigned m_wealth_adder = 6;
};

class Seabass: public Fish
{
   public:
      Seabass()
      {
	 Create();
      }

      Seabass(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Seabass";
	 m_type = SEABASS;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MARLIN, Aspects::GREATER_HUNT);
         AddUpgrade(TUNA, Aspects::GREATER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 3);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      Seabass* Clone() const {return new Seabass(*this);}
};

class Great_Seabass: public Seabass
{
   public:
      Great_Seabass()
      {
	 Create();
      }

      Great_Seabass(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Seabass";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
	 m_level = 2;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Seabass::GetYield(spaces, loc, yield, 6);
      }

      Great_Seabass* Clone() const {return new Great_Seabass(*this);}
};

class Superior_Seabass: public Seabass
{
   public:
      Superior_Seabass()
      {
	 Create();
      }

      Superior_Seabass(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Seabass";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 4;
	 m_level = 3;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Seabass::GetYield(spaces, loc, yield, 12);
      }
      Superior_Seabass* Clone() const {return new Superior_Seabass(*this);}
};

class Parrotfish: public Fish
{
   public:
      Parrotfish()
      {
	 Create();
      }

      Parrotfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Parrotfish";
	 m_type = PARROTFISH;
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 2;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MARLIN, Aspects::GREATER_HUNT);
         AddUpgrade(ANGLERFISH, Aspects::GREATER_EXOTIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 1);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_tech_adder);
      Parrotfish* Clone() const {return new Parrotfish(*this);}
};


class Great_Parrotfish: public Parrotfish
{
   public:
      Great_Parrotfish()
      {
	 Create();
      }

      Great_Parrotfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Parrotfish";
	 m_base_yield.m_wealth = 3;
	 m_max_aspects = 3;
	 m_level = 2;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Parrotfish::GetYield(spaces, loc, yield, 2);
      }
      Great_Parrotfish* Clone() const {return new Great_Parrotfish(*this);}
};

class Superior_Parrotfish: public Parrotfish
{
   public:
      Superior_Parrotfish()
      {
	 Create();
      }

      Superior_Parrotfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Parrotfish";
	 m_base_yield.m_wealth = 6;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Parrotfish::GetYield(spaces, loc, yield, 3);
      }

      Superior_Parrotfish* Clone() const {return new Superior_Parrotfish(*this);}
};

class Marlin : public Fish
{
   public:
      Marlin()
      {
	 Create();
      }

      Marlin(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Marlin";
	 m_type = MARLIN;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 4;
	 m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BLUE_WHALE, Aspects::SUBLIME_HERD);
         AddUpgrade(WHITE_SHARK, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 4, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, const unsigned m_food_wealth_adder, unsigned m_tech_adder);
      Marlin* Clone() const {return new Marlin(*this);}
};

class Great_Marlin : public Marlin
{
   public:
      Great_Marlin()
      {
	 Create();
      }

      Great_Marlin(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Marlin";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 5;
	 m_level = 3;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Marlin::GetYield(spaces, loc, yield, 6, 3);
      }
      Great_Marlin* Clone() const {return new Great_Marlin(*this);}
};

class Anglerfish: public Fish
{
   public:
      Anglerfish()
      {
	 Create();
      }

      Anglerfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Anglerfish";
	 m_type = ANGLERFISH;
	 m_base_yield.m_wealth = 6;
	 m_max_aspects = 4;
	 m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(WHITE_SHARK, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned m_awe_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 0.75, 5);
      }
      Anglerfish* Clone() const {return new Anglerfish(*this);}
};

class Great_Anglerfish: public Anglerfish
{
   public:
      Great_Anglerfish()
      {
	 Create();
      }

      Great_Anglerfish(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Anglerfish";
	 m_base_yield.m_wealth = 12;
	 m_max_aspects = 5;
	 m_level = 3;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Anglerfish::GetYield(spaces, loc, yield, 1.5, 8);
      }
      Great_Anglerfish* Clone() const {return new Great_Anglerfish(*this);}
};


class Tuna: public Fish
{
   public:
      Tuna()
      {
	 Create();
      }

      Tuna(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Tuna";
	 m_type = TUNA;
	 m_base_yield.m_food = 4;
	 m_max_aspects = 4;
	 m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BLUE_WHALE, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 0.5,3);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, unsigned m_food_adder);
      Tuna* Clone() const {return new Tuna(*this);}
};

class Great_Tuna: public Tuna
{
   public:
      Great_Tuna()
      {
	 Create();
      }

      Great_Tuna(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Tuna";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 5;
	 m_level = 3;
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Tuna::GetYield(spaces, loc, yield, 0.75,6);
      }
      Great_Tuna* Clone() const {return new Great_Tuna(*this);}
};

class WhiteShark: public Fish
{
   public:
      WhiteShark()
      {
	 Create();
      }

      WhiteShark(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "White Shark";
	 m_type = WHITE_SHARK;
	 m_base_yield.m_food = 5;
	 m_base_yield.m_wealth= 10;
	 m_base_yield.m_danger = 0;
	 m_max_aspects = 6;
	 m_level = 3;
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      WhiteShark* Clone() const {return new WhiteShark(*this);}
};


class BlueWhale: public Fish
{
   public:
      BlueWhale()
      {
	 Create();
      }

      BlueWhale(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Blue Whale";
	 m_type = BLUE_WHALE;
	 m_base_yield.m_food = 8;
	 m_max_aspects = 6;
	 m_level = 3;
	 AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }


      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      BlueWhale* Clone() const {return new BlueWhale(*this);}
};

class Chicken : public Animal
{
   public:
      Chicken()
      {
	 Create();
      }

      Chicken(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Chicken";
	 m_type = CHICKEN;
	 m_base_yield.m_food = 1;
	 m_max_aspects = 1;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(RABBIT, Aspects::LESSER_HERD);
         AddUpgrade(BEAVER, Aspects::LESSER_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 3);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      Chicken* Clone() const {return new Chicken(*this);}

   protected:
      static const unsigned m_food_adder = 3;
};

class Great_Chicken : public Chicken
{
   public:
      Great_Chicken()
      {
	 Create();
      }

      Great_Chicken(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Chicken";
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Chicken::GetYield(spaces, loc, yield, 5);
      }
      Great_Chicken* Clone() const {return new Great_Chicken(*this);}
};

class Superior_Chicken : public Chicken
{
   public:
      Superior_Chicken()
      {
	 Create();
      }

      Superior_Chicken(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Chicken";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Chicken::GetYield(spaces, loc, yield, 10);
      }
      Superior_Chicken* Clone() const {return new Superior_Chicken(*this);}
};

class Rabbit : public Animal
{
   public:
      Rabbit()
      {
	 Create();
      }

      Rabbit(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Rabbit";
	 m_type = RABBIT;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(DEER, Aspects::POTENT_HERD);
         AddUpgrade(WISENT, Aspects::GREATER_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      Rabbit* Clone() const {return new Rabbit(*this);}
};

class Great_Rabbit : public Rabbit
{
   public:
      Great_Rabbit()
      {
	 Create();
      }

      Great_Rabbit(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Rabbit";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Rabbit::GetYield(spaces, loc, yield, 5);
      }
      Rabbit* Clone() const {return new Rabbit(*this);}
};

class Superior_Rabbit : public Rabbit
{
   public:
      Superior_Rabbit()
      {
	 Create();
      }

      Superior_Rabbit(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Rabbit";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Rabbit::GetYield(spaces, loc, yield, 10);
      }
      Superior_Rabbit* Clone() const {return new Superior_Rabbit(*this);}
};

class Beaver: public Animal
{
   public:
      Beaver()
      {
	 Create();
      }

      Beaver(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Beaver";
	 m_type = BEAVER;
	 m_base_yield.m_food   = 2;
	 m_base_yield.m_wealth = 1;
	 m_max_aspects = 2;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BOAR, Aspects::POTENT_HUNT);
         AddUpgrade(WISENT, Aspects::GREATER_HUNT, Aspects::GREATER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_natura_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 1, 7);
      }
      Beaver* Clone() const {return new Beaver(*this);}
};

class Great_Beaver: public Beaver
{
   public:
      Great_Beaver()
      {
	 Create();
      }

      Great_Beaver(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Beaver";
	 m_base_yield.m_food   = 4;
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Beaver::GetYield(spaces, loc, yield, 2, 14);
      }
      Great_Beaver* Clone() const {return new Great_Beaver(*this);}
};

class Superior_Beaver: public Beaver 
{
   public:
      Superior_Beaver()
      {
	 Create();
      }

      Superior_Beaver(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Beaver";
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Beaver::GetYield(spaces, loc, yield, 4, 32);
      }
      Superior_Beaver* Clone() const {return new Superior_Beaver(*this);}
};

class Deer: public Animal
{
   public:
      Deer()
      {
	 Create();
      }

      Deer(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Deer";
	 m_type = DEER;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 3;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MOOSE, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 4, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder);
      Deer* Clone() const {return new Deer(*this);}
};

class Great_Deer: public Deer 
{
   public:
      Great_Deer()
      {
	 Create();
      }

      Great_Deer(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Deer";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 4;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Deer::GetYield(spaces, loc, yield, 8, 4);
      }
      Great_Deer* Clone() const {return new Great_Deer(*this);}
};


class Superior_Deer: public Deer 
{
   public:
      Superior_Deer()
      {
	 Create();
      }

      Superior_Deer(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Deer";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Deer::GetYield(spaces, loc, yield, 16, 8);
      }
      Superior_Deer* Clone() const {return new Superior_Deer(*this);}
};

class Boar : public Animal
{
   public:
      Boar()
      {
	 Create();
      }

      Boar(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Boar";
	 m_type = BOAR;
	 m_base_yield.m_food   = 4;
	 m_base_yield.m_wealth = 1;
	 m_base_yield.m_danger = 1;
	 m_max_aspects = 3;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MOOSE, Aspects::SUBLIME_HUNT);
         AddUpgrade(BEAR, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_multiplier);
      Boar* Clone() const {return new Boar(*this);}
};

class Great_Boar : public Boar
{
   public:
      Great_Boar()
      {
	 Create();
      }

      Great_Boar(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Boar";
	 m_base_yield.m_food   = 6;
	 m_base_yield.m_wealth = 2;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 4;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Boar::GetYield(spaces, loc, yield, 3);
      }
      Great_Boar* Clone() const {return new Great_Boar(*this);}
};

class Superior_Boar : public Boar
{
   public:
      Superior_Boar()
      {
	 Create();
      }

      Superior_Boar(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Boar";
	 m_base_yield.m_food   = 8;
	 m_base_yield.m_wealth = 4;
	 m_base_yield.m_danger = 3;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Boar::GetYield(spaces, loc, yield, 4);
      }
      Superior_Boar* Clone() const {return new Superior_Boar(*this);}
};

class Wisent: public Animal
{
   public:
      Wisent()
      {
	 Create();
      }

      Wisent(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Wisent";
	 m_type = WISENT;
	 m_base_yield.m_food   = 4;
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 4;
	 m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MOOSE, Aspects::SUBLIME_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 1, 4, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, 
	            unsigned m_food_multiplier, unsigned m_food_adder, unsigned m_wealth_adder);
      Wisent* Clone() const {return new Wisent(*this);}
};


class Great_Wisent: public Wisent 
{
   public:
      Great_Wisent()
      {
	 Create();
      }

      Great_Wisent(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Wisent";
	 m_base_yield.m_food   = 6;
	 m_base_yield.m_wealth = 3;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Wisent::GetYield(spaces, loc, yield, 2, 8, 4);
      }
      Great_Wisent* Clone() const {return new Great_Wisent(*this);}
};

class Moose: public Animal
{
   public:
      Moose()
      {
	 Create();
      }

      Moose(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Moose";
	 m_type = MOOSE;
	 m_base_yield.m_food   = 8;
	 m_max_aspects = 6;
	 m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Moose* Clone() const {return new Moose(*this);}
};


class Stoat : public Animal
{
   public:
      Stoat()
      {
	 Create();
      }

      Stoat(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Stoat";
	 m_type = STOAT;
	 m_base_yield.m_wealth = 1;
	 m_max_aspects = 1;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BEAVER, Aspects::LESSER_EXOTIC);
         AddUpgrade(FOX, Aspects::LESSER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      Stoat* Clone() const {return new Stoat(*this);}
};

class Great_Stoat : public Stoat

{
   public:
      Great_Stoat()
      {
	 Create();
      }

      Great_Stoat(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Stoat";
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Stoat::GetYield(spaces, loc, yield, 4);
      }
      Great_Stoat* Clone() const {return new Great_Stoat(*this);}
};

class Superior_Stoat : public Stoat
{
   public:
      Superior_Stoat()
      {
	 Create();
      }

      Superior_Stoat(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Stoat";
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 3;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Stoat::GetYield(spaces, loc, yield, 8);
      }
      Superior_Stoat* Clone() const {return new Superior_Stoat(*this);}
};

class Fox : public Animal
{
   public:
      Fox()
      {
	 Create();
      }

      Fox(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Fox";
	 m_type = FOX;
	 m_base_yield.m_wealth = 1;
	 m_base_yield.m_danger = 1;
	 m_max_aspects = 2;
	 m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BOAR, Aspects::POTENT_HUNT);
         AddUpgrade(WOLF, Aspects::GREATER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 2);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      Fox* Clone() const {return new Fox(*this);}
};

class Great_Fox : public Fox
{
   public:
      Great_Fox()
      {
	 Create();
      }

      Great_Fox(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Fox";
	 m_base_yield.m_wealth = 2;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 3;
	 m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Fox::GetYield(spaces, loc, yield, 4);
      }
      Great_Fox* Clone() const {return new Great_Fox(*this);}
};

class Superior_Fox : public Fox
{
   public:
      Superior_Fox()
      {
	 Create();
      }

      Superior_Fox(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Superior Fox";
	 m_base_yield.m_wealth = 4;
	 m_base_yield.m_danger = 3;
	 m_max_aspects = 4;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Fox::GetYield(spaces, loc, yield, 8);
      }
      Superior_Fox* Clone() const {return new Superior_Fox(*this);}
};

class Wolf: public Animal
{
   public:
      Wolf()
      {
	 Create();
      }

      Wolf(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Wolf";
	 m_type = WOLF;
	 m_base_yield.m_wealth = 6;
	 m_base_yield.m_danger = 1;
	 m_max_aspects = 4;
	 m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BEAR, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 GetYield(spaces, loc, yield, 3, 1, 10);
      }
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
	    unsigned m_animal_wealth_adder, unsigned m_animal_danger_adder, unsigned m_mineral_wealth_adder);
      Wolf* Clone() const {return new Wolf(*this);}
};


class Great_Wolf: public Wolf 
{
   public:
      Great_Wolf()
      {
	 Create();
      }

      Great_Wolf(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Great Wolf";
	 m_base_yield.m_wealth = 12;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 5;
	 m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 Wolf::GetYield(spaces, loc, yield, 5, 2, 15);
      }
      Great_Wolf* Clone() const {return new Great_Wolf(*this);}
};

class Bear: public Animal
{
   public:
      Bear()
      {
	 Create();
      }

      Bear(const std::vector<Aspects::aspect_t> aspects)
      {
	 Create();
	 m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Bear";
	 m_type = BEAR;
	 m_base_yield.m_wealth = 5;
	 m_base_yield.m_wealth = 20;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 4;
	 m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Bear* Clone() const {return new Bear(*this);}
};

class KangarooRat : public Animal
{
   public:
      KangarooRat()
      {
         Create();
      }

      KangarooRat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
	 m_name = "Kangaroo Rat";
	 m_type = KANGAROO_RAT;
	 m_base_yield.m_food = 1;
	 m_level = 1;
	 m_max_aspects = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GOAT, Aspects::LESSER_HERD);
         AddUpgrade(ARMADILLO, Aspects::LESSER_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 2);
      }
      KangarooRat* Clone() const {return new KangarooRat(*this);}
};

class Great_KangarooRat : public KangarooRat
{
   public:
      Great_KangarooRat()
      {
         Create();
      }

      Great_KangarooRat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
	  {
         m_name = "Great Kangaroo Rat";
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         KangarooRat::GetYield(spaces, loc, yield, 4);
      }
      Great_KangarooRat* Clone() const {return new Great_KangarooRat(*this);}
};

class Superior_KangarooRat : public KangarooRat
{
   public:
      Superior_KangarooRat()
      {
         Create();
      }

      Superior_KangarooRat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
	  {
         m_name = "Superior Kangaroo Rat";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 2;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         KangarooRat::GetYield(spaces, loc, yield, 8);
      }
      Superior_KangarooRat* Clone() const {return new Superior_KangarooRat(*this);}
};

class DesertTortoise : public Animal
{
   public:
      DesertTortoise()
      {
         Create();
      }

      DesertTortoise(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
	  {
         m_name = "DesertTortoise";
         m_type = DESERT_TORTOISE;
	 m_base_yield.m_wealth = 1;
         m_level = 1;
	 m_max_aspects = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ARMADILLO, Aspects::LESSER_EXOTIC);
         AddUpgrade(RATTLESNAKE, Aspects::LESSER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 3);
      }
      DesertTortoise* Clone() const {return new DesertTortoise(*this);}
};

class Great_DesertTortoise : public DesertTortoise
{
   public:
      Great_DesertTortoise()
      {
         Create();
      }

      Great_DesertTortoise(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
	  {
         m_name = "Great DesertTortoise";
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DesertTortoise::GetYield(spaces, loc, yield, 8);
      }
      Great_DesertTortoise* Clone() const {return new Great_DesertTortoise(*this);}
};

class Superior_DesertTortoise : public DesertTortoise
{
   public:
      Superior_DesertTortoise()
      {
         Create();
      }

      Superior_DesertTortoise(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
	  {
         m_name = "Superior DesertTortoise";
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         DesertTortoise::GetYield(spaces, loc, yield, 16);
      }
      Superior_DesertTortoise* Clone() const {return new Superior_DesertTortoise(*this);}
};

class Goat : public Animal
{
   public:
      Goat()
      {
         Create();
      }

      Goat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Goat";
         m_type = GOAT;
	 m_base_yield.m_food = 1;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(JAVELINA, Aspects::POTENT_HUNT);
         AddUpgrade(COYOTE, Aspects::GREATER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 6);
      }
      Goat* Clone() const {return new Goat(*this);}
};

class Great_Goat : public Goat
{
   public:
      Great_Goat()
      {
         Create();
      }

      Great_Goat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Goat";
	 m_base_yield.m_food = 3;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Goat::GetYield(spaces, loc, yield, 15);
      }
      Great_Goat* Clone() const {return new Great_Goat(*this);}
};

class Superior_Goat : public Goat
{
   public:
      Superior_Goat()
      {
         Create();
      }

      Superior_Goat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Goat";
	 m_base_yield.m_food = 6;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Goat::GetYield(spaces, loc, yield, 30);
      }
      Superior_Goat* Clone() const {return new Superior_Goat(*this);}
};

class Armadillo : public Animal
{
   public:
      Armadillo()
      {
         Create();
      }

      Armadillo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Armadillo";
         m_type = ARMADILLO;
	 m_base_yield.m_food   = 1;
	 m_base_yield.m_wealth = 3;
         m_level = 1;
	 m_max_aspects = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(JAVELINA, Aspects::POTENT_HUNT);
         AddUpgrade(GREY_FOX, Aspects::POTENT_EXOTIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 1);
      }
      Armadillo* Clone() const {return new Armadillo(*this);}
};

class Great_Armadillo : public Armadillo
{
   public:
      Great_Armadillo()
      {
         Create();
      }

      Great_Armadillo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Armadillo";
	 m_base_yield.m_food  = 2;
	 m_base_yield.m_wealth = 6;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Armadillo::GetYield(spaces, loc, yield, 2);
      }
      Great_Armadillo* Clone() const {return new Great_Armadillo(*this);}
};

class Superior_Armadillo : public Armadillo
{
   public:
      Superior_Armadillo()
      {
         Create();
      }

      Superior_Armadillo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Armadillo";
	 m_base_yield.m_food  = 4;
	 m_base_yield.m_wealth = 12;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Armadillo::GetYield(spaces, loc, yield, 4);
      }
      Superior_Armadillo* Clone() const {return new Superior_Armadillo(*this);}
};

class Rattlesnake : public Animal
{
   public:
      Rattlesnake()
      {
         Create();
      }

      Rattlesnake(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Rattlesnake";
         m_type = RATTLESNAKE;
	 m_base_yield.m_wealth = 3;
	 m_base_yield.m_danger = 1;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(GREY_FOX, Aspects::POTENT_EXOTIC);
         AddUpgrade(COYOTE, Aspects::GREATER_PREDATOR);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_PREDATOR, Aspects::GREATER_PREDATOR);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_PREDATOR, Aspects::GREATER_HUNT);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_PREDATOR, Aspects::GREATER_HERD);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_PREDATOR, Aspects::GREATER_EXOTIC);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_HUNT, Aspects::GREATER_HUNT);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_HUNT, Aspects::GREATER_HERD);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_HUNT, Aspects::GREATER_EXOTIC);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_HERD, Aspects::GREATER_HERD);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_HERD, Aspects::GREATER_EXOTIC);
         AddUpgrade(GILA_MONSTER, Aspects::GREATER_EXOTIC, Aspects::GREATER_EXOTIC);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 1);
      }
      Rattlesnake* Clone() const {return new Rattlesnake(*this);}
};

class Great_Rattlesnake : public Rattlesnake
{
   public:
      Great_Rattlesnake()
      {
         Create();
      }

      Great_Rattlesnake(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Rattlesnake";
	 m_base_yield.m_wealth = 5;
	 m_base_yield.m_danger = 1;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Rattlesnake::GetYield(spaces, loc, yield, 2);
      }
      Great_Rattlesnake* Clone() const {return new Great_Rattlesnake(*this);}
};

class Superior_Rattlesnake : public Rattlesnake
{
   public:
      Superior_Rattlesnake()
      {
         Create();
      }

      Superior_Rattlesnake(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Rattlesnake";
	 m_base_yield.m_wealth = 10;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Rattlesnake::GetYield(spaces, loc, yield, 3);
      }
      Superior_Rattlesnake* Clone() const {return new Superior_Rattlesnake(*this);}
};

class Javelina : public Animal
{
   public:
      Javelina()
      {
         Create();
      }

      Javelina(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Javlina";
         m_type = JAVELINA;
	 m_base_yield.m_food = 3;
         m_level = 1;
	 m_max_aspects = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BIG_HORN, Aspects::SUBLIME_HUNT, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_danger_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 3, 1);
      }
      Javelina* Clone() const {return new Javelina(*this);}
};

class Great_Javelina : public Javelina
{
   public:
      Great_Javelina()
      {
         Create();
      }

      Great_Javelina(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Javelina";
	 m_base_yield.m_food = 5;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Javelina::GetYield(spaces, loc, yield, 6, 2);
      }
      Great_Javelina* Clone() const {return new Great_Javelina(*this);}
};

class Superior_Javelina : public Javelina
{
   public:
      Superior_Javelina()
      {
         Create();
      }

      Superior_Javelina(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Javelina";
	 m_base_yield.m_food = 12;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Javelina::GetYield(spaces, loc, yield, 12, 3);
      }
      Superior_Javelina* Clone() const {return new Superior_Javelina(*this);}
};

//KCJ
class GreyFox : public Animal
{
   public:
      GreyFox()
      {
         Create();
      }

      GreyFox(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Grey Fox";
         m_type = GREY_FOX;
	 m_base_yield.m_food = 1;
	 m_base_yield.m_wealth = 2;
         m_level = 1;
	 m_max_aspects = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BOBCAT, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 5);
      }
      GreyFox* Clone() const {return new GreyFox(*this);}
};

class Great_GreyFox : public GreyFox
{
   public:
      Great_GreyFox()
      {
         Create();
      }

      Great_GreyFox(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Grey Fox";
	 m_base_yield.m_food = 2;
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GreyFox::GetYield(spaces, loc, yield, 10);
      }
      Great_GreyFox* Clone() const {return new Great_GreyFox(*this);}
};

class Superior_GreyFox : public GreyFox
{
   public:
      Superior_GreyFox()
      {
         Create();
      }

      Superior_GreyFox(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Grey Fox";
	 m_base_yield.m_food = 4;
	 m_base_yield.m_wealth = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GreyFox::GetYield(spaces, loc, yield, 15);
      }
      Superior_GreyFox* Clone() const {return new Superior_GreyFox(*this);}
};

class Coyote : public Animal
{
   public:
      Coyote()
      {
         Create();
      }

      Coyote(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Coyote";
         m_type = COYOTE;
	 m_base_yield.m_food   = 3;
	 m_base_yield.m_wealth = 5;
	 m_base_yield.m_danger = 2;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BIG_HORN, Aspects::SUBLIME_HUNT, Aspects::SUBLIME_HERD);
         AddUpgrade(BOBCAT, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 5);
      }
      Coyote* Clone() const {return new Coyote(*this);}
};

class Great_Coyote : public Coyote
{
   public:
      Great_Coyote()
      {
         Create();
      }

      Great_Coyote(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Coyote";
	 m_base_yield.m_food   = 6;
	 m_base_yield.m_wealth = 10;
	 m_base_yield.m_danger = 3;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Coyote::GetYield(spaces, loc, yield, 8);
      }
      Great_Coyote* Clone() const {return new Great_Coyote(*this);}
};

class GilaMonster : public Animal
{
   public:
      GilaMonster()
      {
         Create();
      }

      GilaMonster(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Gila Monster";
         m_type = GILA_MONSTER;
	 m_base_yield.m_tech   =  5;
	 m_base_yield.m_wealth = 10;
	 m_base_yield.m_range  =  1;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(BOBCAT, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_adder, unsigned m_natura_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo, 5, 15);
      }
      GilaMonster* Clone() const {return new GilaMonster(*this);}
};

class Great_GilaMonster : public GilaMonster
{
   public:
      Great_GilaMonster()
      {
         Create();
      }

      Great_GilaMonster(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Gila Monster";
	 m_base_yield.m_tech   = 10;
	 m_base_yield.m_wealth = 20;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GilaMonster::GetYield(spaces, loc, yield, 10, 25);
      }
      Great_GilaMonster* Clone() const {return new Great_GilaMonster(*this);}
};

class BigHorn : public Animal
{
   public:
      BigHorn()
      {
         Create();
      }

      BigHorn(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Big Horn";
         m_type = BIG_HORN;
	 m_base_yield.m_food = 8;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      BigHorn* Clone() const {return new BigHorn(*this);}
};

class Bobcat : public Animal
{
   public:
      Bobcat()
      {
         Create();
      }

      Bobcat(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Bobcat";
         m_type = BOBCAT;
	 m_base_yield.m_wealth = 5;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Bobcat* Clone() const {return new Bobcat(*this);}
};

class Frog : public Animal
{
   public:
      Frog()
      {
         Create();
      }

      Frog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Frog";
         m_type = FROG;
	 m_base_yield.m_food = 1;
	 m_base_yield.m_range = 1;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(OTTER, Aspects::LESSER_HUNT, Aspects::LESSER_HERD);
         AddUpgrade(IGUANA, Aspects::LESSER_EXOTIC, Aspects::LESSER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 2);
      }
      Frog* Clone() const {return new Frog(*this);}
};

class Great_Frog : public Frog
{
   public:
      Great_Frog()
      {
         Create();
      }

      Great_Frog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Frog";
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Frog::GetYield(spaces, loc, yield, 4);
      }
      Great_Frog* Clone() const {return new Great_Frog(*this);}
};

class Superior_Frog : public Frog
{
   public:
      Superior_Frog()
      {
         Create();
      }

      Superior_Frog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Frog";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Frog::GetYield(spaces, loc, yield, 8);
      }
      Superior_Frog* Clone() const {return new Superior_Frog(*this);}
};

class PoisonDartFrog : public Animal
{
   public:
      PoisonDartFrog()
      {
         Create();
      }

      PoisonDartFrog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Poison Dart Frog";
         m_type = POISON_DART_FROG;
	 m_base_yield.m_wealth = 1;
	 m_base_yield.m_range = 1;
	 m_max_aspects = 1;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(OTTER, Aspects::LESSER_HUNT, Aspects::LESSER_HERD);
         AddUpgrade(IGUANA, Aspects::LESSER_EXOTIC, Aspects::LESSER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 2);
      }
      PoisonDartFrog* Clone() const {return new PoisonDartFrog(*this);}
};

class Great_PoisonDartFrog : public PoisonDartFrog
{
   public:
      Great_PoisonDartFrog()
      {
         Create();
      }

      Great_PoisonDartFrog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Poison Dart Frog";
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         PoisonDartFrog::GetYield(spaces, loc, yield, 4);
      }
      Great_PoisonDartFrog* Clone() const {return new Great_PoisonDartFrog(*this);}
};

class Superior_PoisonDartFrog : public PoisonDartFrog
{
   public:
      Superior_PoisonDartFrog()
      {
         Create();
      }

      Superior_PoisonDartFrog(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Poison Dart Frog";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         PoisonDartFrog::GetYield(spaces, loc, yield, 8);
      }
      Superior_PoisonDartFrog* Clone() const {return new Superior_PoisonDartFrog(*this);}
};

class Otter : public Animal
{
   public:
      Otter()
      {
         Create();
      }

      Otter(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Otter";
         m_type = OTTER;
	 m_base_yield.m_food = 2;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(TAPIR, Aspects::POTENT_HUNT);
         AddUpgrade(BUFFALO, Aspects::GREATER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 3);
      }
      Otter* Clone() const {return new Otter(*this);}
};

class Great_Otter : public Otter
{
   public:
      Great_Otter()
      {
         Create();
      }

      Great_Otter(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Otter";
	 m_base_yield.m_food = 4;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Otter::GetYield(spaces, loc, yield, 6);
      }
      Great_Otter* Clone() const {return new Great_Otter(*this);}
};

class Superior_Otter : public Otter
{
   public:
      Superior_Otter()
      {
         Create();
      }

      Superior_Otter(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Otter";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Otter::GetYield(spaces, loc, yield, 10);
      }
      Superior_Otter* Clone() const {return new Superior_Otter(*this);}
};

class Iguana : public Animal
{
   public:
      Iguana()
      {
         Create();
      }

      Iguana(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Iguana";
         m_type = IGUANA;
	 m_base_yield.m_wealth = 2;
	 m_max_aspects = 2;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(TAPIR, Aspects::POTENT_HUNT);
         AddUpgrade(KOMODO_DRAGON, Aspects::GREATER_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_danger_Adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo, 3, 1);
      }
      Iguana* Clone() const {return new Iguana(*this);}
};

class Great_Iguana : public Iguana
{
   public:
      Great_Iguana()
      {
         Create();
      }

      Great_Iguana(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Iguana";
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 3;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Iguana::GetYield(spaces, loc, yield, 6, 1);
      }
      Great_Iguana* Clone() const {return new Great_Iguana(*this);}
};

class Superior_Iguana : public Iguana
{
   public:
      Superior_Iguana()
      {
         Create();
      }

      Superior_Iguana(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Iguana";
	 m_base_yield.m_wealth = 8;
	 m_max_aspects = 4;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Iguana::GetYield(spaces, loc, yield, 12, 2);
      }
      Superior_Iguana* Clone() const {return new Superior_Iguana(*this);}
};

class Tapir : public Animal
{
   public:
      Tapir()
      {
         Create();
      }

      Tapir(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Tapir";
         m_type = TAPIR;
	 m_base_yield.m_food   = 1;
	 m_base_yield.m_wealth = 1;
	 m_max_aspects = 3;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGUTAN, Aspects::SUBLIME_HERD, Aspects::SUBLIME_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_natura_limit);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 1, 7);
      }
      Tapir* Clone() const {return new Tapir(*this);}
};

class Great_Tapir : public Tapir
{
   public:
      Great_Tapir()
      {
         Create();
      }

      Great_Tapir(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Tapir";
	 m_base_yield.m_food   = 2;
	 m_base_yield.m_wealth = 4;
	 m_max_aspects = 4;
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Tapir::GetYield(spaces, loc, yield, 2, 14);
      }
      Great_Tapir* Clone() const {return new Great_Tapir(*this);}
};

class Superior_Tapir : public Tapir
{
   public:
      Superior_Tapir()
      {
         Create();
      }

      Superior_Tapir(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Tapir";
	 m_base_yield.m_food   = 4;
	 m_base_yield.m_wealth = 8;
	 m_max_aspects = 3;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Tapir::GetYield(spaces, loc, yield, 4. 24);
      }
      Superior_Tapir* Clone() const {return new Superior_Tapir(*this);}
};

class Buffalo : public Animal
{
   public:
      Buffalo()
      {
         Create();
      }

      Buffalo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Buffalo";
         m_type = BUFFALO;
	 m_base_yield.m_food = 4;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(ORANGUTAN, Aspects::SUBLIME_HERD, Aspects::SUBLIME_HUNT);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, unsigned m_food_bonus);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 0.4, 3);
      }
      Buffalo* Clone() const {return new Buffalo(*this);}
};

class Great_Buffalo : public Buffalo
{
   public:
      Great_Buffalo()
      {
         Create();
      }

      Great_Buffalo(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Buffalo";
	 m_base_yield.m_food = 8;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Buffalo::GetYield(spaces, loc, yield, 0.5, 5);
      }
      Great_Buffalo* Clone() const {return new Great_Buffalo(*this);}
};

class KomodoDragon : public Animal
{
   public:
      KomodoDragon()
      {
         Create();
      }

      KomodoDragon(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Komodo Dragon";
         m_type = KOMODO_DRAGON;
	 m_base_yield.m_wealth = 4;
	 m_base_yield.m_danger = 2;
	 m_base_yield.m_range  = 1;
	 m_max_aspects = 4;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(CROCODILE, Aspects::SUBLIME_PREDATOR);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, 2);
      }
      KomodoDragon* Clone() const {return new KomodoDragon(*this);}
};

class Great_KomodoDragon : public KomodoDragon
{
   public:
      Great_KomodoDragon()
      {
         Create();
      }

      Great_KomodoDragon(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Komodo Dragon";
	 m_base_yield.m_wealth = 8;
	 m_base_yield.m_danger = 3;
	 m_max_aspects = 5;
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         KomodoDragon::GetYield(spaces, loc, yield, 4);
      }
      Great_KomodoDragon* Clone() const {return new Great_KomodoDragon(*this);}
};

class Orangutan : public Animal
{
   public:
      Orangutan()
      {
         Create();
      }

      Orangutan(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Orangutan";
         m_type = ORANGUTAN;
	 m_base_yield.m_food = 8;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Orangutan* Clone() const {return new Orangutan(*this);}
};

class Crocodile : public Animal
{
   public:
      Crocodile()
      {
         Create();
      }

      Crocodile(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Crocodile";
         m_type = CROCODILE;
	 m_base_yield.m_wealth = 8;
	 m_base_yield.m_danger = 1;
	 m_base_yield.m_range  = 1;
	 m_max_aspects = 6;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Crocodile* Clone() const {return new Crocodile(*this);}
};

class Marten : public Animal
{
   public:
      Marten()
      {
         Create();
      }

      Marten(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Marten";
         m_type = MARTEN;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MUSK_DEER, Aspects::POTENT_HUNT);
         AddUpgrade(PANGOLIN, Aspects::POTENT_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      Marten* Clone() const {return new Marten(*this);}
};

class Great_Marten : public Marten
{
   public:
      Great_Marten()
      {
         Create();
      }

      Great_Marten(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Marten";
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Marten::GetYield(spaces, loc, yield, foo);
      }
      Great_Marten* Clone() const {return new Great_Marten(*this);}
};

class Superior_Marten : public Marten
{
   public:
      Superior_Marten()
      {
         Create();
      }

      Superior_Marten(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Marten";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Marten::GetYield(spaces, loc, yield, foo);
      }
      Superior_Marten* Clone() const {return new Superior_Marten(*this);}
};

class Monal : public Animal
{
   public:
      Monal()
      {
         Create();
      }

      Monal(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Monal";
         m_type = MONAL;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(MUSK_DEER, Aspects::POTENT_PREDATOR, Aspects::POTENT_EXOTIC);
         AddUpgrade(PANGOLIN, Aspects::POTENT_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      Monal* Clone() const {return new Monal(*this);}
};

class Great_Monal : public Monal
{
   public:
      Great_Monal()
      {
         Create();
      }

      Great_Monal(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Monal";
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Monal::GetYield(spaces, loc, yield, foo);
      }
      Great_Monal* Clone() const {return new Great_Monal(*this);}
};

class Superior_Monal : public Monal
{
   public:
      Superior_Monal()
      {
         Create();
      }

      Superior_Monal(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Monal";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Monal::GetYield(spaces, loc, yield, foo);
      }
      Superior_Monal* Clone() const {return new Superior_Monal(*this);}
};

class MuskDeer : public Animal
{
   public:
      MuskDeer()
      {
         Create();
      }

      MuskDeer(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Musk Deer";
         m_type = MUSK_DEER;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(SNOW_LEOPARD, Aspects::GREATER_PREDATOR);
         AddUpgrade(LANGUR_MONKEY, Aspects::GREATER_EXOTIC);
         AddUpgrade(YAK, Aspects::GREATER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      MuskDeer* Clone() const {return new MuskDeer(*this);}
};

class Great_MuskDeer : public MuskDeer
{
   public:
      Great_MuskDeer()
      {
         Create();
      }

      Great_MuskDeer(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Musk Deer";
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         MuskDeer::GetYield(spaces, loc, yield, foo);
      }
      Great_MuskDeer* Clone() const {return new Great_MuskDeer(*this);}
};

class Superior_MuskDeer : public MuskDeer
{
   public:
      Superior_MuskDeer()
      {
         Create();
      }

      Superior_MuskDeer(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Musk Deer";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         MuskDeer::GetYield(spaces, loc, yield, foo);
      }
      Superior_MuskDeer* Clone() const {return new Superior_MuskDeer(*this);}
};

class Pangolin : public Animal
{
   public:
      Pangolin()
      {
         Create();
      }

      Pangolin(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Pangolin";
         m_type = PANGOLIN;
         m_level = 1;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(LANGUR_MONKEY, Aspects::GREATER_EXOTIC);
         AddUpgrade(YAK, Aspects::GREATER_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      Pangolin* Clone() const {return new Pangolin(*this);}
};

class Great_Pangolin : public Pangolin
{
   public:
      Great_Pangolin()
      {
         Create();
      }

      Great_Pangolin(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Pangolin";
         m_level = 2;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Pangolin::GetYield(spaces, loc, yield, foo);
      }
      Great_Pangolin* Clone() const {return new Great_Pangolin(*this);}
};

class Superior_Pangolin : public Pangolin
{
   public:
      Superior_Pangolin()
      {
         Create();
      }

      Superior_Pangolin(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Superior Pangolin";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Pangolin::GetYield(spaces, loc, yield, foo);
      }
      Superior_Pangolin* Clone() const {return new Superior_Pangolin(*this);}
};

class SnowLeopard : public Animal
{
   public:
      SnowLeopard()
      {
         Create();
      }

      SnowLeopard(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Snow Leopard";
         m_type = SNOW_LEOPARD;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PANDA, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      SnowLeopard* Clone() const {return new SnowLeopard(*this);}
};

class Great_SnowLeopard : public SnowLeopard
{
   public:
      Great_SnowLeopard()
      {
         Create();
      }

      Great_SnowLeopard(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Snow Leopard";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         SnowLeopard::GetYield(spaces, loc, yield, foo);
      }
      Great_SnowLeopard* Clone() const {return new Great_SnowLeopard(*this);}
};

class LangurMonkey : public Animal
{
   public:
      LangurMonkey()
      {
         Create();
      }

      LangurMonkey(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Langur Monkey";
         m_type = LANGUR_MONKEY;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PANDA, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      LangurMonkey* Clone() const {return new LangurMonkey(*this);}
};

class Great_LangurMonkey : public LangurMonkey
{
   public:
      Great_LangurMonkey()
      {
         Create();
      }

      Great_LangurMonkey(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Langur Monkey";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         LangurMonkey::GetYield(spaces, loc, yield, foo);
      }
      Great_LangurMonkey* Clone() const {return new Great_LangurMonkey(*this);}
};

class Yak : public Animal
{
   public:
      Yak()
      {
         Create();
      }

      Yak(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Yak";
         m_type = YAK;
         m_level = 2;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
         AddUpgrade(PANDA, Aspects::SUBLIME_EXOTIC, Aspects::SUBLIME_HERD);
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);
      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         GetYield(spaces, loc, yield, foo);
      }
      Yak* Clone() const {return new Yak(*this);}
};

class Great_Yak : public Yak
{
   public:
      Great_Yak()
      {
         Create();
      }

      Great_Yak(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Great Yak";
         m_level = 3;
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
         Yak::GetYield(spaces, loc, yield, foo);
      }
      Great_Yak* Clone() const {return new Great_Yak(*this);}
};

class Panda : public Animal
{
   public:
      Panda()
      {
         Create();
      }

      Panda(const std::vector<Aspects::aspect_t> aspects)
      {
         Create();
         m_aspects = aspects;
      }

      void Create(void)
      {
         m_name = "Panda";
         m_type = PANDA;
         m_level = 3;
         AddUpgrades();
      }

      void AddUpgrades(void)
      {
         m_upgrades.clear();
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield);
      Panda* Clone() const {return new Panda(*this);}
};
#endif
