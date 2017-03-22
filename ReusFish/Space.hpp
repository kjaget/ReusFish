#ifndef SPACE_INC__
#define SPACE_INC__

#include "Source.hpp"
#include "SourceContainer.hpp"

class Space
{
   public:
      Space() : m_source(source_container.Add(new Source())) {}
      Space(Source *source) : m_source(source_container.Add(source)) {}
      Space(const Source *source) : m_source(source_container.Add(source)) {}
      Space(const Source *source, int aspect) 
      { 
	 Source *l_source = source->Clone();
	 l_source->AddAspect((Aspects::aspect_t)aspect);
	 m_source = source_container.Add(l_source);
      }
      Space(const Space &space, int aspect) 
      { 
	 Source *l_source = space.m_source->Clone();
	 l_source->AddAspect((Aspects::aspect_t)aspect);
	 m_source = source_container.Add(l_source);
      }
      Space(const Space &other)
      {
	 m_source = other.m_source;
	 m_yield  = other.m_yield;
      }
      Space& operator=(const Space &rhs)
      {
	 if (this != &rhs)
	 {
	    m_source = rhs.m_source;
	    m_yield  = rhs.m_yield;
	 }
	 return *this;
      }
      ~Space() { }

      bool operator==(const Space &rhs) const
      {
	 return (*m_source == *rhs.m_source);
      }
      size_t Hash (void) const
      {
	 if (m_source)
	    return m_source->Hash();
	 return 0;
      }
      void Print(void) const
      {
	 if (m_source)
	    m_source->Print();
	 else
	 {
	    std::cout << "City:";
	 }
	 m_yield.Print();
      }
      const Source *m_source;
      Yield         m_yield;
};

#endif
