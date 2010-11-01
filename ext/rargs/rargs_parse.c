#include "include/rargs/rargs_parse.h"
#include "include/rargs/rargs_describe.h"
#include "include/rargs/rargs_error.h"
#include "include/rargs/rargs_free.h"

/***********************************************************************************************************************
																					Parameter Sets
***********************************************************************************************************************/

/*************************************
*  RARG_parse_ParameterSetsForMatch  *
*************************************/

BOOL RARG_parse_ParameterSetsForMatch(	rarg_parse_descriptor_t*	parse_descriptor,
																				rarg_parameter_set_t*			parameter_sets,
																				BOOL											raise_exception_on_match_fail )	{	

	//	we do this here to allow looping by macro (R_Parse)
	if (		parse_descriptor->argc <= 0 
			&&	! rb_block_given_p() )	{
		return FALSE;
	}

	//	Parse parameter_sets for match
	parse_descriptor->matched_parameter_set	=	RARG_parse_ParameterSets(	parse_descriptor,
																																			parameter_sets );

	//	Iterate matched parameter_set parameters
	if ( parse_descriptor->matched_parameter_set == NULL )	{
	
		if ( raise_exception_on_match_fail )	{
			RARG_error_NoMatchForParameters(	parse_descriptor,
																				parameter_sets );
		}
	
	}
	//	assign matched parameter values to value receivers
	else	{
	
		rarg_matched_parameter_t* matched_parameter	=	parse_descriptor->matched_parameter_set->parameters;
		while ( matched_parameter != NULL )	{

			if ( matched_parameter->receiver )	{
				*matched_parameter->receiver	=	matched_parameter->match;
			}
			matched_parameter							= matched_parameter->next;

		}
	}
	
	//	FIX - free parameter sets
	
	return parse_descriptor->args_parsed;
}

/*****************************
*  RARG_parse_ParameterSets  *
*****************************/

rarg_matched_parameter_set_t* RARG_parse_ParameterSets(	rarg_parse_descriptor_t*		parse_descriptor, 
																												rarg_parameter_set_t*				parameter_set )	{	

	while ( parameter_set != NULL )	{

		parse_descriptor->matched_parameter_set	=	calloc( 1, sizeof( rarg_matched_parameter_set_t ) );
		parse_descriptor->matched_parameter_ptr	=	& parse_descriptor->matched_parameter_set->parameters;

		// if all parameters in a parameter_set match args
		if ( ( parse_descriptor->matched_parameter_set->last_arg	=	RARG_parse_Parameters(	parse_descriptor,
																																												parameter_set->parameters ) )

			//	if we require exact match and have args remaining we don't match
			&&	(		! parameter_set->require_exact
					||	parse_descriptor->matched_parameter_set->last_arg == parse_descriptor->argc ) )	{

			//	otherwise, success - matched parameter_set
			break;
		}
		
		RARG_free_MatchedParameterSet( parse_descriptor->matched_parameter_set );
		parse_descriptor->matched_parameter_set = NULL;
		
		parameter_set	= parameter_set->next;
	}
	//	success = match
	//	failure = NULL
	return parse_descriptor->matched_parameter_set;
}

/**************************
*  RARG_parse_Parameters  *
**************************/

BOOL RARG_parse_Parameters(	rarg_parse_descriptor_t*				parse_descriptor, 
														rarg_parameter_t*								parameter )	{
	
	parse_descriptor->args_parsed	=	0;
			
	if (		! parse_descriptor->argc
			&&	parameter->possible_match->type == RARG_BLOCK
			&&	rb_block_given_p() )	{
			
			if ( RARG_parse_PossibleMatches(	parse_descriptor,
																				parameter ) )	{
				parse_descriptor->args_parsed = TRUE;
			}
			else	{
				parse_descriptor->args_parsed = FALSE;
			}
	}
	else while(		parameter != NULL )	{
	
		//	advance matched parameter to the end
		while (			*parse_descriptor->matched_parameter_ptr != NULL 
						&&	*( parse_descriptor->matched_parameter_ptr = & ( *parse_descriptor->matched_parameter_ptr )->next ) != NULL );
	
		//	for each arg, test the current parameter
		// if parsing allowed types fails, break from parsing these parameters and go to next parameter_set

		BOOL	matched	=	FALSE;
		//	if we have a block match descriptor from our loop or if we didn't loop and have a block descriptor
		if (		! ( matched = RARG_parse_PossibleMatches(	parse_descriptor,
																											parameter ) )
				&&	! parameter->optional ) {
				
			parse_descriptor->args_parsed = FALSE;
			break;
		}
		
		parameter	= parameter->next;
		//	don't advance count if we matched block or if we had a non-matched optional parameter - doesn't correspond to args
		if (		matched
				&&	! ( *parse_descriptor->matched_parameter_ptr )->block_match )	{
			parse_descriptor->args_parsed++;		
		}
	}

	//	if we got here we matched
	//	* we have the option of requiring exact match (in which case we test which_parameter == argc)
	//	* or of allowing repeats, in which case we return the index of the next unused arg
	//	we test for this after return, in parameter set
	return parse_descriptor->args_parsed;
}

/***********************************************************************************************************************
																					Possible Matches
***********************************************************************************************************************/

/*******************************
*  RARG_parse_PossibleMatches  *
*******************************/

BOOL RARG_parse_PossibleMatches(	rarg_parse_descriptor_t*			parse_descriptor,
																	rarg_parameter_t*							parameter )	{

	VALUE	rb_arg	=	( parse_descriptor->argc && ( parse_descriptor->args_parsed <= parse_descriptor->argc ) ? parse_descriptor->args[ parse_descriptor->args_parsed ] : Qnil );

	BOOL matched	=	FALSE;

	rarg_possible_match_t*	possible_match	=	parameter->possible_match;

	if ( *parse_descriptor->matched_parameter_ptr == NULL )	{
		*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
	}
	else if ( ( *parse_descriptor->matched_parameter_ptr )->receiver != NULL )	{
		( *parse_descriptor->matched_parameter_ptr )->next		=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
		parse_descriptor->matched_parameter_ptr								=	& ( *parse_descriptor->matched_parameter_ptr )->next;
	}

	//	if we have more parameters but no more args, check to see if we are looking for a block
	//	if so, parse it
	//	otherwise, break and return FALSE;
	if (	rb_arg == Qnil ) {

		while ( possible_match != NULL )	{

			//	a nil arg can be a block (doesn't correspond to an arg)
			if (		possible_match->type == RARG_BLOCK
					&&	( matched	=	RARG_parse_PossibleMatch( parse_descriptor,
																										possible_match,
																										rb_arg ) ) )	{
				break;
			}
			//	or can be an explicit nil type
			else if (		possible_match->type == RARG_TYPE
							&&	( matched	=	RARG_parse_PossibleTypeMatch( parse_descriptor,
																														possible_match,
																														rb_arg ) ) )	{
				break;
			}

			possible_match = possible_match->next;
		}
		
	}
	else if ( parameter )	{
		
		// test each allowed type for this parameter slot to see if this arg matches parameter
		while ( possible_match != NULL )	{

			//	if our possible match is true, we matched this parameter (continue to next)
			//	if our possible match is false, we do not match this possible match 
			if (	( matched = RARG_parse_PossibleMatch( parse_descriptor,
																									possible_match,
																									rb_arg ) ) )	{
				break;
			}

			possible_match = possible_match->next;
		}
	}
	
	// if we get here we didn't match
	return matched;
}

/*****************************
*  RARG_parse_PossibleMatch  *
*****************************/

BOOL RARG_parse_PossibleMatch(		rarg_parse_descriptor_t*			parse_descriptor, 
																	rarg_possible_match_t*				possible_match, 
																	VALUE													rb_arg )	{

	int	matched	=	FALSE;

	switch ( possible_match->type )	{
		
		case RARG_GROUP:
			matched	=	RARG_parse_PossibleGroupMatch(	parse_descriptor,
																								possible_match,
																								rb_arg );
			break;
			
		case RARG_BLOCK:
			matched	=	RARG_parse_PossibleBlockMatch(	parse_descriptor,
																								possible_match,
																								rb_arg );
			break;
		
		case RARG_HASH:
			matched	=	RARG_parse_PossibleHashMatch(	parse_descriptor,
																							possible_match,
																							rb_arg );
			break;
		
		case RARG_TYPE:
			matched = RARG_parse_PossibleTypeMatch(	parse_descriptor,
																							possible_match,
																							rb_arg );
			break;
		
		case RARG_ANCESTOR:
			matched	=	RARG_parse_PossibleAncestorMatches(	parse_descriptor,
																										possible_match,
																										rb_arg );
			break;
	
		case RARG_METHOD:
			matched	=	RARG_parse_PossibleMethodMatches(	parse_descriptor,
																									possible_match,
																									rb_arg );
			break;
		
		case RARG_IF_ELSE:
			matched	=	RARG_parse_PossibleIfElseMatch(	parse_descriptor,
																								possible_match,
																								rb_arg );
			break;

		case RARG_INDEX:
			matched	=	RARG_parse_PossibleIndexMatch(	parse_descriptor,
																								possible_match,
																								rb_arg );
			break;
		
		default:
			rb_raise( rb_eArgError, "We should never have gotten here." );
			break;
	
	}
	
	return matched;
}

/***********************************************************************************************************************
																					Possible Match Details
***********************************************************************************************************************/

/**********************************
*  RARG_parse_PossibleGroupMatch  *
**********************************/

BOOL RARG_parse_PossibleGroupMatch(	rarg_parse_descriptor_t*			parse_descriptor,
																		rarg_possible_match_t*				possible_match,
																		VALUE													rb_arg )	{
	
	rarg_possible_group_match_t*	possible_group_match	=	possible_match->possible->group;

	BOOL	matched		=	TRUE;

	while ( possible_group_match != NULL )	{
	
		if ( ! ( matched = RARG_parse_PossibleMatch(	parse_descriptor,
																									possible_group_match->match,
																									rb_arg ) ) )	{
			
			matched	=	FALSE;
			break;
		}
		
		//	advance rb_arg
		(void) RI_NextArg(	parse_descriptor, rb_arg );
	
		possible_group_match = possible_group_match->next;
	}

	return matched;
}

/**********************************
*  RARG_parse_PossibleBlockMatch  *
**********************************/

BOOL RARG_parse_PossibleBlockMatch(		rarg_parse_descriptor_t*			parse_descriptor,
																			rarg_possible_match_t*				possible_match,
																			VALUE													rb_arg )	{

	rarg_possible_closure_match_t*	possible_block_match	=	possible_match->possible->block;

	BOOL	matched	=	FALSE;
	
	VALUE	rb_block_as_lambda	=	Qnil;
	
	if ( possible_block_match->arg_not_block )	{
		
		VALUE	rb_arg_class				=	rb_obj_class( rb_arg );
		VALUE	rb_arg_ancestors		=	rb_mod_ancestors( rb_arg_class );
		
		if ( rb_ary_includes( rb_arg_ancestors, rb_cProc ) == Qtrue )	{
			rb_block_as_lambda	=	rb_arg;
			matched = TRUE;
		}
		
	}
	else if ( rb_block_given_p() )	{

		rb_block_as_lambda	=	rb_block_lambda();

		( *parse_descriptor->matched_parameter_ptr )->block_match = TRUE;

		matched = TRUE;

	}

	if ( matched )	{

		VALUE	rb_arity	=	rb_funcall(	rb_block_as_lambda,
																	rb_intern( "arity" ),
																	0 );

		if (	(		possible_block_match->possible_arity == NULL
					||	( matched = RARG_parse_PossibleBlockArityMatch( possible_block_match->possible_arity,
																															rb_arity ) ) )
					&&	possible_match->receiver != NULL )	{

			if (		possible_block_match->arg_not_block
					||	possible_block_match->lambda_instead_of_proc )	{
		
				( *parse_descriptor->matched_parameter_ptr )->match			=	rb_block_as_lambda;
				( *parse_descriptor->matched_parameter_ptr )->receiver	=	possible_match->receiver;
			}
			else {
				
				VALUE	rb_block_as_proc						=	rb_block_proc();
				( *parse_descriptor->matched_parameter_ptr )->match			=	rb_block_as_proc;
				( *parse_descriptor->matched_parameter_ptr )->receiver	=	possible_match->receiver;
			}

		}
	}

	return matched;
}

/***************************************
*  RARG_parse_PossibleBlockArityMatch  *
***************************************/

BOOL RARG_parse_PossibleBlockArityMatch(	rarg_possible_closure_match_arity_t*	possible_arity_match,
																					VALUE																rb_arity	)	{

	BOOL	matched	=	FALSE;
	
	int	c_arity	=	FIX2INT( rb_arity );
	
	while ( possible_arity_match )	{
		
		if ( possible_arity_match->arity == c_arity )	{
			matched = TRUE;
			break;
		}
		
		possible_arity_match	=	possible_arity_match->next;
	}
	
	return matched;
}

/*********************************
*  RARG_parse_PossibleHashMatch  *
*********************************/

BOOL RARG_parse_PossibleHashMatch(		rarg_parse_descriptor_t*			parse_descriptor, 
																			rarg_possible_match_t*				possible_match, 
																			VALUE													rb_arg )	{

	rarg_possible_hash_match_t*	possible_hash_match	=	possible_match->possible->hash;

	BOOL	matched	=	FALSE;

	if ( TYPE( rb_arg ) == T_HASH )	{
		
		//	once we match a hash we assume we have matched unless more settings tell us otherwise
		matched	=	TRUE;
				
		VALUE rb_array_key_data	=	rb_funcall( rb_arg,
																					rb_intern( "first" ),
																					0 );
		VALUE	rb_key	=	rb_ary_shift( rb_array_key_data );
		VALUE	rb_data	=	rb_ary_shift( rb_array_key_data );
		
		if ( possible_hash_match->possible_index_match )	{
			
			matched = RARG_parse_PossibleIndexMatch(	parse_descriptor,
																								possible_match,
																								rb_arg );
		}
		
		if (		matched
				&&	possible_hash_match->possible_key_match )	{
		
			matched = RARG_parse_PossibleHashKeyOrDataMatch(	parse_descriptor,
																												possible_hash_match->possible_key_match,
																												rb_arg,
																												rb_key );
		}
		
		if (		matched
				&&	possible_hash_match->possible_data_match )	{
		
			matched = RARG_parse_PossibleHashKeyOrDataMatch(	parse_descriptor,
																												possible_hash_match->possible_data_match,
																												rb_arg,
																												rb_data );
		}

	}
	
	if ( matched )	{

		if ( possible_match->receiver != NULL )	{

			if ( ( *parse_descriptor->matched_parameter_ptr )->receiver != NULL )	{
				parse_descriptor->matched_parameter_ptr		=	& ( *parse_descriptor->matched_parameter_ptr )->next;
				*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
			}
			
			( *parse_descriptor->matched_parameter_ptr )->receiver									=	possible_match->receiver;	
			( *parse_descriptor->matched_parameter_ptr )->match											=	rb_arg;			
		}
	}

	return matched;
}

	/**********************************
	*  RARG_parse_PossibleIndexMatch  *
	**********************************/

	BOOL RARG_parse_PossibleIndexMatch(	rarg_parse_descriptor_t*			parse_descriptor,
																			rarg_possible_match_t*				possible_match,
																			VALUE													rb_arg )	{

		rarg_possible_hash_index_match_t*	possible_index_match	=	possible_match->possible->hash->possible_index_match;
			
		BOOL	has_required_indexes	=	TRUE;
		
		//	a "possible index match" can be one or more indexes; if multiple are specified together, all are expected
		while ( possible_index_match != NULL ) {
			
			VALUE	rb_index_ref	=	Qnil;
			if (		possible_index_match->index_name
									//	symbol
					&&	(		( rb_index_ref	=	rb_hash_aref(	rb_arg,
																									ID2SYM( rb_intern( possible_index_match->index_name ) ) ) ) != Qnil
									//	or string
							||	( rb_index_ref	=	rb_hash_aref(	rb_arg,
																									rb_str_new2( possible_index_match->index_name ) ) ) != Qnil ) )	{
				
				//	if we get to this point we match
				if (		possible_index_match->receiver != NULL
						||	possible_index_match->assign_parent_hash_for_match )	{
					
					( *parse_descriptor->matched_parameter_ptr )->match			=	( possible_index_match->assign_parent_hash_for_match ? 
																																			rb_arg 
																																			: rb_index_ref );
					( *parse_descriptor->matched_parameter_ptr )->receiver	=	( possible_index_match->assign_parent_hash_for_match ? 
																																			possible_match->receiver 
																																			: possible_index_match->receiver );
				
				}
				
			}
			else if ( ! possible_index_match->optional )	{

				has_required_indexes	=	FALSE;
				break;
			}
			
			possible_index_match = possible_index_match->next;
		}
		
		return has_required_indexes;
	}

	/******************************************
	*  RARG_parse_PossibleHashKeyOrDataMatch  *
	******************************************/

	BOOL RARG_parse_PossibleHashKeyOrDataMatch(	rarg_parse_descriptor_t*								parse_descriptor, 
																							rarg_possible_hash_key_data_match_t*		possible_hash_key_or_data, 
																							VALUE																		rb_hash_arg,
																							VALUE																		rb_key_or_data )	{

		rarg_possible_match_t**	this_possible_key_or_data	=	& possible_hash_key_or_data->possible_match;

		//	if no key/data types are specified, any are allowed
		BOOL	matched	=	TRUE;
		if ( possible_hash_key_or_data )	{
			//	but once we start testing, we assume a match hasn't happened yet
			matched	=	FALSE;
			while ( *this_possible_key_or_data != NULL )	{
				
				if ( ( matched	=	RARG_parse_PossibleMatch( parse_descriptor,
																										possible_hash_key_or_data->possible_match,
																										rb_key_or_data ) ) )	{
				
					//	if we matched our key or data and are supposed to assign our parent hash for the match then
					//	we will have set the match already to the key or data; we test if this has happened and 
					//	override the key or data with the parent hash
					
					if (		( *parse_descriptor->matched_parameter_ptr )->match
							&&	possible_hash_key_or_data->assign_parent_hash_for_match	)	{
						
						( *parse_descriptor->matched_parameter_ptr )->match	=	rb_hash_arg;
					}
					
					//	and we matched so we're done with this key or data
					break;
				}
				
				this_possible_key_or_data = & ( *this_possible_key_or_data )->next;
			}

			// if we get here we didn't match
			return matched;
		}
		return TRUE;
	}

/*********************************
*  RARG_parse_PossibleTypeMatch  *
*********************************/

BOOL RARG_parse_PossibleTypeMatch(	rarg_parse_descriptor_t*			parse_descriptor, 
																		rarg_possible_match_t*				possible_match, 
																		VALUE													rb_arg )	{

	const int	rb_arg_type					=	TYPE( rb_arg );
	const int allowed_match_type	=	possible_match->possible->types->type;
	
	int	matched	=	FALSE;
	
	//	check for allowed types
	if ( allowed_match_type == R_ANY )	{
		matched	=	TRUE;
	}
	else if (	allowed_match_type == R_NOT_NIL )	{

		if ( rb_arg != Qnil )	{
			matched	=	TRUE;
		}
		matched = FALSE;
	}
	
	if ( ! matched ) switch ( rb_arg_type )	{

		case T_NIL:
			if ( allowed_match_type & R_NIL )	{
				matched	=	TRUE;
			}
			break;
			
		case T_CLASS:
			if ( allowed_match_type & R_CLASS )	{
				matched	=	TRUE;
			}
			break;

		case T_MODULE:
			if ( allowed_match_type & R_MODULE )	{
				matched	=	TRUE;
			}
			break;

		case T_FLOAT:
			if ( allowed_match_type & R_FLOAT )	{
				matched	=	TRUE;
			}
			break;

		case T_STRING:
			if ( allowed_match_type & R_STRING )	{
				matched	=	TRUE;	
			}
			break;

		case T_SYMBOL:
			if ( allowed_match_type & R_SYMBOL )	{
				matched	=	TRUE;
			}			
			break;


		case T_REGEXP:
			if ( allowed_match_type & R_REGEXP )	{
				matched	=	TRUE;	
			}
			break;

		case T_ARRAY:
			if ( allowed_match_type & R_ARRAY )	{
				matched	=	TRUE;
			}
			break;

		case T_HASH:
			if ( allowed_match_type & R_HASH )	{
				matched	=	TRUE;	
			}
			break;

		case T_BIGNUM:
			if ( allowed_match_type & R_BIGNUM )	{
				matched	=	TRUE;
			}
			break;

		case T_FILE:
			if ( allowed_match_type & R_FILE )	{
				matched	=	TRUE;	
			}
			break;

		case T_FIXNUM:
			if ( allowed_match_type & R_FIXNUM )	{
				matched	=	TRUE;
			}
			break;

		case T_TRUE:
			if ( allowed_match_type & R_TRUE )	{
				matched	=	TRUE;	
			}
			break;

		case T_FALSE:
			if ( allowed_match_type & R_FALSE )	{
				matched	=	TRUE;	
			}
			break;

		case T_STRUCT:
			if ( allowed_match_type & R_STRUCT )	{
				matched	=	TRUE;
			}
		case T_DATA:
			if ( allowed_match_type & R_DATA )	{
				matched	=	TRUE;
			}
		case T_OBJECT:
			if (		allowed_match_type & R_OBJECT )	{
				matched	=	TRUE;	
			}
			break;
			
		case T_MATCH:
			if ( allowed_match_type & R_MATCH )	{
				matched	=	TRUE;	
			}
			break;

		case T_RATIONAL:
			if ( allowed_match_type & R_RATIONAL )	{
				matched	=	TRUE;
			}
			break;

		case T_COMPLEX:
			if ( allowed_match_type & R_COMPLEX )	{
				matched	=	TRUE;
			}
			break;
	}
	
	//	if we matched we want to store reference to match data so we don't have to reparse the matched parameter_set
	if ( matched )	{

		if ( possible_match->receiver != NULL )	{

			if ( ( *parse_descriptor->matched_parameter_ptr )->receiver != NULL )	{
				parse_descriptor->matched_parameter_ptr		=	& ( *parse_descriptor->matched_parameter_ptr )->next;
				*parse_descriptor->matched_parameter_ptr	=	calloc( 1, sizeof( rarg_matched_parameter_t ) );
			}
			
			( *parse_descriptor->matched_parameter_ptr )->receiver									=	possible_match->receiver;	
			( *parse_descriptor->matched_parameter_ptr )->match											=	rb_arg;			
		}
	}
	
	return matched;
}

/***************************************
*  RARG_parse_PossibleAncestorMatches  *
***************************************/

BOOL RARG_parse_PossibleAncestorMatches(	rarg_parse_descriptor_t*			parse_descriptor, 
																					rarg_possible_match_t*				possible_match, 
																					VALUE													rb_arg )	{
	
	BOOL	matched	=	TRUE;

	//	test ancestor(s)
	if ( possible_match->possible->ancestors != NULL )	{
		
		VALUE	rb_arg_class			=	rb_obj_class( rb_arg );
		VALUE	rb_arg_ancestors	=	rb_mod_ancestors( rb_arg_class );
		
		rarg_possible_ancestor_matches_t**	c_this_possible_ancestor	=	& possible_match->possible->ancestors;
		
		while ( *c_this_possible_ancestor != NULL )	{
			
			if ( rb_ary_includes( rb_arg_ancestors, ( *c_this_possible_ancestor )->ancestor ) == Qfalse )	{
				matched = FALSE;
				break;
			}
			
			c_this_possible_ancestor	=	& ( *c_this_possible_ancestor )->next;
		}
	}

	if (		matched
			&&	possible_match->receiver )	{
		
		( *parse_descriptor->matched_parameter_ptr )->match			=	rb_arg;
		( *parse_descriptor->matched_parameter_ptr )->receiver	=	possible_match->receiver;
	}
	
	return matched;
}

/*************************************
*  RARG_parse_PossibleMethodMatches  *
*************************************/

BOOL RARG_parse_PossibleMethodMatches(		rarg_parse_descriptor_t*			parse_descriptor, 
																					rarg_possible_match_t*				possible_match, 
																					VALUE													rb_arg )	{

	//	no required methods means match
	BOOL	matched	=	TRUE;

	//	test method(s)
	if ( possible_match->possible->methods )	{

		rarg_possible_method_match_t**	c_this_possible_method	=	& possible_match->possible->methods;

		while ( *c_this_possible_method != NULL )	{

			VALUE	rb_return_value	=	Qnil;
			//	if ensure_return_non_nil == TRUE or possible_return != NULL, call method
			if (		( *c_this_possible_method )->ensure_return_non_nil
					||	( *c_this_possible_method )->possible_return )	{
				
				rb_return_value	=	rb_funcall2(	(			( ( *c_this_possible_method )->object == Qnil )
																					||	( ( *c_this_possible_method )->object == Qfalse )	? rb_arg : ( *c_this_possible_method )->object ),
																				( *c_this_possible_method )->method,
																				( *c_this_possible_method )->argc,
																				( *c_this_possible_method )->args );
			}

			//	if ensure_return_non_nil is TRUE check to see if value is nil
			if ( ( *c_this_possible_method )->ensure_return_non_nil )	{
				if ( rb_return_value == Qnil )	{
					matched = FALSE;
				}
			}		
			//	otherwise if possible_return is non-NULL we iterate it to check if method's return matches one of given values
			else if ( ( *c_this_possible_method )->possible_return ) {
				
				rarg_possible_method_response_match_t**	c_this_possible_method_response	=	& ( *c_this_possible_method )->possible_return;
				
				//	if we get here we need to invert the matched pattern - matched is FALSE now until a value matches
				matched = FALSE;
				while ( *c_this_possible_method_response )	{
				
					if ( rb_return_value == ( *c_this_possible_method )->possible_return->value )	{
						matched = TRUE;
						break;
					}
				c_this_possible_method_response	=	& ( *c_this_possible_method_response )->next;
				}
			
			}
			//	otherwise check if object responds to method
			else if ( rb_respond_to( rb_arg, ( *c_this_possible_method )->method ) == Qfalse )	{
				matched = FALSE;
				break;
			}

			c_this_possible_method	=	& ( *c_this_possible_method )->next;
		}
	
	}
	
	if (		matched
			&&	possible_match->receiver )	{
		
		( *parse_descriptor->matched_parameter_ptr )->match			=	rb_arg;
		( *parse_descriptor->matched_parameter_ptr )->receiver	=	possible_match->receiver;
	}
	
	return matched;
}

/***************************************
*  RARG_parse_PossibleIfElseMatch  *
***************************************/

BOOL RARG_parse_PossibleIfElseMatch(	rarg_parse_descriptor_t*			parse_descriptor, 
																			rarg_possible_match_t*				possible_match, 
																			VALUE													rb_arg )	{

	rarg_possible_if_else_match_t*	possible_if_else_match	=	possible_match->possible->if_else;

	BOOL	matched			=	TRUE;
	while ( possible_if_else_match )	{
		
		switch ( possible_if_else_match->type )	{
		
			case RARG_CONDITION_IF_VALUE:
				//	we start with matched == true
				//	if we get a second if having not matched the first, we fail
				//	continue to the next possible_if_else_match to look for an else
				if ( ! matched )	{
					break;
				}
				matched = RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																												possible_match,
																												possible_if_else_match,
																												rb_arg );
				//	if our condition is not true and we have an else, it will be parsed next loop
				break;

			case RARG_CONDITION_IF_MATCH:
				//	we start with matched == true
				//	if we get a second if having not matched the first, we fail
				//	continue to the next possible_if_else_match to look for an else
				if ( ! matched )	{
					break;
				}
				matched = RARG_parse_PossibleIfElseMatchMatch(	parse_descriptor,
																												possible_match,
																												possible_if_else_match,
																												rb_arg );
				break;

			
			case RARG_CONDITION_ELSE_IF_VALUE:
				//	if matched is true then we skip this because it is an else condition
				if ( matched )	{
					break;
				}
				matched = RARG_parse_PossibleIfElseValueMatch(	parse_descriptor,
																												possible_match,
																												possible_if_else_match,
																												rb_arg );
				break;
			
			case RARG_CONDITION_ELSE_IF_MATCH:
				//	if matched is true then we skip this because it is an else condition
				if ( matched )	{
					break;
				}
				matched = RARG_parse_PossibleIfElseMatchMatch(	parse_descriptor,
																												possible_match,
																												possible_if_else_match,
																												rb_arg );
				break;
			
			case RARG_CONDITION_ELSE_MATCH:
				//	if matched is true then we skip this because it is an else condition
				if ( matched )	{
					break;
				}
				matched = RARG_parse_PossibleMatch(	parse_descriptor,
																						possible_if_else_match->possible->match->action,
																						rb_arg );
				break;
				
			default:
				rb_raise( rb_eArgError, "We should never have gotten here." );
		}
		
		possible_if_else_match	=	possible_if_else_match->next;
	}
	
	return matched;
}

	/***************************************
	*  RARG_parse_PossibleIfElseValueMatch  *
	***************************************/

	BOOL RARG_parse_PossibleIfElseValueMatch(	rarg_parse_descriptor_t*					parse_descriptor, 
																						rarg_possible_match_t*						possible_match __attribute__ ((unused )), 
																						rarg_possible_if_else_match_t*		possible_if_else_match,
																						VALUE															rb_arg  )	{

		BOOL	matched	=	FALSE;
		
		//	if we have a value
		VALUE	rb_variable	=	*possible_if_else_match->possible->value->variable;
		VALUE	rb_value		= possible_if_else_match->possible->value->value;

		//	if our condition is true
		if (		(		rb_value != Qnil
						&&	rb_variable == rb_value )
				||	(		rb_value == Qnil
						&&	rb_variable != Qnil ) )	{
			matched = RARG_parse_PossibleMatch( parse_descriptor,
																					possible_if_else_match->possible->value->action,
																					rb_arg );
		}
		
		return matched;
	}

	/***************************************
	*  RARG_parse_PossibleIfElseMatchMatch  *
	***************************************/

	BOOL RARG_parse_PossibleIfElseMatchMatch(	rarg_parse_descriptor_t*					parse_descriptor, 
																						rarg_possible_match_t*						possible_match __attribute__ ((unused )), 
																						rarg_possible_if_else_match_t*		possible_if_else_match,
																						VALUE															rb_arg )	{

		BOOL	matched	=	FALSE;

		if ( ( matched = RARG_parse_PossibleMatch(	parse_descriptor,
																								possible_if_else_match->possible->match->condition,
																								rb_arg ) ) )	{

			//	if we match this arg, parse next arg
			(void) RI_NextArg(	parse_descriptor, rb_arg );
			matched = RARG_parse_PossibleMatch( parse_descriptor,
																					possible_if_else_match->possible->match->action,
																					rb_arg );
		}
		
		return matched;
	}

/***********************************************************************************************************************
																					Arg Iteration
***********************************************************************************************************************/

/*************************************
*  RARG_parse_IterateHashDescriptor  *
*************************************/

VALUE RARG_parse_IterateHashDescriptor(	rarg_parse_descriptor_t*			parse_descriptor,
																				VALUE													rb_hash,
																				VALUE													c_function(		int			argc,
																																										VALUE*	args,
																																										VALUE		rb_self ),
																				VALUE													rb_arg_to_pass, ... )	{

	//	collect passed args into ruby array
	VALUE		rb_args_to_pass	=	rb_ary_new();

	va_list	var_args;
	va_start( var_args, rb_arg_to_pass );
	
		while ( rb_arg_to_pass != Qnil )	{
			
			rb_ary_push(	rb_args_to_pass,
										rb_arg_to_pass );
			
			rb_arg_to_pass = va_arg( var_args, VALUE );
		}
	
	va_end( var_args );

	rarg_hash_iterator_passed_args_type_t	rb_passed_info;
	rb_passed_info.c_function						=	c_function;
	rb_passed_info.rb_self							=	parse_descriptor->rb_self;
	rb_passed_info.rb_passed_args				=	rb_args_to_pass;
	rb_passed_info.rb_return_receiver		= rb_hash_new();

	do {

		rb_hash_foreach(	rb_hash,	
											RARG_parse_IterateHashFunctionForKeyValue, 
											(VALUE) & rb_passed_info );

		/* remaining args are hashes */
	} while ( RI_NextArg( parse_descriptor, rb_hash ) );

	
	return rb_passed_info.rb_return_receiver;
}

/**************************************
*  RARG_parse_IterateArrayDescriptor  *
**************************************/

VALUE RARG_parse_IterateArrayDescriptor(	rarg_parse_descriptor_t*					parse_descriptor,
																					VALUE															rb_array,
																					VALUE															c_function(		int			argc,
																																													VALUE*	args,
																																													VALUE		rb_self ),
																					VALUE															rb_arg_to_pass, ... )	{

	VALUE	rb_return	=	rb_ary_new();

	//	collect passed args into ruby array
	VALUE		rb_args_to_pass	=	rb_ary_new();

	va_list	var_args;
	va_start( var_args, rb_arg_to_pass );
	
		while ( rb_arg_to_pass != Qnil )	{
			
			rb_ary_push(	rb_args_to_pass,
										rb_arg_to_pass );
			
			rb_arg_to_pass = va_arg( var_args, VALUE );
		}
	
	va_end( var_args );

	//	if we have passed args we pass: passed args, ..., *array_splat
	if ( RARRAY_LEN( rb_args_to_pass ) )	{
		
		rb_array	=	rb_ary_concat(	rb_args_to_pass,
																rb_array );
	}

	do {

		VALUE	rb_this_return	=	c_function(	RARRAY_LEN( rb_array ),
																				RARRAY_PTR( rb_array ),
																				parse_descriptor->rb_self );

		rb_ary_push(	rb_return, 
									rb_this_return );
		
		/* remaining args are arrays */
	} while ( RI_NextArg( parse_descriptor, rb_array ) );
	
	return rb_return;
}

/**************************************
*  RARG_parse_IterateArrayDescriptor  *
**************************************/

static int RARG_parse_IterateHashFunctionForKeyValue(	VALUE	rb_key,
																											VALUE	rb_data,
																											VALUE	rb_passed_args )	{
	
	//	rb_passed_args is not actually a VALUE
	//	it is actually a pointer to a struct, which holds our actual value
	
	rarg_hash_iterator_passed_args_type_t*	rb_passed_info	=	(rarg_hash_iterator_passed_args_type_t*) rb_passed_args;
	
	VALUE	rb_additional_args	=	rb_ary_new();
	rb_ary_push(	rb_additional_args,
								rb_key );
	rb_ary_push(	rb_additional_args,
								rb_data );
	
	rb_passed_info->rb_passed_args	=	rb_ary_concat(	rb_passed_info->rb_passed_args,
																										rb_additional_args );
			
	VALUE		rb_return_value		=	rb_passed_info->c_function(	RARRAY_LEN( rb_passed_info->rb_passed_args ),
																													RARRAY_PTR( rb_passed_info->rb_passed_args ),
																													rb_passed_info->rb_self );

	rb_hash_aset(	rb_passed_info->rb_return_receiver,
								rb_key,
								rb_return_value );
	
	return ST_CONTINUE;
}
