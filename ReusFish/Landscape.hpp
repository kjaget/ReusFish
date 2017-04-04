#pragma once

#include <vector>
#include "Space.hpp"
#include "Yield.hpp"

class Landscape
{
	public:
		Landscape(void);
		Landscape(unsigned size);

		bool operator<(const Landscape &rhs) const;
		bool operator==(const Landscape &rhs) const;

		Space &operator [] (const unsigned i);
		const Space &operator [] (const unsigned i) const;

		size_t Hash(void) const;
		size_t size(void) const;

		void Reset(void);
		void AddSpace(biome_t biome, const Source &source);
		void AddSpace(biome_t biome);
		void StartCity(void);
		void EndCity(void);
		void SetGoal(const Yield &goal);
		void SetYield(void);

		bool BeatsGoal(void) const;
		int Score(const Yield &goal, unsigned start_pos, unsigned end_pos) const;
		int Score(const Yield &goal) const;
		int Score(void) const;
		void Print(void) const;
		void PrintAll(void);

	private:
		void GetYield(Yield &yield, unsigned start_pos, unsigned end_pos) const;
		void GetYield(Yield &yield) const;
		int ScoreHelper(unsigned goal, unsigned val, double multiplier) const;
		unsigned Food(unsigned start_pos, unsigned end_pos) const;
		unsigned Tech(unsigned start_pos, unsigned end_pos) const;
		unsigned Wealth(unsigned start_pos, unsigned end_pos) const;
		unsigned Awe(unsigned start_pos, unsigned end_pos) const;
		unsigned Danger(unsigned start_pos, unsigned end_pos) const;

		std::vector<Space>   m_spaces;
		static unsigned char m_start;
		static unsigned char m_end;
		static Yield         m_goal;
};
