#pragma once

#include "Source.hpp"
#include "Space.hpp"

class Building : public Source
{
	public :
		Building(void);
		void SetStartEnd(unsigned start, unsigned end);

		virtual Building* Clone(void) const;

	protected:
		unsigned char m_start;
		unsigned char m_end;
};

class City : public Building
{
	public :
		City(void);
		virtual City* Clone(void) const;
};

class Mill: public Building
{
	public :
		Mill();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Mill* Clone(void) const;
};

class Druid: public Building
{
	public :
		Druid(void);
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Druid *Clone(void) const;
};

class Shrine: public Building
{
	public :
		Shrine(void);
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Shrine *Clone(void) const;
};

class Circus: public Building
{
	public :
		Circus(void);
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Circus *Clone(void) const;
};


class Market: public Building
{
	public :
		Market(void);
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Market *Clone(void) const;
};

class Bank: public Building
{
	public :
		Bank(void);

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Bank *Clone(void) const;
};

class Lighthouse : public Building
{
	public:
		Lighthouse(void);

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Lighthouse* Clone(void) const;
};

class Harbor : public Building
{
	public:
		Harbor(void);
		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Harbor* Clone(void) const;
};

class University: public Building
{
	public :
		University();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		University* Clone(void) const;
};


class Geologist: public Building
{
	public :
		Geologist();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Geologist* Clone(void) const;
};

class Alchemist: public Building
{
	public :
		Alchemist();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Alchemist* Clone(void) const;
};
class Apothecary: public Building
{
	public :
		Apothecary();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Apothecary* Clone(void) const;
};
class Workshop: public Building
{
	public :
		Workshop();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Workshop* Clone(void) const;
};
