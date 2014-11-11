#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
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
      Building() {m_class = NON_NATURAL; m_type = BUILDING; }
      virtual Building* Clone() const {return new Building(*this);}
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 yield.Reset();

	 unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};

	 // hard coded city extents for now...
	 for (unsigned i = 4; i < 9; i+= 1)
	 {
	    if ((spaces[i].m_source->Class() == FISH) && (spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
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

      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)
      {
	 yield.Reset();

	 // hard coded city extents for now...
	 for (unsigned i = 4; i < 9; i+= 1)
	 {
	    if ((spaces[i].m_source->Class() == FISH) && (spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
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
      Landscape(unsigned size, unsigned start, unsigned end) : 
	 m_spaces(size),
	 m_start(start),
	 m_end(end) 
      {}
      Landscape(unsigned size, unsigned start, unsigned end, const Yield &goal) : 
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
      unsigned size(void) const
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

      bool BeatsGoal(void)
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
	    yield += m_spaces[i].m_yield;
	    superior_count += m_spaces[i].m_source->CountAspects(Aspects::SUBLIME);
	    greater_count  += m_spaces[i].m_source->CountAspects(Aspects::GREATER);
	 }

	 score += ScoreHelper(goal.m_food, yield.m_food, 5000.0);
	 score += ScoreHelper(goal.m_tech, yield.m_tech, 5000.0);
	 score += ScoreHelper(goal.m_wealth, yield.m_wealth, 5000.0);
	 score += ScoreHelper(goal.m_danger, yield.m_danger, 5000.0);
	 score += ScoreHelper(goal.m_awe, yield.m_awe, 5000.0);
	 score += ScoreHelper(goal.m_natura, yield.m_natura, 5000.0);

	 int delta = score - INT_MIN;

	 delta = (int)((double)delta * (1. - 0.01 * superior_count - 0.005 * greater_count));
	 score = delta - INT_MIN;
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

      void Print(void)
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
	 std::cout << " H:" << Hash() << std::endl;
	 for (unsigned i = 0; i < m_spaces.size(); i++)
	 {
	    m_spaces[i].Print();
	    std::cout << " :: " ;
	    Yield yield;
	    m_spaces[i].m_source->GetNatura(m_spaces, i, yield);
	    unsigned natura = yield.m_natura;
	    unsigned range  = yield.m_range;
	    m_spaces[i].m_source->GetYield(m_spaces, i, yield);
	    yield.m_natura = natura;
	    yield.m_range = std::max<int>(yield.m_range, range);
	    yield.Print();
	    std::cout << std::endl;
	 }
      }

   private:
      std::vector<Space> m_spaces;
      unsigned           m_start;
      unsigned           m_end;
      Yield              m_goal;
};

#if 0
class FishFactory
{
   public:
      FishFactory() : m_level_limit(3) {}
      void LevelLimit(unsigned limit) {m_level_limit = limit;}
      typedef std::function<Fish*()> Builder;

      void Register(Builder const& builder) {
	 Fish *dummy = builder();
	 if (dummy->Level() <= m_level_limit)
	    m_vector.push_back(builder);
	 delete dummy;
      }

      unsigned Size(void) const
      {
	 return m_vector.size();
      }

      /// returns a pointer to a new instance of Fish (or a derived class)
      /// if the index was valid, 0 otherwise
      Fish* Build(unsigned index) const {
	 if (index >= Size()) return NULL;
	 return (m_vector[index])();
      }

   private:
      std::vector<Builder> m_vector;
      unsigned m_level_limit;
};

template <typename Derived> Fish* FishBuilder() { return new Derived(); }
static FishFactory fish_factory;


void permute(Landscape &spaces, int pos, unsigned start_pos, unsigned end_pos)
{
   unsigned i;
   static Yield best_food;
   static Yield best_tech;
   static Yield best_wealth;
   static Yield best_yield;

   if (pos < 0)
   {
      Yield yield;
      spaces.SetYield();
      spaces.GetYield(yield, start_pos, end_pos);
      bool print = false;
      unsigned total;
      unsigned best_total;

      if ((yield.m_food > 200) && (yield.m_tech > 50) && (yield.m_wealth > 125))
      {

      if ((yield.m_food > 0) && ((yield.m_food > best_food.m_food) || 
	  ((yield.m_food == best_food.m_food) && ((yield.m_tech + yield.m_wealth) >= (best_food.m_tech + best_food.m_wealth) ))))
      {
	 best_food = yield;
	 std::cout << "Best food " << std::endl;
	 print = true;
      }
      if ((yield.m_tech > 0) && ((yield.m_tech > best_tech.m_tech) || 
	  ((yield.m_tech == best_tech.m_tech) && ((yield.m_food + yield.m_wealth) >= (best_tech.m_food + best_tech.m_wealth) ))))
      {
	 best_tech = yield;
	 std::cout << "Best tech" << std::endl;
	 print = true;
      }
      if ((yield.m_wealth > 0) && ((yield.m_wealth > best_wealth.m_wealth) || 
	  ((yield.m_wealth == best_wealth.m_wealth) && ((yield.m_food + yield.m_tech) >= (best_wealth.m_food + best_wealth.m_tech) ))))
      {
	 best_wealth = yield;
	 std::cout << "Best wealth " << std::endl;
	 print = true;
      }

      total = yield.m_food + yield.m_tech + yield.m_wealth;
      best_total = best_yield.m_food + best_yield.m_tech + best_yield.m_wealth;
      if ((total > 0) && (total >= best_total))
      {
	 best_yield = yield;
	 std::cout << "Best total" << std::endl;
	 print = true;
      }

      if (print)
      {
	 std::cout << "Food = " << yield.m_food << " Wealth = " << yield.m_wealth << " Tech = " << yield.m_tech << " Score = " << spaces.Score() << std::endl;
	 spaces.PrintAll();
	 std::cout << "***************************************************" << std::endl;
      }
      }
      return;
   }

   while ((pos > 0) && (spaces[pos].m_source->Class() != FISH))
	   pos -= 1;
   
   if (spaces[pos].m_source->Class() == FISH)
   {
      for (i = 0; i < fish_factory.Size(); i++)
      {
	 if (spaces[pos].m_source)
	    delete spaces[pos].m_source;
	 spaces[pos].m_source = fish_factory.Build(i);
	 permute(spaces, pos - 1, start_pos, end_pos);
      }
   }
   else
      permute(spaces, pos - 1, start_pos, end_pos);
}
#endif
static std::priority_queue<Landscape> priority_queue;
UsedList<unsigned, Landscape> used_list;

void remaining_moves(unsigned initial_pos)
{
   
   Landscape landscape;
   int best_score = INT_MIN;

   while (!priority_queue.empty())
   {
      landscape = priority_queue.top();
      priority_queue.pop();
      	       if (landscape.BeatsGoal() || (landscape.Score() >= best_score))
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
	    landscape[pos].m_source->GetUpgrades(landscape[pos].Biome(), upgrades);
	    for (unsigned i = 0; i < upgrades.size(); i++)
	    {
	       Space saved_space = landscape[pos];
	       landscape[pos] = Space(landscape[pos].Biome(), upgrades[i]);
	       landscape.SetYield();
	       if (used_list.Insert(landscape))
	          priority_queue.push(landscape);
	       landscape[pos] = saved_space;
	    }

	    for (unsigned aspect = 0; aspect < Aspects::ASPECT_T_MAX ; aspect++)
	    {
	       if (aspects.IsValid((Aspects::aspect_t)aspect, landscape[pos].m_source->Class()) &&
		     landscape[pos].m_source->AddAspect((Aspects::aspect_t)aspect))
	       {
		  landscape.SetYield();
		  if (used_list.Insert(landscape))
		     priority_queue.push(landscape);
		  landscape[pos].m_source->RemoveNewestAspect();
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
	  if (used_list.Insert(spaces))
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
      SourceList source_list = giants.GetSources(spaces[pos].Biome());
      for (unsigned i = 0; i < source_list.m_sources.size(); i++)
      {
	 spaces[pos] = Space(spaces[pos].Biome(), source_list[i]);
	 initial_moves(spaces, pos - 1);
      }
   }
   else
      initial_moves(spaces, pos - 1);
}

int main (int argc, char **argv)
{
   Landscape test_spaces (6, 0, 6, Yield());
   test_spaces[0] = Space(SWAMP, new Salt());
   test_spaces[0].m_source->AddAspect(Aspects::LESSER_SEISMIC);
   test_spaces[1] = Space(SWAMP, new Great_Phosphorus ());
   test_spaces[1].m_source->AddAspect(Aspects::GREATER_REACTION);
   test_spaces[2] = Space(SWAMP, new Great_Elderberry());

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
#if 0
   unsigned size = 4;
   if (argc > 1)
   {
      size = atoi(argv[1]);
      std::cout << size << std::endl;
   }
   if (argc > 2)
   {
      unsigned limit = atoi(argv[2]);
      fish_factory.LevelLimit(limit);
   }

   Landscape spaces(size+8);
#endif
   Landscape spaces(18, 4, 12, Yield(200,50,125,0,0,0,0,0));
#if 0
   for (unsigned i = 0; i < 10; i++)
   {
      spaces[i] = Space(OCEAN);
      if (spaces[i].m_source)
	 delete spaces[i].m_source;
   }
   spaces[0].m_source = new Great_Tuna;
   spaces[1].m_source = new BlueWhale;
   spaces[2].m_source = new Superior_Parrotfish;
   spaces[3].m_source = new Superior_Parrotfish;
   spaces[4].m_source = new Great_Marlin;
   spaces[5].m_source = new Lighthouse;
   spaces[6].m_source = new Superior_Parrotfish;
   spaces[7].m_source = new Superior_Clownfish;
   spaces[8].m_source = new BlueWhale;
   spaces[9].m_source = new Harbor;
      Yield yield;
      spaces.SetYield();
      spaces.GetYield(yield, 4, 12);
	 std::cout << "Food = " << yield.m_food << " Wealth = " << yield.m_wealth << " Tech = " << yield.m_tech << std::endl;
	 spaces.PrintAll();
	 std::cout << "***************************************************" << std::endl;
#else
   unsigned i;
   for (i = 0; i < 0; i++)
      spaces[i] = Space(FOREST);
   for (; i < 10; i++)
      spaces[i] = Space(OCEAN);
   for (; i < 18; i++)
      spaces[i] = Space(FOREST);

   spaces[5] = Space(OCEAN, new Lighthouse);
   spaces[9] = Space(OCEAN, new Harbor);

//   Landscape spaces2(spaces);

#if 0
   fish_factory.Register(FishBuilder<Fish>);
//   fish_factory.Register(FishBuilder<Mackerel>);
   fish_factory.Register(FishBuilder<Great_Mackerel>);
   fish_factory.Register(FishBuilder<Superior_Mackerel>);
//   fish_factory.Register(FishBuilder<Clownfish>);
   fish_factory.Register(FishBuilder<Great_Clownfish>);
//   fish_factory.Register(FishBuilder<Superior_Clownfish>);
//   fish_factory.Register(FishBuilder<Seabass>);
   fish_factory.Register(FishBuilder<Great_Seabass>);
   fish_factory.Register(FishBuilder<Superior_Seabass>);
//   fish_factory.Register(FishBuilder<Parrotfish>);
   fish_factory.Register(FishBuilder<Great_Parrotfish>);
   fish_factory.Register(FishBuilder<Superior_Parrotfish>);

   fish_factory.Register(FishBuilder<Marlin>);
   fish_factory.Register(FishBuilder<Great_Marlin>);

   fish_factory.Register(FishBuilder<Tuna>);
   fish_factory.Register(FishBuilder<Great_Tuna>);

   //fish_factory.Register(FishBuilder<Anglerfish>);
   //fish_factory.Register(FishBuilder<Great_Anglerfish>);

   fish_factory.Register(FishBuilder<BlueWhale>);
   //fish_factory.Register(FishBuilder<WhiteShark>);
#endif

   initial_moves(spaces, 8);
   remaining_moves(8);
#endif

   return 0;
}
