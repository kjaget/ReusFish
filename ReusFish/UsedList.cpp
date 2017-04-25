#include <climits>
#include <cstring>

#include "UsedList.hpp"

template <class T, class S>
UsedListContainer<T,S>::~UsedListContainer()
{
	delete [] m_list;
}

template <class T, class S>
bool UsedListContainer<T,S>::operator==(const UsedListContainer<T, S> &rhs) const
{
	if (m_size != rhs.m_size)
		return false;
	for (unsigned i = 0; i < m_size; i++)
		if (m_list[i] != rhs.m_list[i])
			return false;
	return true;
}

template <>
void UsedListContainer<Landscape, const Source *>::SetHash(void)
{
	m_hash = 0;
	for (size_t i = 0; i < m_size; i++)
	{
		const unsigned size_t_bits_minus_one = CHAR_BIT * sizeof(size_t) - 1;
		size_t rot_val = (size_t)m_list[i];
		rot_val = ((rot_val >> (3*i)) & ((1 << (size_t_bits_minus_one - 3*i)) - 1))|
				   (rot_val << (size_t_bits_minus_one - 3*i));
		m_hash += rot_val;
	}
}

template <>
void UsedListContainer<std::pair<biome_t, const Source *>, std::pair<biome_t, const Source *>>::SetHash(void)
{
	m_hash = 0;
	for (size_t i = 0; i < m_size; i++)
	{
		const unsigned size_t_bits_minus_one = CHAR_BIT * sizeof(size_t) - 1;
		size_t rot_val = (size_t)m_list[i].second;
		rot_val = ((rot_val >> (3*i)) & ((1 << (size_t_bits_minus_one - 3*i)) - 1))|
				   (rot_val << (size_t_bits_minus_one - 3*i));
		m_hash += rot_val;
		m_hash += m_list[i].first * 65535ULL;
	}
}

template <>
UsedListContainer<Landscape, const Source *>::UsedListContainer(const Landscape &t_in)
{
	m_size = t_in.size();
	m_list = new const Source *[m_size];
	for (size_t i = 0; i < m_size; i++)
		m_list[i] = t_in[i].m_source;
	SetHash();
}

template <class T, class S>
UsedListContainer<T, S>::UsedListContainer(const T &t_in)
{
	m_size = 1;
	m_list = new S[m_size];
	m_list[0] = t_in;
	SetHash();
}

template <class T, class S>
UsedListContainer<T,S>::UsedListContainer(const UsedListContainer<T, S> &orig)
{
	m_size = orig.m_size;
	m_list = new S[m_size];
	memcpy(m_list, orig.m_list, m_size * sizeof (S));
	m_hash = orig.m_hash;
}


template <class T, class S>
size_t UsedListContainer<T,S>::Hash(void) const
{
	return m_hash;
}


template <class Key, class T, class S>
UsedList<Key, T, S>::UsedList(void) : 
	m_entries (0), 
	m_accesses(0), 
	m_hits(0), 
	m_collisions(0)
{
}

template <class Key, class T, class S>
bool UsedList<Key, T, S>::Exists(const T &entry)
{
	UsedListContainer<T,S> container(entry);
	typename std::unordered_map<Key, std::vector<UsedListContainer<T,S>> >::const_iterator it = m_hash.find(container.Hash());
	m_accesses += 1;
	if (it == m_hash.end())
		return false;
	for (unsigned i = 0; i < it->second.size(); i++)
		if (container == it->second[i])
			return true;
	return false;
}

template <class Key, class T, class S>
bool UsedList<Key, T, S>::Insert(const T &entry)
{
	UsedListContainer<T, S> container(entry);
	Key key = container.Hash();

	typename std::unordered_map<Key, std::vector<UsedListContainer<T,S>> >::iterator it = m_hash.find(key);
	m_accesses += 1;
	if (it == m_hash.end())
	{
		m_entries += 1;
		m_hash[key] = std::vector<UsedListContainer<T,S>>(1, container);
		return true;
	}
	//std::cout << "=====================================" << std::endl;
	///entry.PrintAll();

	for (size_t i = 0; i < it->second.size(); i++)
	{
		//std::cout << "----------------------------------------" << std::endl;
		//it->second[i].PrintAll();
		if (container == it->second[i])
		{
			//std::cout << "Match\n";
			m_hits += 1;
			return false;
		}
	}

	m_entries += 1;
	m_collisions += 1;
	it->second.push_back(container);
	return true;
}

template <class Key, class T, class S>
void UsedList<Key, T, S>::Print(void) const
{
	std::cout << "UsedList : Accesses = " << m_accesses << " Hits = " << m_hits << " Collisions = " << m_collisions << " Entries = " << m_entries << " Hash size = " << m_hash.size() << std::endl;
}

template class UsedListContainer<Landscape, const Source *>;
template class UsedListContainer<std::pair<biome_t, const Source *>, std::pair<biome_t, const Source *>>;
template class UsedList<size_t, Landscape, const Source *>;
template class UsedList<size_t, std::pair<biome_t, const Source *>>;
