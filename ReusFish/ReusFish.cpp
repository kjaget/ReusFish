#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <limits>

#include "Aspects.hpp"
#include "Animal.hpp"
#include "Biome.hpp"
#include "Giants.hpp"
#include "Mineral.hpp"
#include "Plant.hpp"
#include "Source.hpp"
#include "Space.hpp"
#include "UsedList.hpp"
#include "Yield.hpp"

class Building : public Source
{
   public :
      Building() {m_class = NON_NATURAL; m_type = BUILDING; m_start = 0; m_end = 0;}
      Building(unsigned start, unsigned end) { m_class = NON_NATURAL; m_type = BUILDING, m_start = start; m_end = end; }
      virtual Building* Clone() const {return new Building(*this);}
   protected:
      unsigned  char m_start;
      unsigned  char m_end;
};

class City : public Building
{
   public :
      City()
      {
	 Create();
      }

      City(unsigned start, unsigned end)	
      {
		  (void)start;
		  (void)end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "City";
      }
};

class Building1 : public Building
{
   public :
      Building1()
      {
	 Create();
      }

      Building1(unsigned start, unsigned end)	
      {
		  m_start = start;
		  m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Building 1";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
	 Yield dummy_yield;
	 AddAllInRange(spaces, loc, dummy_yield, m_start, m_end, Yield(0,10,5,0,0,0), MINERAL);
	 if (dummy_yield.m_tech > 30)
	    dummy_yield = Yield(0,10*3,5*3,0,0,0);
	 yield += dummy_yield;

	 std::vector<unsigned> food_yield;
	 GetFood(spaces, loc, m_start, m_end, yield, food_yield);
	 unsigned food = 0;
	 for (unsigned i = m_start; i <= m_end; i++)
	    food += food_yield[i];

	 yield.m_tech   += food / 2;
	 yield.m_wealth += food / 2;
      }
};

class Building2 : public Building
{
   public :
      Building2()
      {
	 Create();
      }

      Building2(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Building 2";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
	 AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), COFFEA, TEA_PLANT);

	 std::vector<unsigned> tech_yield;
	 GetTech(spaces, loc, std::max<int>(0, int(loc) - 1), (loc + 1), yield, tech_yield);
	 unsigned tech = 0;
	 for (unsigned i = std::max<int>(0, int(loc) - 1); (i <= (loc + 1)) && (i < spaces.size()); i++)
	    tech += tech_yield[i];

	 yield.m_tech += tech / 2;
      }
};

class Mill: public Building
{
   public :
      Mill()
      {
	 Create();
      }

      Mill(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Mill";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
		  (void)loc;
	 unsigned plant_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Class() == PLANT)
	       plant_count += 1;

	 plant_count = std::min<unsigned>(plant_count,3);
	 yield.m_food += 15 * plant_count;

	 unsigned animal_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if ((spaces[i].m_source->Type() == BOAR) ||
		  (spaces[i].m_source->Type() == RABBIT))
	       animal_count += 1;

	 if (animal_count == 1)
	    yield.m_tech += 100;
	 else if (animal_count == 2)
	    yield.m_tech += 50;
      }
};

class Circus: public Building
{
   public :
      Circus()
      {
	 Create();
      }

      Circus(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Circus";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
		  (void)loc;
	 bool seen_flag[BIOME_T_MAX] = {0};

	 seen_flag[BIOME_NONE] = true;

	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	 {
	    if ((spaces[i].m_source->Class() == ANIMAL) && !seen_flag[biome_list[i]])
	    {
	       seen_flag[biome_list[i]] = true;
	       yield.m_food += 30;
	       yield.m_tech += 10;
	       yield.m_wealth += 30;
	    }
	 }
      }
};


class Market: public Building
{
   public :
      Market()
      {
	 Create();
      }

      Market(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Market";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
		  (void)loc;
	 unsigned animal_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Class() == ANIMAL)
	       animal_count += 1;

	 animal_count = std::min<unsigned>(animal_count,3);
	 yield.m_food += 15 * animal_count;

	 unsigned salt_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Type() == SALT)
	       salt_count += 1;
	 if (salt_count > 0)
	    yield.m_wealth += 35;
	 if (salt_count > 1)
	    yield.m_wealth += 25;
	 if (salt_count > 2)
	    yield.m_wealth += 15;

      }
};

class Multinational: public Building
{
   public :
      Multinational()
      {
	 Create();
      }

      Multinational(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Multinational";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
		  (void)loc;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if ((spaces[i].m_source->Class() == ANIMAL) ||
	        (spaces[i].m_source->Class() == MINERAL) ||
	        (spaces[i].m_source->Class() == PLANT))
	       yield.m_wealth += 5;

	 unsigned wealth_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Type() == SALT)
	       wealth_count += 1;
	 wealth_count = std::min<unsigned>(wealth_count,3);
	 yield.m_wealth += 50 * wealth_count;

      }
};
class Bank: public Building
{
   public :
      Bank()
      {
	 Create();
      }

      Bank(unsigned start, unsigned end)	
      {
	 m_start = start;
	 m_end = end;
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Bank";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
      {
		  (void)mask;
	 AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(25,0,25,0,0,0), LYCHEE, TOPAZ, CHILLI_PEPPER);

	 std::vector<unsigned> wealth_yield;
	 GetWealth(spaces, loc, (int)loc - 1, loc + 1, yield, wealth_yield);
	 for (unsigned i = loc - 1; i <= loc + 1; i++)
	    if (i != loc)
	       yield.m_wealth += wealth_yield[i];
      }
};

class Lighthouse : public Building
{
   public:
      Lighthouse()
      {
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Lighthouse";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const 
      {
		  (void)loc;
	 yield.Reset();

	 unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};

	 // hard coded city extents for now...
	 for (unsigned i = 4; i < 9; i+= 1)
	 {
	    if ((biome_list[i] == OCEAN) && 
		(spaces[i].m_source->Class() == ANIMAL) && 
		(spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
	    {
	       yield.m_tech   += 5;
	       yield.m_wealth += 5;
	       if (spaces[i].m_source->Type() == ANGLERFISH)
		  yield.m_wealth += 50;
	       if (!seen_flag[spaces[i].m_source->Type()])
	       {
		  seen_flag[spaces[i].m_source->Type()] = 1;
		  yield.m_food += 35;
	       }
	    }
	 }
      }
      virtual Lighthouse* Clone() const {return new Lighthouse(*this);}
};

class Harbor : public Building
{
   public:
      Harbor()
      {
	 Create();
      }

      virtual void Create(void)
      {
	 m_name = "Harbor";
      }

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
		  (void)loc;
	 yield.Reset();

	 // hard coded city extents for now...
	 for (unsigned i = 4; i < 9; i+= 1)
	 {
	    if ((biome_list[i] == OCEAN) && (spaces[i].m_source->Class() == ANIMAL) && (spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
	    {
	       yield.m_food   += 5;
	       yield.m_wealth += 5;
	       if (i >= 7)
		  yield.m_food  += 10;
	    }
	 }
	 for (unsigned i = 0; i < spaces.size(); i+= 1)
	 {
	    if (spaces[i].m_source->Type() == SEABASS)
	    {
	       Yield this_yield;
	       spaces[i].m_source->GetYield(spaces, i, yield);
	       for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j < (i + yield.m_range)) && (j < spaces.size()); j++)
		  if ((j >= 4) && (j <= 17))
		     yield.m_food += unsigned(yield.m_food * 0.5);
	    }
	 }
      }
      virtual Harbor* Clone() const {return new Harbor(*this);}
};

#include "Landscape.hpp"
static std::priority_queue<Landscape, std::deque<Landscape> > priority_queue;
UsedList<unsigned, Landscape> used_list;

void remaining_moves(unsigned initial_pos)
{
   Landscape landscape;
   int best_score = std::numeric_limits<int>::min();
   bool logging = false;
   unsigned upgrades_added = 0;
   unsigned aspects_added = 0;
   unsigned landspaces_processed = 0;

   while (!priority_queue.empty())
   {
      landscape = priority_queue.top();
      priority_queue.pop();
      if (priority_queue.size() > 100000000)
	 logging = true;

      if (!used_list.Insert(landscape))
	 continue;
      if ((landscape.Score() > best_score))
      {
	 std::cout << "***************************************************" << std::endl;
	 std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landspaces_processed << std::endl;

	 if (landscape.BeatsGoal())
	 {
	    std::cout << "Beats goal" << std::endl;
	    used_list.Print();
	 }
	 landscape.PrintAll();
	 best_score = landscape.Score();
      }
      if ((++landspaces_processed % 100000) == 0)
	 std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << " Landscapes " << landspaces_processed << std::endl;

      SourceList upgrades;
      for (int pos = (int)initial_pos; pos >= 0; pos--)
      {
	 landscape[pos].m_source->GetUpgrades(biome_list[pos], upgrades);
	 for (unsigned i = 0; i < upgrades.size(); i++)
	 {
	    Space saved_space = landscape[pos];
	    landscape[pos] = Space(upgrades[i]);
	    landscape.SetYield();
	    if (logging)
	    {
	       std::cout << "***************************************************" << std::endl;
	       std::cout << "Upgrades " << upgrades_added << " Aspects " << aspects_added << std::endl;
	       landscape.Print();
	    }

	    //if (used_list.Insert(landscape))
	    {
	       upgrades_added += 1;
	       priority_queue.push(landscape);
	    }
	    landscape[pos] = saved_space;
	 }

	 for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
	 {
	    // Skip lesser aspects
	    // Use greater aspect instead of potent one if possible
	    if ((aspect & 3) && 
		  !(((aspect & 3) == 1) && aspects.IsValid((Aspects::aspect_t)(aspect + 1), landscape[pos].m_source->Class())) &&
		  aspects.IsValid((Aspects::aspect_t)aspect, landscape[pos].m_source->Class()) &&
		  landscape[pos].m_source->CanAddAspect((Aspects::aspect_t)aspect))
	    {
	       Space saved_space = landscape[pos];
	       landscape[pos] = Space(landscape[pos], aspect);
	       landscape.SetYield();
	       if (logging)
	       {
		  std::cout << "***************************************************" << std::endl;
		  landscape.Print();
	       }
	       //if (used_list.Insert(landscape))
	       {
		  aspects_added+=1;
		  priority_queue.push(landscape);
	       }
	       landscape[pos] = saved_space;
	    }
	 }
      }
   }
}

void initial_moves(Landscape &spaces, int pos, const Giants &giants)
{
   if (pos < 0)
   {
      static int best_score = std::numeric_limits<int>::min();

      spaces.SetYield();
      int score = spaces.Score();
      //if (used_list.Insert(spaces))
      {
	 if ((score > best_score))
	 {
	    std::cout << "***************************************************" << std::endl;
	    if (spaces.BeatsGoal())
	    {
	       std::cout << "Beats goal" << std::endl;
	       used_list.Print();
	    }
	    spaces.PrintAll();
	    best_score = score;
	 }
	 //if (used_list.Insert(spaces))
	 priority_queue.push(spaces);
      }
      return;
   }

   // For each space which isn't a building, grab the list of possible starting sources
   // for this biome.
   if (spaces[pos].m_source->Class() != NON_NATURAL)
   {
      SourceList source_list = giants.GetSources(biome_list[pos]);
      for (unsigned i = 0; i < source_list.size(); i++)
      {
	 spaces[pos] = Space(source_list[i]);
	 initial_moves(spaces, pos - 1, giants);
      }
   }
   else
      initial_moves(spaces, pos - 1, giants);
}

static unsigned city_start = 0;
static unsigned city_end = 14;
unsigned char Landscape::m_start = city_start;
unsigned char Landscape::m_end   = city_end;
Yield Landscape::m_goal  = Yield(200, 200, 1250, 0, 0, 0);

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
   Landscape spaces(15);
   Giants giants;

   biome_list[0] = MOUNTAIN;
   biome_list[1] = MOUNTAIN;
   biome_list[2] = MOUNTAIN;
   biome_list[3] = MOUNTAIN;
   biome_list[4] = DESERT;
   biome_list[5] = DESERT;
   biome_list[6] = DESERT;
   biome_list[7] = DESERT;
   biome_list[8] = DESERT;
   biome_list[9] = DESERT;
   biome_list[10] = DESERT;
   biome_list[11] = MOUNTAIN;
   biome_list[12] = MOUNTAIN;
   biome_list[13] = MOUNTAIN;
   biome_list[14] = MOUNTAIN;
  
   spaces[0] = Space(new Multinational(city_start, city_end));
   spaces[1] = Space(new Source());
   spaces[2] = Space(new Source());
   spaces[3] = Space(new Source());
   spaces[4] = Space(new City());
   spaces[5] = Space(new City());
   spaces[6] = Space(new City());
   spaces[7] = Space(new City());
   spaces[8] = Space(new Market(city_start, city_end));
   spaces[9] = Space(new Source());
   spaces[10] = Space(new Source());
   spaces[11] = Space(new Source());
   spaces[12] = Space(new Source());
   spaces[13] = Space(new Source());
   spaces[14] = Space(new Source());

   initial_moves(spaces,12,giants);
   remaining_moves(12);

   return 0;

#if 0
   for (i = 1; i < 6; i++)
      biome_list[i] = MOUNTAIN;
   for (; i < 11; i++)
   biome_list[i] = DESERT;
   for (; i < 15; i++)
      biome_list[i] = MOUNTAIN;

   spaces[0] = Space(new Source());
   spaces[1] = Space(new Bank(city_start, city_end));
   for (i = 2; i < 6; i++)
      spaces[i] = Space(new Source());
   for (; i < 10; i++)
      spaces[i] = Space(new City());
   spaces[i++] = Space(new Market(city_start, city_end));
   for (; i < 15; i++)
      spaces[i] = Space(new Source());
   initial_moves(spaces,13);
   remaining_moves(13);

   return 0;
#endif
#if 0
   Landscape test_spaces (17, 0, 15, Yield(50, 300, 75, 0, 25, 0));
   test_spaces[0] = Space(OCEAN, new Great_Mackerel());
   test_spaces[0].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[1] = Space(OCEAN, new Great_Mackerel());
   test_spaces[1].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[2] = Space(OCEAN, new Great_Clownfish());
   test_spaces[2].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[2].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[3] = Space(OCEAN, new Great_Clownfish());
   test_spaces[3].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[3].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[4] = Space(SWAMP);
   test_spaces[5] = Space(SWAMP);
   test_spaces[6] = Space(SWAMP);
   test_spaces[7] = Space(SWAMP);
   test_spaces[7] = Space(SWAMP, new Building1(0,15));
   test_spaces[8] = Space(SWAMP, new Great_Onyx());
   test_spaces[8].m_source->AddAspect(Aspects::POTENT_CRYSTAL);
   test_spaces[8].m_source->AddAspect(Aspects::POTENT_CRYSTAL);
   test_spaces[8].m_source->AddAspect(Aspects::POTENT_CRYSTAL);
   test_spaces[8].m_source->AddAspect(Aspects::POTENT_CRYSTAL);
   test_spaces[12] = Space(SWAMP, new Building2(0,15));

   test_spaces.SetYield();
   test_spaces.PrintAll();
   return 0;
   SourceList upgrades;
   for (unsigned pos = 0; pos < 3; pos++)
   {
      test_spaces[pos].m_source->GetUpgrades(test_spaces[pos].Biome(), upgrades);
   }
   for (unsigned pos = 0; pos < 3; pos++)
      test_spaces[pos].m_source->AddAspect(Aspects::LESSER_PREDATOR);
   for (unsigned pos = 0; pos < 3; pos++)
   {
      test_spaces[pos].m_source->GetUpgrades(test_spaces[pos].Biome(), upgrades);
   }
   test_spaces.SetYield();
   test_spaces.PrintAll();
   return 0;
#endif
#if 0
   unsigned city_start = 0;
   unsigned city_end = 14;
   Landscape spaces(16, city_start, city_end, Yield(50,300,75,0,20,0));
   unsigned i;

   for (i = 0; i < 5; i++)
      biome_list[i] = OCEAN;
   for (; i < 16; i++)
      biome_list[i] = SWAMP;

   for (i = 0; i < 5; i++)
      spaces[i] = Space(new Source());
   for (; i < 9; i++)
      spaces[i] = Space(new City());
   spaces[i++] = Space(new Building1(city_start, city_end));
   for (; i < 14; i++)
      spaces[i] = Space(new Source());
   spaces[i++] = Space(new Building2(city_start, city_end));
   for (; i < 16; i++)
      spaces[i] = Space(new Source());
#endif
#if 0
   Landscape spaces(3, 0, 3, Yield(50,300,75,0,20,0));
   unsigned i;
   for (i = 0; i < 3; i++)
      biome_list[i] = SWAMP;
   spaces[0] = Space(new Great_Tomato());
   spaces[1] = Space(new Building1(0,2));
   spaces[2] = Space(new Tomato());
   spaces.SetYield();
   spaces.PrintAll();
   initial_moves(spaces,1);
   remaining_moves(1);
   return 0;
#endif
}
