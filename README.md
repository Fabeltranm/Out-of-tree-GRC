# Out-of-tree-GRC
Out-of-tree modules - GNU Radio Companion

Implementacion de bloques funcionales de GNURadio para la tarjeta QUACHO-BASIC, para interactuar directamente desde el software.

Bloques en los que se esta trabajando actualmente:

1. Bloque serial tx/rx
2. Bloque HID (Human Interface Device)

Para Instalar los bloques en gnuradio realizar el siguiente ciclo de instrucciones

1. crear un directorio dentro de la carpeta del proyecto llamada build
luego
$ mkdir build && cd build && cmake .. && make
$ sudo make install && sudo ldconfig
