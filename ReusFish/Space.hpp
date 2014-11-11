#ifndef SPACE_INC__
#define SPACE_INC__

#include "Source.hpp"

class Space
{
   public:
      Space() : m_source(NULL) {}
      Space(Source *source) : m_source(source->Clone()) {}
      Space(const Space &other)
      {
		  if (other.m_source)
	 m_source = other.m_source->Clone();
		  else
			  m_source = NULL;
	 m_yield  = other.m_yield;
      }
      Space& operator=(const Space &rhs)
      {
	 if (this != &rhs)
	 {
	    if (m_source)
	       delete m_source;
		if (rhs.m_source)
	    m_source = rhs.m_source->Clone();
		else
			m_source = NULL;
	    m_yield  = rhs.m_yield;
	 }
	 return *this;
      }
      ~Space() { if (m_source) delete m_source; }

      bool operator==(const Space &rhs) const
      {
	 return ((m_source == NULL) && (rhs.m_source == NULL)) ||
	    (*m_source == *rhs.m_source);
      }
      unsigned Hash (void) const
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
      Source  *m_source;
      Yield    m_yield;
};

#endif
