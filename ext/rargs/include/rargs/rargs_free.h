#ifndef RB_RARGS_FREE
	#define RB_RARGS_FREE

	#include <ruby.h>
	#include "rargs_types.h"

void RARG_free_ParameterSets( rarg_parameter_set_t* rarg_parameter_set );	
void RARG_free_Parameters( rarg_parameter_t* rarg_parameter );
void RARG_free_PossibleMatches( rarg_possible_match_t* rarg_possible_match );
void RARG_free_PossibleBlockMatch( rarg_possible_block_match_t* rarg_possible_block_match );
void RARG_free_PossibleBlockArityMatches( rarg_possible_block_match_arity_t* rarg_possible_block_arity_match );
void RARG_free_PossibleHashMatch( rarg_possible_hash_match_t* possible_hash_match );
void RARG_free_PossibleHashIndexMatches( rarg_possible_hash_index_match_t* rarg_possible_hash_index_match );
void RARG_free_PossibleHashKeyOrDataMatch( rarg_possible_hash_key_data_match_t* rarg_allowed_hash_key_type );
void RARG_free_PossibleTypeMatch( rarg_possible_type_match_t* rarg_possible_type_match );
void RARG_free_PossibleAncestorMatches( rarg_possible_ancestor_matches_t* rarg_possible_instance_ancestor_match );
void RARG_free_PossibleMethodMatches( rarg_possible_method_match_t* rarg_possible_instance_method_match );
void RARG_free_MatchedParameterSet( rarg_matched_parameter_set_t* rarg_matched_parameter_set );
	
#endif