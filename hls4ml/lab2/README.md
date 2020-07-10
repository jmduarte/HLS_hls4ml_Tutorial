# hls4ml+QKeras Lab

- Download QKeras and install the package (you may add `--user` to `pip install` commands if you're not in a conda environment)
```
git clone https://github.com/google/qkeras
cd qkeras
pip install -e .
cd ..
pip install jupyter
```
- Note if you're remote, you'll have to log in with port forwarding, e.g. `ssh -L 127.0.0.1:8888:127.0.0.1:8888 username@host`
- Make a "Xilinx" jupyter kernel that has Xilinx libraries in the PATH
  - Edit `python_wrapper.sh` and insert the appropriate path to your Xilinx installation `settings64.sh` script and the correct LICENSE_SERVER if appropriate (or just comment that out)
  - Edit `kernel.json` to put the correct absolute path to `python_wrapper.sh`
  - Copy `kernel.json` to a new folder: `$HOME/.local/share/jupyter/kernels/xilinx/kernel.json`
- Launch jupyter
```
jupyter notebook --port 8888 --ip 127.0.0.1 --no-browser
```
- Open the `hls4ml_API.ipynb` notebook and follow the instructions there
- Then open the `hls4ml_qkeras.ipynb` notebook and follow the instructions there
