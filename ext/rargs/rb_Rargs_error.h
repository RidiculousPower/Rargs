#ifndef RB_RARGS_ERROR
	#define RB_RARGS_ERROR

	#include <ruby.h>
	
	#include "rb_Rargs_types.h"
	
void RARG_error_NoMatchForParameters(	rarg_parse_descriptor_t*	parse_descriptor,
																			rarg_parameter_set_t*			parameter_sets );
	char* RARG_error_StringDescriptorForParameterSets( rarg_parameter_set_t*		parameter_sets );
	char* RARG_error_StringDescriptorForActualPassedArgs( int			argc,
																												VALUE*	args );
	
#endif