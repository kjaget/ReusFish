#pragma once

#include "SourceType.hpp"
#include "SourceFactory.hpp"

class SourceTypeList : public SourceFactory<source_type_t, unsigned char>
{
	public :
		SourceTypeList(void);
		unsigned GetBestSourceLevel(source_type_t t);

	private :
		std::array<unsigned, SOURCE_TYPE_T_MAX> m_best_sources;
		unsigned m_init;
};
