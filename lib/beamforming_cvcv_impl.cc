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
#include "beamforming_cvcv_impl.h"

namespace gr {
  namespace beamforming {

    beamforming_cvcv::sptr
    beamforming_cvcv::make(int fft_len)
    {
      return gnuradio::get_initial_sptr
        (new beamforming_cvcv_impl(fft_len));
    }

    /*
     * The private constructor
     */
    beamforming_cvcv_impl::beamforming_cvcv_impl(int fft_len)
      : gr::block("beamforming_cvcv",
               gr::io_signature::make(1, 1, sizeof (gr_complex) * fft_len),
              gr::io_signature::make(1, 1, sizeof (gr_complex) * fft_len))
    {
	d_fft_len = fft_len;
}

    /*
     * Our virtual destructor.
     */
    beamforming_cvcv_impl::~beamforming_cvcv_impl()
    {
    }

    void
    beamforming_cvcv_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
       	ninput_items_required[0] = noutput_items;
    }

    int
    beamforming_cvcv_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
	const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];


        // Do <+signal processing+>
        // Tell runtime system how many input items we consumed on
        // each input stream.

	std::vector<tag_t> tags;
        get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+1);
      for (unsigned i = 0; i < tags.size(); i++) {
        if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_chan_taps") {
            d_channel_state = pmt::c32vector_elements(tags[i].value);
            remove_item_tag(0, tags[i]);
          }
        if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_carr_offset") {
            carrier_offset = pmt::to_long(tags[i].value);
          }
        }

          int j=0;
          std::cout << "Yahya and Karmo are ruling right now...\n";
          for(std::vector<gr_complex>::const_iterator i = d_channel_state.begin(); i != d_channel_state.end(); i++){


            // std::cout << "Debugging shit\n";
            // std::cout << *i << "\n";
            out[j] = *i;
            j++;
          }
       //  memcpy((void *) out,
       // (void *) d_channel_state.begin(),
       // sizeof(gr_complex) * d_fft_len);

        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace beamforming */
} /* namespace gr */

