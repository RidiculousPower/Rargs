#ifndef RB_RARGS
	#define RB_RARGS

	#include "rb_Rargs_types.h"
	#include "rb_Rargs_define.h"
	#include "rb_Rargs_parse.h"
	#include "rb_Rargs_free.h"
	#include "rb_Rargs_error.h"

	extern	rarg_possible_type_match_t*	rarg_tmp;

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
			R_Key												and
			R_Data											and
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
			R_MatchKey									and
			R_MatchData									and			
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
				R_ParameterSet(		R_Parameter(	R_Hash(	R_Key(	R_Type(	R_SYMBOL | R_STRING ) ),
																							R_Data(	R_MatchArrayForHash(	rb_hash_parameter_set_index_keys_array ) ),
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
																																																																							
	/***********************
	*  RARG Public Macros  *
	***********************/

	#define R_DefineAndParse( argc, args, rb_self, parameter_set, ... )			          R_Define( argc, args, rb_self, parameter_set,##__VA_ARGS__ );		\
																																					          R_Parse();
                                                                                
	//	copy init info to pass internally - we leave the originally argc/args alone
	#define R_Init( passed_argc, passed_args, passed_rb_self )							          rarg_parse_descriptor_t								rarg_parse_descriptor;					\
																																					          rarg_parse_descriptor.argc						= passed_argc;								\
																																					          rarg_parse_descriptor.args						=	passed_args;								\
																																					          rarg_parse_descriptor.args_parsed			=	0;													\
																																					          rarg_parse_descriptor.rb_self					=	passed_rb_self;
                                                                                    
	//	we define rarg_parameter_sets as static so that the first time the method runs its arg definition structs are defined
	//	after that we only have to parse, not re-define                               
	#define R_Define( argc, args, rb_self, parameter_set, ... )												R_Init( passed_argc, passed_args, passed_rb_self );								\
																																										rarg_parameter_set_t*	rarg_parameter_sets	=	RARG_define_ParameterSets( parameter_set,##__VA_ARGS__, NULL );
                                                                                    
                                                                                    
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
	#define R_MatchType( type, receiver )																		          R_MatchPossibleType( R_Type( type ), receiver )
	#define R_MatchPossibleType( possible_match, receiver )									          RARG_define_PossibleMatch_assignMatchToValue( possible_match, & receiver )
	#define R_MatchPossibleTypeForHash( possible_match, receiver )					          RARG_define_PossibleMatch_assignHashForKeyDataMatchToValue( possible_match, & receiver )
                                                                                    
	#define R_Any()																																		R_Type( R_ANY )
	#define R_NotNil()																											          R_Type( R_NOT_NIL )
	#define R_String()																											          R_Type( R_STRING )
	#define R_Symbol()																											          R_Type( R_SYMBOL )
	#define R_StringSymbol()																								          R_Type( R_STRING_SYMBOL )
	#define R_Array()																												          R_Type( R_ARRAY )
	                                                                                  
	#define R_Hash( hash_key, hash_data )																		          RARG_define_PossibleHashMatch( hash_key, hash_data )
	#define R_Key( possible_match, ... )																		          RARG_define_PossibleHashMatch_KeyOrDataMatch( possible_match,##__VA_ARGS__, NULL )
	#define R_Data( possible_match, ... )																		          RARG_define_PossibleHashMatch_KeyOrDataMatch( possible_match,##__VA_ARGS__, NULL )
	#define R_Index( index_string, ... )																		          RARG_define_PossibleHashMatch_indexesMatch( index_string,##__VA_ARGS__, NULL )
	#define R_IndexMatch( index_string, possible_match, ... )									        RARG_define_PossibleHashMatch_indexesMatch_dataMatch( R_Index( index_string ), possible_match,##__VA_ARGS__, NULL )
	#define R_Ancestor( class_name, ... )																		          RARG_define_PossibleAncestorMatch( class_name,##__VA_ARGS__, NULL )
	#define R_AncestorInstance( class_or_module_instance, ... )							          RARG_define_PossibleAncestorInstanceMatch( class_or_module_instance,##__VA_ARGS__, R_TERMINAL )
	#define R_Class( class_or_module_name, ... )														          R_Ancestor( class_or_module_name,##__VA_ARGS__ )
	#define R_ClassInstance( class_or_module_instance, ... )								          R_AncestorInstance( class_or_module_instance,##__VA_ARGS__ )
	#define R_Proc()																												          R_AncestorInstance( rb_cProc )
	#define R_Lambda()																											          R_Proc()
	#define R_ProcWithArity( arity, ... )																		          RI_Arity( R_Proc(), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_LambdaWithArity( arity, ... )																	          RI_Arity( R_Lambda(), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
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

		/*------------------------*
		*  RARG Possible Matches  *
		*------------------------*/

	#define R_MatchAny( receiver )																					          R_MatchPossibleType( R_Any(), receiver )
	#define R_MatchNotNil( receiver )																				          R_MatchPossibleType( R_NotNil(), receiver )
	#define R_MatchString( receiver )																				          R_MatchPossibleType( R_String(), receiver )
	#define R_MatchSymbol( receiver )																				          R_MatchPossibleType( R_Symbol(), receiver )
	#define R_MatchStringSymbol( receiver )																	          R_MatchPossibleType( R_StringSymbol(), receiver )
	#define R_MatchArray( receiver )																				          R_MatchPossibleType( R_Array(), receiver )
	#define R_MatchHash( key, data, receiver )															          R_MatchPossibleType( R_Hash( key, data ), receiver )
	#define R_MatchKey( possible_match, receiver )													          R_MatchPossibleType( possible_match, receiver )
	#define R_MatchData( possible_match, receiver )													          R_MatchPossibleType( possible_match, receiver )
	#define R_MatchIndex( index_string, receiver )													          R_MatchPossibleType( R_Index( index_string ), receiver )
	#define R_MatchIndexMatch( index_string, possible_match, receiver )								R_MatchPossibleType( R_IndexMatch( index_string, possible_match ), receiver )
	#define R_MatchProc( receiver )																					          R_MatchPossibleType( R_Proc(), receiver )
	#define R_MatchLambda( receiver )																				          R_MatchProc( receiver )
	#define R_MatchProcWithArity( receiver, arity, ... )										          RI_Arity( R_MatchProc( receiver ),##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchLambdaWithArity( receiver, arity, ... )									          RI_Arity( R_MatchLambda( receiver ),##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchBlockProc( receiver )																		          R_MatchPossibleType( R_BlockProc(), receiver )
	#define R_MatchBlockLambda( receiver )																	          R_MatchPossibleType( R_BlockLambda(), receiver )
	#define R_MatchBlockProcWithArity( receiver, arity, ... )								          RI_Arity( R_MatchBlockProc( receiver ), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchBlockLambdaWithArity( receiver, arity, ... )							          RI_Arity( R_MatchBlockLambda( receiver ), arity,##__VA_ARGS__, R_TERMINATE_ARITY )
	#define R_MatchMethodInstance( receiver )																          R_MatchPossibleType( R_Method(), receiver )
	#define R_MatchAncestor( class_or_module_name, receiver )								          R_MatchPossibleType( R_Ancestor( class_or_module_name ), receiver )
	#define R_MatchAncestorInstance( class_or_module_instance, receiver )		          R_MatchPossibleType( R_AncestorInstance( class_or_module_instance ), receiver )
	#define R_MatchGroup( receiver, possible_match, ... )															R_MatchPossibleType( R_Group( possible_match,##_VA_ARGS__ ), receiver )

	#define R_MatchAnyForHash( receiver )																		          R_MatchPossibleTypeForHash( R_Any(), receiver )     
	#define R_MatchNotNilForHash( receiver )																          R_MatchPossibleTypeForHash( R_NotNil(), receiver )
	#define R_MatchStringForHash( receiver )																          R_MatchPossibleTypeForHash( R_String(), receiver )
	#define R_MatchSymbolForHash( receiver )																          R_MatchPossibleTypeForHash( R_Symbol(), receiver )
	#define R_MatchStringSymbolForHash( receiver )													          R_MatchPossibleTypeForHash( R_StringSymbol(), receiver )
	#define R_MatchArrayForHash( receiver )																	          R_MatchPossibleTypeForHash( R_Array(), receiver )
	#define R_MatchHashForHash( key, data, receiver )												          R_MatchPossibleTypeForHash( R_Hash( key, data ), receiver )
	#define R_MatchIndexForHash( receiver )																	          R_MatchPossibleTypeForHash( R_StringSymbol(), receiver )
	#define R_MatchProcForHash( receiver )																	          R_MatchPossibleTypeForHash( R_Proc(), receiver )                                                                                    
	#define R_MatchGroupForHash( receiver, possible_match, ... )											R_MatchPossibleTypeForHash( R_Group( possible_match,##_VA_ARGS__ ), receiver )

	#define R_IfElse( possible_if_else_match, ... )													          RARG_define_PossibleIfElseMatch( possible_if_else_match,##__VA_ARGS__, NULL )
	#define R_IfValue( rb_variable, possible_match )												          RARG_define_PossibleIfValueMatch( & rb_variable, Qnil, possible_match )
	#define R_IfValueEquals( rb_variable, rb_value, possible_match )				          RARG_define_PossibleIfValueMatch( & rb_variable, rb_value, possible_match )
	#define R_IfMatch( if_possible_match, then_possible_match )							          RARG_define_PossibleIfMatchMatch( if_possible_match, then_possible_match )
	#define R_ElseIfValue( rb_variable, possible_match )										          RARG_define_PossibleElseIfValueMatch( & rb_variable, Qnil, possible_match )
	#define R_ElseIfValueEquals( rb_variable, rb_value, possible_match )		          RARG_define_PossibleElseIfValueMatch( & rb_variable, rb_value, possible_match )
	#define R_ElseIfMatch( if_possible_match, then_possible_match )					          RARG_define_PossibleElseIfMatchMatch( if_possible_match, then_possible_match )
	#define R_Else( possible_match )																				          RARG_define_PossibleElseMatch( possible_match )
	
		/*---------------*
		*  RARG Parsing  *
		*---------------*/

	#define R_Parse()																												          RARG_parse_ParameterSetsForMatch( & rarg_parse_descriptor, rarg_parameter_sets );

	#define R_ArgsRemaining()																													( rarg_parse_descriptor.argc - rarg_parse_descriptor.args_parsed )
	#define R_RemainingArgs()																													( rarg_parse_descriptor.args + rarg_parse_descriptor.args_parsed )

	#define R_Arg( receiver )																													RI_NextArg( ( & rarg_parse_descriptor ), receiver )

	#define R_IterateHashDescriptor( rb_hash, c_function, ... )												RARG_parse_IterateHashDescriptor( & rarg_parse_descriptor, rb_hash, c_function,##__VA_ARGS__, Qnil )
	#define R_IterateArrayDescriptor( rb_array, c_function, ... )											RARG_parse_IterateArrayDescriptor( & rarg_parse_descriptor, rb_array, c_function,##__VA_ARGS__, Qnil )
		
#endif
