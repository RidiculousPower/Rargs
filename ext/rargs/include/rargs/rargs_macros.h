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
	
	#define R_SimplifyArray( rb_array )																											( RARRAY_LEN( rb_array ) ? ( ( RARRAY_LEN( rb_array ) == 1 ) ? RARRAY_PTR( rb_array )[0] : rb_array ) : Qnil )
	#define R_SimplifyHash( rb_hash )																												( RHASH_SIZE( rb_hash ) ? ( ( RHASH_SIZE( rb_hash ) == 1 ) ? rb_ary_entry( rb_funcall( rb_hash, rb_intern( "first" ), 0 ), 1 ) : rb_hash ) : Qnil )

	#define R_ReturnEnumeratorIfNoBlock( argc, args, rb_self )															RETURN_ENUMERATOR( rb_self, argc, args )
	
#endif
	