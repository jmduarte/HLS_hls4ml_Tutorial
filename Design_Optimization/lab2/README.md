# Pipelining Lab 2: Baseline Matrix Multiplication Project

Read source files
- `matrixmul.cpp` contains the top function of matrix multiplication (now pipelined with II=1)
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
- For the timing, you should see (now with II=1 and latency=1)
```
* Summary: 
+---------+---------+----------+----------+-----+-----+----------+
|  Latency (cycles) |  Latency (absolute) |  Interval | Pipeline |
|   min   |   max   |    min   |    max   | min | max |   Type   |
+---------+---------+----------+----------+-----+-----+----------+
|        1|        1| 5.000 ns | 5.000 ns |    1|    1| function |
+---------+---------+----------+----------+-----+-----+----------+
```
- For the resources, you should see (the biggest change is the DSPs)
```
+---------------------+---------+-------+---------+---------+-----+
* Summary: 
+---------------------+---------+-------+---------+---------+-----+
|         Name        | BRAM_18K| DSP48E|    FF   |   LUT   | URAM|
+---------------------+---------+-------+---------+---------+-----+
|DSP                  |        -|     18|        -|        -|    -|
|Expression           |        -|      0|        0|      366|    -|
|FIFO                 |        -|      -|        -|        -|    -|
|Instance             |        -|      -|        -|        -|    -|
|Memory               |        -|      -|        -|        -|    -|
|Multiplexer          |        -|      -|        -|       72|    -|
|Register             |        -|      -|      340|        -|    -|
+---------------------+---------+-------+---------+---------+-----+
|Total                |        0|     18|      340|      438|    0|
+---------------------+---------+-------+---------+---------+-----+
|Available SLR        |     1440|   2280|   788160|   394080|  320|
+---------------------+---------+-------+---------+---------+-----+
|Utilization SLR (%)  |        0|   ~0  |    ~0   |    ~0   |    0|
+---------------------+---------+-------+---------+---------+-----+
|Available            |     4320|   6840|  2364480|  1182240|  960|
+---------------------+---------+-------+---------+---------+-----+
|Utilization (%)      |        0|   ~0  |    ~0   |    ~0   |    0|
+---------------------+---------+-------+---------+---------+-----+
- Try changing the pipeline pragma to
```
  #pragma HLS PIPELINE II=3
```
- How do the latency, II, and resource change?