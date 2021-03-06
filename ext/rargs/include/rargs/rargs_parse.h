#ifndef RB_RARGS_PARSE
  #define RB_RARGS_PARSE

  #include <ruby.h>
  
  #include "rargs_types.h"
  #include "rargs_define.h"

	#include "rargs_macros.h"

BOOL RARG_parse_ParameterSetsForMatch(  rarg_parse_descriptor_t*  parse_descriptor,
                                        rarg_parameter_set_t*      parameter_sets,
                                        BOOL                      raise_exception_on_match_fail );  
rarg_matched_parameter_set_t* RARG_parse_ParameterSets(  rarg_parse_descriptor_t*    parse_descriptor, 
                                                        rarg_parameter_set_t*        parameter_set );  
BOOL RARG_parse_Parameters(  rarg_parse_descriptor_t*        parse_descriptor, 
                            rarg_parameter_t*                parameter );
BOOL RARG_parse_PossibleMatches(  rarg_parse_descriptor_t*      parse_descriptor,
                                  rarg_parameter_t*              parameter );
BOOL RARG_parse_PossibleMatch(    rarg_parse_descriptor_t*      parse_descriptor, 
                                  rarg_possible_match_t*        possible_match, 
                                  VALUE                          rb_arg );
BOOL RARG_parse_PossibleGroupMatch(  rarg_parse_descriptor_t*      parse_descriptor,
                                    rarg_possible_match_t*        possible_match,
                                    VALUE                          rb_arg  );
BOOL RARG_parse_PossibleBlockMatch(    rarg_parse_descriptor_t*      parse_descriptor,
                                      rarg_possible_match_t*        possible_match,
                                      VALUE                          rb_arg );
BOOL RARG_parse_PossibleBlockArityMatch(  rarg_possible_closure_match_arity_t*  possible_arity_match,
                                          VALUE                                rb_arity  );
BOOL RARG_parse_PossibleHashMatch(    rarg_parse_descriptor_t*      parse_descriptor, 
                                      rarg_possible_match_t*        possible_match, 
                                      VALUE                          rb_arg );
  BOOL RARG_parse_PossibleIndexMatch(  rarg_parse_descriptor_t*      parse_descriptor,
                                      rarg_possible_match_t*        possible_match,
                                      VALUE                          rb_arg );
  BOOL RARG_parse_PossibleHashKeyOrDataMatch(  rarg_parse_descriptor_t*                parse_descriptor, 
                                              rarg_possible_hash_key_data_match_t*    possible_hash_key_or_data, 
                                              VALUE                                    rb_arg,
                                              VALUE                                    rb_key_or_data );
BOOL RARG_parse_PossibleTypeMatch(  rarg_parse_descriptor_t*      parse_descriptor, 
                                    rarg_possible_match_t*        possible_match, 
                                    VALUE                          rb_arg );
BOOL RARG_parse_PossibleAncestorMatches(  rarg_parse_descriptor_t*      parse_descriptor, 
                                          rarg_possible_match_t*        possible_match, 
                                          VALUE                          rb_arg );
BOOL RARG_parse_PossibleMethodMatches(    rarg_parse_descriptor_t*      parse_descriptor, 
                                          rarg_possible_match_t*        possible_match, 
                                          VALUE                          rb_arg );
BOOL RARG_parse_PossibleIfElseMatch(  rarg_parse_descriptor_t*      parse_descriptor, 
                                      rarg_possible_match_t*        possible_match, 
                                      VALUE                          rb_arg );
  BOOL RARG_parse_PossibleIfElseValueMatch(  rarg_parse_descriptor_t*          parse_descriptor, 
                                            rarg_possible_match_t*            possible_match, 
                                            rarg_possible_if_else_match_t*    possible_if_else_match,
                                            VALUE                              rb_arg  );
  BOOL RARG_parse_PossibleIfElseMatchMatch(  rarg_parse_descriptor_t*          parse_descriptor, 
                                            rarg_possible_match_t*            possible_match, 
                                            rarg_possible_if_else_match_t*    possible_if_else_match,
                                            VALUE                              rb_arg );

VALUE RARG_parse_IterateHashDescriptor(  rarg_parse_descriptor_t*      parse_descriptor,
                                        VALUE                          rb_hash,
																				VALUE													rb_self,
                                        VALUE                          c_function(    int      argc,
                                                                                    VALUE*  args,
                                                                                    VALUE    rb_self ),
                                        VALUE                          rb_arg_to_pass, ... );
VALUE RARG_parse_IterateArrayDescriptor(  rarg_parse_descriptor_t*          parse_descriptor,
                                          VALUE                              rb_array,
																					VALUE																rb_self,
                                          VALUE                              c_function(    int      argc,
                                                                                          VALUE*  args,
                                                                                          VALUE    rb_self ),
                                          VALUE                              rb_arg_to_pass, ... );
VALUE RARG_parse_SplatArrayDescriptor(  rarg_parse_descriptor_t*          parse_descriptor,
                                          VALUE                              rb_array,
																					VALUE																rb_self,
                                          VALUE                              c_function(    int      argc,
                                                                                          VALUE*  args,
                                                                                          VALUE    rb_self ),
                                          VALUE                              rb_arg_to_pass, ... );


#endif