#pragma once

#include <climits>
#include <cstring>
#include <unordered_map>
#include <vector>

#include "Landscape.hpp"

class UsedListContainer
{
	public:
		UsedListContainer(const Landscape &landscape);
		UsedListContainer(const UsedListContainer &orig);
		~UsedListContainer();
		bool operator==(const UsedListContainer &rhs) const;
		void SetHash(void);
		size_t Hash(void) const;

	protected:
		const Source **m_list;
		biome_t       *m_blist;
		size_t         m_hash;
		unsigned char  m_size;
};

template <class Key, class T> class UsedList
{
	public:
		UsedList(void);
		bool Exists(const T &entry);
		bool Insert(const T &entry);
		void Print(void) const;
	protected:
		std::unordered_map<Key, std::vector<UsedListContainer> > m_hash;
		unsigned m_entries;
		unsigned m_accesses;
		unsigned m_hits;
		unsigned m_collisions;
};
