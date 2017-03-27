#pragma once

#include "Source.hpp"
#include "Space.hpp"

class Building : public Source
{
	public :
		Building() {m_class = NON_NATURAL; m_type = BUILDING; m_start = 0; m_end = 0;}
		Building(unsigned start, unsigned end) { m_class = NON_NATURAL; m_type = BUILDING, m_start = start; m_end = end; }
		virtual Building* Clone() const {return new Building(*this);}

		virtual void SetStartEnd(unsigned start, unsigned end)
		{
			m_start = start;
			m_end = end;
		}
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
			m_start = start;
			m_end = end;
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
			if (mask & (YIELD_MASK_TECH | YIELD_MASK_WEALTH))
			{
				Yield dummy_yield;
				AddAllInRange(spaces, loc, dummy_yield, m_start, m_end, Yield(0,10,5,0,0,0), mask, MINERAL);
				if (dummy_yield.m_tech > 30)
					dummy_yield = Yield(0,10*3,5*3,0,0,0);
				yield += dummy_yield;

				std::vector<unsigned> food_yield;
				GetFood(spaces, loc, m_start, m_end, yield, food_yield);
				unsigned food = 0;
				for (unsigned i = m_start; i <= m_end; i++)
					food += food_yield[i];

				yield.AddTech(food / 2, mask);
				yield.AddWealth(food / 2, mask);
			}
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
			AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(0,25,0,0,0,0), mask, COFFEA, TEA_PLANT);


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
			(void)loc;
			AddInRange(spaces, loc, yield, m_start, m_end, Yield(15,0,0,0,0,0), mask, ANIMAL, 3);
			AddInRange(spaces, loc, yield, m_start, m_end, Yield(35,0,0,0,0,0), mask, FOXGLOVE, DANDELION, DANDELION, 2);

#if 0
			if (mask & YIELD_MASK_TECH)
			{
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
#endif
		}
};

class Druid: public Building
{
	public :
		Druid()
		{
			Create();
		}

		Druid(unsigned start, unsigned end)	
		{
			m_start = start;
			m_end = end;
			Create();
		}

		virtual void Create(void)
		{
			m_name = "Druid";
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			(void)loc;
			AddInRange(spaces, loc, yield, m_start, m_end, Yield(0,15,0,0,0,0), mask, MINERAL, 3);
		}
};

class Shrine: public Building
{
	public :
		Shrine()
		{
			Create();
		}

		Shrine(unsigned start, unsigned end)	
		{
			m_start = start;
			m_end = end;
			Create();
		}

		virtual void Create(void)
		{
			m_name = "Shrine";
		}

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			(void)loc;
			AddInRange(spaces, loc, yield, m_start, m_end, Yield(10,0,5,0,0,0), mask, ANIMAL, 3);
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
			(void)loc;
			if (mask & (YIELD_MASK_FOOD | YIELD_MASK_TECH | YIELD_MASK_WEALTH))
			{
				bool seen_flag[BIOME_T_MAX] = {0};

				seen_flag[BIOME_NONE] = true;

				for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
				{
					if ((spaces[i].m_source->Class() == ANIMAL) && !seen_flag[biome_list[i]])
					{
						seen_flag[biome_list[i]] = true;
						yield.AddFood(30, mask);
						yield.AddTech(10, mask);
						yield.AddWealth(30, mask);
					}
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
			(void)loc;
			if (mask & YIELD_MASK_FOOD)
			{
				unsigned animal_count = 0;
				for (unsigned i = m_start; (i <= m_end) && (i < spaces.size()); i+= 1)
					if (spaces[i].m_source->Class() == ANIMAL)
						animal_count += 1;

				animal_count = std::min<unsigned>(animal_count,3);
				yield.m_food += 15 * animal_count;
			}
			if (mask & YIELD_MASK_WEALTH)
			{
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
			(void)loc;
			if (mask & YIELD_MASK_WEALTH)
			{
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
			AddAllInRange(spaces, loc, yield, m_start, m_end, Yield(25,0,25,0,0,0), mask, LYCHEE, TOPAZ, CHILLI_PEPPER);

			if (mask & YIELD_MASK_WEALTH)
			{
				std::vector<unsigned> wealth_yield;
				GetWealth(spaces, loc, (int)loc - 1, loc + 1, yield, wealth_yield);
				for (unsigned i = loc - 1; i <= loc + 1; i++)
					if (i != loc)
						yield.m_wealth += wealth_yield[i];
			}
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const 
		{
			(void)loc;
			yield.Reset();

			unsigned seen_flag[SOURCE_TYPE_T_MAX] = {0};

			// hard coded city extents for now...
			if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH | YIELD_MASK_TECH))
			{
				for (unsigned i = 4; i < 9; i+= 1)
				{
					if ((biome_list[i] == OCEAN) && 
							(spaces[i].m_source->Class() == ANIMAL) && 
							(spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
					{
						yield.AddTech(5, mask);
						yield.AddWealth(5, mask);
						if (spaces[i].m_source->Type() == ANGLERFISH)
							yield.AddWealth(50, mask);
						if (!seen_flag[spaces[i].m_source->Type()])
						{
							seen_flag[spaces[i].m_source->Type()] = 1;
							yield.AddFood(35, mask);
						}
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

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const
		{
			(void)loc;
			yield.Reset();

			// hard coded city extents for now...
			if (mask & (YIELD_MASK_FOOD | YIELD_MASK_WEALTH))
			{
				for (unsigned i = 4; i < 9; i+= 1)
				{
					if ((biome_list[i] == OCEAN) && (spaces[i].m_source->Class() == ANIMAL) && (spaces[i].m_source->Type() !=  SOURCE_TYPE_NONE))
					{
						yield.AddFood(5, mask);
						yield.AddWealth(5, mask);
						if (i >= 7)
							yield.AddFood(10, mask);
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
								yield.AddFood(yield.m_food * 0.5, mask);
					}
				}
			}
		}
		virtual Harbor* Clone() const {return new Harbor(*this);}
};

