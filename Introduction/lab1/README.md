# Lab 1: Creating a High-Level Synthesis Project

Open Vivado HLS GUI
- Linux: type `vivado_hls` at terminal
- Windows: open **Vivado HLS** through desktop icon or start menu

Select **Create New Project** from the Quick Start icons
- This action opens the Project wizard

Enter Project Name `fir_prj`

Specify project location
- Click **Browse** and navigate to `Vivado_HLS_Tutorial/Introduction/lab1`
- Select the `lab1` directory and click **OK**
- Click **Next**

Specify C design files
- Click **Add Files**
- Select `fir.c` from the `lab1` directory
- Use **Browse** to specify `fir (fir.c)` as the top-level function
- Click **Next**
- Click **Add Files** and select `fir_test.c` and `out.gold.dat`
- Click **Next**

Solution Configuration
- Leave the default solution name **solution1**
- Leave the default clock period **10 ns**
- Leave the uncertainty blank (defaults to **12.5% of clock cycle**)
- From the **Parts** tab, select `xcvu9p-flgb2104-1-i` and click **OK**
  - This sets the target device, which can be changed later
- Click **Finish** to open the HLS project

GUI Dashboard Layout
- Explorer pane: Standard file explorer. Located on left side of dashboard.
- Information pane: File viewing pane. Located in center of dashboard.
- Auxiliary pane: Optimized navigation. Located on right side of dashboard.
- Console pane: Displays messages, errors, and warnings. Located on bottom of dashboard.
- Toolbar buttons: Shortcuts to common operations. Located at top of dashboard.

C Simulation
- *This step confirms that the C/C++ code is correct*
- Expand `Test Bench` in the Explorer pane
- Open `fir_test.c`
  - This is called the **Test Bench File**
- Navigate to the `main()` function by selecting `main()` in the Outline tab of the Auxiliary pane
  - The test bench file contants the top-level function `main()` which calls the function to be synthesized (in this case `fir`)
- Click the **Run C Simulation** button to compile and execute the C code
- Click **OK** in the C Simulation dialog box
- The Console pane should give a readout ending with the following:
```
INFO: [SIM 211-1] CSim done with 0 errors.
INFO: [SIM 211-3] *************** CSIM finish ***************
Finished C simulation.
```

Synthesis
- *This step synthesizes the C code into an RTL design*
- Click the **Run C Synthesis** button
  - When synthesis completes, a report file will automatically open
- Click **Performance Estimates** in the Outline tab of the Auxiliary pane
  - This pane provides information about clock performance and latency
- Click **Utilizatin Estimates** in the Outline tab
  - This pane provides information about resource usage

RTL Verification
- *This step simulates the RTL design*
- Click the **Run C/RTL CoSimulation** button
- Click **OK** in the C/RTL Co-simulation dialog box
- Once Co-simulation has completed, the Console pane will display a message ending with:
```
INFO: [COSIM 212-1000] *** C/RTL co-simulation finished: PASS ***
Finished C/RTL cosimulation.
```

IP Creation
- *This step packages the design into an IP block which can be used as a tool later*
- Click the **Export RTL** button
- Check that the Format Selection option is set to **IP Catalog**
- Click **OK**
- The IP block can be found in `fir_prj/solution1/impl/ip/xilinx_com_hls_fir_1_0.zip`
