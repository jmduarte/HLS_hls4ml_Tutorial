
open_project vhls_prj

set_top hls_macc

add_files hls_macc.c
add_files -tb hls_macc_test.c

open_solution solution1 -reset
set_part  {xc7z020clg484-1}
create_clock -period 4

puts "\n"
puts "************************************************************************"
puts "*  Running csim_design to validate C code is functional"
puts "************************************************************************"
puts "\n"
csim_design
puts "\n"
puts "************************************************************************"
puts "*  Running csynth_design to create core RTL"
puts "************************************************************************"
puts "\n"
csynth_design
puts "\n"
puts "************************************************************************"
puts "*  Running cosim_design to verify RTL - using main() in hls_macc_test.c"
puts "************************************************************************"
puts "\n"
cosim_design
puts "\n"
puts "*************************************************************************"
puts "*  Running export_design to generate bus adapters and final IP package"
puts "*************************************************************************"
puts "\n"
export_design

exit

