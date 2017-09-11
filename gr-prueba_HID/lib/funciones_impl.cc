/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "funciones_impl.h"
// funciones para el uso del puerto serial 
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
// Headers needed for sleeping.
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "hidtest.h"

namespace gr {
  namespace prueba_seleccion {
    float devolver;
    funciones::sptr
    funciones::make(float seleccion)
    {      
        return gnuradio::get_initial_sptr
        (new funciones_impl(seleccion));
    };

    /*
     * The private constructor*/
    funciones_impl::funciones_impl(float seleccion)
      : gr::block("funciones",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
      seleccion_(seleccion)
      
    {
     //
    };

    /*
     * Our virtual destructor.
     */
    funciones_impl::~funciones_impl()
    {
    };

// funcion que abre el puerto serial
  float
  funciones_impl::open_(void)
  {
   
    printf("ok");
   return 1;

   };




//------------------------------------------------------------------------------------


    void
    funciones_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    funciones_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      float *in = (float *) input_items[0];
      float *out = (float *) output_items[0];
      
      
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      
      for(int i=0;i<noutput_items;i++)
          {
             prueba(in[i]);
                
          }	
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
// funcion job-now
    void
    funciones_impl::prueba(float serial_data)
        {
         devolver=open_();
         //main_hidtest();
        }

  } /* namespace prueba_seleccion */
} /* namespace gr */

