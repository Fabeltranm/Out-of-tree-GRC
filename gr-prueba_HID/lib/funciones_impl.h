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

#ifndef INCLUDED_PRUEBA_SELECCION_FUNCIONES_IMPL_H
#define INCLUDED_PRUEBA_SELECCION_FUNCIONES_IMPL_H

#include <prueba_seleccion/funciones.h>
#include "hidapi.h"
#include <wchar.h>

namespace gr {
  namespace prueba_seleccion {
    
    class funciones_impl : public funciones
    {
     private:
      float seleccion_; // valor que se importa desde el GUI de GNURADIO
      int fd;

      // variables usadas exclusivamente para HID
      hid_device *handle; // agregado
      int res;
      unsigned char buf[8];// 1 extra byte for the report ID
      #define MAX_STR 255
      wchar_t wstr[MAX_STR];
      int i;
       

     public:
      struct hid_device_info *devs, *cur_dev;
      funciones_impl(float seleccion);
      ~funciones_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      void prueba(float serial_data);
      float open_(void);
    };

  } // namespace prueba_seleccion
} // namespace gr

#endif /* INCLUDED_PRUEBA_SELECCION_FUNCIONES_IMPL_H */

