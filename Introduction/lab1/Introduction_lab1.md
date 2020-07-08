# Lab 1: Creating a High-Level Synthesis Project

Open Vivado HLS GUI
- Linux: type `vivado_hls` at terminal
- Windows: open **Vivado HLS** through desktop icon or start menu

Select **Create New Project** from the Quick Start icons
- This action opens the Project wizard

Enter Project Name `fir_prj`

Specify project location
- Click **Browse** and navigate to `\Vivado_HLS_Tutorial\Introduction\lab1`
- Select the `lab1` directory and click **OK**
- Click **Next**

Specify C design files
- Click **Add Files**
- Select `fir.c` from the `lab1` directory
- Use **Browse** to specify `fir.c` as the top-level function
- Click **Next**
- Click **Add Files** and select `fir_test.c` and `out.gold.dat`
- Click **Next**

Solution Configuration
- Leave the default solution name **solution1**
- Leave the default clock period **10 ns**
- Leave the uncertainty blank (defaults to **12.5% of clock cycle**)
- From the **Parts** tab, select `xcvu9p-flgb2104-1` and click **OK**
- Click **Finish** to open the HLS project
