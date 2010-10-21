#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/rb_Rargs.h"

/***********
*  R_Type  *
***********/

//	We test all generic possible matches here with Type Match
DESCRIBE( RARG_define_PossibleTypeMatch, "rarg_possible_match_t* RARG_define_PossibleTypeMatch( rarg_type_t type, ... ); R_Type( type, ... )" )
	IT( "returns a possible match struct with a type set" )
		rarg_possible_match_t* possible_type_match = R_Type( R_STRING | R_SYMBOL, R_ARRAY );
		//	make sure we got a struct back
		SHOULD_NOT_BE_NULL( possible_type_match );
		//	and that the possible match type is RARG_TYPE
		SHOULD_EQUAL( possible_type_match->type, RARG_TYPE );
		//	and that the type is what we said it should be
		SHOULD_EQUAL( possible_type_match->possible->types->type, R_STRING | R_SYMBOL | R_ARRAY );
		//	and that it is not optional by default
		SHOULD_BE_FALSE( possible_type_match->optional );
		//	receiver should be NULL
		SHOULD_BE_NULL( possible_type_match->receiver );
		//	description should be NULL
		SHOULD_BE_NULL( possible_type_match->description );
		//	next should be NULL
		SHOULD_BE_NULL( possible_type_match->next );
	END_IT
END_DESCRIBE

/***********
*  R_Type  *
***********/

/***************
*  R_Ancestor  *
***************/

/***********************
*  R_AncestorInstance  *
***********************/

/************
*  R_Group  *
************/

void rb_Rargs_Define_spec( void )	{
	
	CSpec_Run( DESCRIPTION( RARG_define_PossibleTypeMatch ), CSpec_NewOutputVerbose() );

}
