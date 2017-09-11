/* -*- c++ -*- */

#define PRUEBA_SELECCION_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "prueba_seleccion_swig_doc.i"

%{
#include "prueba_seleccion/funciones.h"
%}


%include "prueba_seleccion/funciones.h"
GR_SWIG_BLOCK_MAGIC2(prueba_seleccion, funciones);
