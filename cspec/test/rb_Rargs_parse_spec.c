#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/rb_Rargs.h"

#include <string.h>

#include "vm_core.h"

#define RT_ParseDescriptor( parse_descriptor, passed_argc, passed_args )		parse_descriptor								=	calloc( 1, sizeof( rarg_parse_descriptor_t ) );														\
																																						parse_descriptor->argc					=	passed_argc;																															\
																																						parse_descriptor->args					=	passed_args;																															\
																																						parse_descriptor->args_parsed		=	0;																																				\
																																						if ( parse_descriptor->matched_parameter_set != NULL )	{																										\
																																							free( parse_descriptor->matched_parameter_set );																													\
																																							parse_descriptor->matched_parameter_set = NULL;																														\
																																						}																																																						\
																																						parse_descriptor->matched_parameter_set	=	calloc( 1, sizeof( rarg_matched_parameter_set_t ) );							\
																																						parse_descriptor->matched_parameter_ptr	=	& parse_descriptor->matched_parameter_set->parameters;

//	this is a dirty hack to get around the problem of passing a block in C
//	rb_iterate does not seem to pass a block as we might expect (even if the effect is the same,
//	it doesn't use the block slot)
//	we use eval to instantiate the block slot and globals in order to retain data during the call
//	since we are just doing this for testing which will never be running multiple times at once,
//	this shouldn't be a major concern, even if it is ugly.
//	it is at least not as ugly as not having the block properly spec'ed at all.
rarg_parse_descriptor_t*	RARG_parse_PossibleBlockMatch_parse_descriptor;
rarg_possible_match_t*		RARG_parse_PossibleBlockMatch_possible_match;
VALUE RARG_parse_PossibleBlockMatch_proc_relay( VALUE parse_descriptor_and_possible_match );

/**********************************
*  RARG_parse_PossibleBlockMatch  *
**********************************/

DESCRIBE( RARG_parse_PossibleBlockMatch, "RARG_parse_PossibleBlockMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match )" )
	IT( "tests for presence of passed block" )
		
		RARG_parse_PossibleBlockMatch_parse_descriptor	=	calloc( 1, sizeof( rarg_parse_descriptor_t ) );
		RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set		=	calloc( 1, sizeof( rarg_matched_parameter_set_t ) );
		RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_ptr		=	& RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters;
		*RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
		
		VALUE	rb_block	=	Qnil;
		RARG_parse_PossibleBlockMatch_possible_match		=	R_MatchBlockProc( rb_block );
		
		BOOL matched = rb_eval_string( "RARG_parse_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );
		
		SHOULD_BE_TRUE( matched );

		SHOULD_NOT_BE_NULL( RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters );
		SHOULD_NOT_BE_NULL( RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters->match );

		SHOULD_EQUAL( *RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters->receiver, rb_block );
		SHOULD_BE_TRUE( RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters->block_match );

	END_IT
END_DESCRIBE

VALUE RARG_parse_PossibleBlockMatch_proc_relay( VALUE arg __attribute__ ((unused)) )	{
	
	rarg_parse_descriptor_t*	parse_descriptor	=	RARG_parse_PossibleBlockMatch_parse_descriptor;
	rarg_possible_match_t*		possible_match		=	RARG_parse_PossibleBlockMatch_possible_match;
	
	VALUE	matched	=	RARG_parse_PossibleBlockMatch(	parse_descriptor,
																									possible_match );
	
	return matched;
}

/***************************************
*  RARG_parse_PossibleBlockArityMatch  *
***************************************/

DESCRIBE( RARG_parse_PossibleBlockArityMatch, "RARG_parse_PossibleBlockArityMatch( rarg_possible_block_match_arity_t* possible_arity_match, VALUE rb_arity )" )
	IT( "tests arity of a passed block" )

		RARG_parse_PossibleBlockMatch_parse_descriptor	=	calloc( 1, sizeof( rarg_parse_descriptor_t ) );
		RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set		=	calloc( 1, sizeof( rarg_matched_parameter_set_t ) );
		RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_ptr		=	& RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_set->parameters;
		*RARG_parse_PossibleBlockMatch_parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
		
		VALUE	rb_block	=	Qnil;
		RARG_parse_PossibleBlockMatch_possible_match		=	R_MatchBlockProcWithArity( rb_block, 1, 3 );
		
		VALUE matched = rb_eval_string( "RARG_parse_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );
		SHOULD_BE_TRUE( matched );

		matched = rb_eval_string( "RARG_parse_PossibleBlockMatch_proc_relay( Object ) { |arg_one, arg_two| return arg_one }" );
		SHOULD_BE_FALSE( matched );

		matched = rb_eval_string( "RARG_parse_PossibleBlockMatch_proc_relay( Object ) { |arg_one, arg_two, arg_three| return arg_one }" );
		SHOULD_BE_TRUE( matched );

	END_IT
END_DESCRIBE

/*********************************
*  RARG_parse_PossibleTypeMatch  *
*********************************/

DESCRIBE( RARG_parse_PossibleTypeMatch, "RARG_parse_PossibleTypeMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg is a given underying type (R_<type> which correspond in name to Ruby's T_<type>, always in caps)" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_array };
		RT_ParseDescriptor( parse_descriptor, 1, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		VALUE	rb_array_match	=	Qnil;
		rarg_possible_match_t*	possible_match	=	R_MatchType( rb_array_match, R_ARRAY );
		
		BOOL	matched	=	RARG_parse_PossibleTypeMatch(	parse_descriptor,
																									possible_match,
																									rb_array );		
		SHOULD_BE_TRUE( matched );
		
		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	args_two[]	=	{ rb_string };
		RT_ParseDescriptor( parse_descriptor, 1, args_two );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
		
		matched	=	RARG_parse_PossibleTypeMatch(	parse_descriptor,
																						possible_match,
																						rb_string );		
		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

/***************************************
*  RARG_parse_PossibleAncestorMatches  *
***************************************/

DESCRIBE( RARG_parse_PossibleAncestorMatches, "RARG_parse_PossibleAncestorMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg has ancestor(s) in ancestors chain" )

		//	string match
		
		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_array };
		RT_ParseDescriptor( parse_descriptor, 1, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		VALUE	rb_ancestor_match	=	Qnil;
		rarg_possible_match_t*	possible_match	=	R_MatchAncestor( rb_ancestor_match, "Object" );
		
		BOOL	matched	=	RARG_parse_PossibleAncestorMatches(	parse_descriptor,
																												possible_match,
																												rb_array );		
		SHOULD_BE_TRUE( matched );

		//	string fail

		rb_ancestor_match	=	Qnil;
		possible_match	=	R_MatchAncestor( rb_ancestor_match, "String" );
		
		matched	=	RARG_parse_PossibleAncestorMatches(	parse_descriptor,
																									possible_match,
																									rb_array );		
		SHOULD_BE_FALSE( matched );

		//	instance match

		rb_ancestor_match	=	Qnil;
		possible_match	=	R_MatchAncestorInstance( rb_ancestor_match, rb_cObject );
		
		matched	=	RARG_parse_PossibleAncestorMatches(	parse_descriptor,
																									possible_match,
																									rb_array );		
		SHOULD_BE_TRUE( matched );

		//	instance fail

		rb_ancestor_match	=	Qnil;
		possible_match	=	R_MatchAncestorInstance( rb_ancestor_match, rb_cProc );
		
		matched	=	RARG_parse_PossibleAncestorMatches(	parse_descriptor,
																									possible_match,
																									rb_array );		
		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

/*************************************
*  RARG_parse_PossibleMethodMatches  *
*************************************/

DESCRIBE( RARG_parse_PossibleMethodMatches, "RARG_parse_PossibleMethodMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg responds to method or returns non-nil for method or returns given values for method" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	args[]	=	{ rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 1, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		VALUE	rb_object_match	=	Qnil;
		rarg_possible_match_t*	possible_match	=	R_MatchRespondsTo( rb_object_match, "name" );
		
		BOOL	matched	=	RARG_parse_PossibleMethodMatches(	parse_descriptor,
																											possible_match,
																											rb_cObject );		
		SHOULD_BE_TRUE( matched );

		possible_match	=	R_MatchRespondsTo( rb_object_match, "non_existant_method" );
		
		matched	=	RARG_parse_PossibleMethodMatches(	parse_descriptor,
																								possible_match,
																								rb_cObject );		
		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

	/**********************************
	*  RARG_parse_PossibleIndexMatch  *
	**********************************/

DESCRIBE( RARG_parse_PossibleIndexMatch, "RARG_parse_PossibleIndexMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests for match against index of current hash match" )
		
		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_hash	=	rb_hash_new();
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_str_new2( "data" ) );

		VALUE	args[]	=	{ rb_hash };
		RT_ParseDescriptor( parse_descriptor, 1, args );

		VALUE	rb_data	=	Qnil;
		rarg_possible_match_t*	possible_match	=	R_MatchIndex( rb_data, "key" );
		
		BOOL	matched	=	RARG_parse_PossibleIndexMatch(	parse_descriptor,
																										possible_match,
																										rb_hash );		
		SHOULD_BE_TRUE( matched );
		
		matched = FALSE;
		
		VALUE	rb_hash_two	=	rb_hash_new();
		rb_hash_aset(	rb_hash_two,
									ID2SYM( rb_intern( "another_key" ) ),
									rb_str_new2( "data" ) );
		VALUE	args_two[]	=	{ rb_hash_two };
		RT_ParseDescriptor( parse_descriptor, 1, args_two );
		matched	=	RARG_parse_PossibleIndexMatch(	parse_descriptor,
																							possible_match,
																							rb_hash_two );		
		SHOULD_BE_FALSE( matched );
		
	END_IT
END_DESCRIBE

/*********************************
*  RARG_parse_PossibleHashMatch  *
*********************************/

DESCRIBE( RARG_parse_PossibleHashMatch, "RARG_parse_PossibleHashMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests for presence of hash, potentially also checking key/data for matches, or looking for the presence of indexes with optional data matching" )

		rarg_parse_descriptor_t*	parse_descriptor;
		VALUE	rb_hash	=	rb_hash_new();
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_str_new2( "data" ) );
		VALUE	args[]	=	{ rb_hash };
		RT_ParseDescriptor( parse_descriptor, 1, args );

		rarg_possible_match_t*	possible_match	=	R_Hash(	R_Key(	R_Symbol() ),
																											R_Data(	R_String() ) );
		BOOL	matched	=	RARG_parse_PossibleHashMatch(	parse_descriptor,
																									possible_match,
																									rb_hash );		
		SHOULD_BE_TRUE( matched );
		
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args_two[]	=	{ rb_array };
		RT_ParseDescriptor( parse_descriptor, 1, args_two );

		matched	=	RARG_parse_PossibleHashMatch(	parse_descriptor,
																						possible_match,
																						rb_array );		

		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

/**********************************
*  RARG_parse_PossibleGroupMatch  *
**********************************/

DESCRIBE( RARG_parse_PossibleGroupMatch, "RARG_parse_PossibleGroupMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests each possible match in a possible group match to see if this parameter matches for this possibility" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_arg_one	=	rb_str_new2( "a string" );
		VALUE	rb_arg_two	=	ID2SYM( rb_intern( "a symbol" ) );
		VALUE	args[] = { rb_arg_one, rb_arg_two };

		VALUE	rb_string	=	Qnil;
		VALUE	rb_symbol	=	Qnil;

		//	Test 1 - match

		RT_ParseDescriptor( parse_descriptor, 2, args );
		rarg_possible_match_t*	possible_group_match	=	R_Group(	R_MatchString( rb_string ),
																															R_MatchSymbol( rb_symbol ) );
		BOOL	matched	=	RARG_parse_PossibleGroupMatch( parse_descriptor, possible_group_match, rb_arg_one );
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_arg_one );
		SHOULD_EQUAL( *parse_descriptor->matched_parameter_set->parameters->receiver, rb_string );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->next->match, rb_arg_two );
		SHOULD_EQUAL( *parse_descriptor->matched_parameter_set->parameters->next->receiver, rb_symbol );

		//	test 2 - false match

		//	make arg two not match
		RT_ParseDescriptor( parse_descriptor, 2, args );
		VALUE	args_two[]	=	{ rb_cObject, rb_ary_new() };
		matched	=	RARG_parse_PossibleGroupMatch( parse_descriptor, possible_group_match, *args_two );
		SHOULD_BE_FALSE( matched );
		
	END_IT
END_DESCRIBE

	/****************************************
	*  RARG_parse_PossibleIfElseMatchMatch  *
	****************************************/

DESCRIBE( RARG_parse_PossibleIfElseMatchMatch, "RARG_parse_PossibleIfElseMatchMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match __attribute__ ((unused )), rarg_possible_if_else_match_t* possible_if_else_match, VALUE rb_arg )" )
	IT( "tests if current arg matches and either tests next arg against if condition or current arg against else condition" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array };
		RT_ParseDescriptor( parse_descriptor, 2, args );

		VALUE	rb_string_match	=	Qnil;
		VALUE	rb_array_match	=	Qnil;
		
		//	true match
		
		rarg_possible_match_t* possible_match	=	R_IfElse(	R_IfMatch(	R_MatchString( rb_string_match ),
																																	R_MatchArray( rb_array_match ) ));

		rarg_possible_if_else_match_t*	possible_if_match_match	=	possible_match->possible->if_else;

		BOOL	matched	=	RARG_parse_PossibleIfElseMatchMatch(	parse_descriptor,
																													possible_match,
																													possible_if_match_match,
																													rb_string );
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_string );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->next->match, rb_array );

		//	false first condition match
		
		VALUE	rb_symbol_match	=	Qnil;
		possible_match	=	R_IfElse(	R_IfMatch(	R_MatchArray( rb_array_match ),
																						R_MatchSymbol( rb_symbol_match ) ));

		possible_if_match_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseMatchMatch(	parse_descriptor,
																										possible_match,
																										possible_if_match_match,
																										rb_string );
		SHOULD_BE_FALSE( matched );
		

		//	false second condition match
		
		RT_ParseDescriptor( parse_descriptor, 2, args );
		possible_match	=	R_IfElse(	R_IfMatch(	R_MatchString( rb_string_match ),
																						R_MatchSymbol( rb_array_match ) ));

		possible_if_match_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseMatchMatch(	parse_descriptor,
																										possible_match,
																										possible_if_match_match,
																										rb_string );
		SHOULD_BE_FALSE( matched );
		
		//	if fail / else match

		RT_ParseDescriptor( parse_descriptor, 2, args );
		possible_match	=	R_IfElse(	R_IfMatch(	R_MatchArray( rb_array_match ),
																						R_MatchSymbol( rb_symbol_match ) ),
																R_Else(			R_MatchString( rb_string_match ) ) );

		possible_if_match_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseMatch(	parse_descriptor,
																							possible_match,
																							rb_string );
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_string );
		SHOULD_BE_NULL( parse_descriptor->matched_parameter_set->parameters->next );

		//	if fail / else fail

		RT_ParseDescriptor( parse_descriptor, 2, args );
		VALUE	rb_block	=	Qnil;
		possible_match	=	R_IfElse(	R_IfMatch(	R_MatchArray( rb_array_match ),
																						R_MatchSymbol( rb_symbol_match ) ),
																R_Else(			R_MatchBlockProc( rb_block ) ) );

		possible_if_match_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseMatch(	parse_descriptor,
																							possible_match,
																							rb_string );
		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

	/****************************************
	*  RARG_parse_PossibleIfElseValueMatch  *
	****************************************/

DESCRIBE( RARG_parse_PossibleIfElseValueMatch, "RARG_parse_PossibleIfElseValueMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match __attribute__ ((unused )), rarg_possible_if_else_match_t* possible_if_else_match, VALUE rb_arg )" )
	IT( "tests if current arg matches and either tests next arg against if condition or current arg against else condition" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array };
		RT_ParseDescriptor( parse_descriptor, 2, args );

		//	match if variable is non-nil
		
		VALUE	rb_string_match	=	Qnil;
		VALUE	rb_value	=	Qtrue;
		rarg_possible_match_t*	possible_match	=	R_IfElse(	R_IfValue(	rb_value,
																												R_MatchString( rb_string_match ) ) );
		rarg_possible_if_else_match_t*	possible_if_value_match	=	possible_match->possible->if_else;

		BOOL	matched	=	RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																													possible_match,
																													possible_if_value_match,
																													rb_string );
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_string );

		//	match if variable is Qtrue
		
		RT_ParseDescriptor( parse_descriptor, 2, args );
		rb_value	=	Qtrue;
		possible_match	=	R_IfElse(	R_IfValueEquals(	rb_value, Qtrue,
																									R_MatchString( rb_string_match ) ) );
		possible_if_value_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																										possible_match,
																										possible_if_value_match,
																										rb_string );
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_string );

		//	Fail - value non-nil
				
		RT_ParseDescriptor( parse_descriptor, 2, args );
		rb_value	=	Qnil;
		possible_match	=	R_IfElse(	R_IfValue(	rb_value,
																						R_MatchString( rb_string_match ) ) );
		possible_if_value_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																										possible_match,
																										possible_if_value_match,
																										rb_string );
		SHOULD_BE_FALSE( matched );

		//	Fail - value not equal
				
		RT_ParseDescriptor( parse_descriptor, 2, args );
		rb_value	=	Qfalse;
		possible_match	=	R_IfElse(	R_IfValueEquals(	rb_value, Qtrue,
																									R_MatchString( rb_string_match ) ) );
		possible_if_value_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																										possible_match,
																										possible_if_value_match,
																										rb_string );
		SHOULD_BE_FALSE( matched );

		//	Fail - match doesn't match
				
		RT_ParseDescriptor( parse_descriptor, 2, args );
		rb_value	=	Qtrue;
		VALUE	rb_array_match	=	Qnil;
		possible_match	=	R_IfElse(	R_IfValue(	rb_value,
																						R_MatchArray( rb_array_match ) ) );
		possible_if_value_match	=	possible_match->possible->if_else;

		matched	=	RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																										possible_match,
																										possible_if_value_match,
																										rb_string );
		SHOULD_BE_FALSE( matched );

	END_IT
END_DESCRIBE

	/***********************************
	*  RARG_parse_PossibleIfElseMatch  *
	***********************************/

DESCRIBE( RARG_parse_PossibleIfElseMatch, "RARG_parse_PossibleIfElseMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests if current arg matches and either tests next arg against if condition or current arg against else condition" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array, rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 3, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		VALUE	rb_string_match		=	Qnil;
		VALUE	rb_array_match		=	Qnil;
		VALUE	rb_object_match		=	Qnil;

		rarg_possible_match_t*	possible_match	=	R_IfElse(		R_IfMatch(	R_MatchString( rb_string_match ),
																																			R_IfElse(	R_IfMatch(	R_MatchArray( rb_array_match ),
																																														R_MatchAncestorInstance( rb_object_match, rb_cObject ) ) ) ) );

		
		BOOL	matched	=	RARG_parse_PossibleIfElseMatch(	parse_descriptor,
																										possible_match,
																										rb_string );		
		SHOULD_BE_TRUE( matched );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_string );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->next->match, rb_array );
		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->next->next->match, rb_cObject );

	END_IT
END_DESCRIBE

/*****************************
*  RARG_parse_PossibleMatch  *
*****************************/

DESCRIBE( RARG_parse_PossibleMatch, "RARG_parse_PossibleMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests a possible match against a passed arg to see if this parameter matches for this possibility" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array, rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 3, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		rarg_possible_match_t*	possible_match	=	R_String();

		
		BOOL	matched	=	RARG_parse_PossibleMatch(	parse_descriptor,
																							possible_match,
																							rb_string );		
		SHOULD_BE_TRUE( matched );

	END_IT
END_DESCRIBE

/*******************************
*  RARG_parse_PossibleMatches  *
*******************************/

DESCRIBE( RARG_parse_PossibleMatches, "RARG_parse_PossibleMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_t* parameter )" )
	IT( "iterates possible matches for passed args and tests for match for each specified parameter" )
		
		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array, rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 3, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		rarg_parameter_t* parameter = R_Parameter(	R_String(),
																								R_Array() );
		
		BOOL	matched	=	RARG_parse_PossibleMatches(	parse_descriptor,
																								parameter );		
		SHOULD_BE_TRUE( matched );

	END_IT
END_DESCRIBE

/**************************
*  RARG_parse_Parameters  *
**************************/

DESCRIBE( RARG_parse_Parameters, "RARG_parse_Parameters( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_t* parameter )" )
	IT( "iterates possible matches for passed args and tests for match for each specified parameter" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array, rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 3, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		rarg_parameter_t* parameter = R_Parameter(	R_String(),
																								R_Array() );
		
		BOOL	matched	=	RARG_parse_Parameters(	parse_descriptor,
																						parameter );		
		SHOULD_BE_TRUE( matched );

	END_IT
END_DESCRIBE

/*************************************
*  RARG_parse_ParameterSets          *
*  RARG_parse_ParameterSetsForMatch  *
*************************************/

DESCRIBE( RARG_parse_ParameterSets, "RARG_parse_ParameterSets( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_set_t* parameter_set )" )
	IT( "iterates possible sets of parameters tests for match for each set of parameters until a match is found or all are exhausted" )

		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_string	=	rb_str_new2( "some string" );
		VALUE	rb_array	=	rb_ary_new();
		VALUE	args[]	=	{ rb_string, rb_array, rb_cObject };
		RT_ParseDescriptor( parse_descriptor, 3, args );
		parse_descriptor->matched_parameter_ptr		=	& parse_descriptor->matched_parameter_set->parameters;
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );

		VALUE	rb_string_match	=	Qnil;
		VALUE	rb_array_match	=	Qnil;
		
		rarg_parameter_set_t* parameter_set = R_ParameterSet(	R_Parameter(	R_MatchString( rb_string_match ),
																																				R_MatchArray( rb_array_match ) ),
																													R_Parameter(	R_MatchArray( rb_array_match ) ) );
		
		rarg_matched_parameter_set_t*	matched_parameter_set	=	RARG_parse_ParameterSets(	parse_descriptor,
																																										parameter_set );		
		SHOULD_NOT_BE_NULL( matched_parameter_set );
		SHOULD_EQUAL( matched_parameter_set->parameters->match, rb_string );
		SHOULD_EQUAL( matched_parameter_set->parameters->next->match, rb_array );
	
		//	RARG_parse_ParameterSetsForMatch
	
		RARG_parse_ParameterSetsForMatch(	parse_descriptor,
																			parameter_set );
	
		SHOULD_EQUAL( rb_string, rb_string_match );
		SHOULD_EQUAL( rb_array, rb_array_match );
	
	END_IT
END_DESCRIBE

void rb_Rargs_parse_spec( void )	{
	
	rb_define_method( rb_cObject, "RARG_parse_PossibleBlockMatch_proc_relay", RARG_parse_PossibleBlockMatch_proc_relay, 1 );
	
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleBlockMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleBlockArityMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleTypeMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleAncestorMatches ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleMethodMatches ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleHashMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleIndexMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleGroupMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleIfElseMatchMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleIfElseValueMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleIfElseMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleMatches ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_Parameters ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_ParameterSets ), CSpec_NewOutputVerbose() );

}
