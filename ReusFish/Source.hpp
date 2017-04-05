#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>
#include <limits>

#include "Aspects.hpp"
#include "Biome.hpp"
#include "SourceClass.hpp"
#include "SourceType.hpp"
#include "SourceTypeList.hpp"

class Space;
typedef std::vector<const Source *> SourceList;

// This source upgrades to <new_source> with <aspect1> or <aspect2>
class Upgrade
{
	public:
		Upgrade(void) : 
			m_new_source(SOURCE_TYPE_NONE), 
			m_aspect1(Aspects::ASPECT_T_MAX),
			m_aspect2(Aspects::ASPECT_T_MAX) 
		{}
		Upgrade(source_type_t source_type,
				Aspects::aspect_t aspect1,
				Aspects::aspect_t aspect2) : 
			m_new_source(source_type), 
			m_aspect1(aspect1), 
			m_aspect2(aspect2) 
		{}

		bool operator==(const Upgrade &rhs) const
		{
			return ((m_new_source == rhs.m_new_source) &&
					(m_aspect1 == rhs.m_aspect1) &&
					(m_aspect2 == rhs.m_aspect2));
		}
		source_type_t m_new_source;
		Aspects::aspect_t m_aspect1;
		Aspects::aspect_t m_aspect2;
};

class Source
{
	public :
		Source(void);
		Source(const Source &original);
		Source(const std::vector<Aspects::aspect_t> &aspects);
		virtual void Create(void);
		virtual ~Source();
		bool operator==(const Source &rhs) const;
		source_class_t Class(void) const;
		source_type_t  Type(void)  const;
		unsigned char  UpgradeCount(void) const;
		size_t Hash(void) const;

		virtual void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned mask = YIELD_MASK_ALL) const;
		virtual void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield) const;
		virtual unsigned GetRange(std::vector<Space> &spaces, unsigned loc) const;
		virtual bool PostProcess(const std::vector<Space> &spaces, unsigned loc, Yield &yield, std::vector<Yield> &global_yield) ;
		virtual void ResetPostProcess(void);
		void GetAspects(unsigned natura, Yield &yield, unsigned mask) const;
		bool AddAspect(Aspects::aspect_t aspect);
		bool CanAddAspect(Aspects::aspect_t aspect) const;
		unsigned CountAspects(Aspects::aspect_class_t aspect_class) const;
		virtual void GetUpgrades (biome_t biome, SourceList &upgrades) const;
		virtual bool IsValidForBiome(biome_t biome) const;
		void SetUpgradeCount(unsigned char upgrade_count);
		virtual Source* Clone() const;
		void Print(void) const;

	protected:
		void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3, unsigned max_count) const;

		void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3, unsigned max_count) const;
		void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const;
		void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const;
		void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const;

		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const;
		void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const;
		void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const;
		void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const;
		void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2, source_type_t type3) const;
		void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1, source_type_t type2) const;
		void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_type_t type1) const;

		// Same as above, but classes rather than types
		void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_class_t source_class, unsigned max_count) const;
		void AddInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, 
				const Yield &yield_adder, unsigned mask, source_class_t source_class, unsigned max_count) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const;
		void AddAllInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield, int start, unsigned end,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const;
		void AddIfInRange(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const;

		void AddIfAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const;
		void AddAllAdjacent(const std::vector<Space> &spaces, unsigned loc, Yield &yield,
				const Yield &yield_adder, unsigned mask, source_class_t source_class) const;

		// 
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, int start, unsigned end, source_class_t source_class) const;
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range, source_class_t source_class) const;
		bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_class_t source_class) const;
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, int start, unsigned end,
				source_type_t type1, source_type_t type2, source_type_t type3) const; 
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
				source_type_t type1, source_type_t type2, source_type_t type3) const ;
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
				source_type_t type1, source_type_t type2) const;
		bool NotInRange(const std::vector<Space> &spaces, unsigned loc, unsigned range,
				source_type_t type1) const;
		bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
				source_type_t type1, source_type_t type2, source_type_t type3);

		bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc,
				source_type_t type1, source_type_t type2) const;
		bool NotAdjacent(const std::vector<Space> &spaces, unsigned loc, source_type_t type1) const;


		void GetFood(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &food_yield) const;
		void GetFood(std::vector<Space> &spaces, unsigned loc, int start, int end, const Yield &yield, std::vector<unsigned> &food_yield) const;
		void GetTech(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &tech_yield) const;
		void GetTech(std::vector<Space> &spaces, unsigned loc, int start, int end, const Yield &yield, std::vector<unsigned> &tech_yield) const;
		void GetWealth(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &wealth_yield) const;
		void GetWealth(std::vector<Space> &spaces, unsigned loc, int start, int end, const Yield &yield, std::vector<unsigned> &wealth_yield) const;
		void GetDanger(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &danger_yield) const;
		void GetDanger(std::vector<Space> &spaces, unsigned loc, int start, int end, const Yield &yield, std::vector<unsigned> &danger_yield) const;
		void GetAwe(std::vector<Space> &spaces, unsigned loc, const Yield &yield, std::vector<unsigned> &awe_yield) const;
		void GetAwe(std::vector<Space> &spaces, unsigned loc, int start, int end, const Yield &yield, std::vector<unsigned> &awe_yield) const;

		void AddUpgrade(source_type_t source_type, Aspects::aspect_t aspect1, Aspects::aspect_t aspect2 = Aspects::ASPECT_T_MAX);

		source_class_t                 m_class;
		source_type_t                  m_type;
		unsigned char                  m_level;
		unsigned char                  m_max_aspects;
		unsigned char                  m_upgrade_count;
		const char                    *m_name;
		Yield                          m_base_yield;
		std::vector<Aspects::aspect_t> m_aspects;
		std::vector<Upgrade>           m_upgrades;
};

