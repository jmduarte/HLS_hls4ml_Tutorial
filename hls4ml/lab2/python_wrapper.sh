#!/bin/bash
source /PATH/TO/Vivado/20XX.X/settings64.sh 
export XILINXD_LICENSE_FILE=2100@LICENSE_SERVER
export LM_LICENSE_FILE=2100@LICENSE_SERVER
exec python "$@"
