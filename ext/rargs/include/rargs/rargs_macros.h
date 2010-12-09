#ifndef RARGS_MACROS
	#define RARGS_MACROS

	#define R_Arg( receiver )                                                          \
	  ( ( rarg_parse_descriptor->args_parsed < rarg_parse_descriptor->argc ) ?                                                                                      \
	            ( ( receiver = rarg_parse_descriptor->args[ rarg_parse_descriptor->args_parsed++ ] ) != Qnil )                                        \
	            : FALSE )
	#define R_IterateHashDescriptor( rb_hash, c_function, ... )                        R_IterateHashDescriptorWithSelf( rb_hash, c_function, Qnil,##__VA_ARGS__ )
	#define R_IterateHashDescriptorWithSelf( rb_hash, c_function, rb_other_self, ... ) RARG_parse_IterateHashDescriptor( rarg_parse_descriptor, rb_hash, rb_other_self, c_function,##__VA_ARGS__, Qnil )
	#define R_IterateHash( rb_hash, c_function, ... )                                  R_IterateHashDescriptor( rb_hash, c_function,##__VA_ARGS__ )
	#define R_IterateArrayDescriptor( rb_array, c_function, ... )                      R_IterateArrayDescriptorWithSelf( rb_array, c_function, Qnil,##__VA_ARGS__ )
	#define R_IterateArrayDescriptorWithSelf( rb_array, c_function, rb_other_self, ... )  RARG_parse_IterateArrayDescriptor( rarg_parse_descriptor, rb_array, rb_other_self, c_function,##__VA_ARGS__, Qnil )
	#define R_IterateArray( rb_array, c_function, ... )																			R_IterateArrayDescriptor( rb_array, c_function,##__VA_ARGS__ )
	#define R_SplatArrayDescriptor( rb_array, c_function, ... )															R_IterateArrayDescriptorWithSelf( rb_array, c_function, Qnil,##__VA_ARGS__ )
	#define R_SplatArrayDescriptorWithSelf( rb_array, c_function, rb_other_self, ... )			RARG_parse_SplatArrayDescriptor( rarg_parse_descriptor, rb_array, rb_other_self, c_function,##__VA_ARGS__, Qnil )

	#define RI_NextArg( parse_descriptor, receiver )                                                                \
	  ( ( parse_descriptor->args_parsed < parse_descriptor->argc ) ?                                                                                      \
	              ( ( receiver = parse_descriptor->args[ parse_descriptor->args_parsed++ ] ) != Qnil )                                        \
	              : FALSE )
	
	#define R_SimplifyArray( rb_array )																											( RARRAY_LEN( rb_array ) ? ( RARRAY_LEN( rb_array ) == 1 ? RARRAY_PTR( rb_array )[0] : rb_array ) : Qnil )
	
#endif
	