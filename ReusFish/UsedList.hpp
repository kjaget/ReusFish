#pragma once

#include <unordered_map>
#include <vector>

#include "Landscape.hpp"

// T is the input type
// S is the storage type
template <class T, class S>
class UsedListContainer
{
	public:
		UsedListContainer(const T &t_in);
		UsedListContainer(const UsedListContainer<T, S> &orig);
		~UsedListContainer();
		bool operator==(const UsedListContainer<T, S> &rhs) const;
		void SetHash(void);
		size_t Hash(void) const;

	private :
		S      *m_list;
		size_t  m_size;
		size_t  m_hash;
};

template <class Key, class T, class S = T> class UsedList
{
	public:
		UsedList(void);
		bool Exists(const T &entry);
		bool Insert(const T &entry);
		void Print(void) const;
	protected:
		std::unordered_map<Key, std::vector<UsedListContainer<T,S>> > m_hash;
		unsigned m_entries;
		unsigned m_accesses;
		unsigned m_hits;
		unsigned m_collisions;
};
