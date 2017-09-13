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

// parametros del dispositivo HID quacho
#define FCDPROPLUS_VENDOR_ID    0x03eb
#define FCDPROPLUS_PRODUCT_ID   0x2402



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
              gr::io_signature::make(0, 0, 0)),
      seleccion_(seleccion)
      
    { 
    // BUsqueda y visualizacion de dispositivos HID conectados al equipo    
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs; 
    while (cur_dev) {
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Release:      %hx\n", cur_dev->release_number);
        printf("  Interface:    %d\n",  cur_dev->interface_number);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);
 
    // Set up the command buffer.
    memset(buf,0x00,sizeof(buf));
    buf[0] = 0x01;
    buf[1] = 0x81;

    // inicializacion del dispositivo HID esperado segun VENDOR_ID y PRODUCT_ID
    handle=hid_open( FCDPROPLUS_VENDOR_ID ,FCDPROPLUS_PRODUCT_ID, NULL);
        if(handle == NULL )
              printf("no se encuentra dispositivo HID");
        else
              printf("dispositivo encontrado...");

    
    // Read the Manufacturer String
    wstr[0] = 0x0000;
    res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read manufacturer string\n");
    printf("Manufacturer String: %ls\n", wstr);
 
    // Read the Product String
    wstr[0] = 0x0000;
    res = hid_get_product_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read product string\n");
    printf("Product String: %ls\n", wstr);
 
    // Read the Serial Number String
    wstr[0] = 0x0000;
    res = hid_get_serial_number_string(handle, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read serial number string\n");
    printf("Serial Number String: (%d) %ls", wstr[0], wstr);
    printf("\n");
 
    // Read Indexed String 1
    wstr[0] = 0x0000;
    res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
    if (res < 0)
        printf("Unable to read indexed string 1\n");
    printf("Indexed String 1: %ls\n", wstr);
 
    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);
 
    // send and receive 20 reports
    for (int r = 0; r < 20; r++) {
        // send some dummy data
        buf[0] = 0x0; //report number
//        for (i = 1; i < sizeof(buf); i++) {
//            buf[i] = r + i;
//        }
 
//        res = hid_write(handle, buf, sizeof(buf));
//        if (res < 0) {
//            printf("Unable to write()\n");
//            printf("Error: %ls\n", hid_error(handle));
//        }S
 
        // Read requested state. hid_read() has been set to be
        // non-blocking by the call to hid_set_nonblocking() above.
        // This loop demonstrates the non-blocking nature of hid_read().
        res = 0;
        while (res == 0) {
            res = hid_read(handle, buf, sizeof(buf));
            if (res == 0)
                printf("waiting...\n");
            if (res < 0)
                printf("Unable to read()\n");
            #ifdef WIN32
            Sleep(500);
            #else
            usleep(500*1000);
            #endif
        }
 
        printf("Data read:\n   ");
        // Print out the returned buffer.
        for (i = 0; i < res; i++)
            printf("%02hhx ", buf[i]);
        printf("\n");
      }
    };

    /*
     * Our virtual destructor.
     */
    funciones_impl::~funciones_impl()
    {
    };

// funcion para enviar-recibir datos de dispositivo HID
  float
  funciones_impl::open_(void)
  {
 
   res = 0;
        while (res == 0) {
            res = hid_read(handle, buf, sizeof(buf));
            if (res == 0)
                printf("waiting...\n");
            if (res < 0)
                printf("Unable to read()\n");

            usleep(5000);

        }
 
        printf("Data read:\n   ");
        // Print out the returned buffer.
        for (i = 0; i < res; i++)
            printf("%02hhx ", buf[i]);
        printf("\n");
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
      //float *out = (float *) output_items[0];
      
      
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
          
        }

  } /* namespace prueba_seleccion */
} /* namespace gr */

