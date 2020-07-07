/*******************************************************************************
Vendor: Xilinx
Associated Filename: hls_realfft_test.h
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

#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include "hls_realfft.h"
#include "reference_fft.h"
#include <cstdio>

using namespace std;

typedef float real32_t;
typedef complex<real32_t> creal32_t;

#define NUM_TESTS 8

void signal_gen(din_t *signal, int num_samples);

int main(void)
{
   int err_cnt = 0;
   short din_val = 0;

   din_t * const signal_buf = new din_t [REAL_FFT_LEN];
   hls::stream<din_t> frontend_din("fe_din");
   hls::stream<xfft_axis_t> frontend_dout("fe_dout");
   dout_t * const fft_din = new dout_t [REAL_FFT_LEN/2];
   dout_t * const fft_dout = new dout_t [REAL_FFT_LEN/2];
   hls::stream<xfft_axis_t> backend_din("be_din");
   hls::stream<dout_t> backend_dout("be_dout");
   ofstream tvin_ofs("realfft_fe_tvin.dat");
   tvin_ofs.fill('0');
   ofstream tvout_ofs("realfft_be_tvout.dat");
   tvout_ofs.fill('0');

   for (int i = 0; i < NUM_TESTS; i++) {
      // Generate a new set of samples
      signal_gen(signal_buf, REAL_FFT_LEN / 2);
      // Put samples into fronted DUT input stream
      for (int j = 0; j < REAL_FFT_LEN / 2; j++) {
         frontend_din << signal_buf[j];
         // Capture input TVs for system level (Vivado XSIM) RTL simulation
         tvin_ofs.width(DIN_W / 4);
         tvin_ofs << hex << ap_uint<DIN_W>(signal_buf[j].range(DIN_W - 1, 0)) << endl;
      }
      // Frontend DUT - applies a window function to data pairwise
      // output is formatted for XFFT AXIS input (complex TDATA w/ TLAST)
      hls_real2xfft(frontend_din, frontend_dout);
      // Put output of FE through reference FFT - HW will use Xilinx FFT IP
      for (int j = 0; j < REAL_FFT_LEN / 2; j++) {
         xfft_axis_t windowed_samples = frontend_dout.read();
         fft_din[j].real(windowed_samples.data.real());
         fft_din[j].imag(windowed_samples.data.imag());
      }
      fft_rad2_dit_nr<DOUT_W, 16>(fft_dout, fft_din, REAL_FFT_LEN / 2, false);
      // convert ref FFT floating point output into fixed-point for backend
      for (int j = 0; j < REAL_FFT_LEN / 2; j++) {
         xfft_axis_t fft_axis_out;
         fft_axis_out.data.real(fft_dout[j].real());
         fft_axis_out.data.imag(fft_dout[j].imag());
         fft_axis_out.last = j == REAL_FFT_LEN / 2 - 1 ? 1 : 0;
         backend_din << fft_axis_out;
      }
      // Backend DUT
      hls_xfft2real(backend_din, backend_dout);

      for (int j = 0; j < REAL_FFT_LEN / 2; j++) {
         dout_t dout = backend_dout.read();
         float re = dout.real().to_float();
         float im = dout.imag().to_float();
         real32_t mag = sqrt(re * re + im * im);

         // write output test vector
         ap_uint<2*DOUT_W> tv_dout = (dout.imag().range(DOUT_W - 1, 0),
               dout.real().range(DOUT_W - 1, 0));
         tvout_ofs.width(2 * DOUT_W / 4);
         tvout_ofs << hex << tv_dout << endl;

         // Printout information for each bin
         if (i == NUM_TESTS - 1) {
            printf("%4d:\t{ %9.6f, %9.6f }; mag = %8.6f\n", j, re, im, mag);
         }
      }
      fflush(stdout);
      cout << endl;
   }

   tvin_ofs.close();
   tvout_ofs.close();
   delete [] signal_buf;
   delete [] fft_din;
   delete [] fft_dout;

   cout << "*** TEST COMPLETE ***" << endl << endl;
   return err_cnt;
}

void signal_gen(din_t *signal, int num_samples)
{
   enum {NUM_FREQ = 5};
   struct freq_comp_data {
      double cycles_per_win;
      double phase;
      double amplitude;
   } freq_set[NUM_FREQ] = {
         {497.0, 0.7, 0.8}, {235.0, 1.6, 1.0}, {100.0, 0.0, 0.6},
         {35.0, 0.0, 0.8}, {5.0, 0.0, 0.9}
   };
   static uint64_t t = 0;
   // Generate samples
   for(int i = 0; i < num_samples; i++) {
      double sum_freq = 0.0, sum_ampl = 0.0;
      for (int j = 0; j < NUM_FREQ; j++) {
         sum_freq += freq_set[j].amplitude *
            cos(2.0 * M_PI * freq_set[j].cycles_per_win * t / (2 * num_samples));
         sum_ampl += freq_set[j].amplitude;
      }

      din_t sample = ap_fixed<DIN_W, 1, AP_TRN, AP_SAT>(sum_freq / sum_ampl);
      signal[i] = sample;
      t++;
   }
}
