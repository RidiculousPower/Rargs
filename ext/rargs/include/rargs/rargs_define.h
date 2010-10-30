#ifndef RB_RARGS_DEFINE
	#define RB_RARGS_DEFINE

	#include <ruby.h>
	
	#include "rargs_types.h"

	rarg_parameter_set_t* RARG_define_ParameterSets( rarg_parameter_set_t* parameter_set, ... );	
	rarg_parameter_set_t* RARG_define_ParameterSet( rarg_parameter_t* parameter, ... );	
	rarg_parameter_t* RARG_define_Parameter( rarg_possible_match_t* possible_match, ... );
	rarg_possible_match_t* RARG_define_PossibleGroupMatch( rarg_possible_match_t* possible_match, ... );
	rarg_possible_match_t* RARG_define_PossibleTypeMatch( rarg_type_t type, ... );
	rarg_possible_match_t* RARG_define_PossibleAncestorMatch( char* c_class_name, ... );
	rarg_possible_match_t* RARG_define_PossibleAncestorInstanceMatch( VALUE rb_class_instance, ... );
	rarg_possible_match_t* RARG_define_PossibleMethodMatch( char* c_method, ... );
	rarg_possible_match_t* RARG_define_PossibleHashMatch(	rarg_possible_hash_key_data_match_t*	possible_key_match, 
																												rarg_possible_hash_key_data_match_t*	possible_data_match );
		rarg_possible_hash_key_data_match_t* RARG_define_PossibleHashMatch_KeyOrDataMatch( rarg_possible_match_t* possible_match, ... );
	rarg_possible_match_t* RARG_define_PossibleHashMatch_indexesMatch(	char*	c_index, ... );
	rarg_possible_match_t* RARG_define_PossibleHashMatch_indexesMatch_dataMatch(	rarg_possible_match_t*		possible_hash_index_match, 
																																								rarg_possible_match_t*		possible_data_match, ... );
	rarg_possible_match_t* RARG_define_Block_procMatch();
	rarg_possible_match_t* RARG_define_Block_lambdaMatch();

rarg_possible_match_t* RARG_define_PossibleIfElseMatch( rarg_possible_if_else_match_t* possible_if_else_match, ... );
	rarg_possible_if_else_match_t* RARG_define_PossibleIfMatchMatch( rarg_possible_match_t*	possible_match_condition,
																																						rarg_possible_match_t*	possible_match_action		);
	rarg_possible_if_else_match_t* RARG_define_PossibleIfValueMatch( VALUE*									possible_match_variable,
																																						VALUE										possible_match_value,
																																						rarg_possible_match_t*	possible_match_action );
	rarg_possible_if_else_match_t* RARG_define_PossibleElseIfMatchMatch( rarg_possible_match_t*	possible_match_condition,
																																								rarg_possible_match_t*	possible_match_action		);
	rarg_possible_if_else_match_t* RARG_define_PossibleElseIfValueMatch( VALUE*									possible_match_variable,
																																								VALUE										possible_match_value,
																																								rarg_possible_match_t*	possible_match_action );
	rarg_possible_if_else_match_t* RARG_define_PossibleElseMatch(	rarg_possible_match_t*	possible_match_action		);
	rarg_possible_match_t* RARG_define_PossibleMethodResponds(	char*	method_name, ... );
	rarg_possible_match_t* RARG_define_PossibleMethodReturns(	char*										method_name, 
																														VALUE										possible_method_return, ... );
	rarg_possible_match_t* RARG_define_PossibleMethodReturnsWithArgs(	char*										method_name, 
																																		int											argc,
																																		VALUE*									args,
																																		VALUE										possible_method_return, ... );
	rarg_possible_match_t* RARG_define_PossibleMethodsReturnNonNil(	char* method_name, ... );
	rarg_possible_match_t* RARG_define_PossibleMethodReturnsNonNilWithArgs(	char*		method_name,
																																					int			argc,
																																					VALUE*	args );



		rarg_parameter_set_t* RARG_define_ParameterSet_requireExactMatch(	rarg_parameter_set_t*		parameter_set, ... );	
		rarg_parameter_t* RARG_define_Parameter_setOptional( rarg_parameter_t*	parameter, ... );
		rarg_possible_match_t* RARG_define_PossibleMatch_setOptional( rarg_possible_match_t*	possible_match, ... );
		rarg_possible_match_t* RARG_define_PossibleBlockMatch_arity( rarg_possible_match_t*	possible_match, int arity, ... );
		rarg_possible_match_t* RARG_define_PossibleMatch_assignMatchToValue(	rarg_possible_match_t*	possible_match, 
																																					VALUE*									receiver );
		rarg_possible_hash_key_data_match_t* RARG_define_PossibleMatch_assignHashForKeyDataMatchToValue(	rarg_possible_hash_key_data_match_t*	possible_hash_key_or_data_match, 
																																																			VALUE*																receiver );
	rarg_possible_match_t* definePossibleMatch_assignIndexMatchToValue(	rarg_possible_match_t*	possible_index_match, 
																																			VALUE*												receiver );
	rarg_possible_hash_key_data_match_t* definePossibleMatch_assignHashKeyDataMatchToValue(	rarg_possible_hash_key_data_match_t*		possible_hash_key_data_match, 
																																													VALUE*																	receiver );
	rarg_parameter_set_t* RARG_define_ParameterSet_description(	rarg_parameter_set_t*		parameter_set,
																															int											order_ranking,
																															char*										description, ... );	
	rarg_parameter_t* RARG_define_Parameter_description(	rarg_parameter_t*		parameter,
																												int									order_ranking,
																												char*								description, ... );	
	rarg_possible_match_t* RARG_define_PossibleMatch_description(	rarg_possible_match_t*	possible_match,
																																int											order_ranking,
																																char*										description, ... );	


	extern VALUE rb_cObject;
	extern VALUE rb_cClass;

	extern VALUE rb_cMethod;

	extern VALUE rb_cProc;

	/*************************
	*  RARG Internal Macros  *
	*************************/

	#ifndef NEVER
		#define NEVER																															FALSE
	#endif

	#define RI_AllocPossibleMatch()																							calloc( 1, sizeof( rarg_possible_match_t ) )
	#define RI_AllocPossibleGroupMatch()																				calloc( 1, sizeof( rarg_possible_group_match_t ) )
	#define RI_AllocPossibleMatchDetails()																			calloc( 1, sizeof( rarg_possible_match_frame_t ) )
	#define RI_AllocPossibleBlockMatch()																				calloc( 1, sizeof( rarg_possible_block_match_t ) )
	#define RI_AllocPossibleHashMatch()																					calloc( 1, sizeof( rarg_possible_hash_match_t ) )
	#define RI_AllocPossibleTypeMatch()																					calloc( 1, sizeof( rarg_possible_type_match_t ) )
	#define RI_AllocPossibleAncestorMatch()																			calloc( 1, sizeof( rarg_possible_ancestor_matches_t ) )
	#define RI_AllocPossibleIfElseMatch()																				calloc( 1, sizeof( rarg_possible_if_else_match_t ) )
	#define RI_AllocPossibleIfElseValueMatch()																	calloc( 1, sizeof( rarg_possible_if_else_value_match_t ) )
	#define RI_AllocPossibleIfElseMatchMatch()																	calloc( 1, sizeof( rarg_possible_if_else_match_match_t ) )
	#define RI_AllocPossibleIfElsePossibleMatch()																calloc( 1, sizeof( rarg_possible_if_else_match_type_t ) )
	#define RI_AllocPossibleMethodMatch()																				calloc( 1, sizeof( rarg_possible_method_match_t ) )
	#define RI_AllocPossibleMethodReturnMatch()																	calloc( 1, sizeof( rarg_possible_method_response_match_t ) )
	#define RI_AllocPossibleMethodDetailsMatch()																calloc( 1, sizeof( rarg_possible_method_response_match_t ) )


	#define RI_AllocAndAssignPossibleMatch( var )																( var )	= RI_AllocPossibleMatch()
	#define RI_AllocAndAssignPossibleMatchDetails( var )												( var )->possible							= RI_AllocPossibleMatchDetails()
	#define RI_AllocAndAssignPossibleBlockMatch( var )													( var )->possible->block			= RI_AllocPossibleBlockMatch()
	#define RI_AllocAndAssignPossibleHashMatch( var )														( var )->possible->hash				= RI_AllocPossibleHashMatch()
	#define RI_AllocAndAssignPossibleAncestorsMatch( var )											( var )->possible->ancestors	= RI_AllocPossibleAncestorMatch()
	#define RI_AllocAndAssignPossibleMethodsMatch( var )												( var )->possible->methods		= RI_AllocPossibleMethodMatch()
	#define RI_AllocAndAssignPossibleTypeMatch( var )														( var )->possible->types			= RI_AllocPossibleTypeMatch()

	#define RI_AssignPossibleMatchType( var, rarg_type )												( var )->type = rarg_type;
	
	//----------------------------------------------------------------------------------------------------------//

	#define RI_CreatePossibleMatch( possible_match_ptr_var )											RI_AllocAndAssignPossibleMatch( possible_match_ptr_var );															\
																																								RI_AllocAndAssignPossibleMatchDetails( possible_match_ptr_var );

	#define RI_CreatePossibleBlockMatch( possible_block_match_ptr_var )						RI_AllocAndAssignPossibleBlockMatch( possible_block_match_ptr_var );
	#define RI_CreatePossibleHashMatch( possible_hash_match_ptr_var )							RI_AllocAndAssignPossibleHashMatch( possible_hash_match_ptr_var );
	#define RI_CreatePossibleTypeMatch( possible_type_match_ptr_var )							RI_AllocAndAssignPossibleTypeMatch( possible_type_match_ptr_var );
	#define RI_CreatePossibleAncestorsMatch( possible_ancestors_match_ptr_var )		RI_AllocAndAssignPossibleAncestorsMatch( possible_ancestors_match_ptr_var );
	#define RI_CreatePossibleMethodsMatch( possible_methods_match_ptr_var )				RI_AllocAndAssignPossibleMethodsMatch( possible_methods_match_ptr_var );

	#define RI_CreatePossibleBlockMatchForPossibleMatch( possible_match )					RI_AssignPossibleMatchType( possible_match, RARG_BLOCK );						\
																																								RI_AllocAndAssignPossibleBlockMatch( possible_match );
	#define RI_CreatePossibleHashMatchForPossibleMatch( possible_match )					RI_AssignPossibleMatchType( possible_match, RARG_HASH );						\
																																								RI_AllocAndAssignPossibleHashMatch( possible_match );
	#define RI_CreatePossibleTypeMatchForPossibleMatch( possible_match )					RI_AssignPossibleMatchType( possible_match, RARG_TYPE );						\
																																								RI_AllocAndAssignPossibleTypeMatch( possible_match );
	#define RI_CreatePossibleAncestorsMatchForPossibleMatch( possible_match )			RI_AssignPossibleMatchType( possible_match, RARG_ANCESTOR );				\
																																								RI_AllocAndAssignPossibleAncestorsMatch( possible_match );
	#define RI_CreatePossibleMethodsMatchForPossibleMatch( possible_match )				RI_AssignPossibleMatchType( possible_match, RARG_METHOD );				\
																																								RI_AllocAndAssignPossibleMethodsMatch( possible_match );

	#define RI_CreatePossibleMatchWithBlock( possible_match_ptr_var )							RI_CreatePossibleMatch( possible_match_ptr_var );										\
																																								RI_CreatePossibleBlockMatchForPossibleMatch( possible_match_ptr_var );
	#define RI_CreatePossibleMatchWithHash( possible_match_ptr_var )							RI_CreatePossibleMatch( possible_match_ptr_var );										\
																																								RI_CreatePossibleHashMatchForPossibleMatch( possible_match_ptr_var );
	#define RI_CreatePossibleMatchWithType( possible_match_ptr_var )							RI_CreatePossibleMatch( possible_match_ptr_var );										\
																																								RI_CreatePossibleTypeMatchForPossibleMatch( possible_match_ptr_var );
	#define RI_CreatePossibleMatchWithAncestors( possible_match_ptr_var )					RI_CreatePossibleMatch( possible_match_ptr_var );										\
																																								RI_CreatePossibleAncestorsMatchForPossibleMatch( possible_match_ptr_var );
	#define RI_CreatePossibleMatchWithMethods( possible_match_ptr_var )						RI_CreatePossibleMatch( possible_match_ptr_var );										\
																																								RI_CreatePossibleMethodsMatchForPossibleMatch( possible_match_ptr_var );

	#define RI_Arity( arity, ... )																								RARG_define_PossibleBlockMatch_arity( arity,##__VA_ARGS__, NULL )
	#define R_TERMINATE_ARITY -4

	#define R_Cascade( a, b )																											( ( a ) ? ( b ) : FALSE )


	
#endif