#pragma once

static const unsigned YIELD_MASK_FOOD   = 0x1;
static const unsigned YIELD_MASK_TECH   = 0x2;
static const unsigned YIELD_MASK_WEALTH = 0x4;
static const unsigned YIELD_MASK_DANGER = 0x8;
static const unsigned YIELD_MASK_AWE    = 0x10;
static const unsigned YIELD_MASK_NATURA = 0x20;
static const unsigned YIELD_MASK_ALL    = 0xFF;

class Yield
{
	public:
		Yield();
		Yield(unsigned short food, 
			  unsigned short tech, 
			  unsigned short wealth,
			  unsigned short danger, 
			  unsigned short awe, 
			  short          natura);
		Yield(unsigned short food, 
				unsigned short tech, 
				unsigned short wealth,
				unsigned short danger, 
				unsigned short awe, 
				short          natura, 
				unsigned char  range,
				unsigned char  natura_range);
		void Reset(void);
		Yield& operator+= (const Yield &rhs);
		bool operator> (const Yield &rhs) const
		{
			if ((rhs.m_food > 0) && (rhs.m_food > m_food))
				return false;
			if ((rhs.m_tech > 0) && (rhs.m_tech > m_tech))
				return false;
			if ((rhs.m_wealth > 0) && (rhs.m_wealth > m_wealth))
				return false;
			if ((rhs.m_danger > 0) && (rhs.m_danger > m_danger))
				return false;
			if ((rhs.m_awe > 0) && (rhs.m_awe > m_awe))
				return false;
			if ((rhs.m_natura != 0) && (rhs.m_natura > m_natura))
				return false;
			return true;
		}
		bool operator==(const Yield &rhs) const
		{
			return (m_food == rhs.m_food) &&
				(m_tech == rhs.m_tech) &&
				(m_wealth == rhs.m_wealth) &&
				(m_danger == rhs.m_danger) &&
				(m_awe == rhs.m_awe) &&
				(m_natura == rhs.m_natura) &&
				(m_range == rhs.m_range) &&
				(m_natura_range == rhs.m_natura_range) ;
		}
		void Print(void) const;

		void Add(const Yield &rhs, unsigned mask)
		{
			if (mask & YIELD_MASK_FOOD)
				m_food += rhs.m_food;
			if (mask & YIELD_MASK_TECH)
				m_tech += rhs.m_tech;
			if (mask & YIELD_MASK_WEALTH)
				m_wealth += rhs.m_wealth;
			if (mask & YIELD_MASK_DANGER)
				m_danger += rhs.m_danger;
			if (mask & YIELD_MASK_AWE)
				m_awe += rhs.m_awe;
			if (mask & YIELD_MASK_NATURA)
				m_natura += rhs.m_natura;
		}
		void AddFood(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_FOOD)
				m_food += adder;
		}
		void AddTech(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_TECH)
				m_tech += adder;
		}
		void AddWealth(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_WEALTH)
				m_wealth += adder;
		}
		void AddDanger(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_DANGER)
				m_danger += adder;
		}
		void AddAwe(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_AWE)
				m_awe += adder;
		}
		void AddNatura(int adder, unsigned mask)
		{
			if (mask & YIELD_MASK_NATURA)
				m_natura += adder;
		}
		unsigned GetMask(void) const
		{
			unsigned mask = 0;
			if (m_food) mask |= YIELD_MASK_FOOD;
			if (m_tech) mask |= YIELD_MASK_TECH;
			if (m_wealth) mask |= YIELD_MASK_WEALTH;
			if (m_danger) mask |= YIELD_MASK_DANGER;
			if (m_awe) mask |= YIELD_MASK_AWE;
			if (m_natura) mask |= YIELD_MASK_NATURA;
			return mask;
		}

		unsigned short m_food;
		unsigned short m_tech;
		unsigned short m_wealth;
		unsigned short m_danger;
		unsigned short m_awe;
		short m_natura;
		unsigned char  m_range;
		unsigned char  m_natura_range;
};

