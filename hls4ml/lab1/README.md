# hls4ml Lab

- Make sure your python environment (`conda` or otherwise) with `hls4ml` is working

- Take a look at the config for the 1-layer model `keras-config.yml`
```
KerasJson: KERAS_1layer.json
KerasH5:   KERAS_1layer_weights.h5
InputData: KERAS_1layer_input_features.dat
OutputPredictions: KERAS_1layer_predictions.dat
OutputDir: my-hls-test
ProjectName: myproject
XilinxPart: xcku115-flvb2104-2-i
ClockPeriod: 5
Backend: Vivado
IOType: io_parallel
HLSConfig:
  Model:
    Precision: ap_fixed<8,4>
    ReuseFactor: 1
```

- Run the conversion
```
hls4ml convert -c keras-config.yml
```

- This will create a folder called `my-hls-test`. If you want to change the projectory directory name edit the yml configuration file.

- Run project design synthesis with Vivado HLS
```
hls4ml build -p my-hls-test -c -s
```
- or alternatively:
```
cd my-hls-test
vivado_hls -f build_prj.tcl "csim=1 synth=1 cosim=0 export=0"
```

- Readout resource usage and latency from the synthesis report
```
hls4ml report -p my-hls-test
```

- Extract and compare area under the ROC curve from keras (floating point calculations) and HLS (fixed point calculations)
```
pip install scikit-learn matplotlib 
python extract_roc.py -c keras-config.yml
```

- Change precision of calculations and reuse factor in the keras configuration file and check effect on NN performance (AUC) and FPGA resource usage using the scripts above.

```
ReuseFactor: N  # N = number of times a multiplier is used to do a computation 
DefaultPrecision: ap_fixed<X,Y>  # X = total number of bits, Y = number of integer bits, X-Y = number of decimal bits
```
- NB: suggest to change the project output directory in the keras configuration for each test to avoid overwriting of previous projects.
