#!/usr/bin/env ruby

require 'mkmfmf'

target  = "rargs"
  
default_cflags  = "-march=x86-64 -gfull -fcatch-undefined-behavior -fno-common -fsigned-char -pipe"

# Create our makefile from sources
with_cflags( default_cflags ) do
	create_makefile( target )
end
