#include <iostream>
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
	     unsigned short awe,
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
	     unsigned short awe,
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
