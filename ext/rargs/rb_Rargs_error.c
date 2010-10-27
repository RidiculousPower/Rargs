#include "rargs_error.h"
#include "rargs_describe.h"

/************************************
*  RARG_error_NoMatchForParameters  *
************************************/

void RARG_error_NoMatchForParameters(	rarg_parse_descriptor_t*	parse_descriptor,
																			rarg_parameter_set_t*			parameter_sets )	{

	//	return needs to be freed
	char*	c_string_descriptor_for_parameter_sets			=	RARG_error_StringDescriptorForParameterSets( parameter_sets );
	//	return will be freed by ruby
	char*	c_string_descriptor_for_actual_passed_args	=	RARG_error_StringDescriptorForActualPassedArgs( parse_descriptor->argc,
																																																			parse_descriptor->args );

	char*	c_error_string	=	calloc(	strlen( c_string_descriptor_for_parameter_sets )
																+	strlen( c_string_descriptor_for_actual_passed_args )
																+ 1, sizeof( char ) );
	sprintf( c_error_string, "%s%s", c_string_descriptor_for_parameter_sets, c_string_descriptor_for_actual_passed_args );
	
	free( c_string_descriptor_for_parameter_sets );

	VALUE	rb_exception	=	rb_exc_new2( rb_eArgError, c_error_string );

	free( c_error_string );

	rb_exc_raise( rb_exception );

}

/************************************************
*  RARG_error_StringDescriptorForParameterSets  *
************************************************/

char* RARG_error_StringDescriptorForParameterSets( rarg_parameter_set_t*		parameter_sets )	{

	VALUE	rb_arg_formats_array			=	RARG_collectDescriptionsForParameterSets( parameter_sets );
	VALUE	rb_arg_formats_string			=	rb_funcall(	rb_arg_formats_array,
																								rb_intern( "join" ),
																								1,
																								rb_str_new( "\n * ",
																														4 ) );
	char*	c_arg_formats_string	=	StringValuePtr( rb_arg_formats_string );
	char*	c_format_string				=	"Failed to match any acceptable parameter formats. Acceptable formats:\n * %s\n\n";
	
	//	append formats to error string
	int		c_error_string_length	=	strlen( c_arg_formats_string ) + strlen( c_format_string );
	char*	c_string_descriptor_for_parameter_sets				=	calloc( c_error_string_length + 1, sizeof( char ) );		
	sprintf(	c_string_descriptor_for_parameter_sets, 
						c_format_string, 
						c_arg_formats_string );			
	
	return c_string_descriptor_for_parameter_sets;
}

/***************************************************
*  RARG_error_StringDescriptorForActualPassedArgs  *
***************************************************/

char* RARG_error_StringDescriptorForActualPassedArgs( int			argc,
																											VALUE*	args )	{

	VALUE	rb_arg_descriptions	=	rb_ary_new();
	
	int	c_which_arg	=	0;
	for ( c_which_arg = 0 ; c_which_arg < argc ; c_which_arg++ )	{
		VALUE	rb_string_descriptor_for_arg	=	rb_funcall(	args[ c_which_arg ],
																											rb_intern( "inspect" ),
																											0 );
		rb_ary_push(	rb_arg_descriptions,
									rb_string_descriptor_for_arg );
	}
	
	VALUE	rb_string_descriptor_for_actual_passed_args	=	rb_funcall(	rb_arg_descriptions,
																																	rb_intern( "join" ),
																																	1,
																																	rb_str_new( ", ",
																																							2 ) );

	
	char* c_string_descriptor_for_actual_passed_args	=	StringValuePtr( rb_string_descriptor_for_actual_passed_args );
	
	return c_string_descriptor_for_actual_passed_args;
}

