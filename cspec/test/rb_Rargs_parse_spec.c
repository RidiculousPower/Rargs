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
																												rb_cProc );		
		SHOULD_BE_TRUE( matched );
		

	END_IT
END_DESCRIBE

/*************************************
*  RARG_parse_PossibleMethodMatches  *
*************************************/

DESCRIBE( RARG_parse_PossibleMethodMatches, "RARG_parse_PossibleMethodMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg responds to method or returns non-nil for method or returns given values for method" )

	END_IT
END_DESCRIBE

	/***************************************
	*  RARG_parse_PossibleIfElseMatchMatch  *
	***************************************/

DESCRIBE( RARG_parse_PossibleIfElseMatchMatch, "RARG_parse_PossibleIfElseMatchMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match __attribute__ ((unused )), rarg_possible_if_else_match_t* possible_if_else_match, VALUE rb_arg )" )
	IT( "tests if current arg matches and either tests next arg against if condition or current arg against else condition" )

	END_IT
END_DESCRIBE

	/***************************************
	*  RARG_parse_PossibleIfElseValueMatch  *
	***************************************/

DESCRIBE( RARG_parse_PossibleIfElseValueMatch, "RARG_parse_PossibleIfElseValueMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match __attribute__ ((unused )), rarg_possible_if_else_match_t* possible_if_else_match, VALUE rb_arg )" )
	IT( "tests if value of specified variable is either non-nil (if not specified) or is specified value; if so, attempts match against current arg" )

	END_IT
END_DESCRIBE

/***************************************
*  RARG_parse_PossibleIfElseMatch  *
***************************************/

DESCRIBE( RARG_parse_PossibleIfElseMatch, "RARG_parse_PossibleIfElseMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match __attribute__ ((unused )), rarg_possible_if_else_match_t* possible_if_else_match, VALUE rb_arg )" )
	IT( "allows conditional match testing, grouping together conditional matches" )

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

/*****************************
*  RARG_parse_PossibleMatch  *
*****************************/

DESCRIBE( RARG_parse_PossibleMatch, "RARG_parse_PossibleMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests a possible match against a passed arg to see if this parameter matches for this possibility" )

	END_IT
END_DESCRIBE

/*******************************
*  RARG_parse_PossibleMatches  *
*******************************/

DESCRIBE( RARG_parse_PossibleMatches, "RARG_parse_PossibleMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_t* parameter )" )
	IT( "iterates possible matches for passed args and tests for match for each specified parameter" )

	END_IT
END_DESCRIBE

//	0 possible matches

//	1 possible match

//	more than 1 possible match


/**************************
*  RARG_parse_Parameters  *
**************************/

DESCRIBE( RARG_parse_Parameters, "RARG_parse_Parameters( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_t* parameter )" )
	IT( "iterates possible matches for passed args and tests for match for each specified parameter" )

	END_IT
END_DESCRIBE

//	0 possible matches

//	1 possible match

//	more than 1 possible match

/*****************************
*  RARG_parse_ParameterSets  *
*****************************/

DESCRIBE( RARG_parse_ParameterSets, "RARG_parse_ParameterSets( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_set_t* parameter_set )" )
	IT( "iterates possible sets of parameters tests for match for each set of parameters until a match is found or all are exhausted" )

	END_IT
END_DESCRIBE

//	0 parameters

//	1 parameter

//	more than 1 parameter

/*************************************
*  RARG_parse_ParameterSetsForMatch  *
*************************************/

DESCRIBE( RARG_parse_ParameterSetsForMatch, "RARG_parse_ParameterSetsForMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_parameter_set_t* parameter_sets )" )
	IT( "parses parameters and assigns success to specified receivers or throws error" )

	END_IT
END_DESCRIBE

//	0 parameter sets

//	1 parameter set

//	more than 1 parameter set

/*********************
*  R_Define  *
*********************/

DESCRIBE( R_Define, "R_Define( argc, args, rb_self, parameter_set, ... )" )
	IT( "defines parameter sets for the current function" )

	END_IT
END_DESCRIBE

/************
*  R_Parse  *
************/

DESCRIBE( R_Parse, "R_Parse()" )
	IT( "parses parameter sets for the current passed args for the current function; assumes R_Define has been called" )

	END_IT
END_DESCRIBE

/*********************
*  R_DefineAndParse  *
*********************/

DESCRIBE( R_DefineAndParse, "R_DefineAndParse( argc, args, rb_self, parameter_set, ... )" )
	IT( "defines and parses parameter sets for the current passed args for the current function" )

	END_IT
END_DESCRIBE

/**********
*  R_Arg  *
**********/

DESCRIBE( R_Arg, "R_Arg( rb_receiver )" )
	IT( "grabs the next argument and assigns it to the specified receiver; useful after parsing when additional arguments remain" )

	END_IT
END_DESCRIBE


/*************************************
*  RARG_parse_IterateHashDescriptor  *
*************************************/

DESCRIBE( RARG_parse_IterateHashDescriptor, "RARG_parse_IterateHashDescriptor( rb_hash, c_function )" )
	IT( "sends each key/data pair in the hash back to the present function as key, data with optional args prepended" )

	END_IT
END_DESCRIBE

/**************************************
*  RARG_parse_IterateArrayDescriptor  *
**************************************/

DESCRIBE( RARG_parse_IterateArrayDescriptor, "RARG_parse_IterateArrayDescriptor( rb_array, c_function )" )
	IT( "sends each element in the array back to the present function with optional args prepended" )

	END_IT
END_DESCRIBE


void rb_Rargs_Parse_spec( void )	{
	
	rb_define_method( rb_cObject, "RARG_parse_PossibleBlockMatch_proc_relay", RARG_parse_PossibleBlockMatch_proc_relay, 1 );
	
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleBlockMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleBlockArityMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleTypeMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleHashMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleIndexMatch ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleAncestorMatches ), CSpec_NewOutputVerbose() );

	CSpec_Run( DESCRIPTION( RARG_parse_PossibleGroupMatch ), CSpec_NewOutputVerbose() );

}
