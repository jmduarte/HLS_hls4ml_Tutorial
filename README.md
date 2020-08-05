# HLS & `hls4ml` Tutorial

- Original files can be downloaded from Xilinx (after agreeing to license) here: [ug871-design-files.zip](https://www.xilinx.com/cgi-bin/docs/ctdoc?cid=026f56e2-0a0f-4986-aeb7-e92917398939;d=ug871-design-files.zip)
- Xilinx Vivado HLS Guide: [ug871-vivado-high-level-synthesis-tutorial.pdf](ug871-vivado-high-level-synthesis-tutorial.pdf)

## Software Requirements

- Vivado/Vitis Design Suite 2017.1 or later release (and source `/PATH/TO/Vivado/20XX.X/settings64.sh` with correct path/version)
- Miniconda (can be downloaded from https://docs.conda.io/en/latest/miniconda.html)
- Once Miniconda is installed and setup, create the conda environment with `hls4ml` and `qkeras`:
```
conda env create -f environment.yml
```
- The setup to make a Jupyter kernel with the Xilinx libraries is (assuming Vivado is already set up / sourced)
```
python setup_kernel.py
```

## Labs

1. [Introduction to HLS Lab 1](Introduction/lab1/README.md)
1. [Introduction to HLS Lab 2](Introduction/lab2/README.md)
1. [Pipelining Lab 1](Design_Optimization/lab1/README.md)
1. [Pipelining Lab 2](Design_Optimization/lab2/README.md)
1. [hls4ml Lab](hls4ml/lab1/README.md)
1. [hls4ml+QKeras Lab](hls4ml/lab2/README.md)

## Other Resources 

- Parallel Programming for FPGAs (HLS Book): http://kastner.ucsd.edu/hlsbook/
- HLS Book Labs: https://pp4fpgas.readthedocs.io/en/latest/index.html
- UCSD CSE 237C: http://kastner.ucsd.edu/ryan/cse237c/
- `hls4ml` tutorial at Fast ML workshop: https://github.com/FPGA4HEP/course_material/tree/fml
- `QKeras` in `hls4ml`: https://indico.cern.ch/event/919468/contributions/3863588/attachments/2039929/3416087/sps_qkeras.pdf
- `QKeras` and `hls4ml` API functionality notebook: https://gist.github.com/thesps/c7e59cf5597804693b8663ddc9496b64
- `QKeras` and `hls4ml` API PR: https://github.com/hls-fpga-machine-learning/hls4ml/pull/195
- "Official" `hls4ml` tutorial: https://github.com/hls-fpga-machine-learning/hls4ml-tutorial
