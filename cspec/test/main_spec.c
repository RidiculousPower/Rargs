#include <cspec.h>
#include <ruby.h>

void rb_Rargs_Define_spec( void );
void rb_Rargs_Parse_spec( void );

int main( void )	{
	
	ruby_init();

	rb_Rargs_Define_spec();
	rb_Rargs_Parse_spec();
	
}