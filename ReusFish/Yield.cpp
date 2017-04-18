#include <iostream>
#include <limits>
#include "Yield.hpp"

Yield::Yield() :
	m_food   (0),
	m_tech   (0),
	m_wealth (0),
	m_danger (0),
	m_awe    (0),
	m_natura (0),
	m_range  (0),
	m_natura_range(0)
{
}

Yield::Yield(unsigned short food, 
			unsigned short tech,
			unsigned short wealth,
			unsigned short danger,
			short          awe,
			short          natura) :
	m_food   (food),
	m_tech   (tech),
	m_wealth (wealth),
	m_danger (danger),
	m_awe    (awe),
	m_natura (natura),
	m_range  (0),
	m_natura_range(0)
{
}

Yield::Yield(unsigned short food, 
		unsigned short tech, 
		unsigned short wealth,
		unsigned short danger,
		short          awe,
		short          natura,
		unsigned char  range = 0,
		unsigned char  natura_range = 0) :
	m_food   (food),
	m_tech   (tech),
	m_wealth (wealth),
	m_danger (danger),
	m_awe    (awe),
	m_natura (natura),
	m_range  (range),
	m_natura_range(natura_range)
{
}

void Yield::Reset(void)
{
	m_food         = 0;
	m_tech         = 0;
	m_wealth       = 0;
	m_danger       = 0;
	m_awe          = 0;
	m_natura       = 0;
	m_range        = 0;
	m_natura_range = 0;
}

Yield& Yield::operator+= (const Yield &rhs)
{
	m_food   += rhs.m_food;
	m_tech   += rhs.m_tech;
	m_wealth += rhs.m_wealth;
	m_danger += rhs.m_danger;
	m_awe    += rhs.m_awe;
	m_natura += rhs.m_natura;
	// Ranges don't add
	return *this;
}
bool Yield::operator> (const Yield &rhs) const
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
bool Yield::operator==(const Yield &rhs) const
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

void Yield::Print(void) const
{
	std::cout << "F" << m_food;
	std::cout << " T" << m_tech;
	std::cout << " W" << m_wealth;
	std::cout << " D" << m_danger;
	std::cout << " A" << m_awe;
	std::cout << " N" << m_natura;
	std::cout << " R" << (unsigned) m_range;
	std::cout << " NR" << (unsigned) m_natura_range;
}
void Yield::Add(const Yield &rhs, unsigned mask)
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
void Yield::AddFood(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_FOOD)
		m_food += adder;
}
void Yield::AddTech(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_TECH)
		m_tech += adder;
}
void Yield::AddWealth(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_WEALTH)
	{
		if ((adder > 0) && ((unsigned short)(adder + m_wealth) < m_wealth) )
			m_wealth = std::numeric_limits<unsigned short>::max();
		else if ((adder < 0) && ((unsigned short)(adder + m_wealth) > m_wealth) )
			m_wealth = std::numeric_limits<unsigned short>::min();
		else
			m_wealth += adder;
	}
}
void Yield::AddDanger(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_DANGER)
		m_danger += adder;
}
void Yield::AddAwe(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_AWE)
		m_awe += adder;
}
void Yield::AddNatura(int adder, unsigned mask)
{
	if (mask & YIELD_MASK_NATURA)
		m_natura += adder;
}
unsigned Yield::GetMask(void) const
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

