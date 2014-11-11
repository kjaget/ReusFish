#ifndef SOURCE_FACTORY_INC__
#define SOURCE_FACTORY_INC__

#include <functional>
#include <unordered_map>
#include <vector>

class Source;

template <typename T, typename U> 
struct std::hash<std::pair<T,U> > 
{ 
	std::size_t operator() (std::pair<T,U> orig) const
	{ 
		return std::hash<T>()(orig.first) + 31 * std::hash<U>()(orig.second); 
	}
};

template <typename Key1, typename Key2> 
class SourceFactory
{
   public:
	   SourceFactory() {};
      typedef std::function<Source*()> Builder;

      void Register(Key1 key1, Key2 key2, Builder const& builder)
      {
	 auto it = m_map.find(std::pair<Key1, Key2>(key1, key2));
	 if (it == m_map.end()) 
		 m_map.emplace(std::pair<Key1,Key2>(key1,key2), builder);
      }

      bool Get(Key1 key1, Key2 key2, Builder &builder) const {
	 auto it = m_map.find(std::pair<Key1, Key2>(key1, key2));
	 if (it == m_map.end()) 
	    return false;

	 builder = it->second;
	 return true;
      }
      
      Source *Build(Key1 key1, Key2 key2) const 
      {
	 auto it = m_map.find(std::pair<Key1, Key2>(key1, key2));
	 if (it == m_map.end()) 
	    return NULL;

	 return it->second();
      }

   private:
      std::unordered_map<std::pair<Key1, Key2>, Builder> m_map;
};

template <typename Derived> Source* SourceBuilder() { return new Derived(); }

#endif

