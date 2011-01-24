#include "include/rargs/rargs_define.h"
#include "include/rargs/rargs_error.h"

/***********************************************************************************************************************
                                          Parameter Sets
***********************************************************************************************************************/

/************************
*  defineParameterSets  *
************************/

rarg_parameter_set_t* RARG_define_ParameterSets( rarg_parameter_set_t* parameter_set, ... )  {  

  rarg_parameter_set_t*    root_parameter_set  =  parameter_set;
  rarg_parameter_set_t**  this_parameter_set  =  & root_parameter_set;

  //  for each possible type, create FIFO chain in root_possible_match
  va_list  var_args;
  va_start( var_args, parameter_set );
  
    while ( parameter_set != NULL )  {
      
      //  make sure parameter sets are chained together at the end; it is possible we get chains of parameter sets
      if ( parameter_set != *this_parameter_set )  {
        while ( *this_parameter_set != NULL )  {
          this_parameter_set              =  & ( *this_parameter_set )->next;
        }
        *this_parameter_set = parameter_set;
        this_parameter_set  =  & ( *this_parameter_set )->next;
      }
      
      parameter_set = va_arg( var_args, rarg_parameter_set_t* );
    }
  
  va_end( var_args );
  
  return root_parameter_set;
}

/***********************
*  defineParameterSet  *
***********************/

rarg_parameter_set_t* RARG_define_ParameterSet( rarg_parameter_t* parameter, ... )  {  

  rarg_parameter_set_t*  parameter_set      =  calloc( 1, sizeof( rarg_parameter_set_t ) );
  rarg_parameter_t**    this_parameter    =  & parameter_set->parameters;
  
  va_list  var_args;
  va_start( var_args, parameter );
  
    while ( parameter != NULL )  {

      //  make sure parameter are chained together at the end; it is possible we get chains of parameter
      while ( *this_parameter != NULL )  {
        this_parameter  =  & ( *this_parameter )->next;
      }
      *this_parameter = parameter;

      parameter = va_arg( var_args, rarg_parameter_t* );
    }
  
  va_end( var_args );
  
  return parameter_set;
}


/********************
*  defineParameter  *
********************/

rarg_parameter_t* RARG_define_Parameter( rarg_possible_match_t* possible_match, ... )  {

  rarg_parameter_t*        parameter              =  calloc( 1, sizeof( rarg_parameter_t ) );
  rarg_possible_match_t**  this_possible_match    =  & parameter->possible_match;

  //  for each possible match, create FIFO chain in parameter
  va_list  var_args;
  va_start( var_args, possible_match );
  
    while ( possible_match != NULL )  {
      
      //  make sure possible matches are chained together at the end; it is possible we get chains of possible matches
      while ( *this_possible_match != NULL )  {
        this_possible_match = & ( *this_possible_match )->next;
      }
      *this_possible_match  =  possible_match;
      
      possible_match = va_arg( var_args, rarg_possible_match_t* );
    }
  
  va_end( var_args );
  
  return parameter;
}

/***********************************************************************************************************************
                                          Possible Match Types
***********************************************************************************************************************/

/**********************************
*  RARG_define_PossibleGroupMatch  *
**********************************/

rarg_possible_match_t* RARG_define_PossibleGroupMatch( rarg_possible_match_t* possible_match, ... )  {

  rarg_possible_match_t*  possible_group_match    = NULL;  
  RI_CreatePossibleMatch( possible_group_match );
  RI_AssignPossibleMatchType( possible_group_match, RARG_GROUP );
  rarg_possible_group_match_t**  this_possible_match      =  & possible_group_match->possible->group;

  va_list  var_args;
  va_start( var_args, possible_match );

    while( possible_match != NULL )  {
      
      if ( *this_possible_match != NULL )  {
        this_possible_match  =  & ( *this_possible_match )->next;
      }
      *this_possible_match  =  RI_AllocPossibleGroupMatch();
      ( *this_possible_match )->match = possible_match;

      possible_match = va_arg( var_args, rarg_possible_match_t* );
    }
    
  va_end( var_args );  

  return possible_group_match;
}

/**********************************
*  RARG_define_PossibleTypeMatch  *
**********************************/

rarg_possible_match_t* RARG_define_PossibleTypeMatch( rarg_type_t type, ... )  {
  
  rarg_possible_match_t* possible_type_match;
  RI_CreatePossibleMatchWithType( possible_type_match );
  
  //  | together types
  va_list  var_args;
  va_start( var_args, type );

    while ( type )  {
    
      if ( possible_type_match->possible->types->type )  {
        possible_type_match->possible->types->type  |=  type;
      }
      else {
        possible_type_match->possible->types->type  =    type;
      }

      type = va_arg( var_args, rarg_type_t );
    }
  
  va_end( var_args );

  return possible_type_match;
}

/**************************************
*  RARG_define_PossibleAncestorMatch  *
**************************************/

rarg_possible_match_t* RARG_define_PossibleAncestorMatch( char* c_class_name, ... )  {

  rarg_possible_match_t*              possible_ancestors_match    = NULL;  
  RI_CreatePossibleMatch( possible_ancestors_match );
  RI_AssignPossibleMatchType( possible_ancestors_match, RARG_ANCESTOR );
  rarg_possible_ancestor_matches_t**  this_possible_ancestor_match      =  & possible_ancestors_match->possible->ancestors;

  va_list  var_args;
  va_start( var_args, c_class_name );

    while( c_class_name != NULL )  {
      
      if ( *this_possible_ancestor_match )  {
        this_possible_ancestor_match  =  & ( *this_possible_ancestor_match )->next;
      }
      *this_possible_ancestor_match  =  RI_AllocPossibleAncestorMatch();
      
      ID  constant_id  =  rb_intern( c_class_name );
      
      VALUE  rb_class_instance  =  rb_const_get(  rb_cObject, constant_id );

      ( *this_possible_ancestor_match )->ancestor = rb_class_instance;

      c_class_name = va_arg( var_args, char* );
    }
    
  va_end( var_args );
  
  return possible_ancestors_match;
}

/**************************************
*  RARG_define_PossibleAncestorMatch  *
**************************************/

rarg_possible_match_t* RARG_define_PossibleAncestorInstanceMatch( VALUE rb_class_instance, ... )  {

  rarg_possible_match_t*              possible_ancestors_match    = NULL;  
  RI_CreatePossibleMatch( possible_ancestors_match );
  RI_AssignPossibleMatchType( possible_ancestors_match, RARG_ANCESTOR );
  rarg_possible_ancestor_matches_t**  this_possible_ancestor_match      =  & possible_ancestors_match->possible->ancestors;

  va_list  var_args;
  va_start( var_args, rb_class_instance );

    while( rb_class_instance != R_TERMINAL )  {
      
      if ( *this_possible_ancestor_match != NULL )  {
        this_possible_ancestor_match  =  & ( *this_possible_ancestor_match )->next;
      }
      *this_possible_ancestor_match  =  RI_AllocPossibleAncestorMatch();
      
      ( *this_possible_ancestor_match )->ancestor = rb_class_instance;

      rb_class_instance = va_arg( var_args, VALUE );
    }
    
  va_end( var_args );
  
  return possible_ancestors_match;
}

/**********************************
*  RARG_define_PossibleHashMatch  *
**********************************/

rarg_possible_match_t* RARG_define_PossibleHashMatch(  rarg_possible_hash_key_data_match_t*  possible_key_match, 
                                                      rarg_possible_hash_key_data_match_t*  possible_data_match )  {

  rarg_possible_match_t*          possible_hash_match    = NULL;  
  RI_CreatePossibleMatchWithHash( possible_hash_match );

  possible_hash_match->possible->hash->possible_key_match      =  possible_key_match;
  possible_hash_match->possible->hash->possible_data_match    =  possible_data_match;

  return possible_hash_match;
}

  /*************************************************
  *  RARG_define_PossibleHashMatch_KeyOrDataMatch  *
  *************************************************/

  rarg_possible_hash_key_data_match_t* RARG_define_PossibleHashMatch_KeyOrDataMatch( rarg_possible_match_t* possible_match, ... )  {

    rarg_possible_match_t*		root_possible_match  =  NULL;
    rarg_possible_match_t**		this_possible_match  =  & root_possible_match;

    //  for each possible type, create FIFO chain in root_possible_match
    va_list  var_args;
    va_start( var_args, possible_match );
    
      while ( possible_match != NULL )  {
        
        //  make sure possible matches are chained together at the end; it is possible we get chains of possible matches
        if ( possible_match != *this_possible_match )  {
          while ( *this_possible_match != NULL )  {
            this_possible_match    =  & ( *this_possible_match )->next;
          }
          *this_possible_match  = possible_match;
          this_possible_match    =  & ( *this_possible_match )->next;
        }
        
        possible_match = va_arg( var_args, rarg_possible_match_t* );
      }
    
    va_end( var_args );
    
    rarg_possible_hash_key_data_match_t*  possible_hash_key_or_data_match  =  calloc( 1, sizeof( rarg_possible_hash_key_data_match_t ) );
    
    possible_hash_key_or_data_match->possible_match  =  root_possible_match;
    
    return possible_hash_key_or_data_match;
  }

  /***********************************************
  *  RARG_define_PossibleHashMatch_indexesMatch  *
  ***********************************************/

  rarg_possible_match_t* RARG_define_PossibleHashMatch_indexesMatch(  char*  c_index, ... )  {
    
    rarg_possible_match_t*              possible_index_match    = NULL;  
    RI_CreatePossibleMatch( possible_index_match );
    RI_AssignPossibleMatchType( possible_index_match, RARG_INDEX );
    possible_index_match->possible->hash  =  RI_AllocPossibleHashMatch();

    rarg_possible_hash_index_match_t*    possible_hash_indexes    =  NULL;
    rarg_possible_hash_index_match_t**  this_index_match        =  & possible_hash_indexes;

    va_list  var_args;
    va_start( var_args, c_index );

      while( c_index != NULL )  {
        
        //  use instance function to define
        if (    *this_index_match != NULL
            &&  ( *this_index_match )->index_name != NULL )  {
          this_index_match  =  & ( *this_index_match )->next;
        }
        *this_index_match  =  calloc( 1, sizeof( rarg_possible_hash_index_match_t ) );
        ( *this_index_match )->index_name  =  c_index;
        
        c_index = va_arg( var_args, char* );
      }
      
    va_end( var_args );
    
    possible_index_match->possible->hash->possible_index_match  =  possible_hash_indexes;
    return possible_index_match;
  }

  /***********************************************
  *  RARG_define_PossibleHashMatch_indexesMatch  *
  ***********************************************/

  rarg_possible_match_t* RARG_define_PossibleHashMatch_indexesMatch_dataMatch(  rarg_possible_match_t*        possible_hash_index_match, 
                                                                                rarg_possible_match_t*        possible_data_match, ... )  {
  
    rarg_possible_match_t**  this_possible_data  =  & possible_hash_index_match->possible->hash->possible_index_match->possible_index_data_match;
  
    va_list  var_args;
    va_start( var_args, possible_data_match );

      while( possible_data_match != NULL )  {
        
        while ( *this_possible_data != NULL )  {
          this_possible_data  =  & ( *this_possible_data )->next;
        }
        *this_possible_data  =  possible_data_match;
        
        possible_data_match = va_arg( var_args, rarg_possible_match_t* );
      }
      
    va_end( var_args );
  
    return possible_hash_index_match;
  }

/********************************
*  RARG_define_ProcMatch  *
********************************/

rarg_possible_match_t* RARG_define_ProcMatch()  {

  rarg_possible_match_t*            possible_block_proc_match    = NULL;  
  RI_CreatePossibleMatchWithProc(  possible_block_proc_match );

  possible_block_proc_match->possible->block->arg_not_block  =  TRUE;

  return possible_block_proc_match;
}

/**********************************
*  RARG_define_LambdaMatch  *
**********************************/

rarg_possible_match_t* RARG_define_LambdaMatch()  {

  rarg_possible_match_t*  possible_lambda_match  =  RARG_define_ProcMatch();
  
  possible_lambda_match->possible->block->lambda_instead_of_proc  =  TRUE;
  
  return possible_lambda_match;
}
  
/********************************
*  RARG_define_Block_procMatch  *
********************************/

rarg_possible_match_t* RARG_define_Block_procMatch()  {

  rarg_possible_match_t*            possible_block_proc_match    = NULL;  
  RI_CreatePossibleMatchWithBlock(  possible_block_proc_match );

  return possible_block_proc_match;
}

/**********************************
*  RARG_define_Block_lambdaMatch  *
**********************************/

rarg_possible_match_t* RARG_define_Block_lambdaMatch()  {

  rarg_possible_match_t*  possible_lambda_match  =  RARG_define_Block_procMatch();
  
  possible_lambda_match->possible->block->lambda_instead_of_proc  =  TRUE;
  
  return possible_lambda_match;
}

/***************************************
*  RARG_define_PossibleConditionMatch  *
***************************************/

//  if => if == if && if
//  if => else
//  if => else if => else
rarg_possible_match_t* RARG_define_PossibleIfElseMatch( rarg_possible_if_else_match_t* possible_if_else_match, ... )  {

  rarg_possible_match_t*      possible_match    = NULL;  
  RI_CreatePossibleMatch( possible_match );
  RI_AssignPossibleMatchType( possible_match, RARG_IF_ELSE );
  rarg_possible_if_else_match_t**  this_possible_if_else_match      =  & possible_match->possible->if_else;

  va_list  var_args;
  va_start( var_args, possible_if_else_match );

    while( possible_if_else_match != NULL )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_if_else_match != NULL )  {
        this_possible_if_else_match  =  & ( *this_possible_if_else_match )->next;
      }
      *this_possible_if_else_match  =  possible_if_else_match;

      possible_if_else_match = va_arg( var_args, rarg_possible_if_else_match_t* );
    }
    
  va_end( var_args );
  
  return possible_match;
}

  /**********************************************
  *  RARG_define_PossibleIfMatchMatch  *
  **********************************************/

  rarg_possible_if_else_match_t* RARG_define_PossibleIfMatchMatch( rarg_possible_match_t*  possible_match_condition,
                                                                    rarg_possible_match_t*  possible_match_action    )  {

    rarg_possible_if_else_match_t*  possible_if_else_match  =  RI_AllocPossibleIfElseMatch();
    
    possible_if_else_match->type  =  RARG_CONDITION_IF_MATCH;
    possible_if_else_match->possible  =  RI_AllocPossibleIfElseMatch();
    possible_if_else_match->possible->match  =  RI_AllocPossibleIfElsePossibleMatch();
    possible_if_else_match->possible->match->condition    =  possible_match_condition;
    possible_if_else_match->possible->match->action        =  possible_match_action;
    
    return possible_if_else_match;
  }

  /**********************************************
  *  RARG_define_PossibleIfValueMatch  *
  **********************************************/

  rarg_possible_if_else_match_t* RARG_define_PossibleIfValueMatch( VALUE*                  possible_match_variable,
                                                                            VALUE                    possible_match_value,
                                                                            rarg_possible_match_t*  possible_match_action )  {

    rarg_possible_if_else_match_t*  possible_if_else_match  =  RI_AllocPossibleIfElseMatch();
    
    possible_if_else_match->type  =  RARG_CONDITION_IF_VALUE;

    possible_if_else_match->possible                    =  RI_AllocPossibleIfElsePossibleMatch();
    
    possible_if_else_match->possible->value              =  RI_AllocPossibleIfElseValueMatch();
    
    possible_if_else_match->possible->value->variable    =  possible_match_variable;
    possible_if_else_match->possible->value->value      =  possible_match_value;
    possible_if_else_match->possible->value->action      =  possible_match_action;
    
    return possible_if_else_match;
  }

  /**********************************************
  *  RARG_define_PossibleIfMatchMatch  *
  **********************************************/

  rarg_possible_if_else_match_t* RARG_define_PossibleElseIfMatchMatch( rarg_possible_match_t*  possible_match_condition,
                                                                                rarg_possible_match_t*  possible_match_action    )  {

    rarg_possible_if_else_match_t*  possible_if_else_match  =  RI_AllocPossibleIfElseMatch();
    
    possible_if_else_match->type  =  RARG_CONDITION_ELSE_IF_MATCH;
    possible_if_else_match->possible                      =  RI_AllocPossibleIfElsePossibleMatch();
    possible_if_else_match->possible->match                =  RI_AllocPossibleIfElseMatchMatch();
    possible_if_else_match->possible->match->condition    =  possible_match_condition;
    possible_if_else_match->possible->match->action        =  possible_match_action;
    
    return possible_if_else_match;
  }

  /**********************************************
  *  RARG_define_PossibleIfValueMatch  *
  **********************************************/

  rarg_possible_if_else_match_t* RARG_define_PossibleElseIfValueMatch( VALUE*                  possible_match_variable,
                                                                                VALUE                    possible_match_value,
                                                                                rarg_possible_match_t*  possible_match_action )  {

    rarg_possible_if_else_match_t*  possible_if_else_match  =  RI_AllocPossibleIfElseMatch();
    
    possible_if_else_match->type  =  RARG_CONDITION_ELSE_IF_VALUE;
    possible_if_else_match->possible  =  RI_AllocPossibleIfElseMatch();
    possible_if_else_match->possible->value  =  RI_AllocPossibleIfElseValueMatch();
    possible_if_else_match->possible->value->variable    =  possible_match_variable;
    possible_if_else_match->possible->value->value      =  possible_match_value;
    possible_if_else_match->possible->value->action      =  possible_match_action;
    
    return possible_if_else_match;
  }

  /**********************************************
  *  RARG_define_PossibleIfMatchMatch  *
  **********************************************/

  rarg_possible_if_else_match_t* RARG_define_PossibleElseMatch(  rarg_possible_match_t*  possible_match_action    )  {

    rarg_possible_if_else_match_t*  possible_if_else_match  =  RI_AllocPossibleIfElseMatch();
    
    possible_if_else_match->type  =  RARG_CONDITION_ELSE_MATCH;
    possible_if_else_match->possible                      =  RI_AllocPossibleIfElseMatch();
    possible_if_else_match->possible->match                =  RI_AllocPossibleIfElseMatchMatch();
    possible_if_else_match->possible->match->action        =  possible_match_action;
    
    return possible_if_else_match;
  }

/**********************************************
*  RARG_define_PossibleMethodResponds  *
**********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodResponds(  char*  method_name, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  rarg_possible_method_match_t**  this_possible_method_match      =  & possible_method_return_match->possible->methods;

  va_list  var_args;
  va_start( var_args, method_name );

    while( method_name != NULL )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_match != NULL )  {
        this_possible_method_match  =  & ( *this_possible_method_match )->next;
      }
      *this_possible_method_match  =  RI_AllocPossibleMethodMatch();      

      ( *this_possible_method_match )->method = rb_intern( method_name );

      method_name = va_arg( var_args, char* );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/**********************************************
*  RARG_define_PossibleMethodReturns  *
**********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturns(  char*                    method_name, 
                                                          VALUE                    possible_method_return, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();
  possible_method_return_match->possible->methods->object = Qnil;
  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  rarg_possible_method_response_match_t**  this_possible_method_response_match      =  & possible_method_return_match->possible->methods->possible_return;
  
  va_list  var_args;
  va_start( var_args, possible_method_return );

    while( possible_method_return != Qnil )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_response_match != NULL )  {
        this_possible_method_response_match  =  & ( *this_possible_method_response_match )->next;
      }
      *this_possible_method_response_match  =  RI_AllocPossibleMethodReturnMatch();      

      ( *this_possible_method_response_match )->value = possible_method_return;

      possible_method_return = va_arg( var_args, VALUE );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/**********************************************
*  RARG_define_PossibleMethodReturns  *
**********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturnsWithArgs(  char*                    method_name, 
                                                                  int                      argc,
                                                                  VALUE*                  args,
                                                                  VALUE                    possible_method_return, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();
  possible_method_return_match->possible->methods->object = Qnil;
  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  possible_method_return_match->possible->methods->argc = argc;
  possible_method_return_match->possible->methods->args = args;
  rarg_possible_method_response_match_t**  this_possible_method_response_match      =  & possible_method_return_match->possible->methods->possible_return;
  
  va_list  var_args;
  va_start( var_args, possible_method_return );

    while( possible_method_return != Qnil )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_response_match != NULL )  {
        this_possible_method_response_match  =  & ( *this_possible_method_response_match )->next;
      }
      *this_possible_method_response_match  =  RI_AllocPossibleMethodReturnMatch();      

      ( *this_possible_method_response_match )->value = possible_method_return;

      possible_method_return = va_arg( var_args, VALUE );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/**********************************************
*  RARG_define_PossibleMethodReturnsNonNil  *
**********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodsReturnNonNil(  char* method_name, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  rarg_possible_method_match_t**  this_possible_method_match      =  & possible_method_return_match->possible->methods;
  
  va_list  var_args;
  va_start( var_args, method_name );

    while( method_name != NULL )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_match != NULL )  {
        this_possible_method_match  =  & ( *this_possible_method_match )->next;
      }
      *this_possible_method_match  =  RI_AllocPossibleMethodMatch();      

      ( *this_possible_method_match )->method = rb_intern( method_name );
      ( *this_possible_method_match )->ensure_return_non_nil = TRUE;

      method_name = va_arg( var_args, char* );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/********************************************
*  RARG_define_PossibleMethodReturnsNonNil  *
********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturnsNonNilWithArgs(  char*    method_name,
                                                                        int      argc,
                                                                        VALUE*  args )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();      

  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  possible_method_return_match->possible->methods->argc = argc;
  possible_method_return_match->possible->methods->args = args;
  possible_method_return_match->possible->methods->ensure_return_non_nil = TRUE;

  return possible_method_return_match;  
}

/************************************************
*  RARG_define_PossibleMethodRespondsForObject  *
************************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodRespondsForObject(  VALUE          rb_object,
                                                                    char*          method_name, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  rarg_possible_method_match_t**  this_possible_method_match      =  & possible_method_return_match->possible->methods;

  va_list  var_args;
  va_start( var_args, method_name );

    while( method_name != NULL )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_match != NULL )  {
        this_possible_method_match  =  & ( *this_possible_method_match )->next;
      }
      *this_possible_method_match  =  RI_AllocPossibleMethodMatch();      

      ( *this_possible_method_match )->object = rb_object;
      ( *this_possible_method_match )->method = rb_intern( method_name );

      method_name = va_arg( var_args, char* );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}


/***********************************************
*  RARG_define_PossibleMethodReturnsForObject  *
***********************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturnsForObject(  VALUE                    rb_object,
                                                                    char*                    method_name, 
                                                                    VALUE                    possible_method_return, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();
  possible_method_return_match->possible->methods->object = rb_object;
  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  rarg_possible_method_response_match_t**  this_possible_method_response_match      =  & possible_method_return_match->possible->methods->possible_return;
  
  va_list  var_args;
  va_start( var_args, possible_method_return );

    while( possible_method_return != Qnil )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_response_match != NULL )  {
        this_possible_method_response_match  =  & ( *this_possible_method_response_match )->next;
      }
      *this_possible_method_response_match  =  RI_AllocPossibleMethodReturnMatch();      

      ( *this_possible_method_response_match )->value = possible_method_return;

      possible_method_return = va_arg( var_args, VALUE );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/*******************************************************
*  RARG_define_PossibleMethodReturnsForObjectWithArgs  *
*******************************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturnsForObjectWithArgs(  VALUE                    rb_object,
                                                                            char*                    method_name, 
                                                                            int                      argc,
                                                                            VALUE*                  args,
                                                                            VALUE                    possible_method_return, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();
  possible_method_return_match->possible->methods->object = rb_object;
  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  possible_method_return_match->possible->methods->argc = argc;
  possible_method_return_match->possible->methods->args = args;
  rarg_possible_method_response_match_t**  this_possible_method_response_match      =  & possible_method_return_match->possible->methods->possible_return;
  
  va_list  var_args;
  va_start( var_args, possible_method_return );

    while( possible_method_return != Qnil )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_response_match != NULL )  {
        this_possible_method_response_match  =  & ( *this_possible_method_response_match )->next;
      }
      *this_possible_method_response_match  =  RI_AllocPossibleMethodReturnMatch();      

      ( *this_possible_method_response_match )->value = possible_method_return;

      possible_method_return = va_arg( var_args, VALUE );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/*****************************************************
*  RARG_define_PossibleMethodsReturnNonNilForObject  *
*****************************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodsReturnNonNilForObject(  VALUE      rb_object,
                                                                          char*      method_name, ... )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  rarg_possible_method_match_t**  this_possible_method_match      =  & possible_method_return_match->possible->methods;

  va_list  var_args;
  va_start( var_args, method_name );

    while( method_name != NULL )  {
      
      //  make sure we are at the end of the current chain
      while ( *this_possible_method_match != NULL )  {
        this_possible_method_match  =  & ( *this_possible_method_match )->next;
      }
      *this_possible_method_match  =  RI_AllocPossibleMethodMatch();      

      ( *this_possible_method_match )->object = rb_object;
      ( *this_possible_method_match )->method = rb_intern( method_name );
      ( *this_possible_method_match )->ensure_return_non_nil = TRUE;

      method_name = va_arg( var_args, char* );
    }
    
  va_end( var_args );

  return possible_method_return_match;  
}

/*************************************************************
*  RARG_define_PossibleMethodReturnsNonNilForObjectWithArgs  *
*************************************************************/
  
rarg_possible_match_t* RARG_define_PossibleMethodReturnsNonNilForObjectWithArgs(  VALUE      rb_object,
                                                                                  char*      method_name,
                                                                                  int        argc,
                                                                                  VALUE*    args )  {

  rarg_possible_match_t*      possible_method_return_match    = NULL;  
  RI_CreatePossibleMatch( possible_method_return_match );
  RI_AssignPossibleMatchType( possible_method_return_match, RARG_METHOD );

  possible_method_return_match->possible->methods  =  RI_AllocPossibleMethodMatch();      

  possible_method_return_match->possible->methods->object = rb_object;
  possible_method_return_match->possible->methods->method = rb_intern( method_name );
  possible_method_return_match->possible->methods->argc = argc;
  possible_method_return_match->possible->methods->args = args;
  possible_method_return_match->possible->methods->ensure_return_non_nil = TRUE;

  return possible_method_return_match;  
}

/***********************************************************************************************************************
                                          Possible Match Options
***********************************************************************************************************************/

  /***********************************************
  *  RARG_define_ParameterSet_requireExactMatch  *
  ***********************************************/

  rarg_parameter_set_t* RARG_define_ParameterSet_requireExactMatch(  rarg_parameter_set_t*    parameter_set, ... )  {  

    rarg_parameter_set_t*    root_parameter_set  =  parameter_set;
    rarg_parameter_set_t**  this_parameter_set  =  & parameter_set;
    
    va_list  var_args;
    va_start( var_args, parameter_set );

      while ( parameter_set != NULL )  {
        parameter_set->require_exact  =  TRUE;
        if ( parameter_set != *this_parameter_set )  {
          while ( ( *this_parameter_set )->next != NULL )  {
            this_parameter_set  =  & ( *this_parameter_set )->next;      
          }
          ( *this_parameter_set )->next  =  parameter_set;
          this_parameter_set  =  & ( *this_parameter_set )->next;
        }
        parameter_set = va_arg( var_args, rarg_parameter_set_t* );
      }
    
    va_end( var_args );  
    
    return root_parameter_set;
  }

  /******************************************
  *  RARG_define_Parameter_setOptional  *
  ******************************************/

  rarg_parameter_t* RARG_define_Parameter_setOptional( rarg_parameter_t*  parameter, ... )  {

    rarg_parameter_t*  root_parameter = parameter;
    
    va_list  var_args;
    va_start( var_args, parameter );

      while ( parameter != NULL )  {
        parameter->optional  =  TRUE;
        parameter = va_arg( var_args, rarg_parameter_t* );
      }
      
    va_end( var_args );
    
    return root_parameter;
  }
    
  /******************************************
  *  RARG_define_PossibleMatch_setOptional  *
  ******************************************/

  rarg_possible_match_t* RARG_define_PossibleMatch_setOptional( rarg_possible_match_t*  possible_match, ... )  {

    rarg_possible_match_t*  root_possible_match  =  possible_match;

    va_list  var_args;
    va_start( var_args, possible_match );

      while ( possible_match != NULL )  {
        possible_match->optional  =  TRUE;
        possible_match = va_arg( var_args, rarg_possible_match_t* );
      }
      
    va_end( var_args );
    
    return root_possible_match;
  }

  /*****************************************
  *  RARG_define_PossibleBlockMatch_arity  *
  *****************************************/

  rarg_possible_match_t* RARG_define_PossibleBlockMatch_arity( rarg_possible_match_t*  possible_match, int arity, ... )  {

    rarg_possible_closure_match_arity_t**  possible_block_arity_match_ptr  =  & possible_match->possible->block->possible_arity;

    va_list  var_args;
    va_start( var_args, arity );
      
      while ( arity != R_TERMINATE_ARITY )  {
        if ( *possible_block_arity_match_ptr != NULL )  {
          //  move to end of any defined arities
          while ( *( possible_block_arity_match_ptr = & ( *possible_block_arity_match_ptr )->next ) != NULL );
        }
        *possible_block_arity_match_ptr = calloc( 1, sizeof( rarg_possible_closure_match_arity_t ) );

        ( *possible_block_arity_match_ptr )->arity  =  arity;
        arity = va_arg( var_args, int );
      }
      
    va_end( var_args );
    
    return possible_match;
  }


/***********************************************************************************************************************
                                              Assignment
***********************************************************************************************************************/
  
  /*******************************************
  *  definePossibleMatch_assignMatchToValue  *
  *******************************************/

  rarg_possible_match_t* RARG_define_PossibleMatch_assignMatchToValue(  rarg_possible_match_t*  possible_match, 
                                                                        VALUE*                  receiver )  {

    possible_match->receiver  =  receiver;

    return possible_match;
  }

  /*********************************************************
  *  definePossibleMatch_assignHashForKeyDataMatchToValue  *
  *********************************************************/

  rarg_possible_hash_key_data_match_t* RARG_define_PossibleMatch_assignHashForKeyDataMatchToValue(  rarg_possible_hash_key_data_match_t*  possible_hash_key_or_data_match, 
                                                                                                    VALUE*                                receiver )  {

    possible_hash_key_or_data_match->assign_parent_hash_for_match    =  TRUE;
    possible_hash_key_or_data_match->possible_match->receiver        =  receiver;

    return possible_hash_key_or_data_match;
  }

  /************************************************
  *  definePossibleMatch_assignIndexMatchToValue  *
  ************************************************/

  rarg_possible_match_t* definePossibleMatch_assignIndexMatchToValue(  rarg_possible_match_t*        possible_index_match, 
                                                                      VALUE*                        receiver )  {

    possible_index_match->possible->hash->possible_index_match->receiver  =  receiver;

    return possible_index_match;
  }

  /******************************************************
  *  definePossibleMatch_assignHashKeyDataMatchToValue  *
  ******************************************************/

  rarg_possible_hash_key_data_match_t* definePossibleMatch_assignHashKeyDataMatchToValue(  rarg_possible_hash_key_data_match_t*    possible_hash_key_data_match, 
                                                                                          VALUE*                                  receiver )  {

    possible_hash_key_data_match->possible_match->receiver  =  receiver;

    return possible_hash_key_data_match;
  }

/***********************************************************************************************************************
                                              Descriptions
***********************************************************************************************************************/

/*****************************************
*  RARG_define_ParameterSet_description  *
*****************************************/

rarg_parameter_set_t* RARG_define_ParameterSet_description(  rarg_parameter_set_t*    parameter_set,
                                                            int                      order_ranking,
                                                            char*                    description, ... )  {  

  rarg_description_t**    this_description  =  & parameter_set->description;
  
  va_list  var_args;
  va_start( var_args, description );

    while ( description != NULL )  {
      
      if ( *this_description == NULL )  {
        *this_description = calloc( 1, sizeof( rarg_description_t ) );
      }
      else if ( *( *this_description )->description != '\0' )  {
        ( *this_description )->next    = calloc( 1, sizeof( rarg_description_t ) );
        this_description              =  & ( *this_description )->next;
      }
      ( *this_description )->description    = description;
      ( *this_description )->order_ranking  = order_ranking;

      description = va_arg( var_args, char* );
    }
  
  va_end( var_args );  
    
  return parameter_set;
}

/**************************************
*  RARG_define_Parameter_description  *
**************************************/

rarg_parameter_t* RARG_define_Parameter_description(  rarg_parameter_t*    parameter,
                                                      int                  order_ranking,
                                                      char*                description, ... )  {  

  rarg_description_t**    this_description  =  & parameter->description;
  
  va_list  var_args;
  va_start( var_args, description );

    while ( description != NULL )  {
      
      if ( *this_description == NULL )  {
        *this_description = calloc( 1, sizeof( rarg_description_t ) );
      }
      else if ( *( *this_description )->description != '\0' )  {
        ( *this_description )->next    = calloc( 1, sizeof( rarg_description_t ) );
        this_description                          =  & ( *this_description )->next;
      }
      ( *this_description )->description    = description;
      ( *this_description )->order_ranking  = order_ranking;

      description = va_arg( var_args, char* );
    }
  
  va_end( var_args );  
    
  return parameter;
}

/******************************************
*  RARG_define_PossibleMatch_description  *
******************************************/

rarg_possible_match_t* RARG_define_PossibleMatch_description(  rarg_possible_match_t*  possible_match,
                                                              int                      order_ranking,
                                                              char*                    description, ... )  {  

  rarg_description_t**    this_description  =  & possible_match->description;
  
  va_list  var_args;
  va_start( var_args, description );

    while ( description != NULL )  {
      
      if ( *this_description == NULL )  {
        *this_description = calloc( 1, sizeof( rarg_description_t ) );
      }
      else if ( *( *this_description )->description != '\0' )  {
        ( *this_description )->next    = calloc( 1, sizeof( rarg_description_t ) );
        this_description                          =  & ( *this_description )->next;
      }
      ( *this_description )->description    = description;
      ( *this_description )->order_ranking  = order_ranking;

      description = va_arg( var_args, char* );
    }
  
  va_end( var_args );  
    
  return possible_match;
}

