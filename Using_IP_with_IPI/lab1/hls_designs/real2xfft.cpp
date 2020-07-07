/*******************************************************************************
Vendor: Xilinx
Associated Filename: xfft2real.cpp
Purpose: Part of a Vivado HLS tutorial example
Device: All
Revision History: March 31, 2013 - initial release

*******************************************************************************
Copyright (C) 2013 XILINX, Inc.

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
(individually and collectively, "Critical Applications"). Customer asresultes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES.

*******************************************************************************/

#include "hls_realfft.h"
#include "sliding_win.h"

using namespace hls_window_fn;

// This is the top-level (for HLS) function for the Real FFT frontend processing
// It takes in a stream of real data samples, creates a sliding window (1/2
// old / 1/2 new data) and applies a Hamming windowing function to it before
// packing pairs of samples into a complex format to stream to an XFFT IP Core
// of N/2 points.  This tutorial version takes 16-bit data assumed to be
// in a normalize fixed point format (1 whole bit and 15 fractional bits)
// and outputs 16-bit scaled (i.e. also normalized) complex spectral data
void hls_real2xfft(
      hls::stream<din_t>& din,
      hls::stream<xfft_axis_t>& dout)
{
#pragma HLS INTERFACE axis port=dout
#pragma HLS INTERFACE axis port=din
   din_t data2window[REAL_FFT_LEN], windowed[REAL_FFT_LEN];
#pragma HLS ARRAY_PARTITION variable=data2window cyclic factor=2
#pragma HLS ARRAY_PARTITION variable=windowed cyclic factor=2
#pragma HLS ARRAY_STREAM variable=data2window,windowed depth=2
#pragma HLS DATAFLOW

   sliding_win_1in2out<din_t, REAL_FFT_LEN>(din, data2window);
   window_fn<din_t, din_t, coeff_t, REAL_FFT_LEN, WIN_FN_TYPE, 2>(data2window, windowed);

real2xfft_output:
   for (int i = 0; i < REAL_FFT_LEN; i += 2) {
#pragma HLS PIPELINE rewind
      dout_t cdata(windowed[i], windowed[i + 1]);
      xfft_axis_t fft_axis_d;
      fft_axis_d.data = cdata;
      fft_axis_d.last = i == REAL_FFT_LEN - 2 ? 1 : 0;
      dout.write(fft_axis_d);
   }
}

