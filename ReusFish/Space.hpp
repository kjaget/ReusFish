#pragma once

#include "Source.hpp"

class Space
{
	public:
		Space(void);
		Space(Source *source);
		Space(const Source *source);
		Space(const Source *source, int aspect);
		Space(const Space &space, int aspect);
		Space(const Space &other);
		Space& operator=(const Space &rhs);
		~Space();

		bool operator==(const Space &rhs) const;
		size_t Hash (void) const;
		void Print(void) const;

		const Source *m_source;
		Yield         m_yield;
};
