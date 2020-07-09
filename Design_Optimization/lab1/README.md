# Optimization Lab 1: Baseline Matrix Multiplication Project

Read source files
- `matrixmul.cpp` contains the top function of matrix multiplication
- `matrixmul_test.cpp` is the test bench (with software verification)
- `run_hls.tcl` is the Tcl file running just C simulation and synthesis
  - Note the device part number and clock frequency

Run C Simulation + Synthesis
```
vivado_hls -f build run_hls.tcl
```

Check Resources and Timing Report
```
cat matrixmul_prj/solution1/syn/report/matrixmul_csynth.rpt
```
- For the timing, you should see
```
* Summary: 
+---------+---------+----------+----------+-----+-----+---------+
|  Latency (cycles) |  Latency (absolute) |  Interval | Pipeline|
|   min   |   max   |    min   |    max   | min | max |   Type  |
+---------+---------+----------+----------+-----+-----+---------+
|       79|       79| 0.395 us | 0.395 us |   79|   79|   none  |
+---------+---------+----------+----------+-----+-----+---------+
```
- For the resources, you should see:
```
* Summary: 
+---------------------+---------+-------+---------+---------+-----+
|         Name        | BRAM_18K| DSP48E|    FF   |   LUT   | URAM|
+---------------------+---------+-------+---------+---------+-----+
|DSP                  |        -|      1|        -|        -|    -|
|Expression           |        -|      -|        0|      116|    -|
|FIFO                 |        -|      -|        -|        -|    -|
|Instance             |        -|      -|        -|        -|    -|
|Memory               |        -|      -|        -|        -|    -|
|Multiplexer          |        -|      -|        -|       69|    -|
|Register             |        -|      -|       44|        -|    -|
+---------------------+---------+-------+---------+---------+-----+
|Total                |        0|      1|       44|      185|    0|
+---------------------+---------+-------+---------+---------+-----+
|Available SLR        |     1440|   2280|   788160|   394080|  320|
+---------------------+---------+-------+---------+---------+-----+
|Utilization SLR (%)  |        0|   ~0  |    ~0   |    ~0   |    0|
+---------------------+---------+-------+---------+---------+-----+
|Available            |     4320|   6840|  2364480|  1182240|  960|
+---------------------+---------+-------+---------+---------+-----+
|Utilization (%)      |        0|   ~0  |    ~0   |    ~0   |    0|
+---------------------+---------+-------+---------+---------+-----+