#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/include/rargs/rargs.h"

#include <string.h>

extern VALUE rb_mEnumerable;

/***********
*  R_Type  *
***********/

//  We test all generic possible matches here with Type Match
DESCRIBE( RD_Type, "R_Type( type, ... )" )
  IT( "takes a RARG type and returns a possible match struct with a type set" )
    //  we want to test both |-ing together types and stringing together with commas
    rarg_possible_match_t* possible_type_match = R_Type( R_STRING | R_SYMBOL, R_ARRAY );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_type_match );
    //  and that the possible match type is RARG_TYPE
    SHOULD_EQUAL( possible_type_match->type, RARG_TYPE );
    //  and that the type is what we said it should be
    SHOULD_EQUAL( possible_type_match->possible->types->type, R_STRING | R_SYMBOL | R_ARRAY );
    //  and that it is not optional by default
    SHOULD_BE_FALSE( possible_type_match->optional );
    //  receiver should be NULL
    SHOULD_BE_NULL( possible_type_match->receiver );
    //  description should be NULL
    SHOULD_BE_NULL( possible_type_match->description );
    //  next should be NULL
    SHOULD_BE_NULL( possible_type_match->next );
  END_IT
END_DESCRIBE

/***************
*  R_Ancestor  *
***************/

DESCRIBE( RD_Ancestor, "R_Ancestor( ancestor_name, ... )" )
  IT( "takes an ancestor name string and returns a possible match struct with an ancestor instance set" )
    rarg_possible_match_t* possible_ancestor_match = R_Ancestor( "Enumerable" );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_ancestor_match );
    //  and that the possible match type is RARG_ANCESTOR
    SHOULD_EQUAL( possible_ancestor_match->type, RARG_ANCESTOR );
    //  and that the ancestor is the instance we named
    SHOULD_EQUAL( possible_ancestor_match->possible->ancestors->ancestor, rb_mEnumerable );
  END_IT
END_DESCRIBE

/***********************
*  R_AncestorInstance  *
***********************/

DESCRIBE( RD_AncestorInstance, "R_AncestorInstance( ancestor_instance, ... )" )
  IT( "takes an ancestor instance and returns a possible match struct with an ancestor instance set" )
    rarg_possible_match_t* possible_ancestor_match = R_AncestorInstance( rb_mEnumerable );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_ancestor_match );
    //  and that the possible match type is RARG_ANCESTOR
    SHOULD_EQUAL( possible_ancestor_match->type, RARG_ANCESTOR );
    //  and that the ancestor is the instance we named
    SHOULD_EQUAL( possible_ancestor_match->possible->ancestors->ancestor, rb_mEnumerable );
  END_IT
END_DESCRIBE

/************
*  R_Hash   *
*  R_HashKey    *
*  R_HashData   *
************/

DESCRIBE( RD_HashKeyData, "R_Hash( R_HashKey( possible_match ), R_HashData( possible_match ) )" )
  IT( "takes a key and data, each of which can be any type of possible match" )
    rarg_possible_hash_key_data_match_t* key_possible_match = R_HashKey( R_Any() );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( key_possible_match );
    //  we aren't matching anything, so default is not to assign parent hash
    SHOULD_BE_FALSE( key_possible_match->assign_parent_hash_for_match );
    //  same function so no need to test
    rarg_possible_hash_key_data_match_t* data_possible_match = R_HashData( R_Any() );
    rarg_possible_match_t* possible_hash_match = R_Hash( key_possible_match, data_possible_match );
    //  and that the possible match type is RARG_HASH
    SHOULD_EQUAL( possible_hash_match->type, RARG_HASH);
  END_IT
  IT( "can take NULL arguments" )
    rarg_possible_match_t* possible_hash_match = R_Hash( NULL, NULL );
    SHOULD_NOT_BE_NULL( possible_hash_match );
  END_IT
END_DESCRIBE

/************
*  R_Index  *
************/

DESCRIBE( RD_Index, "R_Index( index_name )" )
  IT( "takes a c string to describe a hash string or symbol index" )
    rarg_possible_match_t* possible_hash_index_match = R_Index( "index_name" );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_hash_index_match );
    SHOULD_EQUAL( strcmp( possible_hash_index_match->possible->hash->possible_index_match->index_name, "index_name" ), 0 );
    SHOULD_BE_FALSE( possible_hash_index_match->possible->hash->possible_index_match->optional );
    SHOULD_BE_FALSE( possible_hash_index_match->possible->hash->possible_index_match->assign_parent_hash_for_match );
    SHOULD_BE_NULL( possible_hash_index_match->possible->hash->possible_index_match->receiver );
    //  and that the possible match type is RARG_HASH
    SHOULD_BE_NULL( possible_hash_index_match->possible->hash->possible_index_match->possible_index_data_match);
  END_IT
END_DESCRIBE

/****************
*  R_BlockProc  *
****************/

DESCRIBE( RD_BlockProc, "R_BlockProc()" )
  IT( "takes no arguments and looks for a block to be present" )
    rarg_possible_match_t* possible_block_match = R_BlockProc();
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_block_match );
    SHOULD_EQUAL( possible_block_match->type, RARG_BLOCK );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block );
    SHOULD_BE_FALSE( possible_block_match->possible->block->lambda_instead_of_proc );
    SHOULD_BE_NULL( possible_block_match->possible->block->possible_arity );
  END_IT
END_DESCRIBE

/******************
*  R_BlockLambda  *
******************/

DESCRIBE( RD_BlockLambda, "R_BlockLambda()" )
  IT( "takes no arguments and looks for a block to be present" )
    rarg_possible_match_t* possible_block_match = R_BlockLambda();
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_block_match );
    SHOULD_EQUAL( possible_block_match->type, RARG_BLOCK );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block );
    SHOULD_BE_TRUE( possible_block_match->possible->block->lambda_instead_of_proc );
    SHOULD_BE_NULL( possible_block_match->possible->block->possible_arity );
  END_IT
END_DESCRIBE

/*************************
*  R_BlockProcWithArity  *
*  R_Arity               *
*************************/

DESCRIBE( RD_BlockProcWithArity, "R_BlockProcWithArity( arity, ... )" )
  IT( "takes arities and looks for a block with one of given arities to be present" )
    rarg_possible_match_t* possible_block_match = R_BlockProcWithArity( 1 );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_block_match );
    SHOULD_EQUAL( possible_block_match->type, RARG_BLOCK );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block );
    SHOULD_BE_FALSE( possible_block_match->possible->block->lambda_instead_of_proc );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block->possible_arity );
    SHOULD_EQUAL( possible_block_match->possible->block->possible_arity->arity, 1 );
    SHOULD_BE_NULL( possible_block_match->possible->block->possible_arity->next );
  END_IT
END_DESCRIBE

/***************************
*  R_BlockLambdaWithArity  *
*  R_Arity                 *
***************************/

DESCRIBE( RD_BlockLambdaWithArity, "R_BlockLambdaWithArity( arity, ... )" )
  IT( "takes arities and looks for a block with one of given arities to be present" )
    rarg_possible_match_t* possible_block_match = R_BlockLambdaWithArity( 1 );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_block_match );
    SHOULD_EQUAL( possible_block_match->type, RARG_BLOCK );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block );
    SHOULD_BE_TRUE( possible_block_match->possible->block->lambda_instead_of_proc );
    SHOULD_NOT_BE_NULL( possible_block_match->possible->block->possible_arity );
    SHOULD_EQUAL( possible_block_match->possible->block->possible_arity->arity, 1 );
    SHOULD_BE_NULL( possible_block_match->possible->block->possible_arity->next );
  END_IT
END_DESCRIBE

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

DESCRIBE( RD_IfElse, "R_IfElse( possible_if_else_match, ... )" )
  IT( "takes a series of possible if/else possible matches; chained ifs are treated as &&" )
    VALUE  rb_value        =  Qtrue;
    VALUE  rb_other_value  =  rb_cObject;
    rarg_possible_if_else_match_t*  possible_if_value_match  =  R_IfValue( rb_value, R_Any() );
    SHOULD_EQUAL( possible_if_value_match->type, RARG_CONDITION_IF_VALUE );
    rarg_possible_if_else_match_t*  possible_if_match_match  =  R_IfMatch( R_Symbol(), R_Any() );
    SHOULD_EQUAL( possible_if_match_match->type, RARG_CONDITION_IF_MATCH );
    rarg_possible_if_else_match_t*  possible_else_if_value_match  =  R_ElseIfValue( rb_other_value, R_Any() );
    SHOULD_EQUAL( possible_else_if_value_match->type, RARG_CONDITION_ELSE_IF_VALUE );
    rarg_possible_if_else_match_t*  possible_else_if_match_match  =  R_ElseIfMatch( R_String(), R_Any() );
    SHOULD_EQUAL( possible_else_if_match_match->type, RARG_CONDITION_ELSE_IF_MATCH );
    rarg_possible_if_else_match_t*  possible_else_value_match      =  R_Else( R_Hash( NULL, NULL ) );
    SHOULD_EQUAL( possible_else_value_match->type, RARG_CONDITION_ELSE_MATCH );

    SHOULD_NOT_BE_NULL( possible_if_value_match );
    SHOULD_NOT_BE_NULL( possible_if_match_match );
    SHOULD_NOT_BE_NULL( possible_else_if_value_match );
    SHOULD_NOT_BE_NULL( possible_else_if_match_match );
    SHOULD_NOT_BE_NULL( possible_else_value_match );

    rarg_possible_match_t* possible_if_else_match = R_IfElse(  possible_if_value_match, 
                                                              possible_if_match_match,
                                                              possible_else_if_value_match,
                                                              possible_else_if_match_match,
                                                              possible_else_value_match );
    
    SHOULD_EQUAL( possible_if_else_match->type, RARG_IF_ELSE );
    SHOULD_NOT_BE_NULL( possible_if_else_match->possible->if_else );
    
    SHOULD_EQUAL( possible_if_else_match->possible->if_else, possible_if_value_match );
    SHOULD_EQUAL( possible_if_else_match->possible->if_else->next, possible_if_match_match );
    SHOULD_EQUAL( possible_if_else_match->possible->if_else->next->next, possible_else_if_value_match );
    SHOULD_EQUAL( possible_if_else_match->possible->if_else->next->next->next, possible_else_if_match_match );
    SHOULD_EQUAL( possible_if_else_match->possible->if_else->next->next->next->next, possible_else_value_match );
    
  END_IT
END_DESCRIBE

/*****************
*  R_RespondsTo  *
*****************/

DESCRIBE( RD_RespondsTo, "R_RespondsTo( ancestor_name, ... )" )
  IT( "takes a method name c string and tests whether parameter responds to method with name" )
    rarg_possible_match_t* possible_responds_to_match = R_RespondsTo( "method" );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_responds_to_match );
    //  and that the possible match type is RARG_METHOD
    SHOULD_EQUAL( possible_responds_to_match->type, RARG_METHOD );
    SHOULD_EQUAL( possible_responds_to_match->possible->methods->method, rb_intern( "method" ) );
  END_IT
END_DESCRIBE

/**************
*  R_Returns  *
**************/

DESCRIBE( RD_Returns, "R_Returns( method_name, rb_return_value, ... )" )
  IT( "takes a method name C string and any number of Ruby return values and tests whether method return matches one of return values" )
    rarg_possible_match_t* possible_method_return_match = R_Returns( "method", Qfalse );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_method_return_match );
    //  and that the possible match type is RARG_METHOD
    SHOULD_EQUAL( possible_method_return_match->type, RARG_METHOD );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->method, rb_intern( "method" ) );
    SHOULD_NOT_BE_NULL( possible_method_return_match->possible->methods->possible_return );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->possible_return->value, Qfalse );
  END_IT
END_DESCRIBE

/**********************
*  R_ReturnsWithArgs  *
**********************/

DESCRIBE( RD_ReturnsWithArgs, "R_ReturnsWithArgs( method_name, argc, args, rb_return_value, ... )" )
  IT( "takes a method name C string, argc, args (VALUE*), and any number of Ruby return values and tests whether method return matches one of return values" )
    VALUE  args[]  =  { Qtrue };
    rarg_possible_match_t* possible_method_return_match = R_ReturnsWithArgs( "method", 1, args, Qfalse );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_method_return_match );
    //  and that the possible match type is RARG_METHOD
    SHOULD_EQUAL( possible_method_return_match->type, RARG_METHOD );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->method, rb_intern( "method" ) );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->argc, 1 );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->args, args );
    SHOULD_NOT_BE_NULL( possible_method_return_match->possible->methods->possible_return );
    SHOULD_EQUAL( possible_method_return_match->possible->methods->possible_return->value, Qfalse );
  END_IT
END_DESCRIBE

/**************************
*  R_ReturnsNonNil  *
**************************/

DESCRIBE( RD_ReturnsNonNil, "R_ReturnsNonNil( method_name, ... )" )
  IT( "takes amy number of method name C strings and tests whether methods return nil" )
    rarg_possible_match_t* possible_method_return_not_nil_match = R_ReturnsNonNil( "method", Qfalse );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_method_return_not_nil_match );
    //  and that the possible match type is RARG_METHOD
    SHOULD_EQUAL( possible_method_return_not_nil_match->type, RARG_METHOD );
    SHOULD_EQUAL( possible_method_return_not_nil_match->possible->methods->method, rb_intern( "method" ) );
    SHOULD_BE_TRUE( possible_method_return_not_nil_match->possible->methods->ensure_return_non_nil );
  END_IT
END_DESCRIBE

/**********************************
*  R_ReturnsNonNilWithArgs  *
**********************************/

DESCRIBE( RD_ReturnsNonNilWithArgs, "R_ReturnsNonNilWithArgs( method_name, argc, args )" )
  IT( "takes a method name C string, argc, and args (VALUE*) and tests whether method return nil" )
    VALUE  args[]  =  { Qtrue };
    rarg_possible_match_t* possible_method_return_not_nil_match = R_ReturnsNonNilWithArgs( "method", 1, args );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( possible_method_return_not_nil_match );
    //  and that the possible match type is RARG_METHOD
    SHOULD_EQUAL( possible_method_return_not_nil_match->type, RARG_METHOD );
    SHOULD_EQUAL( possible_method_return_not_nil_match->possible->methods->method, rb_intern( "method" ) );
    SHOULD_EQUAL( possible_method_return_not_nil_match->possible->methods->argc, 1 );
    SHOULD_EQUAL( possible_method_return_not_nil_match->possible->methods->args, args );
    SHOULD_BE_TRUE( possible_method_return_not_nil_match->possible->methods->ensure_return_non_nil );
  END_IT
END_DESCRIBE

/****************
*  R_Parameter  *
****************/

DESCRIBE( RD_Parameter, "R_ParameterSet( parameter_set, ... )" )
  IT( "takes a method name C string, argc, args (VALUE*), and any number of Ruby return values and tests whether method return matches one of return values" )
    rarg_possible_match_t* possible_match = R_Any();
    rarg_parameter_t* parameter = R_Parameter( possible_match );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( parameter );
    SHOULD_EQUAL( parameter->possible_match, possible_match );
  END_IT
END_DESCRIBE

/*******************
*  R_ParameterSet  *
*******************/

DESCRIBE( RD_ParameterSet, "R_ParameterSet( parameter_set, ... )" )
  IT( "takes a method name C string, argc, args (VALUE*), and any number of Ruby return values and tests whether method return matches one of return values" )
    rarg_possible_match_t* possible_match = R_Any();
    rarg_parameter_t* parameter = R_Parameter( possible_match );
    rarg_parameter_set_t* parameter_set = R_ParameterSet( parameter );
    //  make sure we got a struct back
    SHOULD_NOT_BE_NULL( parameter_set );
    SHOULD_EQUAL( parameter_set->parameters, parameter );
  END_IT
END_DESCRIBE

/*****************
*  R_ExactMatch  *
*****************/

DESCRIBE( RD_ExactMatch, "R_ExactMatch( parameter_set, ... )" )
  IT( "takes a parameter set and matches only if no further args remain after all parameters have matched" )
    rarg_possible_match_t* possible_match = R_Any();
    rarg_parameter_t* parameter = R_Parameter( possible_match );
    rarg_parameter_set_t* parameter_set = R_ExactMatch( R_ParameterSet( parameter ) );
    SHOULD_NOT_BE_NULL( parameter_set );
    SHOULD_BE_TRUE( parameter_set->require_exact );
  END_IT
END_DESCRIBE

/************
*  R_Group  *
************/

DESCRIBE( RD_Group, "R_Group( possible_match, ... )" )
  IT( "takes multiple possible matches and groups them to perform an && match, matching a string of arguments" )
    rarg_possible_match_t* possible_string_match  =  R_String();
    rarg_possible_match_t* possible_hash_match    =  R_Hash( NULL, NULL );
    rarg_possible_match_t* possible_group_match    = R_Group(  possible_string_match,
                                                              possible_hash_match );
    SHOULD_NOT_BE_NULL( possible_group_match );
    SHOULD_NOT_BE_NULL( possible_group_match->possible->group->match );
    SHOULD_EQUAL( possible_group_match->possible->group->match, possible_string_match );
    SHOULD_NOT_BE_NULL( possible_group_match->possible->group->next );
    SHOULD_EQUAL( possible_group_match->possible->group->next->match, possible_hash_match );
  END_IT
END_DESCRIBE

/****************
*  R_MatchType  *
****************/

DESCRIBE( RD_MatchType, "R_MatchType( type, receiver )" )
  IT( "matches given parameter to the specified receiver" )
    VALUE  rb_receiver  =  Qnil;
    rarg_possible_match_t* possible_match  =  R_MatchType( rb_receiver, R_STRING );
    SHOULD_NOT_BE_NULL( possible_match );
    SHOULD_EQUAL( possible_match->type, RARG_TYPE );
    SHOULD_EQUAL( possible_match->receiver, & rb_receiver );
  END_IT
END_DESCRIBE

/*****************
*  R_MatchIndex  *
*****************/

DESCRIBE( RD_MatchIndex, "R_MatchIndex( index_string, receiver )" )
  IT( "matches data corresponding to index in parameter to the specified receiver" )
    VALUE  rb_receiver  =  Qnil;
    rarg_possible_match_t* possible_index_match  =  R_MatchIndex( rb_receiver, "index" );
    SHOULD_NOT_BE_NULL( possible_index_match );
    SHOULD_EQUAL( strcmp( possible_index_match->possible->hash->possible_index_match->index_name, "index" ), 0 );
    SHOULD_EQUAL( possible_index_match->possible->hash->possible_index_match->receiver, & rb_receiver );
    SHOULD_BE_FALSE( possible_index_match->optional );
    SHOULD_BE_FALSE( possible_index_match->possible->hash->possible_index_match->assign_parent_hash_for_match );
  END_IT
END_DESCRIBE

/*************************
*  R_MatchIndexMatch  *
*************************/

DESCRIBE( RD_MatchIndexMatch, "R_MatchIndexMatch( index_string, possible_match, receiver )" )
  IT( "attempts to match data corresponding to index in parameter and assign to the specified receiver" )
    VALUE  rb_receiver  =  Qnil;
    rarg_possible_match_t*  possible_string_match  =  R_String();
    rarg_possible_match_t*  possible_index_match  =  R_MatchIndexMatch( rb_receiver, "index", possible_string_match );
    SHOULD_NOT_BE_NULL( possible_index_match );
    SHOULD_EQUAL( strcmp( possible_index_match->possible->hash->possible_index_match->index_name, "index" ), 0 );
    SHOULD_EQUAL( possible_index_match->possible->hash->possible_index_match->receiver, & rb_receiver );
    SHOULD_EQUAL( possible_index_match->possible->hash->possible_index_match->possible_index_data_match, possible_string_match );
  END_IT
END_DESCRIBE

/*******************************
*  R_MatchPossibleTypeForHash  *
*******************************/

DESCRIBE( RD_MatchPossibleTypeForHash, "R_MatchPossibleTypeForHash( receiver )" )
  IT( "attempts a possible match for a hash key or data and if match occurs, assigns parent hash to the specified receiver" )
    VALUE  rb_receiver  =  Qnil;
    rarg_possible_match_t*  possible_string_match  =  R_String();
    rarg_possible_hash_key_data_match_t* possible_hash_key_data_match  =  R_MatchPossibleTypeForHash( rb_receiver, R_HashKey( possible_string_match ) );
    SHOULD_NOT_BE_NULL( possible_hash_key_data_match );
    SHOULD_EQUAL( possible_hash_key_data_match->possible_match->receiver, & rb_receiver );
    SHOULD_BE_TRUE( possible_hash_key_data_match->assign_parent_hash_for_match );
  END_IT
END_DESCRIBE

/************************
*  R_OptionalParameter  *
*  R_OptionalMatch      *
************************/

DESCRIBE( RD_Optional, "R_OptionalParameter( parameter ); R_OptionalMatch( possible_match )" )
  IT( "marks the given parameter or possible match as optional" )
    rarg_possible_match_t*  possible_match  =  R_OptionalMatch( R_Any() );
    SHOULD_BE_TRUE( possible_match->optional );
    rarg_parameter_t*        parameter        =  R_OptionalParameter( possible_match );
    SHOULD_BE_TRUE( parameter->optional );
  END_IT
END_DESCRIBE

/****************************
*  R_DescribeParameterSet   *
*  R_DescribeParameter      *
*  R_DescribePossibleMatch  *
*  R_ListOrder  *
****************************/

DESCRIBE( RD_Describe, "R_DescribeParameterSet( \"\", ... ); R_DescribeParameter( \"\", ... ); R_DescribePossibleMatch( \"\", ... );" )
  IT( "describes usage for possible match, parameter, or parameter set" )
    rarg_possible_match_t*  possible_match  =  R_DescribePossibleMatch(  R_Any(),
                                                                        1,
                                                                        "<any>" );
    SHOULD_EQUAL( possible_match->description->order_ranking, 1 );
    SHOULD_EQUAL( strcmp( possible_match->description->description, "<any>" ), 0 );
    rarg_parameter_t*        parameter        =  R_DescribeParameter(  R_Parameter( possible_match ),
                                                                    2,
                                                                    "param" );
    SHOULD_EQUAL( parameter->description->order_ranking, 2 );
    SHOULD_EQUAL( strcmp( parameter->description->description, "param" ), 0 );
    rarg_parameter_set_t*    parameter_set    =  R_DescribeParameterSet(  R_ParameterSet( parameter ),
                                                                      3,
                                                                      "param_set" );
    SHOULD_EQUAL( parameter_set->description->order_ranking, 3 );
    SHOULD_EQUAL( strcmp( parameter_set->description->description, "param_set" ), 0 );
  END_IT
END_DESCRIBE



void rb_Rargs_define_spec( void )  {
  
  CSpec_Run( DESCRIPTION( RD_Type ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Ancestor ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_AncestorInstance ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_HashKeyData ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Index ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_BlockProc ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_BlockLambda ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_BlockProcWithArity ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_BlockLambdaWithArity ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_IfElse ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_RespondsTo ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Returns ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_ReturnsWithArgs ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_ReturnsNonNil ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_ReturnsNonNilWithArgs ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Parameter ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_ParameterSet ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_ExactMatch ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Group ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_MatchType ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_MatchIndex ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_MatchIndexMatch ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_MatchPossibleTypeForHash ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Optional ), CSpec_NewOutputVerbose() );
  CSpec_Run( DESCRIPTION( RD_Describe ), CSpec_NewOutputVerbose() );

}
