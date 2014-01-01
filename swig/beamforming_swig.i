/* -*- c++ -*- */

#define BEAMFORMING_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "beamforming_swig_doc.i"

%{
#include "beamforming/beamforming_cvcv.h"
#include "beamforming/beamforming_chan_est_debug_vc.h"
%}


%include "beamforming/beamforming_cvcv.h"
GR_SWIG_BLOCK_MAGIC2(beamforming, beamforming_cvcv);
%include "beamforming/beamforming_chan_est_debug_vc.h"
GR_SWIG_BLOCK_MAGIC2(beamforming, beamforming_chan_est_debug_vc);
