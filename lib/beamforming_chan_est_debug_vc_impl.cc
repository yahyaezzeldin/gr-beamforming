/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "beamforming_chan_est_debug_vc_impl.h"

namespace gr {
  namespace beamforming {

    beamforming_chan_est_debug_vc::sptr
    beamforming_chan_est_debug_vc::make(int fft_len)
    {
      return gnuradio::get_initial_sptr
        (new beamforming_chan_est_debug_vc_impl(fft_len));
    }

    /*
     * The private constructor
     */
    beamforming_chan_est_debug_vc_impl::beamforming_chan_est_debug_vc_impl(int fft_len)
      : gr::block("beamforming_chan_est_debug_vc",
              gr::io_signature::make(1, 1, sizeof(gr_complex) * fft_len),
              gr::io_signature::make(0, 0, 0))
    {

      d_fft_len = fft_len;

    }

    /*
     * Our virtual destructor.
     */
    beamforming_chan_est_debug_vc_impl::~beamforming_chan_est_debug_vc_impl()
    {
    }

    void
    beamforming_chan_est_debug_vc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    beamforming_chan_est_debug_vc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        //gr_complex *out = (gr_complex *) output_items[0];

        // Do <+signal processing+>

        std::cout << "Channel Coefficients\n--------------";
        for (unsigned i = 0;i<d_fft_len;i++){

            std::cout << "Carrier #"<< i << ": " << in[i] << "\n";

        }


        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace beamforming */
} /* namespace gr */

