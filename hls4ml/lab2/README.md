# hls4ml+QKeras Lab

- Make sure your python environment (`conda` or otherwise) with `qkeras` and `jupyter` is working
- Note if you're remote, you'll have to log in with port forwarding, e.g. `ssh -L 127.0.0.1:8888:127.0.0.1:8888 username@host`
- Make a "Xilinx" jupyter kernel that has Xilinx libraries in the PATH
  - Edit `python_wrapper.sh` and insert the appropriate `/PATH/TO/Vivado/20XX.X/settings64.sh` script and the correct `LICENSE_SERVER` if appropriate (or just comment that out)
  - Edit `kernel.json` to put the correct absolute path to `python_wrapper.sh`
  - Copy `kernel.json` to a new location: `$HOME/.local/share/jupyter/kernels/xilinx/kernel.json`
- Launch jupyter
```
jupyter notebook --port 8888 --ip 127.0.0.1 --no-browser
```
- Open the [hls4ml_API.ipynb](hls4ml_API.ipynb) notebook and follow the instructions there
- Then open the [hls4ml_qkeras.ipynb](hls4ml_qkeras.ipynb) notebook and follow the instructions there
