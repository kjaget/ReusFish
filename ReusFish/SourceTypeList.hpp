#pragma once

#include "SourceType.hpp"
#include "SourceFactory.hpp"

class SourceTypeList : public SourceFactory<source_type_t, unsigned>
{
	public :
		SourceTypeList();
};
