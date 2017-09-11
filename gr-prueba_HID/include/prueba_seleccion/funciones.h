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


#ifndef INCLUDED_PRUEBA_SELECCION_FUNCIONES_H
#define INCLUDED_PRUEBA_SELECCION_FUNCIONES_H

#include <prueba_seleccion/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace prueba_seleccion {

    /*!
     * \brief <+description of block+>
     * \ingroup prueba_seleccion
     *
     */
    class PRUEBA_SELECCION_API funciones : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<funciones> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of prueba_seleccion::funciones.
       *
       * To avoid accidental use of raw pointers, prueba_seleccion::funciones's
       * constructor is in a private implementation
       * class. prueba_seleccion::funciones::make is the public interface for
       * creating new instances.
       */
      static sptr make(float seleccion);
    };

  } // namespace prueba_seleccion
} // namespace gr

#endif /* INCLUDED_PRUEBA_SELECCION_FUNCIONES_H */

