#!/bin/bash
source /PATH/TO/settings64.sh 
export XILINXD_LICENSE_FILE=2100@LICENSE_SERVER
export LM_LICENSE_FILE=2100@LICENSE_SERVER
exec python "$@"
