#ifndef DELETE_TAB_HPP  
#define DELETE_TAB_HPP  
#include "query_analyser.hpp"
#include "../../util/log/log_util.h"

#define BASIC_OPS_SCAN    0
#define BASIC_OPS_DELETE  1
#define BASIC_OPS_UPDATE  2

class DeleteAnalyser:public QueryAnalyser
{
public:
DeleteAnalyser(rapidjson::Value & value ,rapidjson::Document & doc_  ):QueryAnalyser( value , doc_ )
{
	oper_type = BASIC_OPS_DELETE ;
}

};

#endif
