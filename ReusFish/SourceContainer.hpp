#pragma once

#include <unordered_map>

#include "Source.hpp"

class SourceContainer
{
	public:
		~SourceContainer();
		const Source *Add(Source *source);
		const Source *Add(const Source *source);

	private:
		std::unordered_multimap<unsigned, const Source *> m_hash;
};

extern SourceContainer source_container;
