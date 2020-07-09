# Lab 2: Using the Tcl Command Interface
Open the Vivado HLS Command Prompt
- Linux: open a new shell
- Windows: open through start menu

In the Vivado HLS GUI, open `solution1/constraints/scripts.tcl`
- This file contains the Tcl commands to create and run all stages of the HLS project set up in Lab 1

The Vivado HLS GUI is no longer needed. You may close it if you wish.

Create a new Tcl file for Lab 2 using the following commands:
```
cd Vivado_HLS_Tutorial/Introduction/lab2
cp ../lab1/fir_prj/solution1/script.tcl run_hls.tcl
```
- This copies the existing Tcl file to the `lab2` directory.

Open `run_hls.tcl` in any text editor and make the following changes:
- Add a `-reset` option to the `open_project` command: `open_project -reset fir_prj`
  - This overwrites any existing project information
- Add a `reset` option to the `open_solution` command: `open_solution -reset "solution1"`
  - This removes any existing solution information when the Tcl file is re-run on the same solution
- Leave the `source` command commented
- Any other directives you wish to use can be included directly in this file
- Add the `exit` command to the last line of the file
- Save and exit

Run the Tcl file
```
vivado_hls -f run_hls.tcl
```
- This command executes all the steps covered in Lab 1
- The results are available in the `fir_prj` directory:
  - Synthesis report located in `fir_prj/solution1/syn/report`
  - Simulation results located in `fir_prj/solution/sim/report`
  - IP package is located in `fir_prj/solution1/impl/ip`
  - RTL output is located in `fir_prj/solution1/impl/` and then `Verilog` or `VHDL`
  
