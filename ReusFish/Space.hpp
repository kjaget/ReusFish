#ifndef SPACE_INC__
#define SPACE_INC__

#include "Biome.hpp"
#include "Source.hpp"

class Space
{
   public:
      Space() : m_source(new Source), m_biome(BIOME_NONE) {}
      Space(biome_t biome) : m_source(new Source), m_biome(biome) {}
      Space(biome_t biome, Source *source) : m_source(source->Clone()), m_biome(biome) {}
      Space(const Space &other)
      {
	 m_source = other.m_source->Clone();
	 m_biome  = other.m_biome;
	 m_yield  = other.m_yield;
      }
      Space& operator=(const Space &rhs)
      {
	 if (this != &rhs)
	 {
	    if (m_source)
	    {
	       delete m_source;
	       m_source = NULL;
	    }
	    m_source = rhs.m_source->Clone();
	    m_biome  = rhs.m_biome;
	    m_yield  = rhs.m_yield;
	 }
	 return *this;
      }
      ~Space() { delete m_source; }

      bool operator==(const Space &rhs) const
      {
	 return (m_biome == rhs.m_biome) &&
	        (*m_source == *rhs.m_source);
      }
      unsigned Hash (void) const
      {
	 unsigned hash = m_biome + (m_biome << 4) + (m_biome << 8) + (m_biome << 12);
	 hash += (hash << 16);
	 hash += m_source->Hash();
	 return hash;
      }
      void Print(void) const
      {
	 
	 switch(m_biome)
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
	 m_source->Print();
	 m_yield.Print();
      }
      biome_t  Biome(void) const {return m_biome;}
      Source  *m_source;
      biome_t  m_biome;
      Yield    m_yield;
};

#endif
