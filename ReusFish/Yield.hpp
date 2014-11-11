#ifndef INC_YIELD_HPP
#define INC_YIELD_HPP

class Yield
{
   public:
      Yield();
      Yield(unsigned short food, 
	    unsigned short tech, 
	    unsigned short wealth,
	    unsigned short danger, 
	    unsigned short awe, 
	    short          natura);
      Yield(unsigned short food, 
	    unsigned short tech, 
	    unsigned short wealth,
	    unsigned short danger, 
	    unsigned short awe, 
	    short          natura, 
	    unsigned char  range,
	    unsigned char  natura_range);
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
	 if ((rhs.m_natura != 0) && (rhs.m_natura > m_natura))
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
	    (m_natura_range == rhs.m_natura_range) ;
      }
      void Print(void) const;

      unsigned short m_food;
      unsigned short m_tech;
      unsigned short m_wealth;
      unsigned short m_danger;
      unsigned short m_awe;
               short m_natura;
      unsigned char  m_range;
      unsigned char  m_natura_range;
};


#endif

