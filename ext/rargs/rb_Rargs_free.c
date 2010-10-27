#include "rargs_free.h"

/***********************************************************************************************************************
																							Parameter Sets
***********************************************************************************************************************/

/****************************
*  RARG_free_ParameterSets  *
****************************/

void RARG_free_ParameterSets( rarg_parameter_set_t* rarg_parameter_set )	{	

	rarg_parameter_set_t* rarg_parameter_set_ptr;
	while ( rarg_parameter_set != NULL )	{
		rarg_parameter_set_ptr = rarg_parameter_set;
		rarg_parameter_set	= rarg_parameter_set->next;
		free( rarg_parameter_set_ptr );
	}
}

/*************************
*  RARG_free_Parameters  *
*************************/

void RARG_free_Parameters( rarg_parameter_t* rarg_parameter )	{
	
	rarg_parameter_t* rarg_parameter_ptr	=	rarg_parameter;
	while ( rarg_parameter != NULL )	{
		rarg_parameter_ptr = rarg_parameter;
		rarg_parameter = rarg_parameter->next;
		free( rarg_parameter_ptr );
	}
}

/******************************
*  RARG_free_PossibleMatches  *
******************************/

void RARG_free_PossibleMatches( rarg_possible_match_t* rarg_possible_match )	{

	rarg_possible_match_t* rarg_possible_match_ptr	=	NULL;
	
	while ( rarg_possible_match != NULL )	{
		switch ( rarg_possible_match->type )	{
			case RARG_BLOCK:
				RARG_free_PossibleBlockMatch( rarg_possible_match->possible->block );
				break;			
			case RARG_HASH:
				RARG_free_PossibleHashMatch( rarg_possible_match->possible->hash );
				break;			
			case RARG_TYPE:
				RARG_free_PossibleTypeMatch( rarg_possible_match->possible->types );
				break;
			case RARG_ANCESTOR:
				RARG_free_PossibleAncestorMatches( rarg_possible_match->possible->ancestors );
				break;
			case RARG_METHOD:
				RARG_free_PossibleMethodMatches( rarg_possible_match->possible->methods );
				break;
			default:
				rb_raise( rb_eArgError, "Unknown rarg_possible_match_type_t type. Should never have gotten here." );
				break;
		}
		rarg_possible_match_ptr		= rarg_possible_match;
		rarg_possible_match				= rarg_possible_match->next;
		free( rarg_possible_match_ptr );
	}
}

/***********************************************************************************************************************
																							Possible Match Types
***********************************************************************************************************************/

/*********************************
*  RARG_free_PossibleBlockMatch  *
*********************************/

void RARG_free_PossibleBlockMatch( rarg_possible_block_match_t* rarg_possible_block_match )	{
	RARG_free_PossibleBlockArityMatches( rarg_possible_block_match->possible_arity );
	free( rarg_possible_block_match );
}

	/****************************************
	*  RARG_free_PossibleBlockArityMatches  *
	****************************************/

	void RARG_free_PossibleBlockArityMatches( rarg_possible_block_match_arity_t* rarg_possible_block_arity_match )	{

		rarg_possible_block_match_arity_t* rarg_possible_block_arity_match_ptr;
		while ( rarg_possible_block_arity_match != NULL )	{
			rarg_possible_block_arity_match_ptr		= rarg_possible_block_arity_match;
			rarg_possible_block_arity_match				= rarg_possible_block_arity_match->next;
			free( rarg_possible_block_arity_match_ptr );
		}

	}

/********************************
*  RARG_free_PossibleHashMatch  *
********************************/

void RARG_free_PossibleHashMatch( rarg_possible_hash_match_t* possible_hash_match )	{
	RARG_free_PossibleHashIndexMatches( possible_hash_match->possible_index_match );
	RARG_free_PossibleHashKeyOrDataMatch( possible_hash_match->possible_key_match );
	RARG_free_PossibleHashKeyOrDataMatch( possible_hash_match->possible_data_match );
	free( possible_hash_match );
}

	/****************************************
	*  RARG_free_PossibleBlockArityMatches  *
	****************************************/

	void RARG_free_PossibleHashIndexMatches( rarg_possible_hash_index_match_t* rarg_possible_hash_index_match )	{

		rarg_possible_hash_index_match_t* rarg_possible_hash_index_match_ptr;
		while ( rarg_possible_hash_index_match != NULL )	{
			rarg_possible_hash_index_match_ptr		= rarg_possible_hash_index_match;
			rarg_possible_hash_index_match				= rarg_possible_hash_index_match->next;
			free( rarg_possible_hash_index_match_ptr );
		}

	}

	/*****************************************
	*  RARG_free_PossibleHashKeyOrDataMatch  *
	*****************************************/

	void RARG_free_PossibleHashKeyOrDataMatch( rarg_possible_hash_key_data_match_t* rarg_allowed_hash_key_type )	{

		rarg_possible_hash_key_data_match_t* rarg_allowed_hash_key_type_ptr;
		RARG_free_PossibleMatches( rarg_allowed_hash_key_type->possible_match );
		free( rarg_allowed_hash_key_type_ptr );
	}

/********************************
*  RARG_free_PossibleTypeMatch  *
********************************/

void RARG_free_PossibleTypeMatch( rarg_possible_type_match_t* rarg_possible_type_match )	{
	free( rarg_possible_type_match );
}

/**************************************
*  RARG_free_PossibleAncestorMatches  *
**************************************/

void RARG_free_PossibleAncestorMatches( rarg_possible_ancestor_matches_t* rarg_possible_instance_ancestor_match )	{

	rarg_possible_ancestor_matches_t* rarg_possible_instance_ancestor_match_ptr;
	while ( rarg_possible_instance_ancestor_match != NULL )	{
		rarg_possible_instance_ancestor_match_ptr		= rarg_possible_instance_ancestor_match;
		rarg_possible_instance_ancestor_match				= rarg_possible_instance_ancestor_match->next;
		free( rarg_possible_instance_ancestor_match_ptr );
	}

}

/************************************
*  RARG_free_PossibleMethodMatches  *
************************************/

void RARG_free_PossibleMethodMatches( rarg_possible_method_match_t* rarg_possible_instance_method_match )	{

	rarg_possible_method_match_t* rarg_possible_instance_method_match_ptr;
	while ( rarg_possible_instance_method_match != NULL )	{
		rarg_possible_instance_method_match_ptr	= rarg_possible_instance_method_match;
//		rarg_possible_instance_method_match			= rarg_possible_instance_method_match->next;
		free( rarg_possible_instance_method_match_ptr );
	}

}

/***********************************************************************************************************************
																					Matched Parameter Sets
***********************************************************************************************************************/

/**********************************
*  RARG_free_MatchedParameterSet  *
**********************************/

void RARG_free_MatchedParameterSet( rarg_matched_parameter_set_t* rarg_matched_parameter_set )	{

	rarg_matched_parameter_t* rarg_matched_parameter			=	rarg_matched_parameter_set->parameters;
	rarg_matched_parameter_t* rarg_next_matched_parameter	=	NULL;
	while ( rarg_matched_parameter != NULL )	{
		rarg_next_matched_parameter = rarg_matched_parameter->next;
		free( rarg_matched_parameter );
		rarg_matched_parameter = rarg_next_matched_parameter;
	}
	free( rarg_matched_parameter_set );
}
