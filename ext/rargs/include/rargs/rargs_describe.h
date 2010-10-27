#ifndef RB_RARGS_DESCRIBE
	#define RB_RARGS_DESCRIBE

	#include <ruby.h>
	
	#include "rargs_types.h"

	VALUE RARG_collectDescriptionsForParameterSets(	rarg_parameter_set_t*		parameter_set );
	VALUE RARG_rubyArrayForDescription( rarg_description_t* description );
	
#endif