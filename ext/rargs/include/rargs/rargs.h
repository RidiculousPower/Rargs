#ifndef RB_RARGS
	#define RB_RARGS

	#include "rargs_types.h"
	#include "rargs_define.h"
	#include "rargs_parse.h"
	#include "rargs_free.h"
	#include "rargs_error.h"

	/*
	
		R_ParameterSet							can take:	R_Parameter
		
		R_Parameter									can take: 
		
			for matching									R_Type and subtypes:
																			R_Any, R_NotNil, R_String, R_Symbol, R_StringSymbol, R_Hash, R_Array
			
			for assigning									R_MatchType and subtypes:
																			R_MatchAny, R_MatchNotNil, R_MatchString, R_MatchSymbol, R_MatchStringSymbol, 
																			R_MatchHash, R_MatchArray
			
			for assigning hash on					R_Match...ForHash:
			key/data match									R_MatchAnyForHash, R_MatchNotNilForHash, R_MatchStringForHash, R_MatchSymbolForHash, 
																			R_MatchStringSymbolForHash, R_MatchHashForHash, R_MatchArrayForHash												
		
		R_Type												can take: type
			
			R_Any												and
			R_NotNil										and
			R_String										and
			R_Symbol										and
			R_StringSymbol							and
			R_Array											and
			R_Hash											and
			R_HashKey												and
			R_HashData											and
			R_Index											can take: ()
			
			
		R_MatchType	and
		R_MatchPossibleTypeForHash		can take: type, receiver
		
			R_MatchAny									and
			R_MatchNotNil								and
			R_MatchString								and
			R_MatchSymbol								and
			R_MatchStringSymbol					and
			R_MatchArray								and
			R_MatchHash									and
			R_MatchHashKey									and
			R_MatchHashData									and			
			R_MatchIndex								and
					
			R_MatchAnyForHash						and
			R_MatchNotNilForHash				and
			R_MatchStringForHash				and
			R_MatchSymbolForHash				and
			R_MatchStringSymbolForHash	and
			R_MatchArrayForHash					and
			R_MatchHashForHash					and
			R_MatchIndexForHash					can take: receiver			<= works in place of Type with implicit Type = R_STRING_OR_SYMBOL
	
	*/

	/*
	
		RARGS Example:
		
			//	Define result parameters
			VALUE	rb_index														=	Qnil;
			VALUE	rb_key															=	Qnil;
			VALUE	rb_hash_parameter_set_index_key				=	Qnil;
			VALUE	rb_hash_parameter_set_index_keys_array	=	Qnil;
			VALUE	rb_args_array												= Qnil;

			R_Define(

				/------------------------------------------------/

				//	{ :index  => [ <key> ] }
				//	{ "index" => [ <key> ] }
				//	{ :index  => <key> }
				//	{ "index" => <key> }
				R_ParameterSet(		R_Parameter(	R_Hash(	R_HashKey(	R_Type(	R_SYMBOL | R_STRING ) ),
																							R_HashData(	R_MatchArrayForHash(	rb_hash_parameter_set_index_keys_array ) ),
																											R_MatchAnyForHash(		rb_hash_parameter_set_index_key ) ) ) ) ),


				/------------------------------------------------/

				//	:index, <key>
				//	"index", <key>
				R_ParameterSet(		R_Parameter(	R_MatchType(		R_SYMBOL | R_STRING,		
																											rb_index ) ),
												R_Parameter(	R_MatchAny(			rb_key ) ) ),

				/------------------------------------------------/

				//	[ <arg> ]
				R_ParameterSet(		R_Parameter(	R_MatchArray(		rb_args_array ) ) ),

				/------------------------------------------------/

				//	<key>
				R_ParameterSet(		R_Parameter(	R_MatchAny(			rb_key ) ) )

				/------------------------------------------------/
				
			)	

			//	Now use result parameters accordingly
			if (		rb_index != Qnil
					&&	rb_key != Qnil )	{
					
			}
			else if (	rb_key != Qnil )	{
			
			}
			else if ( rb_hash_parameter_set_index_key != Qnil )	{
			
			}
			else if ( rb_hash_parameter_set_index_keys_array != Qnil )	{
			
			}
			else if ( rb_args_array != Qnil )	{
			
			}

	*/

	/*

		RARGS Layout:

		parameter_sets have parameters
		parameters have possible matches
		possible matches can have:
			* allowed and prohibited:
					+ type
					+ class
					+ responds to method
					+ hash
							- key-value presence
							- key/data allow/prohibit constraints
									= type
									= class
									= responds to method
					+ array
							- first member constraints
									= type
									= class
									= responds to method
			* receiver for match assignment
					+ hash
							- receiver for key
							- receiver for data match assignment

	*/	
				
	/*

		Thanks for _tar (#ruby on irc.freenode.net) for interface/implementation ideas:
		* multiple type specification
		* bitwise math for types
		* recursive macro design
	
	*/

	#define RI_AllocParseDescriptor()																									calloc( 1, sizeof( rarg_parse_descriptor_t ) );
	#define RI_Declare( descriptor_name, parameter_sets_name )												rarg_parse_descriptor_t*				descriptor_name	=	RI_AllocParseDescriptor();							\
																																										rarg_parameter_set_t*						parameter_sets_name;

	#define RI_Init( descriptor_name, passed_argc, passed_args, passed_rb_self )			descriptor_name->argc						= passed_argc;								\
																																					          descriptor_name->args						=	passed_args;								\
																																					          descriptor_name->args_parsed		=	0;													\
																																					          descriptor_name->rb_self				=	passed_rb_self;
                                                                                    
	#define RI_Define(	parameter_sets_name,	\
											parameter_set, ... )																					parameter_sets_name	=	RARG_define_ParameterSets( parameter_set,##__VA_ARGS__, NULL );

	#define RI_InitAndDefine(	parameter_sets_name,	\
														descriptor_name,			\
														passed_argc,					\
														passed_args,					\
														passed_rb_self,				\
														parameter_set, ... )																		RI_Init( descriptor_name, passed_argc, passed_args, passed_rb_self );								\
																																										RI_Define( parameter_sets_name, parameter_set,##__VA_ARGS__ );

	#define RI_DefineAndParse(	parameter_sets_name,	\
															descriptor_name,			\
															argc,									\
															args,									\
															rb_self,							\
															raise_exception_on_match_fail,											\
															parameter_set, ... )																	RI_Declare( descriptor_name, parameter_sets_name );																							\
																																										RI_InitAndDefine( parameter_sets_name, descriptor_name, argc, args, rb_self, parameter_set,##__VA_ARGS__ );		\
																																					          RI_Parse( parameter_sets_name, descriptor_name, raise_exception_on_match_fail );
																																																																							
	/***********************
	*  RARG Public Macros  *
	***********************/

	#define R_DefineAndParse( argc, args, rb_self, parameter_set, ... )			          R_Define( argc, args, rb_self, parameter_set,##__VA_ARGS__ );		\
																																					          R_Parse();

                                                                                
	//	copy init info to pass internally - we leave the originally argc/args alone
	#define R_Init( passed_argc, passed_args, passed_rb_self )							          RI_Init( rarg_parse_descriptor, passed_argc, passed_args, passed_rb_self );

	//	we define rarg_parameter_sets as static so that the first time the method runs its arg definition structs are defined
	//	after that we only have to parse, not re-define                               
	#define R_Define(	passed_argc,				\
										descriptor_name,		\
										passed_args,				\
										passed_rb_self,			\
										parameter_set, ... )																						RI_Define( rarg_parameter_sets, descriptor_name, argc, args, rb_self, parameter_set,##__VA_ARGS__ );


		/*--------------------*
		*  RARG Descriptions  *
		*--------------------*/
                                                                                    
	#define R_ListOrder( list_order_number )																          list_order_number
	#define R_DescribeParameterSet(		parameter_set,												          \
																		order_ranking_number,									          \
																		description, ... )										          RARG_define_ParameterSet_description(	parameter_set				,																	\
																																					          																			order_ranking_number,																	\
																																					          																			description,##__VA_ARGS__, NULL )
                                                                                    
	#define R_DescribeParameter(			parameter,														          \
																		order_ranking_number,									          \
																		description, ... )										          RARG_define_Parameter_description(	parameter,																							\
																																					          																		order_ranking_number,																		\
																																					          																		description,##__VA_ARGS__, NULL )	
																																					          																	
	#define R_DescribePossibleMatch(	possible_match,												          \
																		order_ranking_number,									          \
																		description, ... )										          RARG_define_PossibleMatch_description(	possible_match,																			\
																																					          																				order_ranking_number,																\
																																					          																				description,##__VA_ARGS__, NULL )

		/*----------------------*
		*  RARG Parameter Sets  *
		*----------------------*/

	#define R_ExactMatch( parameter_set, ... )															          RARG_define_ParameterSet_requireExactMatch( parameter_set,##__VA_ARGS__, NULL )
                                                                                    
	#define R_ParameterSet( parameter, ... )																          RARG_define_ParameterSet( parameter,##__VA_ARGS__, NULL )
	#define R_Parameter( possible_match, ... )															          RARG_define_Parameter( possible_match,##__VA_ARGS__, NULL )
                                                                                    
	#define R_OptionalParameter( possible_match, ... )											          RARG_define_Parameter_setOptional( R_Parameter( possible_match,##__VA_ARGS__, NULL ), NULL )
	#define R_OptionalMatch( possible_match, ... )													          RARG_define_PossibleMatch_setOptional( possible_match,##__VA_ARGS__, NULL )

		/*----------------------*
		*  RARG Possible Types  *
		*----------------------*/

	#define R_Type( type, ... )																							          RARG_define_PossibleTypeMatch( type,##__VA_ARGS__, R_TERMINAL )
	#define R_MatchType( receiver, type )																		          R_MatchPossibleType( receiver, R_Type( type ) )
	#define R_MatchPossibleType( receiver, possible_match )									          RARG_define_PossibleMatch_assignMatchToValue( possible_match, & receiver )
	#define R_MatchPossibleTypeForHash( receiver, possible_match )					          RARG_define_PossibleMatch_assignHashForKeyDataMatchToValue( possible_match, & receiver )
	#define R_MatchPossibleIndexMatch( receiver, possible_index_match )			          definePossibleMatch_assignIndexMatchToValue( possible_index_match, & receiver )
                                                                                    
	#define R_Any()																																		R_Type( R_ANY )
	#define R_NotNil()																											          R_Type( R_NOT_NIL )
	#define R_String()																											          R_Type( R_STRING )
	#define R_Symbol()																											          R_Type( R_SYMBOL )
	#define R_StringSymbol()																								          R_Type( R_STRING_SYMBOL )

	#define R_Nil()																																		R_Type( R_NIL )

	#define R_True()																																	R_Type( R_TRUE )
	#define R_False()																																	R_Type( R_FALSE )
	#define R_TrueOrFalse()																														R_Type( R_TRUE_FALSE )
	#define R_TrueFalse()																															R_TrueOrFalse()

	#define R_Array()																												          R_Type( R_ARRAY )
	#define R_Struct()																												        R_Type( R_STRUCT )
	#define R_File()																												          R_Type( R_FILE )

	#define R_File()																												          R_Type( R_FILE )

	#define R_Class()																																	R_Type( R_CLASS )
	#define R_Module()																																R_Type( R_MODULE )
	#define R_Object()																																R_Type( R_OBJECT )
	#define R_Data()																																	R_Type( R_DATA )
	#define R_Instance()																															R_Type( R_INSTANCE )
	
	#define R_Complex()																											          R_Type( R_COMPLEX )
	#define R_ComplexNumber()																													R_Complex()
	#define R_Float()																												          R_Type( R_FLOAT )
	#define R_FloatNumber()																														R_Float()
	#define R_Rational()																												      R_Type( R_RATIONAL )
	#define R_RationalNumber()																									      R_Rational()
	#define R_FixNum()																																R_Type( R_FIXNUM )
	#define R_Fix()																																		R_FixNum
	#define R_FixNumber()																															R_FixNum()
	#define R_BigNum()																																R_Type( R_BIGNUM )
	#define R_Big()																																		R_BigNum()
	#define R_BigNumber()																															R_BigNum()
	#define R_Number()																																R_Type( R_NUMBER )
	#define R_Num()																																		R_Number()
	#define R_Regexp()																																R_Type( R_REGEXP )
	#define R_RegexpMatch()																														R_Type( R_MATCH )
	                                                                                  
	#define R_Hash( hash_key, hash_data )																		          RARG_define_PossibleHashMatch( hash_key, hash_data )
	#define R_HashKey( possible_match, ... )																		          RARG_define_PossibleHashMatch_KeyOrDataMatch( possible_match,##__VA_ARGS__, NULL )
	#define R_HashData( possible_match, ... )																		          RARG_define_PossibleHashMatch_KeyOrDataMatch( possible_match,##__VA_ARGS__, NULL )
	#define R_Index( index_string, ... )																		          RARG_define_PossibleHashMatch_indexesMatch( index_string,##__VA_ARGS__, NULL )
	#define R_IndexMatch( index_string, possible_match, ... )									        RARG_define_PossibleHashMatch_indexesMatch_dataMatch( R_Index( index_string ), possible_match,##__VA_ARGS__, NULL )
	
	#define R_Ancestor( class_or_module_name, ... )															      RARG_define_PossibleAncestorMatch( class_or_module_name,##__VA_ARGS__, NULL )
	#define R_AncestorInstance( class_or_module_instance, ... )							          RARG_define_PossibleAncestorInstanceMatch( class_or_module_instance,##__VA_ARGS__, R_TERMINAL )

	#define R_Proc()																												          R_AncestorInstance( rb_cProc )
	#define R_Lambda()																											          R_Proc()
	#define R_ProcWithArity( arity, ... )																		          RI_Arity( R_Proc(), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_LambdaWithArity( arity, ... )																	          RI_Arity( R_Lambda(), arity,##__VA_ARGS__, R_TERMINATE_ARITY )

	#define R_Block()																																	R_BlockProc()
	#define R_BlockProc()																										          RARG_define_Block_procMatch()
	#define R_BlockLambda()																									          RARG_define_Block_lambdaMatch()
	#define R_BlockProcWithArity( arity, ... )															          RI_Arity( R_BlockProc(), arity, ##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_BlockLambdaWithArity( arity, ... )														          RI_Arity( R_BlockLambda(), arity, ##__VA_ARGS__, R_TERMINATE_ARITY )

	#define R_Method()																											          R_AncestorInstance( rb_cMethod )

	#define R_Group( possible_match, ... )																						RARG_define_PossibleGroupMatch( possible_match,##__VA_ARGS__, NULL )

	#define R_RespondsTo( method, ... )																								RARG_define_PossibleMethodResponds( method,##__VA_ARGS__, NULL )
	#define R_Returns( method, rb_return_value, ... )																	RARG_define_PossibleMethodReturns( method, rb_return_value,##__VA_ARGS__, Qnil )
	#define R_ReturnsWithArgs( method, argc, args, rb_return_value, ... )							RARG_define_PossibleMethodReturnsWithArgs( method, argc, args, rb_return_value,##__VA_ARGS__, Qnil )
	#define R_ReturnsNonNil( method, ... )																						RARG_define_PossibleMethodsReturnNonNil( method,##__VA_ARGS__, NULL )
	#define R_ReturnsNonNilWithArgs( method, argc, args )															RARG_define_PossibleMethodReturnsNonNilWithArgs( method, argc, args )

	#define R_IfElse( possible_if_else_match, ... )													          RARG_define_PossibleIfElseMatch( possible_if_else_match,##__VA_ARGS__, NULL )
	#define R_IfValue( rb_variable, possible_match )												          RARG_define_PossibleIfValueMatch( & rb_variable, Qnil, possible_match )
	#define R_IfValueEquals( rb_variable, rb_value, possible_match )				          RARG_define_PossibleIfValueMatch( & rb_variable, rb_value, possible_match )
	#define R_IfMatch( if_possible_match, then_possible_match )							          RARG_define_PossibleIfMatchMatch( if_possible_match, then_possible_match )
	#define R_ElseIfValue( rb_variable, possible_match )										          RARG_define_PossibleElseIfValueMatch( & rb_variable, Qnil, possible_match )
	#define R_ElseIfValueEquals( rb_variable, rb_value, possible_match )		          RARG_define_PossibleElseIfValueMatch( & rb_variable, rb_value, possible_match )
	#define R_ElseIfMatch( if_possible_match, then_possible_match )					          RARG_define_PossibleElseIfMatchMatch( if_possible_match, then_possible_match )
	#define R_Else( possible_match )																				          RARG_define_PossibleElseMatch( possible_match )

		/*------------------------*
		*  RARG Possible Matches  *
		*------------------------*/

	#define R_MatchAny( receiver )																					          R_MatchPossibleType( receiver, R_Any() )
	#define R_MatchNotNil( receiver )																				          R_MatchPossibleType( receiver, R_NotNil() )
	#define R_MatchString( receiver )																				          R_MatchPossibleType( receiver, R_String() )
	#define R_MatchSymbol( receiver )																				          R_MatchPossibleType( receiver, R_Symbol() )
	#define R_MatchStringSymbol( receiver )																	          R_MatchPossibleType( receiver, R_StringSymbol() )

	#define R_MatchNil( receiver )																															R_MatchPossibleType( receiver, R_Nil() )

	#define R_MatchTrue( receiver )																															R_MatchPossibleType( receiver, R_True() )
	#define R_MatchFalse( receiver )																														R_MatchPossibleType( receiver, R_False() )
	#define R_MatchTrueOrFalse( receiver )																											R_MatchPossibleType( receiver, R_TrueOrFalse() )
	#define R_MatchTrueFalse( receiver )																												R_MatchTrueOrFalse( receiver )

	#define R_MatchArray( receiver )																														R_MatchPossibleType( receiver, R_Array() )
	#define R_MatchStruct( receiver )																														R_MatchPossibleType( receiver, R_Struct() )
	#define R_MatchFile( receiver )																										          R_MatchPossibleType( receiver, R_File() )

	#define R_MatchClass( receiver )																														R_MatchPossibleType( receiver, R_Class() )
	#define R_MatchModule( receiver )																														R_MatchPossibleType( receiver, R_Module() )
	#define R_MatchObject( receiver )																														R_MatchPossibleType( receiver, R_Object() )
	#define R_MatchData( receiver )																															R_MatchPossibleType( receiver, R_Data() )
	#define R_MatchInstance( receiver )																													R_MatchPossibleType( receiver, R_Instance() )

	#define R_MatchComplex( receiver )																								          R_MatchPossibleType( receiver, R_Complex() )
	#define R_MatchComplexNumber( receiver )																										R_Complex( receiver )
	#define R_MatchFloat( receiver )																									          R_MatchPossibleType( receiver, R_Float() )
	#define R_MatchFloatNumber( receiver )																											R_Float( receiver )
	#define R_MatchRational( receiver )																													R_MatchPossibleType( receiver, R_Rational() )
	#define R_MatchRationalNumber( receiver )																								    R_Rational( receiver )
	#define R_MatchFixNum( receiver )																														R_MatchPossibleType( receiver, R_FixNum() )
	#define R_MatchFix( receiver )																															R_MatchFixNum
	#define R_MatchFixNumber( receiver )																												R_MatchFixNum( receiver )
	#define R_MatchBigNum( receiver )																														R_MatchPossibleType( receiver, R_BigNum() )
	#define R_MatchBig( receiver )																															R_MatchBigNum( receiver )
	#define R_MatchBigNumber( receiver )																												R_MatchBigNum( receiver )
	#define R_MatchNumber( receiver )																														R_MatchPossibleType( receiver, R_Number() )
	#define R_MatchNum( receiver )																															R_MatchNumber( receiver )
	#define R_MatchRegexp( receiver )																														R_MatchPossibleType( receiver, R_Regexp() )
	#define R_MatchRegexpMatch( receiver )																											R_MatchPossibleType( receiver, R_RegexpMatch() )

	#define R_MatchHash( receiver, key, data )															          R_MatchPossibleType( receiver, R_Hash( key, data ) )
	#define R_MatchHashKey( receiver, possible_match )													      R_HashKey( R_MatchPossibleType( receiver, possible_match ) )
	#define R_MatchHashData( receiver, possible_match )													      R_HashData( R_MatchPossibleType( receiver, possible_match ) )
	#define R_MatchIndex( receiver, index_string )													          R_MatchPossibleIndexMatch( receiver, R_Index( index_string ) )
	#define R_MatchIndexMatch( receiver, index_string, possible_match )								R_MatchPossibleIndexMatch( receiver, R_IndexMatch( index_string, possible_match ) )

	#define R_MatchAncestor( receiver, class_or_module_name )								          R_MatchPossibleType( receiver, R_Ancestor( class_or_module_name ) )
	#define R_MatchAncestorInstance( receiver, class_or_module_instance )		          R_MatchPossibleType( receiver, R_AncestorInstance( class_or_module_instance ) )


	#define R_MatchProc( receiver )																					          R_MatchPossibleType( receiver, R_Proc() )
	#define R_MatchLambda( receiver )																				          R_MatchProc( receiver )
	#define R_MatchProcWithArity( receiver, arity, ... )										          RI_Arity( R_MatchProc( receiver ),##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchLambdaWithArity( receiver, arity, ... )									          RI_Arity( R_MatchLambda( receiver ),##__VA_ARGS__, R_TERMINATE_ARITY )

	#define R_MatchBlock( receiver )																									R_MatchBlockProc( receiver )
	#define R_MatchBlockProc( receiver )																		          R_MatchPossibleType( receiver, R_BlockProc() )
	#define R_MatchBlockLambda( receiver )																	          R_MatchPossibleType( receiver, R_BlockLambda() )
	#define R_MatchBlockProcWithArity( receiver, arity, ... )								          RI_Arity( R_MatchBlockProc( receiver ), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchBlockLambdaWithArity( receiver, arity, ... )							          RI_Arity( R_MatchBlockLambda( receiver ), arity,##__VA_ARGS__, R_TERMINATE_ARITY )

	#define R_MatchMethod( receiver )																									R_MatchPossibleType( receiver, R_Method() )

	#define R_MatchHashKeyForHash( receiver, possible_match, ... )												R_MatchPossibleTypeForHash( receiver, R_HashKey( possible_match,##__VA_ARGS__ ) )     
	#define R_MatchHashDataForHash( receiver, possible_match, ... )												R_MatchPossibleTypeForHash( receiver, R_HashData( possible_match,##__VA_ARGS__ ) )

	#define R_MatchRespondsTo( receiver, method, ... )																			R_MatchPossibleType( receiver, R_RespondsTo( method,##__VA_ARGS__ ) )
	#define R_MatchReturns( receiver, method, rb_return_value, ... )												R_MatchPossibleType( receiver, R_Returns( method, rb_return_value,##__VA_ARGS__ ) )
	#define R_MatchReturnsWithArgs( receiver, method, argc, args, rb_return_value, ... )		R_MatchPossibleType( receiver, R_ReturnsWithArgs( method, argc, args, rb_return_value,##__VA_ARGS__ ) )
	#define R_MatchReturnsNonNil( receiver, method, ... )																		R_MatchPossibleType( receiver, R_ReturnsNonNil( method,##__VA_ARGS__ ) )
	#define R_MatchReturnsNonNilWithArgs( receiver, method, argc, args )										R_MatchPossibleType( receiver, R_ReturnsNonNilWithArgs( method, argc, args ) )
	
		/*---------------*
		*  RARG Parsing  *
		*---------------*/

	#define RI_Parse( parameter_sets_name,		\
										parse_descriptor_name, \
										raise_exception_on_match_fail )																	RARG_parse_ParameterSetsForMatch( parse_descriptor_name, parameter_sets_name, raise_exception_on_match_fail );

	#define R_Parse()																												          RI_Parse( rarg_parameter_sets, rarg_parse_descriptor, TRUE );

	#define R_ArgsRemaining()																													( rarg_parse_descriptor.argc - rarg_parse_descriptor.args_parsed )
	#define R_RemainingArgs()																													( rarg_parse_descriptor.args + rarg_parse_descriptor.args_parsed )

	#define R_Arg( receiver )																													\
		( ( rarg_parse_descriptor.args_parsed < rarg_parse_descriptor.argc ) ?																																											\
							( ( receiver = rarg_parse_descriptor.args[ ++rarg_parse_descriptor.args_parsed ] ) != Qnil )																				\
							: FALSE )
	#define R_IterateHashDescriptor( rb_hash, c_function, ... )												RARG_parse_IterateHashDescriptor( & rarg_parse_descriptor, rb_hash, c_function,##__VA_ARGS__, Qnil )
	#define R_IterateHash( rb_hash, c_function, ... )																	R_IterateHashDescriptor( rb_hash, c_function,##__VA_ARGS__ )
	#define R_IterateArrayDescriptor( rb_array, c_function, ... )											RARG_parse_IterateArrayDescriptor( & rarg_parse_descriptor, rb_array, c_function,##__VA_ARGS__, Qnil )
	#define R_IterateArray( rb_array, c_function, ... )																R_IterateArrayDescriptor( rb_array, c_function,##__VA_ARGS__ )
	
	extern	rarg_possible_type_match_t*	rarg_tmp;
	void Init_rargs();

#endif
