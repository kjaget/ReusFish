#include "SourceFactory.hpp"

SourceFactory::SourceFactory() {}

template <Key1, Key2>
void SourceFactory::Register(Key1 key1, Key2 key2, Builder const& builder) {
   auto it = m_map.find(std::pair<Key1, Key2>(key1, key2));
   if (it == m_map.end()) 
      m_map.emplace(SourceFactoryKey(biome,level), builder);
}

bool SourceFactory::Build(Key1 key1, Key2 key2, Builder &builder) const {
   auto it = m_map.find(std::pair<Key1, Key2>(key1, key2));
   if (it == m_map.end()) 
      return false;

   builder = it->second;
   return true;
}

