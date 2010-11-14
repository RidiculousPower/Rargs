#!/usr/bin/env ruby

require 'mkmfmf'
require 'rbconfig'
require 'core-source'

target  = "rargs"

required_core_headers    = [  "vm_core.h" ]
  
default_cflags  = "-march=x86-64 -gfull -fcatch-undefined-behavior -fno-common -fsigned-char -pipe"

# Create our makefile from sources
if ensure_core_headers( required_core_headers )
  with_cflags( default_cflags ) do
    create_makefile( target )
  end
end

header_files = Dir.glob( "../../../../ext/rargs/*.h" )
header_dir = Config::CONFIG[ "rubyhdrdir" ]
puts 'Installing headers: ' + header_files.to_s + ' into ' + header_dir.to_s
FileUtils.cp( header_files, header_dir )
