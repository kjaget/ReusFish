#ifndef ASPECTS_INC__
#define ASPECTS_INC__

#include <iostream>
#include <string>
#include <vector>
#include "SourceClass.hpp"
#include "Yield.hpp"

class Aspect
{
	public :
		Aspect(void) : m_name("None"), m_resource(SOURCE_CLASS_NONE), m_natura_threshold(0) { }
		Aspect(const char *name, source_class_t resource, const Yield &bonus, unsigned natura_threshold, const Yield &natura_bonus) :
			m_name(name),
			m_resource(resource),
			m_bonus(bonus),
			m_natura_threshold(natura_threshold),
			m_natura_bonus(natura_bonus)
		{ 
		}
		void Print(void) const
		{
			std::cout << m_name;
		}

		const char     *m_name;
		source_class_t  m_resource;
		Yield           m_bonus;
		unsigned char   m_natura_threshold;
		Yield           m_natura_bonus;
};

class Aspects
{
	public:
		typedef enum : unsigned char
		{
			LESSER,
			POTENT,
			GREATER,
			SUBLIME,
			ASPECT_CLASS_T_MAX
		} aspect_class_t;

		typedef enum : unsigned char
		{
			LESSER_LEAF,
			POTENT_LEAF,
			GREATER_LEAF,
			SUBLIME_LEAF,
			LESSER_HUNT,
			POTENT_HUNT,
			GREATER_HUNT,
			SUBLIME_HUNT,
			LESSER_FRUIT,
			POTENT_FRUIT,
			GREATER_FRUIT,
			SUBLIME_FRUIT,
			LESSER_GROWTH,
			POTENT_GROWTH,
			GREATER_GROWTH,
			SUBLIME_GROWTH,
			LESSER_HERD,
			POTENT_HERD,
			GREATER_HERD,
			SUBLIME_HERD,
			LESSER_CRYSTAL,
			POTENT_CRYSTAL,
			GREATER_CRYSTAL,
			SUBLIME_CRYSTAL,
			LESSER_EXOTIC,
			POTENT_EXOTIC,
			GREATER_EXOTIC,
			SUBLIME_EXOTIC,
			LESSER_NOBLE,
			POTENT_NOBLE,
			GREATER_NOBLE,
			SUBLIME_NOBLE,
			LESSER_SEISMIC,
			POTENT_SEISMIC,
			GREATER_SEISMIC,
			SUBLIME_SEISMIC,
			LESSER_TOXIC,
			POTENT_TOXIC,
			GREATER_TOXIC,
			SUBLIME_TOXIC,
			LESSER_PREDATOR,
			POTENT_PREDATOR,
			GREATER_PREDATOR,
			SUBLIME_PREDATOR,
			LESSER_REACTION,
			POTENT_REACTION,
			GREATER_REACTION,
			SUBLIME_REACTION,
			ASPECT_T_MAX
		} aspect_t;

		Aspects(void);
		void Enable(aspect_t base_type, unsigned level);
		bool IsEnabled(aspect_t type) const;
		bool IsValid(aspect_t type, source_class_t source_class) const;
		void Print(aspect_t type) const;
		void Bonus(aspect_t type, unsigned natura, Yield &yield) const;
		bool CanUpgrade(aspect_t requirement, aspect_t source_aspect) const;

	private :
		std::vector<Aspect> m_aspects;
		std::vector<bool> m_enabled;
};

extern Aspects aspects;

#endif
