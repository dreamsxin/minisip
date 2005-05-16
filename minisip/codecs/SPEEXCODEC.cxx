/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Copyright (C) 2004 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/
#include<config.h>

#ifdef HAS_SPEEX

#include"SPEEXCODEC.h"
#include<assert.h>
#include<iostream>

#include<speex/speex.h>
#include<libmutil/print_hex.h>

SPEEXCODEC::SPEEXCODEC(){
	
	speex_bits_init(&bits);  // both for encode and decode
	
	//  Encoder Initialization
	
	
	// As a start, just use the narrow-band mode is implemented
	enc_state = speex_encoder_init(&speex_nb_mode); 
	
	// This will hand in the frame size used by the encoder
	speex_encoder_ctl(enc_state,SPEEX_GET_FRAME_SIZE,&frame_size);

	
	// Decoder Initialization
	
	// As a start, just use the narrow-band mode is implemented
	dec_state = speex_decoder_init(&speex_nb_mode); 
	
	// This will hand in the frame size used by the decoder  
	speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);
	
	output_frame = new float[160];
	
}

SPEEXCODEC::~SPEEXCODEC(){

	speex_bits_destroy(&bits);
	speex_encoder_destroy(enc_state);
	speex_decoder_destroy(dec_state);
	delete [] output_frame;
}


uint32_t SPEEXCODEC::encode(void *in_buf, int32_t in_buf_size, void *out_buf){


	for (int i=0; i< in_buf_size; i++){
		input_frame[i]= (float) ((short*)in_buf)[i];
	}
	
	
	//  now for every input frame:
	speex_bits_reset(&bits);
	speex_encode(enc_state, input_frame, &bits);
	// returns the number of bytes that need to be written
	//int bNum = speex_bits_nbytes(&bits); 
	nbBytes = speex_bits_write(&bits, (char*)out_buf, MAX_NB_BYTES);
	
	//out_buf = (void *) bytes_ptr;  // not sure
	//cerr << print_hex((unsigned char*)(out_buf), nbBytes)<<endl; 

	return nbBytes;

}

uint32_t SPEEXCODEC::decode(void *in_buf, int32_t in_buf_size, void *out_buf){


	input_bytes = (char *) in_buf;  // should in_buf also be changed to short (as in encode function)?  If so, then then you should have a for loop here
	//nbBytes = (int) in_buf_size;


	// for every input frame:
	speex_bits_read_from(&bits, input_bytes, in_buf_size);
	speex_decode(dec_state, &bits, output_frame);
	
	for (int i=0; i< 160; i++){
		((short *)out_buf)[i]= (short)output_frame[i];
	}

	return 160;


}


void SPEEXCODEC::decode(void *out_buf){
	//FIX: implement packet loss concealment
//	cerr << "PLC"<< endl;

	speex_bits_read_from(&bits, NULL, 0);
	speex_decode(dec_state, &bits, output_frame);
	
	for (int i=0; i< 160; i++){
		((short *)out_buf)[i]= (short)output_frame[i];
	}
	
	// returns the number of bytes that need to be written
	int bNum = speex_bits_nbytes(&bits);
}


int32_t SPEEXCODEC::getSamplingSizeMs(){
	return 20;
}

int32_t SPEEXCODEC::getSamplingFreq(){
	return 8000;
}


int32_t SPEEXCODEC::getEncodedNrBytes(){
	return 160;
}


int32_t SPEEXCODEC::getInputNrSamples(){
	return 160;
}

string SPEEXCODEC::getCodecName(){
	return "SPEEX";
}

string SPEEXCODEC::getCodecDescription(){
	return "SPEEX 8kHz, Speex";
	// for now we are only using narrow-band (8kHz)

}

int32_t SPEEXCODEC::getSdpMediaType(){
	return 114;  
	// Speex uses Dynamic Payload Type, meaning that there isn't a fixed assigned 
	// payload type number for it.  So, we use an agreed number in minisip 
	// for speex's payload type (114).
}

string SPEEXCODEC::getSdpMediaAttributes(){
	return "speex/8000/1";
	//     <encoding_name>/<clock_rate>/<number_of_channels(for audio streams)>
	//     Here we use the narrow-band (8000) using only one channel (non-sterio)
}

#endif
