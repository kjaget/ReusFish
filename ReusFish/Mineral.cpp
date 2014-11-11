#include "Mineral.hpp"


void Agate::GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_wealth_adder)
{
   yield = m_base_yield;
   GetAspects(spaces[loc].m_yield.m_natura, yield);
   AddIfAdjacent(spaces, loc, yield, Yield(0,0,m_wealth_adder,0,0,0), ANIMAL);
}

