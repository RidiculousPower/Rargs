#include "rb_internal.h"
#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/rb_Rargs.h"

#include <string.h>

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
		rb_arg_two	=	Qnil;
		RT_ParseDescriptor( parse_descriptor, 2, args );
		matched	=	RARG_parse_PossibleGroupMatch( parse_descriptor, possible_group_match, rb_arg_one );
		SHOULD_BE_FALSE( matched );
		
	END_IT
END_DESCRIBE

/**********************************
*  RARG_parse_PossibleBlockMatch  *
**********************************/

VALUE proc_function( VALUE yieldarg __attribute__ ((unused)), VALUE proc_self );
VALUE proc_function( VALUE yieldarg __attribute__ ((unused)), VALUE proc_self ) { return proc_self; }
DESCRIBE( RARG_parse_PossibleBlockMatch, "RARG_parse_PossibleBlockMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match )" )
	IT( "tests for presence of passed block" )

		VALUE	rb_block_proc	=	rb_proc_new( proc_function, rb_cObject );
    rb_thread_t *th = GET_THREAD();
		th->cfp->lfp[0] = GC_GUARDED_PTR( & block );
		
		rarg_parse_descriptor_t*	parse_descriptor;

		VALUE	rb_arg_one	=	rb_proc_new( proc_function, rb_cObject );
		VALUE	args[] = { rb_arg_one };
		RT_ParseDescriptor( parse_descriptor, 1, args );

		VALUE	rb_block	=	Qnil;
		rarg_possible_match_t*	possible_block_match					=	R_MatchBlockProc( rb_block );
		rarg_parse_descriptor_and_possible_match_t*						parse_descriptor_and_possible_match	=	calloc( 1, sizeof( rarg_parse_descriptor_and_possible_match_t ) );
		parse_descriptor_and_possible_match->parse_descriptor	=	parse_descriptor;
		parse_descriptor_and_possible_match->possible_match		=	possible_block_match;
		
		rb_iterate( RARG_parse_PossibleBlockMatch_proc_relay, (VALUE) parse_descriptor_and_possible_match, proc_function, rb_arg_one );

		BOOL	matched	=	(BOOL) parse_descriptor_and_possible_match;

		SHOULD_BE_TRUE( matched );
		SHOULD_NOT_BE_NULL( parse_descriptor->matched_parameter_set->parameters );
		SHOULD_NOT_BE_NULL( parse_descriptor->matched_parameter_set->parameters->match );

		SHOULD_EQUAL( parse_descriptor->matched_parameter_set->parameters->match, rb_arg_one );
		SHOULD_EQUAL( *parse_descriptor->matched_parameter_set->parameters->receiver, rb_block );
		SHOULD_BE_TRUE( parse_descriptor->matched_parameter_set->parameters->block_match );

	END_IT
END_DESCRIBE

/***************************************
*  RARG_parse_PossibleBlockArityMatch  *
***************************************/

DESCRIBE( RARG_parse_PossibleBlockArityMatch, "RARG_parse_PossibleBlockArityMatch( rarg_possible_block_match_arity_t* possible_arity_match, VALUE rb_arity )" )
	IT( "tests arity of apassed block" )

	END_IT
END_DESCRIBE

	/******************************************
	*  RARG_parse_PossibleHashKeyOrDataMatch  *
	******************************************/

DESCRIBE( RARG_parse_PossibleHashKeyOrDataMatch, "RARG_parse_PossibleHashKeyOrDataMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_hash_key_data_match_t* possible_hash_key_or_data, VALUE rb_hash_arg, VALUE rb_key_or_data )" )
	IT( "tests for match against key or data of current hash match" )

	END_IT
END_DESCRIBE

	/**********************************
	*  RARG_parse_PossibleIndexMatch  *
	**********************************/

DESCRIBE( RARG_parse_PossibleIndexMatch, "RARG_parse_PossibleIndexMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests for match against index of current hash match" )

	END_IT
END_DESCRIBE

/*********************************
*  RARG_parse_PossibleHashMatch  *
*********************************/

DESCRIBE( RARG_parse_PossibleHashMatch, "RARG_parse_PossibleHashMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests for presence of hash, potentially also checking key/data for matches, or looking for the presence of indexes with optional data matching" )

	END_IT
END_DESCRIBE


/*********************************
*  RARG_parse_PossibleTypeMatch  *
*********************************/

DESCRIBE( RARG_parse_PossibleTypeMatch, "RARG_parse_PossibleTypeMatch( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg is a given underying type (R_... which correspond in name to T_..., always in caps)" )

	END_IT
END_DESCRIBE

/***************************************
*  RARG_parse_PossibleAncestorMatches  *
***************************************/

DESCRIBE( RARG_parse_PossibleAncestorMatches, "RARG_parse_PossibleAncestorMatches( rarg_parse_descriptor_t* parse_descriptor, rarg_possible_match_t* possible_match, VALUE rb_arg )" )
	IT( "tests whether current arg has ancestor(s) in ancestors chain" )

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
	
//	CSpec_Run( DESCRIPTION( RARG_parse_PossibleGroupMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( RARG_parse_PossibleBlockMatch ), CSpec_NewOutputVerbose() );

}
