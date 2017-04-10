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
			  short          awe, 
			  short          natura);
		Yield(unsigned short food, 
				unsigned short tech, 
				unsigned short wealth,
				unsigned short danger, 
				short          awe, 
				short          natura, 
				unsigned char  range,
				unsigned char  natura_range);
		void Reset(void);
		Yield& operator+= (const Yield &rhs);
		bool operator> (const Yield &rhs) const;
		bool operator==(const Yield &rhs) const;
		void Print(void) const;

		void Add(const Yield &rhs, unsigned mask);
		void AddFood(int adder, unsigned mask);
		void AddTech(int adder, unsigned mask);
		void AddWealth(int adder, unsigned mask);
		void AddDanger(int adder, unsigned mask);
		void AddAwe(int adder, unsigned mask);
		void AddNatura(int adder, unsigned mask);
		unsigned GetMask(void) const;

		unsigned short m_food;
		unsigned short m_tech;
		unsigned short m_wealth;
		unsigned short m_danger;
		short          m_awe;
		short          m_natura;
		unsigned char  m_range;
		unsigned char  m_natura_range;
};

