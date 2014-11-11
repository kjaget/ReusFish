#ifndef INC_YIELD_HPP
#define INC_YIELD_HPP

class Yield
{
   public:
      Yield();
      Yield(unsigned food, 
	    unsigned tech, 
	    unsigned wealth,
	    unsigned danger, 
	    unsigned awe, 
	    unsigned natura);
      Yield(unsigned food, 
	    unsigned tech, 
	    unsigned wealth,
	    unsigned danger, 
	    unsigned awe, 
	    unsigned natura, 
	    unsigned range,
	    unsigned natura_range);
      void Reset(void);
      Yield& operator+= (const Yield &rhs);
      bool operator> (const Yield &rhs) const
      {
	 if ((rhs.m_food > 0) && (rhs.m_food > m_food))
	    return false;
	 if ((rhs.m_tech > 0) && (rhs.m_tech > m_tech))
	    return false;
	 if ((rhs.m_wealth > 0) && (rhs.m_wealth > m_wealth))
	    return false;
	 if ((rhs.m_danger > 0) && (rhs.m_danger > m_danger))
	    return false;
	 if ((rhs.m_awe > 0) && (rhs.m_awe > m_awe))
	    return false;
	 if ((rhs.m_natura > 0) && (rhs.m_natura > m_natura))
	    return false;
	 return true;
      }
      bool operator==(const Yield &rhs) const
      {
	 return (m_food == rhs.m_food) &&
	    (m_tech == rhs.m_tech) &&
	    (m_wealth == rhs.m_wealth) &&
	    (m_danger == rhs.m_danger) &&
	    (m_awe == rhs.m_awe) &&
	    (m_natura == rhs.m_natura) &&
	    (m_range == rhs.m_range) &&
	    (m_natura_range == rhs.m_range) ;
      }
      void Print(void) const;

      unsigned m_food;
      unsigned m_tech;
      unsigned m_wealth;
      unsigned m_danger;
      unsigned m_awe;
      unsigned m_natura;
      unsigned m_range;
      unsigned m_natura_range;
};


#endif

