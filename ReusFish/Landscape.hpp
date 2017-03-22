#ifndef LANDSCAPE_INC__
#define LANDSCAPE_INC__
#include <vector>
#include "Space.hpp"
#include "Yield.hpp"

class Landscape
{
   public:
      Landscape() : 
	 m_spaces(18)
      {}
      Landscape(unsigned size) : m_spaces(size)
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
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	    food += m_spaces[i].m_yield.m_food;
	 return food;
      }
      unsigned Tech(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned tech = 0;
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	    tech += m_spaces[i].m_yield.m_tech;
	 return tech;
      }
      unsigned Wealth(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned wealth = 0;
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	    wealth += m_spaces[i].m_yield.m_wealth;
	 return wealth;
      }
      unsigned Awe(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned awe = 0;
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	    awe += m_spaces[i].m_yield.m_awe;
	 return awe;
      }
      unsigned Danger(unsigned start_pos, unsigned end_pos) const
      {
	 unsigned danger = 0;
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	    danger += m_spaces[i].m_yield.m_danger;
	 return danger;
      }
      void GetYield(Yield &yield, unsigned start_pos, unsigned end_pos) const
      {
	 yield.Reset();
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
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
	    Yield yield;
	    m_spaces[i].m_source->GetYield(m_spaces, i, yield);
	    yield.m_natura = 0;
	    for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < m_spaces.size()); j++)
	       m_spaces[j].m_yield += yield;
	 }
	 // Need a temp non-const copy of Spaces to run post-processing on
	 // Can't use m_spaces since those pointers are consts and point to
	 // a global pool of shared sources.  That doesn't guaratee that each
	 // entry in the array will be unique so one Source might be shared
	 // by two or more entries in m_spaces.
	 //
	 std::vector <Source *> sources;

	 for (unsigned i = 0; i < m_spaces.size(); i++)
	    sources.push_back(m_spaces[i].m_source->Clone());

	 bool changed;
	 Yield yield;
	 std::vector<Yield> global_yield(m_spaces.size());
	 do
	 {
	    changed = false;
	    for (unsigned i = 0; i < m_spaces.size(); i++)
	    {
	       
	       if (sources[i]->PostProcess(m_spaces, i, yield, global_yield))
	       {
		  changed = true;
		  for (unsigned j = std::max<int>(0, (int)i - yield.m_range); (j <= i + yield.m_range) && (j < m_spaces.size()); j++)
		     m_spaces[j].m_yield += yield;
		  for (unsigned j = 0; j < m_spaces.size(); j++)
		     m_spaces[j].m_yield += global_yield[j];
	       }
	    }
	 }
	 while (changed);

	 for (unsigned i = 0; i < m_spaces.size(); i++)
	    delete sources[i];
      }

      bool BeatsGoal(void) const
      {
	 Yield yield;
	 for (unsigned i = m_start; (i <= m_end) && (i < size()); i++)
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
	 //unsigned superior_count = 0;
	 //unsigned greater_count = 0;
	 Yield yield;
	 for (unsigned i = start_pos; (i <= end_pos) && (i < size()); i++)
	 {
	    if (m_spaces[i].m_source)
	    {
	       yield += m_spaces[i].m_yield;
	 //      superior_count += m_spaces[i].m_source->CountAspects(Aspects::SUBLIME);
	 //      greater_count  += m_spaces[i].m_source->CountAspects(Aspects::GREATER);
	    }
	 }

	 score += ScoreHelper(goal.m_food, yield.m_food, 5000.0);
	 score += ScoreHelper(goal.m_tech, yield.m_tech, 5000.0);
	 score += ScoreHelper(goal.m_wealth, yield.m_wealth, 5000.0);
	 score += ScoreHelper(goal.m_danger, yield.m_danger, 5000.0);
	 score += ScoreHelper(goal.m_awe, yield.m_awe, 5000.0);
	 score += ScoreHelper(goal.m_natura, yield.m_natura, 5000.0);

#if 0
	 score -= greater_count * 5000/100;
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
      std::vector<Space>    m_spaces;
      static unsigned char  m_start;
      static unsigned char  m_end;
      static Yield          m_goal;
};
#endif
