/*******************************************************************************
Vendor: Xilinx 
Associated Filename: fir_test.cpp
Purpose: FIR Filter Example for Vivado HLS
Revision History: July 6, 2012 - initial release
                                                
*******************************************************************************
© Copyright 2008 - 2012 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/


#include "fir.h"

void fir_sw(hls::stream<int> &input_val, hls::stream<int> &output_val)
{
	int i;
	static short shift_reg[TAPS] = {0};
	const short coeff[TAPS] = {6,0,-4,-3,5,6,-6,-13,7,44,64,44,7,-13,
                                 -6,6,5,-3,-4,0,6};

	for(i=0; i < RUN_LENGTH; i++){
		int sample;
		sample = input_val.read();

		//Shift Register
		for(int j=0; j < TAPS-1; j++){
			shift_reg[j] = shift_reg[j+1];
		}
		shift_reg[TAPS-1] = sample;

		//Filter Operation
		int acc = 0;
		for(int k=0; k < TAPS; k++){
			acc += shift_reg[k] * coeff[k];
		}
		output_val.write(acc);
	}
}

int main()
{
	hls::stream<int> input_sw;
	hls::stream<int> input_hw;
	hls::stream<int> output_hw;
	hls::stream<int> output_sw;
	
	//Write the input values
	for(int i = 0; i < RUN_LENGTH; i++){
		input_sw.write(i);
		input_hw.write(i);
	}

	//Call to software model of fir
  	fir_sw(input_sw, output_sw);

	//Call to hardware model of fir
	fir_hw(input_hw, output_hw);

	for(int k=0; k < RUN_LENGTH; k++){
		int sw, hw;
		sw = output_sw.read();
		hw = output_hw.read();
		if(sw != hw){
			printf("ERROR: k = %d sw = %d hw = %d\n",k,sw,hw);
		      return 1;
		}
	}
	printf("Success! both SW and HW models match.\n");
	return 0;
}

