#ifndef RB_ARG_PARSER_TYPES
	#define RB_ARG_PARSER_TYPES

	#include <ruby.h>
	
	//------------------------------------------------------------------------------//
	
	#ifndef FALSE
		#define FALSE 0
	#endif
	#ifndef TRUE
		#define TRUE 1
	#endif
	#ifndef BOOL
		typedef int BOOL;
	#endif
	#define RARG_CONTINUE -1

	//------------------------------------------------------------------------------//

	extern VALUE rb_block_lambda( void );

	//------------------------------------------------------------------------------//
	
	enum rarg_types_e	{
	
    R_TERMINAL							= 0,
		
    R_MODULE								= 0x1,
    R_CLASS									= 0x2,
    R_NIL										= 0x4,
    R_OBJECT								= 0x8,
    R_DATA									= 0x10,
    R_STRUCT								= 0x20,

    R_ARRAY									= 0x40,
    R_HASH									= 0x80,

    R_FIXNUM								= 0x100,
    R_BIGNUM								= 0x200,
    R_FLOAT									= 0x400,
    R_COMPLEX								= 0x800,
    R_RATIONAL							= 0x1000,

    R_REGEXP								= 0x2000,
    R_FILE									= 0x4000,
    R_MATCH									= 0x8000,

    R_STRING								= 0x10000,
    R_SYMBOL								= 0x20000,

    R_TRUE									= 0x40000,
    R_FALSE									= 0x80000,
		
		R_META									=	R_MODULE | R_CLASS,
		R_INSTANCE							=	R_STRUCT | R_OBJECT | R_DATA,
		R_STRING_SYMBOL					=	R_STRING | R_SYMBOL,
		R_TEXT									=	R_STRING_SYMBOL | R_REGEXP | R_MATCH,
		R_NUMBER								=	R_FIXNUM | R_BIGNUM	| R_FLOAT | R_COMPLEX | R_RATIONAL,
		R_TRUE_FALSE						=	R_TRUE | R_FALSE,
		R_BUCKET								=	R_ARRAY | R_HASH,
		R_ANY										=	R_NIL
															| R_FILE
															| R_META
															| R_INSTANCE
															| R_TEXT
															| R_NUMBER
															| R_TRUE_FALSE
															| R_BUCKET,
		R_NOT_NIL								=	R_ANY - R_NIL,
		R_NOT_TRUE_FALSE				=	R_ANY - R_TRUE_FALSE,
		R_NOT_TRUE_FALSE_NIL		=	R_NOT_TRUE_FALSE - R_NIL
		
	};

	//------------------------------------------------------------------------------//
														/*  Typedefs  */
	//------------------------------------------------------------------------------//

	typedef struct	rarg_parse_descriptor_s											rarg_parse_descriptor_t;

	typedef struct	rarg_possible_group_match_s									rarg_possible_group_match_t;

	typedef enum		rarg_types_e																rarg_type_t;
	typedef enum		rarg_possible_match_type_e									rarg_possible_match_type_t;

	typedef struct	rarg_description_s													rarg_description_t;

	typedef struct	rarg_parameter_set_s												rarg_parameter_set_t;
	typedef struct	rarg_parameter_s														rarg_parameter_t;

	typedef struct	rarg_possible_match_s												rarg_possible_match_t;
	typedef union		rarg_possible_match_frame_u									rarg_possible_match_frame_t;

	typedef struct	rarg_hash_iterator_passed_args_type_s										rarg_hash_iterator_passed_args_type_t;

	//------------------------------------------------------------------------------//
	
	/*--------.
	|  Block  |
	.--------*/
	
	typedef struct	rarg_possible_block_match_s									rarg_possible_block_match_t;
	typedef struct	rarg_possible_block_match_arity_s						rarg_possible_block_match_arity_t;

	/*-------.
	|  Hash  |
	.-------*/

	typedef struct	rarg_possible_hash_match_s									rarg_possible_hash_match_t;
	typedef struct	rarg_possible_hash_key_data_match_s					rarg_possible_hash_key_data_match_t;
	typedef struct	rarg_possible_hash_index_match_s						rarg_possible_hash_index_match_t;

	/*------------.
	|  Ancestors  |
	.------------*/

	typedef struct	rarg_possible_ancestor_matches_s						rarg_possible_ancestor_matches_t;

	/*----------.
	|  Methods  |
	.----------*/

	typedef struct rarg_possible_method_match_s									rarg_possible_method_match_t;
	typedef struct rarg_possible_method_response_match_s				rarg_possible_method_response_match_t;

	/*-------.
	|  Type  |
	.-------*/

	typedef struct	rarg_possible_type_match_s									rarg_possible_type_match_t;

	/*------------.
	|  If / Else  |
	.------------*/

	typedef enum rarg_possible_condition_match_type_e	rarg_possible_condition_match_type_t;
	typedef struct rarg_possible_if_else_match_s	rarg_possible_if_else_match_t;
	typedef union rarg_possible_if_else_match_type_u	rarg_possible_if_else_match_type_t;
	typedef struct rarg_possible_condition_if_else_value_match_s	rarg_possible_condition_if_else_value_match_t;
	typedef struct rarg_possible_if_else_match_match_s	rarg_possible_if_else_match_match_t;

	//------------------------------------------------------------------------------//
	
	typedef struct	rarg_matched_parameter_set_s								rarg_matched_parameter_set_t;
	typedef struct	rarg_matched_parameter_s										rarg_matched_parameter_t;

	//------------------------------------------------------------------------------//
										/*  Definition Frame Types  */
	//------------------------------------------------------------------------------//

	enum rarg_possible_match_type_e	{
	
		RARG_UNKNOWN,
		RARG_GROUP,
		RARG_BLOCK,
		RARG_HASH,
		RARG_ANCESTOR,
		RARG_METHOD,
		RARG_INDEX,
		RARG_TYPE,
		RARG_IF_ELSE
		
	};

	//------------------------------------------------------------------------------//
										/*  Description Structs  */
	//------------------------------------------------------------------------------//

	struct rarg_parse_descriptor_s	{
		
		int																		argc;
		VALUE*																args;
		int																		args_parsed;

		VALUE																	rb_self;

		int																		matched_parameter_set_index;
		rarg_matched_parameter_set_t*					matched_parameter_set;
		rarg_matched_parameter_t**						matched_parameter_ptr;
		
	};

	struct rarg_description_s	{

		int																		order_ranking;
		char*																	description;

		rarg_description_t*										next;

	};
	
	//------------------------------------------------------------------------------//
												/*  Definition Structs  */
	//------------------------------------------------------------------------------//

	//	descriptions allow in-line definition of argument format to be printed in error
	//	message if no condition matches
	//	descriptions can grow in two directions:	multiple descriptions, multiple descriptions
	//																					(each of which can have multiple descriptions)
	struct rarg_parameter_set_s	{

		rarg_parameter_t*											parameters;
		BOOL																	require_exact;

		rarg_description_t*										description;

		rarg_parameter_set_t*									next;

	};
	
	struct rarg_parameter_s	{

		rarg_possible_match_t*								possible_match;

		BOOL																	optional;

		rarg_description_t*										description;

		rarg_parameter_t*											next;

	};

	struct rarg_possible_match_s	{		

		rarg_possible_match_type_t						type;

		BOOL																	optional;

		rarg_possible_match_frame_t*					possible;
		
		VALUE*																receiver;

		rarg_description_t*										description;

		rarg_possible_match_t*								next;

	};

	union rarg_possible_match_frame_u	{
	
		rarg_possible_group_match_t*							group;

		rarg_possible_block_match_t*							block;
		rarg_possible_hash_match_t*								hash;		
		rarg_possible_ancestor_matches_t*					ancestors;
		rarg_possible_method_match_t*							methods;
		rarg_possible_type_match_t*								types;
		rarg_possible_if_else_match_t*						if_else;
	};

	//------------------------------------------------------------------------------//
												/*  Definition Type Structs  */
	//------------------------------------------------------------------------------//

	struct rarg_possible_group_match_s	{
	
		rarg_possible_match_t*											match;

		rarg_possible_group_match_t*								next;
		
	};

	struct rarg_possible_block_match_s	{
	
		BOOL																				lambda_instead_of_proc;
		rarg_possible_block_match_arity_t*					possible_arity;
		
	};
	
	struct rarg_possible_hash_match_s	{	
		
		rarg_possible_hash_index_match_t*						possible_index_match;
		rarg_possible_hash_key_data_match_t*				possible_key_match;
		rarg_possible_hash_key_data_match_t*				possible_data_match;
		
	};

	struct rarg_possible_ancestor_matches_s	{
	
		VALUE																				ancestor;
		rarg_possible_ancestor_matches_t*						next;

	};

	struct rarg_possible_type_match_s	{

		rarg_type_t																	type;

	};

	struct rarg_possible_condition_match_s	{

		rarg_possible_if_else_match_t*			condition;

	};

	//------------------------------------------------------------------------------//
										/*  Definition Type Support Structs  */
	//------------------------------------------------------------------------------//

	struct rarg_possible_hash_key_data_match_s	{
		
		rarg_possible_match_t*											possible_match;
		BOOL																				assign_parent_hash_for_match;
		
	};

	struct rarg_possible_hash_index_match_s	{
		
		char*																				index_name;				
		BOOL																				optional;
		rarg_possible_match_t*											possible_index_data_match;
		BOOL																				assign_parent_hash_for_match;
		VALUE*																			receiver;
		
		rarg_possible_hash_index_match_t*						next;
		
	};

	struct rarg_possible_block_match_arity_s	{
	
		int																					arity;
		rarg_possible_block_match_arity_t*					next;

	};

	//------------------------------------------------------------------------------//
													/*  Conditional Matching  */
	//------------------------------------------------------------------------------//

	enum rarg_possible_condition_match_type_e	{
		
		RARG_CONDITION_UNKNOWN,
		RARG_CONDITION_IF_VALUE,
		RARG_CONDITION_IF_MATCH,
		RARG_CONDITION_ELSE_IF_VALUE,
		RARG_CONDITION_ELSE_IF_MATCH,
		RARG_CONDITION_ELSE_MATCH
		
	};

	struct rarg_possible_if_else_match_s	{

		rarg_possible_condition_match_type_t			type;

		rarg_possible_if_else_match_type_t*				possible;
				
		rarg_possible_if_else_match_t*						next;

	};

	union rarg_possible_if_else_match_type_u	{

		rarg_possible_condition_if_else_value_match_t*	value;
		rarg_possible_if_else_match_match_t*						match;
	};

	//	if variable is set to value, attempt to match action
	struct rarg_possible_condition_if_else_value_match_s	{
	
		VALUE*																				variable;
		VALUE																					value;
		rarg_possible_match_t*												action;

	};

	//	if condition matches, attempt to match action
	struct rarg_possible_if_else_match_match_s	{
	
		rarg_possible_match_t*												condition;
		rarg_possible_match_t*												action;

	};

	//------------------------------------------------------------------------------//
													/*  Method Return Matching  */
	//------------------------------------------------------------------------------//

	struct rarg_possible_method_match_s	{
	
		ID																						method;
		//	not yet implemented
		rarg_possible_block_match_arity_t*						arity;
		//	not yet implemented
		int																						argc;
		//	not yet implemented
		VALUE*																				args;
		BOOL																					ensure_return_non_nil;
		rarg_possible_method_response_match_t*				possible_return;
		rarg_possible_method_match_t*									next;

	};

	struct rarg_possible_method_response_match_s	{
	
		VALUE																					value;
		rarg_possible_method_response_match_t*				next;
		
	};
		
	//------------------------------------------------------------------------------//
															/*  Hash Iteration  */
	//------------------------------------------------------------------------------//

	struct rarg_hash_iterator_passed_args_type_s	{
	
		VALUE			(*c_function)(		int			argc,
																VALUE*	args,
																VALUE		rb_self );
		VALUE			rb_self;
		VALUE			rb_passed_args;
		VALUE			rb_return_receiver;

	};

	//------------------------------------------------------------------------------//
												/*  Matched Parameter Structs  */
	//------------------------------------------------------------------------------//

	/*********************************
	*  Matched Parameter Set Struct  *
	*********************************/
	
	struct rarg_matched_parameter_set_s	{

		rarg_matched_parameter_t*					parameters;
		int																last_arg;

	};

	/*****************************
	*  Matched Parameter Struct  *
	*****************************/
	
	struct rarg_matched_parameter_s	{

		VALUE															match;
		VALUE*														receiver;
		BOOL															block_match;
		rarg_matched_parameter_t*					next;

	};

#endif