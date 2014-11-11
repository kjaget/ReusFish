#ifndef USEDLIST_INC__
#define USEDLIST_INC__

#include <unordered_map>
#include <vector>

template <class Key, class T> class UsedList
{
   public:
      UsedList() : m_entries (0), m_accesses(0), m_hits(0), m_collisions(0) {}
      bool Exists(const T &entry)
      {
	 std::unordered_map<Key, std::vector<T> >::const_iterator it = m_hash.find(entry.Hash());
	 m_accesses += 1;
	 if (it == m_hash.end())
	    return false;
	 for (unsigned i = 0; i < it->second.size(); i++)
	    if (entry == it->second[i])
	       return true;
	 return false;
      }
      bool Insert(T entry)
      {
	 unsigned hash = entry.Hash();
	 std::unordered_map<Key, std::vector<T> >::iterator it = m_hash.find(hash);
	 m_accesses += 1;
	 if (it == m_hash.end())
	 {
		m_entries += 1;
	    m_hash[hash] = std::vector<T>(1, entry);
	    return true;
	 }
	 //std::cout << "=====================================" << std::endl;
	 ///entry.PrintAll();

	 for (unsigned i = 0; i < it->second.size(); i++)
	 {
	       //std::cout << "----------------------------------------" << std::endl;
	       //it->second[i].PrintAll();
	    if (entry == it->second[i])
	    {
	       //std::cout << "Match\n";
	       m_hits += 1;
	       return false;
	    }
	 }

	 m_entries += 1;
     m_collisions += 1;
	 it->second.push_back(entry);
	 return true;
      }
      void Print(void) const
      {
	 std::cout << "UsedList : Accesses = " << m_accesses << "Hits = " << m_hits << " Collisions = " << m_collisions << " Entries = " << m_entries << " Hash size = " << m_hash.size() << std::endl;
      }
   protected:
      std::unordered_map<Key, std::vector<T> > m_hash;
      unsigned                       m_entries;
      unsigned                       m_accesses;
      unsigned                       m_hits;
      unsigned                       m_collisions;
};

#endif
