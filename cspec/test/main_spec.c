#include <cspec.h>
#include <ruby.h>

void rb_Rargs_define_spec( void );
void rb_Rargs_parse_spec( void );
void rb_Rargs_macro_spec( void );

int main( void )	{
	
	ruby_init();

//	rb_Rargs_define_spec();
//	rb_Rargs_parse_spec();
	rb_Rargs_macro_spec();

}
