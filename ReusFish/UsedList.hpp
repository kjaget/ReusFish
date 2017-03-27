#ifndef USEDLIST_INC__
#define USEDLIST_INC__

#include <climits>
#include <unordered_map>
#include <vector>

#include "Landscape.hpp"

class UsedListContainer
{
	public:
		UsedListContainer(const Landscape &landscape)
		{
			m_size = landscape.size();
			m_list = new const Source *[m_size];
			for (unsigned i = 0; i < m_size; i++)
				m_list[i] = landscape[i].m_source;
			SetHash();
		}
		UsedListContainer(const UsedListContainer &orig)
		{
			m_size = orig.m_size;
			m_list = new const Source *[m_size];
			memcpy(m_list, orig.m_list, m_size * sizeof (*m_list));
			m_hash = orig.m_hash;
		}
		~UsedListContainer()
		{
			delete [] m_list;
		}
		bool operator==(const UsedListContainer &rhs) const
		{
			if (m_size != rhs.m_size)
				return false;
			for (unsigned i = 0; i < m_size; i++)
				if (m_list[i] != rhs.m_list[i])
					return false;
			return true;
		}
		void SetHash(void)
		{
			for (unsigned i = 0; i < m_size; i++)
			{
				size_t rot_val = (size_t)m_list[i];
				const unsigned size_t_bits_minus_one = CHAR_BIT * sizeof(size_t) - 1;
				rot_val = ((rot_val >> i) & ((1 << (size_t_bits_minus_one-i)) - 1))|
					(rot_val << (size_t_bits_minus_one - i));
				m_hash += rot_val;
			}
		}
		size_t Hash(void) const {return m_hash; }
	protected:
		const Source **m_list;
		unsigned char  m_size;
		size_t         m_hash;
};

template <class Key, class T> class UsedList
{
	public:
		UsedList() : m_entries (0), m_accesses(0), m_hits(0), m_collisions(0) {}
		bool Exists(const T &entry)
		{
			UsedListContainer container(entry);
			typename std::unordered_map<Key, std::vector<UsedListContainer> >::const_iterator it = m_hash.find(container.Hash());
			m_accesses += 1;
			if (it == m_hash.end())
				return false;
			for (unsigned i = 0; i < it->second.size(); i++)
				if (container == it->second[i])
					return true;
			return false;
		}
		bool Insert(T entry)
		{
			UsedListContainer container(entry);

			typename std::unordered_map<Key, std::vector<UsedListContainer> >::iterator it = m_hash.find(container.Hash());
			m_accesses += 1;
			if (it == m_hash.end())
			{
				m_entries += 1;
				m_hash[container.Hash()] = std::vector<UsedListContainer>(1, container);
				return true;
			}
			//std::cout << "=====================================" << std::endl;
			///entry.PrintAll();

			for (unsigned i = 0; i < it->second.size(); i++)
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
		void Print(void) const
		{
			std::cout << "UsedList : Accesses = " << m_accesses << "Hits = " << m_hits << " Collisions = " << m_collisions << " Entries = " << m_entries << " Hash size = " << m_hash.size() << std::endl;
		}
	protected:
		std::unordered_map<Key, std::vector<UsedListContainer> > m_hash;
		unsigned m_entries;
		unsigned m_accesses;
		unsigned m_hits;
		unsigned m_collisions;
};

#endif
