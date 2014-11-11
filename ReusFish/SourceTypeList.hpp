#ifndef SOURCE_TYPE_LIST_INC__
#define SOURCE_TYPE_LIST_INC__

#include "SourceType.hpp"
#include "SourceFactory.hpp"

class SourceTypeList : public SourceFactory<source_type_t, unsigned>
{
   public :
      SourceTypeList();
};

extern SourceTypeList source_type_list;
#endif
