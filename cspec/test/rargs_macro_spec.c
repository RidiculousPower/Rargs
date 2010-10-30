#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/include/rargs/rargs.h"

#include <string.h>

/************************
*  R_Type( type, ... )  *
************************/

DESCRIBE( R_Type, "R_Type( type, ... )" )
	IT( "checks an argument for its type" )		

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		
		//	test for each type

		//	nil

		VALUE	args_for_nil[]	=	{ Qnil };
		RI_DefineAndParse( rarg_parameter_sets_for_nil,				rarg_parse_descriptor_for_nil,      argc, args_for_nil,					rb_self, FALSE, R_ParameterSet( R_Parameter( R_Nil() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_nil->args_parsed );
		
		//	true
		
		VALUE	args_for_true[]	=	{ Qtrue };
		RI_DefineAndParse( rarg_parameter_sets_for_true,			rarg_parse_descriptor_for_true,     argc, args_for_true,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_True() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_true->args_parsed );

		//	false

		VALUE	args_for_false[]	=	{ Qfalse };
		RI_DefineAndParse( rarg_parameter_sets_for_false,			rarg_parse_descriptor_for_false,    argc, args_for_false,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_False() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_false->args_parsed );

		//	class

		VALUE	args_for_class[]	=	{ rb_cObject };
		RI_DefineAndParse( rarg_parameter_sets_for_class,			rarg_parse_descriptor_for_class,    argc, args_for_class,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Class() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_class->args_parsed );

		//	module

		VALUE	args_for_module[]	=	{ rb_mEnumerable };
		RI_DefineAndParse( rarg_parameter_sets_for_module,		rarg_parse_descriptor_for_module,   argc, args_for_module, 			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Module() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_module->args_parsed );

		//	string

		VALUE	args_for_string[]	=	{ rb_str_new2( "string" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_string,		rarg_parse_descriptor_for_string,   argc, args_for_string,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_String() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_string->args_parsed );

		//	symbol

		VALUE	args_for_symbol[]	=	{ ID2SYM( rb_intern( "symbol" ) ) };
		RI_DefineAndParse( rarg_parameter_sets_for_symbol,		rarg_parse_descriptor_for_symbol,   argc, args_for_symbol,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Symbol() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_symbol->args_parsed );

		//	array

		VALUE	args_for_array[]	=	{ rb_ary_new() };
		RI_DefineAndParse( rarg_parameter_sets_for_array,			rarg_parse_descriptor_for_array,    argc, args_for_array,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Array() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_array->args_parsed );

		//	hash

		VALUE	args_for_hash[]	=	{ rb_hash_new() };
		RI_DefineAndParse( rarg_parameter_sets_for_hash,			rarg_parse_descriptor_for_hash,    argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Type( R_HASH ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );

		//	fixnum

		VALUE	args_for_fixnum[]	=	{ INT2FIX( 1 ) };
		RI_DefineAndParse( rarg_parameter_sets_for_fixnum,		rarg_parse_descriptor_for_fixnum,   argc, args_for_fixnum,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_FixNum() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_fixnum->args_parsed );

		//	data

		struct rb_data_object_s	{
			BOOL	true_or_false;
		}	data_object;
		VALUE	rb_cDataObject	=	rb_define_class( "DataObject", rb_cObject );
		VALUE	rb_data_object	=	Data_Wrap_Struct(	rb_cDataObject,
																							NULL,
																							NULL,
																							& data_object );
		VALUE	args_for_data[]	=	{ rb_data_object };
		RI_DefineAndParse( rarg_parameter_sets_for_data,			rarg_parse_descriptor_for_data,     argc, args_for_data,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Data() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_data->args_parsed );

		//	file

		VALUE	rb_file	=	rb_file_open( "../test/main_spec.c", "r" );
		VALUE	args_for_file[]	=	{ rb_file };
		RI_DefineAndParse( rarg_parameter_sets_for_file,			rarg_parse_descriptor_for_file,     argc, args_for_file,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_File() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_file->args_parsed );
		rb_io_close( rb_file );

		//	regexp

		VALUE	rb_regexp	=	rb_reg_new_str( rb_str_new2( "regexp" ), 0 );
		VALUE	args_for_regexp[]	=	{ rb_regexp };
		RI_DefineAndParse( rarg_parameter_sets_for_regexp,		rarg_parse_descriptor_for_regexp,   argc, args_for_regexp,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Regexp() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_regexp->args_parsed );

		//	match

		VALUE	args_for_match[]		=	{ rb_eval_string( "/regexp/.match( 'regexp' )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_match,			rarg_parse_descriptor_for_match,    argc, args_for_match,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_RegexpMatch() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_match->args_parsed );

		//	object

		VALUE	args_for_object[]	=	{ rb_eval_string( "Object.new" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_object,		rarg_parse_descriptor_for_object,   argc, args_for_object,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Object() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_object->args_parsed );

		//	float

		VALUE	args_for_float[]	=	{ rb_eval_string( "42.420" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_float,			rarg_parse_descriptor_for_float,    argc, args_for_float, 			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Float() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_float->args_parsed );

		//	bignum

		VALUE	args_for_bignum[]	=	{ rb_eval_string( "10000000000000000000000000" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_bignum,		rarg_parse_descriptor_for_bignum,   argc, args_for_bignum,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_BigNum() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_bignum->args_parsed );

		//	rational

		VALUE	args_for_rational[]	=	{ rb_eval_string( "Rational( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_rational,	rarg_parse_descriptor_for_rational, argc, args_for_rational,		rb_self, FALSE, R_ParameterSet( R_Parameter( R_Rational() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_rational->args_parsed );

		//	complex

		VALUE	args_for_complex[]	=	{ rb_eval_string( "Complex( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_complex,		rarg_parse_descriptor_for_complex,  argc, args_for_complex,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Complex() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_complex->args_parsed );

		//	struct

		VALUE	args_for_struct[]	=	{ rb_eval_string( "Struct.new( 'RargStruct', :answer, :other_answer ).new( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_struct,		rarg_parse_descriptor_for_struct,   argc, args_for_struct,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_Struct() ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_struct->args_parsed );

	END_IT
END_DESCRIBE

/**********************************
*  R_MatchType( receiver, type )  *
**********************************/

DESCRIBE( R_MatchType, "R_MatchType( receiver, type )" )
	IT( "checks an argument for its type and assigns match to receiver" )

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		
		//	test for each type

		//	nil

		VALUE	rb_nil_match	=	Qnil;
		VALUE	args_for_nil[]	=	{ Qnil };
		RI_DefineAndParse( rarg_parameter_sets_for_nil,				rarg_parse_descriptor_for_nil,      argc, args_for_nil,					rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchNil( rb_nil_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_nil->args_parsed );

		//	true
		
		VALUE	rb_true_match	=	Qnil;
		VALUE	args_for_true[]	=	{ Qtrue };
		RI_DefineAndParse( rarg_parameter_sets_for_true,			rarg_parse_descriptor_for_true,     argc, args_for_true,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchTrue( rb_true_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_true->args_parsed );

		//	false

		VALUE	rb_false_match	=	Qnil;
		VALUE	args_for_false[]	=	{ Qfalse };
		RI_DefineAndParse( rarg_parameter_sets_for_false,			rarg_parse_descriptor_for_false,    argc, args_for_false,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchFalse( rb_false_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_false->args_parsed );

		//	class

		VALUE	rb_class_match	=	Qnil;
		VALUE	args_for_class[]	=	{ rb_cObject };
		RI_DefineAndParse( rarg_parameter_sets_for_class,			rarg_parse_descriptor_for_class,    argc, args_for_class,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchClass( rb_class_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_class->args_parsed );

		//	module

		VALUE	rb_module_match	=	Qnil;
		VALUE	args_for_module[]	=	{ rb_mEnumerable };
		RI_DefineAndParse( rarg_parameter_sets_for_module,		rarg_parse_descriptor_for_module,   argc, args_for_module, 			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchModule( rb_module_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_module->args_parsed );

		//	string

		VALUE	rb_string_match	=	Qnil;
		VALUE	args_for_string[]	=	{ rb_str_new2( "string" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_string,		rarg_parse_descriptor_for_string,   argc, args_for_string,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchString( rb_string_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_string->args_parsed );

		//	symbol

		VALUE	rb_symbol_match	=	Qnil;
		VALUE	args_for_symbol[]	=	{ ID2SYM( rb_intern( "symbol" ) ) };
		RI_DefineAndParse( rarg_parameter_sets_for_symbol,		rarg_parse_descriptor_for_symbol,   argc, args_for_symbol,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchSymbol( rb_symbol_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_symbol->args_parsed );

		//	array

		VALUE	rb_array_match	=	Qnil;
		VALUE	args_for_array[]	=	{ rb_ary_new() };
		RI_DefineAndParse( rarg_parameter_sets_for_array,			rarg_parse_descriptor_for_array,    argc, args_for_array,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchArray( rb_array_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_array->args_parsed );

		//	hash

		VALUE	rb_hash_match	=	Qnil;
		VALUE	args_for_hash[]	=	{ rb_ary_new() };
		RI_DefineAndParse( rarg_parameter_sets_for_hash,			rarg_parse_descriptor_for_hash,    argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchArray( rb_hash_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );

		//	fixnum

		VALUE	rb_fixnum_match	=	Qnil;
		VALUE	args_for_fixnum[]	=	{ INT2FIX( 1 ) };
		RI_DefineAndParse( rarg_parameter_sets_for_fixnum,		rarg_parse_descriptor_for_fixnum,   argc, args_for_fixnum,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchFixNum( rb_fixnum_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_fixnum->args_parsed );

		//	data

		VALUE	rb_data_match	=	Qnil;
		struct rb_data_object_s	{
			BOOL	true_or_false;
		}	data_object;
		VALUE	rb_cDataObject	=	rb_define_class( "DataObject", rb_cObject );
		VALUE	rb_data_object	=	Data_Wrap_Struct(	rb_cDataObject,
																							NULL,
																							NULL,
																							& data_object );
		VALUE	args_for_data[]	=	{ rb_data_object };
		RI_DefineAndParse( rarg_parameter_sets_for_data,			rarg_parse_descriptor_for_data,     argc, args_for_data,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchData( rb_data_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_data->args_parsed );

		//	file

		VALUE	rb_file_match	=	Qnil;
		VALUE	rb_file	=	rb_file_open( "../test/main_spec.c", "r" );
		VALUE	args_for_file[]	=	{ rb_file };
		RI_DefineAndParse( rarg_parameter_sets_for_file,			rarg_parse_descriptor_for_file,     argc, args_for_file,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchFile( rb_file_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_file->args_parsed );
		rb_io_close( rb_file );

		//	regexp

		VALUE	rb_regexp_match	=	Qnil;
		VALUE	rb_regexp	=	rb_reg_new_str( rb_str_new2( "regexp" ), 0 );
		VALUE	args_for_regexp[]	=	{ rb_regexp };
		RI_DefineAndParse( rarg_parameter_sets_for_regexp,		rarg_parse_descriptor_for_regexp,   argc, args_for_regexp,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchRegexp( rb_regexp_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_regexp->args_parsed );

		//	match

		VALUE	rb_match_match	=	Qnil;
		VALUE	args_for_match[]		=	{ rb_eval_string( "/regexp/.match( 'regexp' )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_match,			rarg_parse_descriptor_for_match,    argc, args_for_match,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchRegexpMatch( rb_match_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_match->args_parsed );

		//	object

		VALUE	rb_object_match	=	Qnil;
		VALUE	args_for_object[]	=	{ rb_eval_string( "Object.new" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_object,		rarg_parse_descriptor_for_object,   argc, args_for_object,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchObject( rb_object_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_object->args_parsed );

		//	float

		VALUE	rb_float_match	=	Qnil;
		VALUE	args_for_float[]	=	{ rb_eval_string( "42.420" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_float,			rarg_parse_descriptor_for_float,    argc, args_for_float, 			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchFloat( rb_float_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_float->args_parsed );

		//	bignum

		VALUE	rb_bignum_match	=	Qnil;
		VALUE	args_for_bignum[]	=	{ rb_eval_string( "10000000000000000000000000" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_bignum,		rarg_parse_descriptor_for_bignum,   argc, args_for_bignum,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchBigNum( rb_bignum_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_bignum->args_parsed );

		//	rational

		VALUE	rb_rational_match	=	Qnil;
		VALUE	args_for_rational[]	=	{ rb_eval_string( "Rational( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_rational,	rarg_parse_descriptor_for_rational, argc, args_for_rational,		rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchRational( rb_rational_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_rational->args_parsed );

		//	complex

		VALUE	rb_complex_match	=	Qnil;
		VALUE	args_for_complex[]	=	{ rb_eval_string( "Complex( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_complex,		rarg_parse_descriptor_for_complex,  argc, args_for_complex,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchComplex( rb_complex_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_complex->args_parsed );

		//	struct

		VALUE	rb_struct_match	=	Qnil;
		VALUE	args_for_struct[]	=	{ rb_eval_string( "Struct.new( 'RargMatchStruct', :answer, :other_answer ).new( 42, 420 )" ) };
		RI_DefineAndParse( rarg_parameter_sets_for_struct,		rarg_parse_descriptor_for_struct,   argc, args_for_struct,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchStruct( rb_struct_match ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_struct->args_parsed );

	END_IT
END_DESCRIBE

/****************************************************
*  R_MatchPossibleType( receiver, possible_match )  *
****************************************************/

DESCRIBE( R_MatchPossibleType, "R_MatchPossibleType( receiver, possible_match )" )
	IT( "checks possible match against argument and assigns match to receiver" )
		//	R_MatchPossibleType just wraps a possible_match, so we only have to test one
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		VALUE	args_for_complex[]	=	{ rb_complex };
		VALUE	rb_possible_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_possible_type,		rarg_parse_descriptor_for_possible_type,  argc, args_for_complex,			rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchPossibleType( rb_possible_match, R_Complex() ) ) ) );
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_possible_type->args_parsed );		
		SHOULD_EQUAL( rb_possible_match, rb_complex );
	END_IT
END_DESCRIBE

/***********************************************************
*  R_MatchPossibleTypeForHash( receiver, possible_match )  *
***********************************************************/

DESCRIBE( R_MatchPossibleTypeForHash, "R_MatchPossibleTypeForHash( receiver, possible_match )" )
	IT( "checks possible match against hash key/data argument and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_hash	=	rb_hash_new();
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_complex );
		VALUE	args_for_hash[]	=	{ rb_hash };
		VALUE	rb_hash_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_hash,  argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Hash(	R_HashKey( R_Symbol() ),
																																																																																					R_MatchHashDataForHash( rb_hash_match, R_Complex() ) ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );		
		SHOULD_EQUAL( rb_hash_match, rb_hash );
	END_IT
END_DESCRIBE

/***********************************************
*  R_MatchRespondsTo( receiver, method, ... )  *
***********************************************/

DESCRIBE( R_MatchRespondsTo, "R_MatchRespondsTo( receiver, method, ... )" )
	IT( "matches if arg responds to named method and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	args_for_responds_to[]	=	{ rb_cObject };
		VALUE	rb_method_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_responds_to,		rarg_parse_descriptor_for_responds_to,  argc, args_for_responds_to,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchRespondsTo( rb_method_match, "methods" ) ) ) );		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_responds_to->args_parsed );		
		SHOULD_EQUAL( rb_method_match, rb_cObject );
	END_IT
END_DESCRIBE

/*************************************************************
*  R_MatchReturns( receiver, method, rb_return_value, ... )  *
*************************************************************/

DESCRIBE( R_MatchReturns, "R_MatchReturns( receiver, method, rb_return_value, ... )" )
	IT( "matches if named method return matches rb_return_value and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	args_for_returns_match[]	=	{ rb_cObject };
		VALUE	rb_method_returns_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_returns,  argc, args_for_returns_match,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchReturns( rb_method_returns_match, "superclass", rb_cBasicObject ) ) ) );		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_returns->args_parsed );		
		SHOULD_EQUAL( rb_method_returns_match, rb_cObject );
	END_IT
END_DESCRIBE

/*********************************************************************************
*  R_MatchReturnsWithArgs( receiver, method, argc, args, rb_return_value, ... )  *
*********************************************************************************/

DESCRIBE( R_MatchReturnsWithArgs, "R_MatchReturnsWithArgs( receiver, method, argc, args, rb_return_value, ... )" )
	IT( "matches if named method returns matches rb_return_value when passed given args and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_call_object	=	rb_ary_new();
		VALUE	rb_array_contents	=	rb_str_new2( "string" );
		rb_ary_push(	rb_call_object,
									rb_array_contents );
		VALUE	args_for_returns_match[]	=	{ rb_call_object };
		VALUE	rb_method_returns_match	=	Qnil;
		VALUE	rb_index	=	INT2FIX( 0 );
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_returns,  argc, args_for_returns_match,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchReturnsWithArgs( rb_method_returns_match, "[]", 1, & rb_index, rb_array_contents ) ) ) );		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_returns->args_parsed );		
		SHOULD_EQUAL( rb_method_returns_match, rb_call_object );
	END_IT
END_DESCRIBE

/**************************************************
*  R_MatchReturnsNonNil( receiver, method, ... )  *
**************************************************/

DESCRIBE( R_MatchReturnsNonNil, "R_MatchReturnsNonNil( receiver, method, ... )" )
	IT( "matches if named method returns non-nil and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	args_for_returns[]	=	{ rb_cObject };
		VALUE	rb_method_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_returns,		rarg_parse_descriptor_for_returns,  argc, args_for_returns,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchReturnsNonNil( rb_method_match, "methods" ) ) ) );		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_returns->args_parsed );		
		SHOULD_EQUAL( rb_method_match, rb_cObject );
	END_IT
END_DESCRIBE

/*****************************************************************
*  R_MatchReturnsNonNilWithArgs( receiver, method, argc, args )  *
*****************************************************************/

DESCRIBE( R_MatchReturnsNonNilWithArgs, "R_MatchReturnsNonNilWithArgs( receiver, method, argc, args )" )
	IT( "matches if named method returns returns non-nil when passed given args and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_call_object	=	rb_ary_new();
		VALUE	rb_array_contents	=	rb_str_new2( "string" );
		rb_ary_push(	rb_call_object,
									rb_array_contents );
		VALUE	args_for_returns_match[]	=	{ rb_call_object };
		VALUE	rb_method_returns_match	=	Qnil;
		VALUE	rb_index	=	INT2FIX( 0 );
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_returns,  argc, args_for_returns_match,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchReturnsNonNilWithArgs( rb_method_returns_match, "[]", 1, & rb_index ) ) ) );		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_returns->args_parsed );		
		SHOULD_EQUAL( rb_method_returns_match, rb_call_object );
	END_IT
END_DESCRIBE

/************************************************
*  R_MatchHash( receiver, key, data )           *
*  R_MatchHashKey( receiver, possible_match )   *
*  R_MatchHashData( receiver, possible_match )  *
************************************************/

DESCRIBE( R_MatchHash, "R_MatchHash( receiver, key, data )" )
	IT( "matches hash for key and data and assigns match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_hash	=	rb_hash_new();
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_complex );
		VALUE	args_for_hash[]	=	{ rb_hash };
		VALUE	rb_hash_match			=	Qnil;
		VALUE	rb_symbol_match		=	Qnil;
		VALUE	rb_complex_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_hash,  argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchHash(	rb_hash_match,
																																																																																							R_MatchHashKey( rb_symbol_match, R_Symbol() ),
																																																																																							R_MatchHashData( rb_complex_match, R_Complex() ) ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );		
		SHOULD_EQUAL( rb_hash_match, rb_hash );
		SHOULD_EQUAL( rb_symbol_match, ID2SYM( rb_intern( "key" ) ) );
		SHOULD_EQUAL( rb_complex_match, rb_complex );
	END_IT
END_DESCRIBE

/*******************************************************
*  R_MatchHashKeyForHash( receiver, possible_match, ... )  *
*******************************************************/

DESCRIBE( R_MatchHashKeyForHash, "R_MatchHashKeyForHash( receiver, possible_match, ... )" )
	IT( "check key in hash for possible match and if it matches, assign hash to receiver" )

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_hash	=	rb_hash_new();
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_complex );
		VALUE	args_for_hash[]	=	{ rb_hash };
		VALUE	rb_hash_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_hash,  argc, args_for_hash,	rb_self, FALSE, R_ParameterSet( R_Parameter( R_Hash(	R_MatchHashKeyForHash( rb_hash_match, R_Symbol() ),
																																																																																		R_HashData( R_Complex() ) ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );		
		SHOULD_EQUAL( rb_hash_match, rb_hash );

	END_IT
END_DESCRIBE

/********************************************************
*  R_MatchHashDataForHash( receiver, possible_match, ... )  *
********************************************************/

DESCRIBE( R_MatchHashDataForHash, "R_MatchHashDataForHash( receiver, possible_match, ... )" )
	IT( "check data in hash for possible match and if it matches, assign hash to receiver" )

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_hash	=	rb_hash_new();
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_complex );
		VALUE	args_for_hash[]	=	{ rb_hash };
		VALUE	rb_hash_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_hash,  argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_Hash(	R_HashKey( R_Symbol() ),
																																																																																					R_MatchHashDataForHash( rb_hash_match, R_Complex() ) ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );		
		SHOULD_EQUAL( rb_hash_match, rb_hash );

	END_IT
END_DESCRIBE

/*******************************************
*  R_MatchIndex( receiver, index_string )  *
*******************************************/

DESCRIBE( R_MatchIndexMatch, "R_MatchIndexMatch( receiver, index_string, possible_match )" )
	IT( "matches hash with index and tests corresponding data for possible_match, assigning match to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_hash	=	rb_hash_new();
		VALUE	rb_complex	=	rb_eval_string( "Complex( 42, 420 )" );
		rb_hash_aset(	rb_hash,
									ID2SYM( rb_intern( "key" ) ),
									rb_complex );
		VALUE	args_for_hash[]	=	{ rb_hash };
		VALUE	rb_hash_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_hash,		rarg_parse_descriptor_for_hash,  argc, args_for_hash,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchIndexMatch(	rb_hash_match, "key", R_Complex() ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_hash->args_parsed );		
		SHOULD_EQUAL( rb_hash_match, rb_complex );
	END_IT
END_DESCRIBE

/****************************
*  R_MatchProc( receiver )  *
****************************/

DESCRIBE( R_MatchProc, "R_MatchProc( receiver )" )
	IT( "matches Proc and assigns to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_proc	=	rb_eval_string( "Proc.new { |arg| puts 'procproc!' }" );
		VALUE	args_for_proc[]	=	{ rb_proc };
		VALUE	rb_proc_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_proc,		rarg_parse_descriptor_for_proc,  argc, args_for_proc,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchProc(	rb_proc_match ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_proc->args_parsed );		
		SHOULD_EQUAL( rb_proc_match, rb_proc );
	END_IT
END_DESCRIBE

/******************************
*  R_MatchLambda( receiver )  *
******************************/

DESCRIBE( R_MatchLambda, "R_MatchLambda( receiver )" )
	IT( "matches Lambda and assigns to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_lambda	=	rb_eval_string( "lambda { |arg| puts 'lambdalambda!' }" );
		VALUE	args_for_lambda[]	=	{ rb_lambda };
		VALUE	rb_lambda_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_lambda,		rarg_parse_descriptor_for_lambda,  argc, args_for_lambda,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchLambda(	rb_lambda_match ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_lambda->args_parsed );		
		SHOULD_EQUAL( rb_lambda_match, rb_lambda );
	END_IT
END_DESCRIBE

/*************************************************
*  R_MatchProcWithArity( receiver, arity, ... )  *
*************************************************/

DESCRIBE( R_MatchProcWithArity, "R_MatchProcWithArity( receiver, arity, ... )" )
	IT( "matches Proc with one of given arities and assigns to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_proc	=	rb_eval_string( "Proc.new { |arg| puts 'procproc!' }" );
		VALUE	args_for_proc[]	=	{ rb_proc };
		VALUE	rb_proc_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_proc,		rarg_parse_descriptor_for_proc,  argc, args_for_proc,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchProcWithArity(	rb_proc_match, 1 ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_proc->args_parsed );		
		SHOULD_EQUAL( rb_proc_match, rb_proc );
	END_IT
END_DESCRIBE

/***************************************************
*  R_MatchLambdaWithArity( receiver, arity, ... )  *
***************************************************/

DESCRIBE( R_MatchLambdaWithArity, "R_MatchLambdaWithArity( receiver, arity, ... )" )
	IT( "matches Lambda with one of given arities and assigns to receiver" )
		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_lambda	=	rb_eval_string( "lambda { |arg| puts 'lambdalambda!' }" );
		VALUE	args_for_lambda[]	=	{ rb_lambda };
		VALUE	rb_lambda_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_lambda,		rarg_parse_descriptor_for_lambda,  argc, args_for_lambda,				rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchLambdaWithArity(	rb_lambda_match, 1 ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_lambda->args_parsed );		
		SHOULD_EQUAL( rb_lambda_match, rb_lambda );
	END_IT
END_DESCRIBE

/*********************************
*  R_MatchBlockProc( receiver )  *
*********************************/

//	this is a dirty hack to get around the problem of passing a block in C
//	rb_iterate does not seem to pass a block as we might expect (even if the effect is the same,
//	it doesn't use the block slot)
//	we use eval to instantiate the block slot and globals in order to retain data during the call
//	since we are just doing this for testing which will never be running multiple times at once,
//	this shouldn't be a major concern, even if it is ugly.
//	it is at least not as ugly as not having the block properly spec'ed at all.
rarg_parse_descriptor_t*	RARG_macro_PossibleBlockMatch_parse_descriptor;
rarg_parameter_set_t*			RARG_macro_PossibleBlockMatch_parameter_set;
VALUE											rb_block_match_arg;
VALUE RARG_macro_PossibleBlockMatch_proc_relay( VALUE arg __attribute__ ((unused)) );

DESCRIBE( R_MatchBlockProc, "R_MatchBlockProc( receiver )" )
	IT( "matches block and assigns to receiver as Proc" )

		RARG_macro_PossibleBlockMatch_parse_descriptor	= RI_AllocParseDescriptor();
		RARG_macro_PossibleBlockMatch_parameter_set			= NULL;
		VALUE	rb_self	=	rb_cObject;
		rb_block_match_arg	=	Qnil;
		RI_InitAndDefine( RARG_macro_PossibleBlockMatch_parameter_set, RARG_macro_PossibleBlockMatch_parse_descriptor,  0, NULL,	rb_self, R_ParameterSet( R_Parameter( R_MatchBlockProc(	rb_block_match_arg ) ) ) );

		rb_eval_string( "RARG_macro_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );
		
	END_IT
END_DESCRIBE
VALUE RARG_macro_PossibleBlockMatch_proc_relay( VALUE arg __attribute__ ((unused)) )	{
	
	RI_Parse( RARG_macro_PossibleBlockMatch_parameter_set, RARG_macro_PossibleBlockMatch_parse_descriptor, FALSE );
	SHOULD_BE_TRUE( RARG_macro_PossibleBlockMatch_parse_descriptor->args_parsed );
	SHOULD_BE_TRUE( rb_block_match_arg != Qnil );
	
	return Qnil;
}

/***********************************
*  R_MatchBlockLambda( receiver )  *
***********************************/

DESCRIBE( R_MatchBlockLambda, "R_MatchBlockLambda( receiver )" )
	IT( "matches block and assigns to receiver as Lambda" )

		RARG_macro_PossibleBlockMatch_parse_descriptor = RI_AllocParseDescriptor();
		RARG_macro_PossibleBlockMatch_parameter_set			= NULL;
		VALUE	rb_self	=	rb_cObject;
		rb_block_match_arg	=	Qnil;
		RI_InitAndDefine( RARG_macro_PossibleBlockMatch_parameter_set, RARG_macro_PossibleBlockMatch_parse_descriptor,  0, NULL,	rb_self, R_ParameterSet( R_Parameter( R_MatchBlockLambda(	rb_block_match_arg ) ) ) );

		rb_eval_string( "RARG_macro_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );

	END_IT
END_DESCRIBE

/******************************************************
*  R_MatchBlockProcWithArity( receiver, arity, ... )  *
******************************************************/

DESCRIBE( R_MatchBlockProcWithArity, "R_MatchBlockProcWithArity( receiver, arity, ... )" )
	IT( "matches block with one of given arities and assigns to receiver as Proc" )

		RARG_macro_PossibleBlockMatch_parse_descriptor = RI_AllocParseDescriptor();
		RARG_macro_PossibleBlockMatch_parameter_set			= NULL;
		VALUE	rb_self	=	rb_cObject;
		rb_block_match_arg	=	Qnil;
		RI_InitAndDefine( RARG_macro_PossibleBlockMatch_parameter_set, RARG_macro_PossibleBlockMatch_parse_descriptor,  0, NULL,	rb_self, R_ParameterSet( R_Parameter( R_MatchBlockProcWithArity(	rb_block_match_arg, 1 ) ) ) );

		rb_eval_string( "RARG_macro_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );

	END_IT
END_DESCRIBE

/********************************************************
*  R_MatchBlockLambdaWithArity( receiver, arity, ... )  *
********************************************************/

DESCRIBE( R_MatchBlockLambdaWithArity, "R_MatchBlockLambdaWithArity( receiver, arity, ... )" )
	IT( "matches block with one of given arities and assigns to receiver as Proc" )

		RARG_macro_PossibleBlockMatch_parse_descriptor = RI_AllocParseDescriptor();
		RARG_macro_PossibleBlockMatch_parameter_set			= NULL;
		VALUE	rb_self	=	rb_cObject;
		rb_block_match_arg	=	Qnil;
		RI_InitAndDefine( RARG_macro_PossibleBlockMatch_parameter_set, RARG_macro_PossibleBlockMatch_parse_descriptor,  0, NULL,	rb_self, R_ParameterSet( R_Parameter( R_MatchBlockLambdaWithArity(	rb_block_match_arg, 1 ) ) ) );

		rb_eval_string( "RARG_macro_PossibleBlockMatch_proc_relay( Object ) { |arg| return arg }" );

	END_IT
END_DESCRIBE

/******************************************************
*  R_MatchAncestor( receiver, class_or_module_name )  *
******************************************************/

DESCRIBE( R_MatchAncestor, "R_MatchAncestor( receiver, class_or_module_name )" )
	IT( "checks whether arg has class_or_module_name as one of its ancestors and assigns match to receiver" )

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_ancestor	=	rb_cModule;
		VALUE	args_for_ancestor[]	=	{ rb_ancestor };
		VALUE	rb_ancestor_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_ancestor,		rarg_parse_descriptor_for_ancestor,  argc, args_for_ancestor,		rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchAncestor(	rb_ancestor_match, "Object" ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_ancestor->args_parsed );		
		SHOULD_EQUAL( rb_ancestor_match, rb_ancestor );

	END_IT
END_DESCRIBE

/******************************************************************
*  R_MatchAncestorInstance( receiver, class_or_module_instance )  *
******************************************************************/

DESCRIBE( R_MatchAncestorInstance, "R_MatchAncestorInstance( receiver, class_or_module_instance )" )
	IT( "checks whether arg has class_or_module_instance as one of its ancestors and assigns match to receiver" )

		VALUE	rb_self	=	rb_cObject;
		VALUE	argc		=	1;
		VALUE	rb_ancestor	=	rb_cModule;
		VALUE	args_for_ancestor[]	=	{ rb_ancestor };
		VALUE	rb_ancestor_match	=	Qnil;
		RI_DefineAndParse( rarg_parameter_sets_for_ancestor,		rarg_parse_descriptor_for_ancestor,  argc, args_for_ancestor,		rb_self, FALSE, R_ParameterSet( R_Parameter( R_MatchAncestorInstance(	rb_ancestor_match, rb_cObject ) ) ) );
		
		SHOULD_BE_TRUE( rarg_parse_descriptor_for_ancestor->args_parsed );		
		SHOULD_EQUAL( rb_ancestor_match, rb_ancestor );

	END_IT
END_DESCRIBE

/********************************************
*  R_IfElse( possible_if_else_match, ... )  *
********************************************/

DESCRIBE( R_IfElse, "R_IfElse( possible_if_else_match, ... )" )
	IT( "checks for chain of if/else if/else statements" )

	END_IT
END_DESCRIBE

/*********************************************
*  R_IfValue( rb_variable, possible_match )  *
*********************************************/

DESCRIBE( R_IfValue, "R_IfValue( rb_variable, possible_match )" )
	IT( "checks for rb_variable to be non-nil and if it is, checks arg for possible_match" )

	END_IT
END_DESCRIBE

/*************************************************************
*  R_IfValueEquals( rb_variable, rb_value, possible_match )  *
*************************************************************/

DESCRIBE( R_IfValueEquals, "R_IfValueEquals( rb_variable, rb_value, possible_match )" )
	IT( "checks for rb_variable to be equal to rb_value and if it is, checks arg for possible_match" )

	END_IT
END_DESCRIBE

/********************************************************
*  R_IfMatch( if_possible_match, then_possible_match )  *
********************************************************/

DESCRIBE( R_IfMatch, "R_IfMatch( if_possible_match, then_possible_match )" )
	IT( "checks arg for possible match and if it matches, checks next arg for possible_match" )

	END_IT
END_DESCRIBE

/*************************************************
*  R_ElseIfValue( rb_variable, possible_match )  *
*************************************************/

DESCRIBE( R_ElseIfValue, "R_ElseIfValue( rb_variable, possible_match )" )
	IT( "if first 'if' fails, checks for rb_variable to be non-nil and if it is, checks arg for possible_match" )

	END_IT
END_DESCRIBE

/*****************************************************************
*  R_ElseIfValueEquals( rb_variable, rb_value, possible_match )  *
*****************************************************************/

DESCRIBE( R_ElseIfValueEquals, "R_ElseIfValueEquals( rb_variable, rb_value, possible_match )" )
	IT( "if first 'if' fails, checks for rb_variable to be equal to rb_value and if it is, checks arg for possible_match" )

	END_IT
END_DESCRIBE

/************************************************************
*  R_ElseIfMatch( if_possible_match, then_possible_match )  *
************************************************************/

DESCRIBE( R_ElseIfMatch, "R_ElseIfMatch( if_possible_match, then_possible_match )" )
	IT( "if first 'if' fails, checks arg for possible match and if it matches, checks next arg for possible_match" )

	END_IT
END_DESCRIBE

/*****************************
*  R_Else( possible_match )  *
*****************************/

DESCRIBE( R_Else, "R_Else( possible_match )" )
	IT( "if first 'if's and 'else if's fail, check arg for possible match" )

	END_IT
END_DESCRIBE

/****************************************************************
*  R_DefineAndParse( argc, args, rb_self, parameter_set, ... )  *
****************************************************************/

DESCRIBE( R_DefineAndParse, "R_DefineAndParse( argc, args, rb_self, parameter_set, ... )" )
	IT( "defines and parses parameter sets for the current passed args for the current function" )

	END_IT
END_DESCRIBE

/*************************
*  R_Arg( rb_receiver )  *
*************************/

DESCRIBE( R_Arg, "R_Arg( rb_receiver )" )
	IT( "grabs the next argument and assigns it to the specified receiver; useful after parsing when additional arguments remain" )

	END_IT
END_DESCRIBE


/***************************************************
*  R_IterateHashDescriptor( rb_hash, c_function )  *
***************************************************/

DESCRIBE( R_IterateHashDescriptor, "R_IterateHashDescriptor( rb_hash, c_function )" )
	IT( "sends each key/data pair in the hash back to the present function as key, data with optional args prepended" )

	END_IT
END_DESCRIBE

/*****************************************************
*  R_IterateArrayDescriptor( rb_array, c_function )  *
*****************************************************/

DESCRIBE( R_IterateArrayDescriptor, "R_IterateArrayDescriptor( rb_array, c_function )" )
	IT( "sends each element in the array back to the present function with optional args prepended" )

	END_IT
END_DESCRIBE


void rb_Rargs_macro_spec( void )	{

	rb_define_method( rb_cObject, "RARG_macro_PossibleBlockMatch_proc_relay", RARG_macro_PossibleBlockMatch_proc_relay, 1 );
	
	CSpec_Run( DESCRIPTION( R_Type ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchType ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchPossibleType ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchPossibleTypeForHash ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchRespondsTo ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchReturns ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchReturnsWithArgs ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchReturnsNonNil ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchReturnsNonNilWithArgs ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchHash ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchHashKeyForHash ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchHashDataForHash ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchIndexMatch ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchProc ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchLambda ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchProcWithArity ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchLambdaWithArity ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchBlockProc ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchBlockLambda ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchBlockProcWithArity ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchBlockLambdaWithArity ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchAncestor ), CSpec_NewOutputVerbose() );
	CSpec_Run( DESCRIPTION( R_MatchAncestorInstance ), CSpec_NewOutputVerbose() );

}
