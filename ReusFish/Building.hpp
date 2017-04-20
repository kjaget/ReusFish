#pragma once

#include "Source.hpp"
#include "Source.hpp"
#include "Space.hpp"

class Building : public Source
{
	public :
		Building(void);
		Building(const Building &other);
		Building(const Yield &completion_requirements);
		void SetStartEnd(unsigned char start, unsigned char end);
		const Yield &GetCompletionRequirements(void) const;
		bool CheckClassCompletion(const std::array<unsigned char, SOURCE_CLASS_T_MAX> &class_count) const;
		void SetClassCompletionCount(source_class_t source_class, unsigned char count);
		bool NeedsClassCount(void) const;

		virtual Building* Clone(void) const;

	protected:
		unsigned char m_start;
		unsigned char m_end;
	private:
		Yield         m_completion_requirements;
		bool          m_needs_class_count;
		std::array<unsigned char, SOURCE_TYPE_T_MAX> m_completion_class_count;
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
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield);
		Bank *Clone(void) const;
	private:
		bool m_post_processed;
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
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield);
		Harbor* Clone(void) const;
	private:
		bool m_post_processed;
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

class CustomsHouse: public Building
{
	public :
		CustomsHouse();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		CustomsHouse* Clone(void) const;
};
class Temple: public Building
{
	public :
		Temple();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Temple* Clone(void) const;
};
class Cathedral: public Building
{
	public :
		Cathedral();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Cathedral* Clone(void) const;
};

class BlastFurnace: public Building
{
	public :
		BlastFurnace();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		BlastFurnace* Clone(void) const;
};

class Hamlet: public Building
{
	public :
		Hamlet();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Hamlet* Clone(void) const;
};
class Barracks: public Building
{
	public :
		Barracks();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Barracks* Clone(void) const;
};
class InventorsTower: public Building
{
	public :
		InventorsTower();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		InventorsTower* Clone(void) const;
};
class Observatory: public Building
{
	public :
		Observatory();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield);
		
		Observatory* Clone(void) const;

	private:
		bool m_post_processed;
};
class Opera: public Building
{
	public :
		Opera();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		
		Opera* Clone(void) const;

	private:
		bool m_post_processed;
};
class Tradepost: public Building
{
	public :
		Tradepost();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Tradepost* Clone(void) const;
};
class Multinational: public Building
{
	public :
		Multinational();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Multinational* Clone(void) const;
};
class Castle: public Building
{
	public :
		Castle();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Castle* Clone(void) const;
};
class Hospital: public Building
{
	public :
		Hospital();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		Hospital* Clone(void) const;
};
class CanalTown: public Building
{
	public :
		CanalTown();

		void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		CanalTown* Clone(void) const;
};
