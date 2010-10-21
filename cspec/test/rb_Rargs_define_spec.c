#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/rb_Rargs.h"

extern VALUE rb_mEnumerable;

/***********
*  R_Type  *
***********/

//	We test all generic possible matches here with Type Match
DESCRIBE( R_Type, "R_Type( type, ... )" )
	IT( "takes a RARG type and returns a possible match struct with a type set" )
		//	we want to test both |-ing together types and stringing together with commas
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

/***************
*  R_Ancestor  *
***************/

DESCRIBE( R_Ancestor, "R_Ancestor( ancestor_name, ... )" )
	IT( "takes an ancestor name string and returns a possible match struct with an ancestor instance set" )
		rarg_possible_match_t* possible_ancestor_match = R_Ancestor( "Enumerable" );
		//	make sure we got a struct back
		SHOULD_NOT_BE_NULL( possible_ancestor_match );
		//	and that the possible match type is RARG_ANCESTOR
		SHOULD_EQUAL( possible_ancestor_match->type, RARG_ANCESTOR );
		//	and that the ancestor is the instance we named
		SHOULD_EQUAL( possible_ancestor_match->possible->ancestors->ancestor, rb_mEnumerable );
	END_IT
END_DESCRIBE

/***********************
*  R_AncestorInstance  *
***********************/

DESCRIBE( R_AncestorInstance, "R_AncestorInstance( ancestor_instance, ... )" )
	IT( "takes an ancestor instance and returns a possible match struct with an ancestor instance set" )
		rarg_possible_match_t* possible_ancestor_match = R_AncestorInstance( rb_mEnumerable );
		//	make sure we got a struct back
		SHOULD_NOT_BE_NULL( possible_ancestor_match );
		//	and that the possible match type is RARG_ANCESTOR
		SHOULD_EQUAL( possible_ancestor_match->type, RARG_ANCESTOR );
		//	and that the ancestor is the instance we named
		SHOULD_EQUAL( possible_ancestor_match->possible->ancestors->ancestor, rb_mEnumerable );
	END_IT
END_DESCRIBE

/***********************
*  R_Method  *
***********************/

/************
*  R_Hash   *
*  R_Key    *
*  R_Data   *
*  R_Index  *
************/

/************
*  R_Proc  *
************/

/*************
*  R_Lambda  *
*************/

/************************
*  R_IfElse             *
*  R_IfValue            *
*  R_IfValueEquals      *
*  R_IfMatch            *
*  R_ElseIfValue        *
*  R_ElseIfValueEquals  *
*  R_ElseIfMatch        *
*  R_Else               *
************************/

/*****************
*  R_RespondsTo  *
*****************/

/**********************************
*  R_MethodReturns                *
*  R_MethodReturnsWithArgs        *
*  R_MethodReturnsNonNil          *
*  R_MethodReturnsNonNilWithArgs  *
**********************************/

/************************
*  R_RequireExactMatch  *
************************/

/************
*  R_Arity  *
************/

/************
*  R_Group  *
************/

/*****************
*  R_ExactMatch  *
*****************/

/***************
*  R_MatchAny  *
***************/

/**********************
*  R_MatchAnyForHash  *
**********************/

/*******************
*  R_ParameterSet  *
*******************/

/****************
*  R_Parameter  *
****************/

/************************
*  R_OptionalParameter  *
*  R_OptionalMatch      *
************************/

/***************************
*  R_DescribeParameterSet  *
***************************/

/************************
*  R_DescribeParameter  *
************************/

/****************************
*  R_DescribePossibleMatch  *
****************************/

/****************
*  R_ListOrder  *
****************/



void rb_Rargs_Define_spec( void )	{
	
	CSpec_Run( DESCRIPTION( R_Type ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_Ancestor ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_AncestorInstance ), CSpec_NewOutputVerbose() );

}
