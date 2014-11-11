#include <algorithm>

#include "Animal.hpp"

void Mackerel::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   yield.m_range = GetRange(spaces, loc);
}

unsigned Mackerel::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   for (unsigned i = std::max<int>((int)loc - range,0); (i <= loc + range) && (i < spaces.size()); i+= 1)
      if ((i != loc) && (spaces[i].m_source->Type() == MACKEREL))
	 range += 1;

   if (range == 3)
   {
      if ((loc >= 3) && (spaces[loc - 3].m_source->Type() == MACKEREL))
	 range += 1;
      if (((loc + 3) < spaces.size()) && (spaces[loc + 3].m_source->Type() == MACKEREL))
	 range += 1;
   }
   if (range > 4)
      range = 4;
   return range;
}

void Clownfish::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), CLOWNFISH, PARROTFISH);
}

void Seabass::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfInRange(spaces, loc, yield, Yield(m_food_adder, 0, 0, 0, 0, 0), MACKEREL, CLOWNFISH);
}

void Parrotfish::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_tech_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};

   for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
   {
      if ((i != loc) && (biome_list[i] == OCEAN) && (spaces[i].m_source->Class() == ANIMAL) &&!seen_flag[spaces[i].m_source->Type()])
      {
	 seen_flag[spaces[i].m_source->Type()] = 1;
	 yield.m_tech += m_wealth_tech_adder;
	 yield.m_wealth += m_wealth_tech_adder;
      }
   }
}

void Marlin::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_wealth_adder, unsigned m_tech_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddAllInRange(spaces, loc, yield, Yield(m_food_wealth_adder, m_tech_adder,0,0,0,0), SEABASS);
   AddAllInRange(spaces, loc, yield, Yield(0, m_tech_adder,m_food_wealth_adder,0,0,0), PARROTFISH);
}

void Anglerfish::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_tech_multiplier, unsigned m_awe_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   if (mask & YIELD_MASK_AWE)
   {
      Yield neighboring_food;
      for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      {
	 if ((spaces[i].m_source->Type() == MACKEREL) ||
	       (spaces[i].m_source->Type() == SEABASS) ||
	       (spaces[i].m_source->Type() == MARLIN))
	 {
	    Yield this_yield;
	    spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_FOOD);
	    neighboring_food += yield;
	 }
      }
      yield.m_tech += unsigned(neighboring_food.m_food * m_tech_multiplier);
   // KCJ Redo as post-process
      if (yield.m_tech >= 10)
	 yield.m_awe += m_awe_adder;
   }
}

void Tuna::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   unsigned i; 

   if (mask & YIELD_MASK_FOOD)
   {
      if (NotInRange(spaces, loc, yield.m_range, TUNA))
	 yield.m_food += m_food_adder;

      Yield neighboring_wealth;
      for (i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
      {
	 if ((spaces[i].m_source->Type() == CLOWNFISH) ||
	     (spaces[i].m_source->Type() == PARROTFISH) ||
	     (spaces[i].m_source->Type() == MARLIN))
	 {
	    Yield this_yield;
	    spaces[i].m_source->GetYield(spaces, i, this_yield, YIELD_MASK_WEALTH);
	    neighboring_wealth += yield;
	 }
      }
      yield.m_food += unsigned(neighboring_wealth.m_wealth * m_food_multiplier);
   }
}

void WhiteShark::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddAllInRange(spaces, loc, yield, Yield(0,0,0,4,0,0), WHITE_SHARK, MARLIN);

   // KCJ - redo as post process
   if (mask & YIELD_MASK_WEALTH)
   {
      std::vector<unsigned> danger_yield(spaces.size());
      GetDanger(spaces, loc, yield, danger_yield);
      yield.m_wealth += 40 - 2 * danger_yield[loc];
   }
}

void BlueWhale::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);
   if (((loc >= 1) && ((spaces[loc - 1].m_source->Class() == SOURCE_CLASS_NONE) ||
		       (spaces[loc - 1].m_source->Class() == NON_NATURAL)) )  &&
       (((loc + 1) < spaces.size()) && ((spaces[loc + 1].m_source->Class() == SOURCE_CLASS_NONE) ||
					(spaces[loc + 1].m_source->Class() == NON_NATURAL)) ) )
      yield.m_food += 25;

   AddAllInRange(spaces, loc, yield, Yield(5,0,0,0,5,0), TUNA, SEABASS, MACKEREL);
}

unsigned BlueWhale::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (((loc >= 1) && ((spaces[loc - 1].m_source->Class() == SOURCE_CLASS_NONE) ||
		       (spaces[loc - 1].m_source->Class() == NON_NATURAL)) )  &&
       (((loc + 1) < spaces.size()) && ((spaces[loc + 1].m_source->Class() == SOURCE_CLASS_NONE) ||
					(spaces[loc + 1].m_source->Class() == NON_NATURAL)) ) )
      range += 1;
   return range;
}

void Chicken::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfInRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), BLUEBERRY);
}

void Rabbit::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfInRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), RABBIT);
}

void Beaver::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, int m_natura_limit, unsigned mask) const
{
   unsigned i;
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   for (i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      if (spaces[i].m_yield.m_natura >= m_natura_limit)
	 yield.m_wealth += m_wealth_adder;
}

void Deer::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_awe_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfInRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,m_awe_adder,0), DANDELION, FOXGLOVE,NIGHTSHADE);
}

void Boar::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_multiplier, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   yield.m_wealth += yield.m_danger * m_wealth_multiplier;
}

void Wisent::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
	            unsigned m_food_multiplier, unsigned m_food_adder, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   yield.m_food += spaces[loc].m_yield.m_natura * m_food_multiplier;
   AddIfInRange(spaces, loc, yield, Yield(m_food_adder,0,m_wealth_adder,0,0,0), DEER, RABBIT);
}

void Moose::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   if (NotInRange(spaces, loc, yield.m_range, BOAR, WOLF, BEAR))
      yield.m_food += 15;
   AddAllInRange(spaces, loc, yield, Yield(6,0,0,0,0,0), PLANT);
}

void Stoat::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), MINERAL);
}

void Fox::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddAllInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), RABBIT, BEAVER, CHICKEN);
}

void Wolf::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
					unsigned m_animal_wealth_adder, unsigned m_animal_danger_adder, unsigned m_mineral_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(0,0,m_animal_wealth_adder,m_animal_danger_adder,0,0), DEER, WISENT, BOAR);
   AddAllInRange(spaces, loc, yield, Yield(0,0,0,1,0,0), MINERAL);

   //KCJ const bonus to other spaces
   if (mask == YIELD_MASK_ALL)
   {
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
	 if (spaces[i].m_source->Class() == MINERAL)
	    spaces[i].m_yield.m_wealth += m_mineral_wealth_adder;
   }
}

void Bear::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   // KCJ redo as post process
   if (mask & YIELD_MASK_WEALTH)
   {
      std::vector<unsigned> danger_yield(spaces.size());
      GetDanger(spaces, loc, yield, danger_yield);
      yield.m_wealth += 2 * danger_yield[loc];
   }
   AddAllInRange(spaces, loc, yield, Yield(3,0,0,0,0,0), DEER, WISENT, BOAR);
}

void KangarooRat::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfInRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), MINERAL);
}

void DesertTortoise::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), PLANT);
}

void Goat::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   // KCJ const global yield adder
   if (mask == YIELD_MASK_ALL)
   {
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
	 if (spaces[i].m_source->Class() == PLANT)
	    spaces[i].m_yield.m_food += m_food_adder;
   }
}

void Armadillo::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), MINERAL);
}

void Rattlesnake::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), KANGAROO_RAT, ARMADILLO, DESERT_TORTOISE);
}

void Javelina::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_danger_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(m_food_adder,0,0,m_danger_adder,0,0), JAVELINA);
}

void GreyFox::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);

   if (m_base_yield.m_wealth >= m_wealth_adder)
      yield.m_wealth += m_wealth_adder;
}

unsigned GreyFox::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (!NotAdjacent(spaces, loc, MINERAL))
      range += 1;
   return range;
}

void Coyote::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);;
   AddAllInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), JAVELINA, GOAT);
}

unsigned Coyote::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (NotAdjacent(spaces, loc, ANIMAL))
      range += 1;
   return range;
}

void GilaMonster::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_adder, int m_natura_limit, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   if (spaces[loc].m_yield.m_natura >= m_natura_limit)
      yield.m_wealth += m_adder;

   AddAllAdjacent(spaces, loc, yield, Yield(m_adder,0,0,0,0,0), PLANT);
   AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_adder,0,0,0), ANIMAL);
   AddAllAdjacent(spaces, loc, yield, Yield(0,m_adder,0,0,0,0), MINERAL);
}

void BigHorn::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllInRange(spaces, loc, yield, Yield(5,0,0,0,0,0), MINERAL);

   // KCJ const global adder
   if (mask == YIELD_MASK_ALL)
   {
   for (unsigned i = 0; i < spaces.size(); i+= 1)
      if ((spaces[i].m_source->Type() == GOAT) ||
          (spaces[i].m_source->Type() == DEER) )
	 spaces[i].m_yield.m_food += 3;
   }
}

void Bobcat::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);

   if (mask & YIELD_MASK_WEALTH)
   {
      // KCJ - redo as post-process
      std::vector<unsigned> danger_yield(spaces.size());
      GetDanger(spaces, loc, std::max<int>(0, (int)loc - yield.m_range), loc + yield.m_range, yield, danger_yield);

      unsigned seen_flag[SOURCE_CLASS_T_MAX] = {0};

      seen_flag[SOURCE_CLASS_NONE] = 1;
      seen_flag[NON_NATURAL] = 1;

      for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      {
	 if (danger_yield[i] >= 5)
	    yield.m_wealth += 5;
	 if ((i != loc) && !seen_flag[spaces[i].m_source->Class()])
	 {
	    seen_flag[spaces[i].m_source->Class()] = 1;
	    yield.m_wealth += 6;
	 }
      }
   }
}

unsigned Bobcat::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   unsigned animal_count = 0;
   for (unsigned i = std::max<int>(0, (int)loc - range); (i <= loc + range) && (i < spaces.size()); i+= 1)
      if (spaces[i].m_source->Class() == ANIMAL)
	 animal_count += 1;
   if (animal_count >= 3)
      range += 1;
   return range;
}


void Frog::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);
   AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), ELDERBERRY);
}

unsigned Frog::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (!NotAdjacent(spaces, loc, ELDERBERRY))
      range += 1;
   return range;
}

void PoisonDartFrog::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), ELDERBERRY);
}

unsigned PoisonDartFrog::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (!NotAdjacent(spaces, loc, ELDERBERRY))
      range += 1;
   return range;
}

void Otter::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), PLANT);
}

void Iguana::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_danger_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,m_danger_adder,0,0), MINERAL);
}

void Tapir::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, int m_natura_limit, unsigned mask) const
{
   unsigned i;
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   for (i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      if (spaces[i].m_yield.m_natura >= m_natura_limit)
	 yield.m_food += m_food_adder;
}

void Buffalo::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, double m_food_multiplier, unsigned m_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,0,0,0), HEMP, TOMATO, MARSH_MALLOW);
   if (mask == YIELD_MASK_ALL)
   {
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      {
	 if (spaces[i].m_source->Class() == PLANT)
	 {
	    // KCJ - adds based on plants' food only
	    Yield yield;
	    spaces[i].m_source->GetYield(spaces, i, yield, YIELD_MASK_FOOD);
	    spaces[i].m_yield.m_food += int(yield.m_food * m_food_multiplier);
	 }
      }
   }
}

void KomodoDragon::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);
   AddAllInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), IGUANA, POISON_DART_FROG);
   AddIfInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), BUFFALO);
   AddIfInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), OTTER);
   AddIfInRange(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), TAPIR);
}

unsigned KomodoDragon::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (!NotAdjacent(spaces, loc, IGUANA))
      range += 1;
   return range;
}

void Orangutan::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);
   AddAllInRange(spaces, loc, yield, Yield(0,12,0,0,0,0), RUBBER_TREE, COFFEA, WHITE_WILLOW);
   AddAllInRange(spaces, loc, yield, Yield(0,12,0,0,0,0), PAPAYA, CACAO_TREE);

   yield.m_tech += std::max<unsigned>(36, yield.m_tech);

   //KCJ - wrong - redo as post-process based on final tech on plant spaces
   if (mask == YIELD_MASK_ALL)
   {
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      {
	 if ((spaces[i].m_source->Type() == WHITE_WILLOW) ||
	     (spaces[i].m_source->Type() == COFFEA))
	 {
	    Yield yield;
	    spaces[i].m_source->GetYield(spaces, i, yield, YIELD_MASK_TECH);
	    spaces[i].m_yield.m_tech += int(yield.m_tech * 0.75);
	 }
      }
   }
}

unsigned Orangutan::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   unsigned tree_count = 0;
   for (unsigned i = std::max<int>(0, (int)loc - range); (i <= loc + range) && (i < spaces.size()); i+= 1)
      if ((spaces[i].m_source->Type() == RUBBER_TREE) ||
          (spaces[i].m_source->Type() == COFFEA) ||
          (spaces[i].m_source->Type() == WHITE_WILLOW) ||
          (spaces[i].m_source->Type() == PAPAYA) ||
          (spaces[i].m_source->Type() == CACAO_TREE))
	 tree_count += 1;
   if (tree_count >= 2)
      range += 1;

   return range;
}

void Crocodile::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   if (mask & YIELD_MASK_WEALTH)
   {
      unsigned mineral_count = 0;
      for (unsigned i = std::max<int>(0, (int)loc - yield.m_range); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
	 if (spaces[i].m_source->Class() == MINERAL)
	    mineral_count += 1;
      if (mineral_count >= 2)
	 yield.m_wealth += 20;
      else if (mineral_count == 1)
	 yield.m_wealth += 10;
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
      {
	 if ((spaces[i].m_source->Type() == BUFFALO) ||
	     (spaces[i].m_source->Type() == ORANGUTAN) ||
	     (spaces[i].m_source->Type() == TAPIR) )
	 {
	    yield.m_wealth += 12;
	    // KCJ const adder - redo as global
	    if (mask == YIELD_MASK_ALL)
	       spaces[i].m_yield.m_food -= 2;
	 }
      }
   }
}

void Marten::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_food_adder, unsigned m_danger_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(m_food_adder,0,0,m_danger_adder,0,0), MINERAL);
}

void Monal::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder, unsigned m_awe_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,m_awe_adder,0), PLANT);
}

void MuskDeer::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_danger_limit, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc, m_danger_limit);
}

unsigned MuskDeer::GetRange(std::vector<Space> &spaces, unsigned loc, unsigned m_danger_limit) const 
{
   unsigned range = m_base_yield.m_range;
   std::vector<unsigned> danger_yield(spaces.size());
   Yield yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   GetDanger(spaces, loc, yield, danger_yield);
   if (danger_yield[loc] >= m_danger_limit)
      range += 1;

   return range;
}
void Pangolin::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
      unsigned m_shy_food_adder, int m_natura_limit, unsigned m_peaceful_food_adder, unsigned m_awe_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   if(spaces[loc].m_yield.m_natura >= m_natura_limit) 
   {
      yield.m_food += m_shy_food_adder;
      yield.m_awe  += m_awe_adder;
   }

   // Hack up a way to check for 1 of 4 types
   Yield old_yield = yield;
   AddIfInRange(spaces, loc, yield, Yield(m_peaceful_food_adder,0,0,0,m_awe_adder,0), MONAL, MARTEN, LANGUR_MONKEY);
   if (old_yield == yield)
      AddIfInRange(spaces, loc, yield, Yield(m_peaceful_food_adder,0,0,0,m_awe_adder,0), YAK);
}

void SnowLeopard::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
      unsigned m_wealth_adder, unsigned m_peak_wealth_adder, unsigned m_danger_adder, unsigned mask) const 
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddAllAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), YAK, MUSK_DEER);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_peak_wealth_adder,m_danger_adder,0,0), SILVER, ZINC);
}

void LangurMonkey::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
      unsigned m_wealth_adder, unsigned m_tech_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_range = GetRange(spaces, loc);

   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), PLANT);
   AddAllAdjacent(spaces, loc, yield, Yield(0,m_tech_adder,0,0,0,0), CINNAMOMUM, LYCHEE, GINKGO);
}

unsigned LangurMonkey::GetRange(std::vector<Space> &spaces, unsigned loc) const 
{
   unsigned range = m_base_yield.m_range;
   if (!NotAdjacent(spaces, loc, PLANT))
      range += 1;
   return range;
}

void Yak::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield,
				   unsigned m_grazer_food_adder, unsigned m_no_animals_food_adder, unsigned m_one_animal_food_adder, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   yield.m_food += spaces[loc].m_yield.m_natura / 5;

   unsigned animal_count = 0;

   for (unsigned i = std::max<int>(0, (int)loc - 1); (i <= loc + 1) && (i < spaces.size()); i+= 1)
      if ((i != loc) && (spaces[i].m_source->Class() == ANIMAL))
	 animal_count += 1;
   if (animal_count == 0)
      yield.m_food += m_no_animals_food_adder;
   else if (animal_count == 1)
      yield.m_food += m_one_animal_food_adder;
}

void Panda::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask) const
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);

   AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,6,0,0), ANIMAL);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,0,0,8,0), MINERAL);

   // KCJ redo as const global adder
   if (mask == YIELD_MASK_ALL)
   {
      for (unsigned i = std::max<int>((int)loc - 1,0); (i <= loc + 1) && (i < spaces.size()); i+= 1)
	 if (spaces[i].m_source->Class() == PLANT)
	    spaces[i].m_yield.m_food += 15;
   }

   // KCJ redo as post-process
   if (mask & YIELD_MASK_WEALTH)
   {
      std::vector<unsigned> awe_yield(spaces.size());
      GetAwe(spaces, loc, std::max<int>((int)loc - yield.m_range,0), loc + yield.m_range, yield, awe_yield);
      unsigned awe = 0;
      for (unsigned i = std::max<int>((int)loc - yield.m_range,0); (i <= loc + yield.m_range) && (i < spaces.size()); i+= 1)
	 awe += awe_yield[i];
      yield.m_wealth += int(0.4 * awe);
   }
}

