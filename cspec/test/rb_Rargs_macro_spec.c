#include <cspec.h>
#include <cspec/cspec_output_header.h>
#include <cspec/cspec_output_verbose.h>
#include <cspec/cspec_output_unit.h>

#include "../../ext/rargs/rb_Rargs.h"

#include <string.h>

//	macro spec not written yet - internals are all tested

/*********************
*  R_DefineAndParse  *
*  R_Define          *
*  R_Parse           *
*********************/

DESCRIBE( R_DefineAndParse, "R_DefineAndParse( argc, args, rb_self, parameter_set, ... )" )
	IT( "defines and parses parameter sets for the current passed args for the current function" )

	END_IT
END_DESCRIBE

/**********
*  R_Arg  *
**********/

DESCRIBE( R_Arg, "R_Arg( rb_receiver )" )
	IT( "grabs the next argument and assigns it to the specified receiver; useful after parsing when additional arguments remain" )

	END_IT
END_DESCRIBE


/****************************
*  R_IterateHashDescriptor  *
****************************/

DESCRIBE( RARG_parse_IterateHashDescriptor, "RARG_parse_IterateHashDescriptor( rb_hash, c_function )" )
	IT( "sends each key/data pair in the hash back to the present function as key, data with optional args prepended" )

	END_IT
END_DESCRIBE

/*****************************
*  R_IterateArrayDescriptor  *
*****************************/

DESCRIBE( RARG_parse_IterateArrayDescriptor, "RARG_parse_IterateArrayDescriptor( rb_array, c_function )" )
	IT( "sends each element in the array back to the present function with optional args prepended" )

	END_IT
END_DESCRIBE


void rb_Rargs_macro_spec( void )	{
	

}
