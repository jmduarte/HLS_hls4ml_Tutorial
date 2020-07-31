############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################

# Reset the project with the -rset option
open_project -reset fir_prj
set_top fir
add_files fir.c
add_files -tb fir_test.c
add_files -tb out.gold.dat

# Reset the project with the -rset option
open_solution -reset "solution1"
set_part {xc7k160tfbg484-2}
create_clock -period 10 -name default

# Leave the previous directives commented out
#source "./fir_prj/solution1/directives.tcl"

csim_design
csynth_design
cosim_design
export_design -format ip_catalog

# Exit vivado HLS
exit
