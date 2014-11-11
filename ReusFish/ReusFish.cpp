#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>

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
      unsigned  m_start;
      unsigned  m_end;
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 unsigned plant_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Class() == PLANT)
	       plant_count += 1;

	 plant_count = std::min<unsigned>(plant_count,3);
	 yield.m_food += 15 * plant_count;

	 unsigned animal_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if ((spaces[i].m_source->Class() == BOAR) ||
	       (spaces[i].m_source->Class() == RABBIT))
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 unsigned animal_count = 0;
	 for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
	    if (spaces[i].m_source->Class() == ANIMAL)
	       animal_count += 1;

	 animal_count = std::min<unsigned>(animal_count,3);
	 yield.m_food += 15 * animal_count;

	 AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,0,25,0,5,0), GREY_FOX, RATTLESNAKE);
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield) const
      {
	 AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(25,0,25,0,0,0), LYCHEE, TOPAZ, CHILLI_PEPPER);

	 std::vector<unsigned> wealth_yield;
	 GetWealth(spaces, loc, (int)loc - 1, loc + 1, yield, wealth_yield);
	 unsigned food = 0;
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

class Landscape
{
   public:
      Landscape() : 
	 m_spaces(18),
	 m_start(0),
	 m_end(0)
      {}
      Landscape(unsigned size) : m_spaces(size),
	 m_start(0),
	 m_end(0)
      {}
      Landscape(unsigned size, unsigned char start, unsigned char end) : 
	 m_spaces(size),
	 m_start(start),
	 m_end(end)
      {}
      Landscape(unsigned size, unsigned char start, unsigned char end, const Yield &goal) : 
	 m_spaces(size),
	 m_start(start),
	 m_end(end),
	 m_goal(goal)
      {}
      bool operator<(const Landscape &rhs) const
      {
	 return Score() < rhs.Score();
      }
      Space &operator [] (const unsigned i)
      {
	 return m_spaces[i];
      }
      const Space &operator [] (const unsigned i) const
      {
	 return m_spaces[i];
      }
      bool operator==(const Landscape &rhs) const
      {
	 return m_spaces == rhs.m_spaces;
      }
      unsigned Hash(void) const
      {
	 unsigned hash = 0x600DF00D;

	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
	    unsigned this_hash = m_spaces[i].Hash();
	    hash += this_hash << (i%32);
	    hash += (this_hash & ~0x80000000U) >> (32 - (i%32));
	 }
	 return hash;
      }
      size_t size(void) const
      {
	 return m_spaces.size();
      }
      unsigned Food(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned food = 0;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    food += m_spaces[i].m_yield.m_food;
	 return food;
      }
      unsigned Tech(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned tech = 0;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    tech += m_spaces[i].m_yield.m_tech;
	 return tech;
      }
      unsigned Wealth(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned wealth = 0;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    wealth += m_spaces[i].m_yield.m_wealth;
	 return wealth;
      }
      unsigned Awe(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned awe = 0;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    awe += m_spaces[i].m_yield.m_awe;
	 return awe;
      }
      unsigned Danger(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned danger = 0;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    danger += m_spaces[i].m_yield.m_danger;
	 return danger;
      }
      void GetYield(Yield &yield, unsigned start_pos, unsigned end_pos) const
      {
	 yield.Reset();
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	    yield += m_spaces[i].m_yield;
      }
      void GetYield(Yield &yield) const
      {
	 GetYield(yield, m_start, m_end);
      }
      void Reset(void)
      {
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	    m_spaces[i].m_yield.Reset();
      }
      void SetYield(void)
      {
	 Reset();

	 // Calculate natura first since it controls the rest of the 
	 // yield of each space
	 std::vector<Yield> natura_yield(m_spaces.size());

	 for (unsigned i = 0; i < m_spaces.size(); i++)
	    if (m_spaces[i].m_source)
	       m_spaces[i].m_source->GetNatura(m_spaces, i, natura_yield[i]);

	 // Natura is the max of all sources in range
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
	    unsigned this_natura = natura_yield[i].m_natura;
	    unsigned this_range  = natura_yield[i].m_natura_range;
	    for (unsigned j = std::max<int>(0, (int)i - this_range); (j <= i + this_range) && (j < m_spaces.size()); j++)
	       m_spaces[j].m_yield.m_natura = std::max<int>(m_spaces[j].m_yield.m_natura, this_natura);
	 }

	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
	    if (m_spaces[i].m_source)
	    {
	       Yield yield;
	       m_spaces[i].m_source->GetYield(m_spaces, i, yield);
	       yield.m_natura = 0;
	       for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < m_spaces.size()); j++)
		  m_spaces[j].m_yield += yield;
	    }
	 }
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	    if ((m_spaces[i].m_source) && (m_spaces[i].m_source->Type() == FLUORITE))
	    {
	       if (m_spaces[i].m_yield.m_tech >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	       if (m_spaces[i].m_yield.m_food >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	       if (m_spaces[i].m_yield.m_wealth >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	       if (m_spaces[i].m_yield.m_danger >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	       if (m_spaces[i].m_yield.m_awe >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	       if (m_spaces[i].m_yield.m_natura >= 10)
		  m_spaces[i].m_yield.m_tech += 25;
	    }
      }

      bool BeatsGoal(void) const
      {
	 Yield yield;
	 for (unsigned i = m_start; (i < m_end) && (i < size()); i++)
	    yield += m_spaces[i].m_yield;
	 if (yield > m_goal)
	    return true;
	 return false;
      }

      int ScoreHelper(unsigned goal, unsigned val, double multiplier) const
      {
	 int score = 0;
	 if (goal)
	 {
	    // Give linear improvement until goal is hit. At that point,
	    // additional yield doesn't matter that much
	    if (val > goal)
	    {
	       score = (int)multiplier;
	       if (val > (1.5*goal))
		  val = (int)(1.5*goal);
	       score += int((double(val - goal) / goal) * (multiplier / 75.0));
	    }
	    else
	       score = int((double)val / goal * multiplier);
	 }
	 return score;
      }
      int Score(const Yield &goal, unsigned start_pos, unsigned end_pos) const
      {
	 int score = 0;
	 unsigned superior_count = 0;
	 unsigned greater_count = 0;
	 Yield yield;
	 for (unsigned i = start_pos; (i < end_pos) && (i < size()); i++)
	 {
	    if (m_spaces[i].m_source)
	    {
	       yield += m_spaces[i].m_yield;
	       superior_count += m_spaces[i].m_source->CountAspects(Aspects::SUBLIME);
	       greater_count  += m_spaces[i].m_source->CountAspects(Aspects::GREATER);
	    }
	 }

	 score += ScoreHelper(goal.m_food, yield.m_food, 5000.0);
	 score += ScoreHelper(goal.m_tech, yield.m_tech, 5000.0);
	 score += ScoreHelper(goal.m_wealth, yield.m_wealth, 5000.0);
	 score += ScoreHelper(goal.m_danger, yield.m_danger, 5000.0);
	 score += ScoreHelper(goal.m_awe, yield.m_awe, 5000.0);
	 score += ScoreHelper(goal.m_natura, yield.m_natura, 5000.0);

	 score -= greater_count * 5000/100;
#if 0
	 int delta = score - INT_MIN;

	 delta = (int)((double)delta * (1. - 0.01 * superior_count - 0.005 * greater_count));
	 score = delta - INT_MIN;
#endif
	 return score;
      }

      int Score(const Yield &goal) const
      {
	 return Score(goal, m_start, m_end);
      }

      int Score(void) const
      {
	 return Score(m_goal, m_start, m_end);
      }

      void Print(void) const
      {
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
	    m_spaces[i].Print();
	    std::cout << std::endl;
	 }
      }
      void PrintAll(void)
      {
	 std::cout << "S:" << Score();
	 std::cout << " F:" << Food(m_start, m_end);
	 std::cout << " T:" << Tech(m_start, m_end);
	 std::cout << " W:" << Wealth(m_start, m_end);
	 std::cout << " D:" << Danger(m_start, m_end);
	 std::cout << " A:" << Awe(m_start, m_end);
	 std::cout << " H:" << Hash() << std::endl;
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
		 biome_list.Print(i);
	    m_spaces[i].Print();
		if (m_spaces[i].m_source)
		{
	    std::cout << " :: " ;
	    Yield yield;
	    m_spaces[i].m_source->GetNatura(m_spaces, i, yield);
	    unsigned natura = yield.m_natura;
	    m_spaces[i].m_source->GetYield(m_spaces, i, yield);
	    yield.m_natura = natura;
	    yield.Print();
		}
	    std::cout << std::endl;
	 }
      }

   private:
      unsigned char      m_start;
      unsigned char      m_end;
      std::vector<Space> m_spaces;
      Yield              m_goal;
};

static std::priority_queue<Landscape, std::deque<Landscape> > priority_queue;
UsedList<unsigned, Landscape> used_list;

void remaining_moves(unsigned initial_pos)
{
   Landscape landscape;
   int best_score = INT_MIN;

   while (!priority_queue.empty())
   {
      landscape = priority_queue.top();
      priority_queue.pop();

      if (!used_list.Insert(landscape))
	 continue;
      if (landscape.BeatsGoal() || (landscape.Score() > best_score))
      {
	 std::cout << "***************************************************" << std::endl;
	 if (landscape.BeatsGoal())
	 {
	    std::cout << "Beats goal" << std::endl;
	    used_list.Print();
	 }
	 landscape.PrintAll();
	 best_score = landscape.Score();
      }

      SourceList upgrades;
      for (int pos = (int)initial_pos; pos >= 0; pos--)
      {
	 landscape[pos].m_source->GetUpgrades(biome_list[pos], upgrades);
	 for (unsigned i = 0; i < upgrades.size(); i++)
	 {
	    Space saved_space = landscape[pos];
	    landscape[pos] = Space(upgrades[i]);
	    landscape.SetYield();
	    //      if (used_list.Insert(landscape))
	    priority_queue.push(landscape);
	    landscape[pos] = saved_space;
	 }


	 for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
	 {
	    if (aspects.IsValid((Aspects::aspect_t)aspect, landscape[pos].m_source->Class()) &&
		  landscape[pos].m_source->CanAddAspect((Aspects::aspect_t)aspect))
	    {
	       Space saved_space = landscape[pos];
	       landscape[pos] = Space(landscape[pos], aspect);
	       landscape.SetYield();
	       //	  if (used_list.Insert(landscape))
	       priority_queue.push(landscape);
	       landscape[pos] = saved_space;
	    }
	 }
      }
   }
}

void initial_moves(Landscape &spaces, int pos)
{
   if (pos < 0)
   {
      static int best_score = INT_MIN;

      spaces.SetYield();
      int score = spaces.Score();
      //if (used_list.Insert(spaces))
      {
	 if (spaces.BeatsGoal() || (score > best_score))
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
	 initial_moves(spaces, pos - 1);
      }
   }
   else
      initial_moves(spaces, pos - 1);
}

int main (int argc, char **argv)
{
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
#else
#if 1
   unsigned city_start = 0;
   unsigned city_end = 14;
   Landscape spaces(15, city_start, city_end, Yield(75,75,300,0,0,0));
   unsigned i;

   biome_list[0] = DESERT;
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
#endif
   initial_moves(spaces,13);
   remaining_moves(13);

   return 0;
}
