#include "Space.hpp"
#include "SourceContainer.hpp"

Space::Space(void) : 
	m_source(source_container.Add(new Source()))
{
}

Space::Space(const Source &source) :
	m_source(source_container.Add(source.Clone()))
{
}

Space::Space(const Source &source, int aspect)
{
	Source *l_source = source.Clone();
	l_source->AddAspect((Aspects::aspect_t)aspect);
	m_source = source_container.Add(l_source);
}

Space::Space(const Space &space, int aspect)
{ 
	Source *l_source = space.m_source->Clone();
	l_source->AddAspect((Aspects::aspect_t)aspect);
	m_source = source_container.Add(l_source);
}

Space::Space(const Space &other) :
	m_source(other.m_source),
	m_yield(other.m_yield)
{
}

Space& Space::operator=(const Space &rhs)
{
	if (this != &rhs)
	{
		m_source = rhs.m_source;
		m_yield  = rhs.m_yield;
	}
	return *this;
}

Space::~Space()
{
}

bool Space::operator==(const Space &rhs) const
{
	return (*m_source == *rhs.m_source);
}

size_t Space::Hash (void) const
{
	if (m_source)
		return m_source->Hash();
	return 0;
}

void Space::Print(void) const
{
	if (m_source)
		m_source->Print();
	else
		std::cout << "City:";

	m_yield.Print();
}
