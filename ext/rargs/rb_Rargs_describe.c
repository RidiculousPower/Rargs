#include "rb_Rargs_describe.h"

/***************************************
*  collectDescriptionsForParameterSet  *
***************************************/

VALUE RARG_collectDescriptionsForParameterSets(	rarg_parameter_set_t*		parameter_set )	{
	
	VALUE	rb_format_strings_array	=	rb_ary_new();

	rarg_parameter_t*					parameter				=	NULL;
	rarg_possible_match_t*		possible_match	=	NULL;
	
	while ( parameter_set != NULL )	{
		
		if ( parameter_set->description )	{
			VALUE	rb_parameter_set_descriptions_array	=	RARG_rubyArrayForDescription( parameter_set->description );
			VALUE	rb_parameter_description_string			=	rb_funcall(	rb_parameter_set_descriptions_array,
																															rb_intern( "join" ),
																															1,
																															rb_str_new( "\n * ",
																																					4 ) );
			rb_ary_store(	rb_format_strings_array,
										parameter_set->description->order_ranking - 1,
										rb_parameter_description_string );
		}
		
		parameter	=	parameter_set->parameters;
		while ( parameter != NULL )	{
			
			if ( parameter->description )	{
				VALUE	rb_parameter_descriptions_array	=	RARG_rubyArrayForDescription( parameter->description );
				rb_funcall(	rb_format_strings_array,
										rb_intern( "insert" ),
										2,
										INT2FIX( parameter->description->order_ranking - 1 ),
										rb_parameter_descriptions_array );
			}

			possible_match = parameter->possible_match;
			while ( possible_match != NULL )	{

				if ( possible_match->description )	{					
					VALUE	rb_possible_match_descriptions_array	=	RARG_rubyArrayForDescription( possible_match->description );
					rb_funcall(	rb_format_strings_array,
											rb_intern( "insert" ),
											2,
											INT2FIX( possible_match->description->order_ranking - 1 ),
											rb_possible_match_descriptions_array );
				}

				possible_match = possible_match->next;
			}
			
			parameter = parameter->next;
		}
	
		parameter_set	= parameter_set->next;
	}
	
	return rb_format_strings_array;
}

/*****************************
*  rubyArrayForDescriptions  *
*****************************/

VALUE RARG_rubyArrayForDescription( rarg_description_t* description )	{

	VALUE	rb_arg_format_array	=	rb_ary_new();
	
	while ( description != NULL )	{
			
		VALUE	rb_arg_format_string	=	rb_str_new2( description->description );
		
		rb_ary_push(	rb_arg_format_array,
									rb_arg_format_string );
		
		description	=	description->next;
	}
	
	return rb_arg_format_array;
}
