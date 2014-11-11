#ifndef BIOME_INC__
#define BIOME_INC__

#include <iostream>
#include <vector>

typedef enum BIOME_T
{
   BIOME_NONE,
   DESERT,
   FOREST,
   OCEAN,
   SWAMP,
   MOUNTAIN,
   BIOME_T_MAX
} biome_t;

class BiomeList
{
public:
      biome_t &operator [] (unsigned i)
      {
	 if (i >= m_list.size())
	    m_list.resize(i + 1);

	 return m_list[i];
      }
      const biome_t &operator [] (unsigned i) const
      {
	 	 return m_list[i];
      }
      void Print(unsigned int i) const
      {
	 if (i >= m_list.size())
	    std::cout << "Undef:";
	 else
	 {
	    switch(m_list[i])
	    {
	       case DESERT:
		  std::cout << "Desert:";
		  break;
	       case FOREST:
		  std::cout << "Forest:";
		  break;
	       case OCEAN:
		  std::cout << "Ocean:";
		  break;
	       case SWAMP:
		  std::cout << "Swamp:";
		  break;
	       case MOUNTAIN:
		  std::cout << "Mountain:";
		  break;
	       default:
		  std::cout << "None:";
		  break;
	    }
	 }
      }
      size_t size(void) const
      {
	 return m_list.size();
      }

   protected:
      std::vector<biome_t> m_list;
};

extern BiomeList biome_list;
#endif

