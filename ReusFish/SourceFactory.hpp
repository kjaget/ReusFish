#pragma once

#include <functional>
#include <unordered_map>

class Source;
namespace std {
	template <typename T, typename U> 
		class hash<pair<T,U> > 
		{ 
			public:
				size_t operator() (const std::pair<T,U> &orig) const
				{ 
					return hash<size_t>()(static_cast<size_t>(orig.first)) + 31 * hash<size_t>()(static_cast<size_t>(orig.second)); 
				}
		};
}

template <typename Key1, typename Key2> 
class SourceFactory
{
	public:
		SourceFactory(void)
	   	{
		};

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

template <typename Derived> Source* SourceBuilder(void)
{ 
	return new Derived();
}
