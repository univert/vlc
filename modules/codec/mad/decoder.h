/***************************************************************************
             mad_adec.h  -  description
                -------------------
    begin                : Mon Nov 5 2001
    copyright            : (C) 2001 by Jean-Paul Saman
    email                : jpsaman@wxs.nl
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _VLC_MAD_ADEC_H_
#define _VLC_MAD_ADEC_H_

/*****************************************************************************
 * mad_adec_thread_t : mad decoder thread descriptor
 *****************************************************************************/

enum mad_scaling { FAST_SCALING, MPG321_SCALING };

typedef struct mad_adec_thread_s
{
    /*
     * Decoder properties
     */
    struct mad_decoder  libmad_decoder;
    mad_timer_t         libmad_timer;  
    byte_t              buffer[MAD_BUFFER_MDLEN];
   
    /*
     * Thread properties
     */
    vlc_thread_t        thread_id;                /* id for thread functions */

    /* The bit stream structure handles the PES stream at the bit level */
    bit_stream_t        bit_stream;

    /*
     * Input properties
     */
    decoder_fifo_t *    p_fifo;                /* stores the PES stream data */
    data_packet_t *     p_data;

    /* Store i_pts for syncing audio frames */
    mtime_t             i_current_pts, i_next_pts;

    /*
     * Output properties
     */
    aout_instance_t *   p_aout; /* opaque */
    aout_input_t *      p_aout_input; /* opaque */
    audio_sample_format_t output_format;
    audio_date_t        end_date;

    enum mad_scaling	audio_scaling;

} mad_adec_thread_t;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/
vlc_thread_t            mad_adec_CreateThread( decoder_fifo_t * p_fifo );

#endif
