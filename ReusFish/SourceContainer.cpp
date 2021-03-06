#include "SourceContainer.hpp"

SourceContainer::~SourceContainer()
{
	for (auto it = m_hash.begin(); it != m_hash.end(); it++)
		delete it->second;
}
const Source *SourceContainer::Add(Source *source)
{
	size_t hash = source->Hash();
	auto range = m_hash.equal_range(hash);
	bool found;

	for (found = false; !found && (range.first != range.second); ++range.first)
		if ((range.first->second == source) || (*(range.first->second) == *source))
		{
			found = true;
			break;
		}

	if (found)
	{
		// Don't delete the pointers stored in the hash
		if (range.first->second != source)
			delete source;
		return range.first->second;
	}

	m_hash.insert(std::pair<unsigned, const Source *> (hash, source));
	return source;
}
const Source *SourceContainer::Add(const Source *source)
{
	size_t hash = source->Hash();
	auto range = m_hash.equal_range(hash);
	bool found;

	for (found = false; !found && (range.first != range.second); ++range.first)
		if ((range.first->second == source) || (*(range.first->second) == *source))
		{
			found = true;
			break;
		}

	if (found)
	{
		// Don't delete the pointers stored in the hash
		if (range.first->second != source)
			std::cout << "SourceContainer.Add - found different pointer in const * version " << std::endl; 
		return range.first->second;
	}

	m_hash.insert(std::pair<unsigned, const Source *> (hash, source));
	return source;
}

SourceContainer source_container;
