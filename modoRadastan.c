
#include <stdlib.h>
#include <spectrum.h>
#include "modoRadastan.h"

unsigned char iPantallaActual = 0;
unsigned char *pantallaActual = DIRECCION_PANTALLA0;

void radasPonerModoRadastan() {

    outp( 0xBF3B, 64 );
    outp( 0xFF3B, 3 );

}

void radasPonerModoNormal() {

    if ( iPantallaActual == 1 ) {
        radasCambiarPantalla();
    }
    
    outp( 0xBF3B, 64 );
    outp( 0xFF3B, 0 );

}

void radasPonerPaleta( unsigned char *paleta ) {
    
    unsigned char i;
    for ( i = 0; i < 16; i++ ) {
        ulaplus_set( i, paleta[ i ] );
    }

}

unsigned char *radasObtenerPantallaActual() {

    return pantallaActual;

}

unsigned char *radasCambiarPantalla() {
    
    unsigned char valorPuerto = inp( 0x00FF );

    if ( ! iPantallaActual ) {
        pantallaActual = DIRECCION_PANTALLA1;
        valorPuerto &= 0xFE;
        iPantallaActual = 1;
    }
    else {
        pantallaActual = DIRECCION_PANTALLA0;
        valorPuerto |= 0x01;
        iPantallaActual = 0;
    }

    outp( 0x00FF, valorPuerto );

    return pantallaActual;

}

void radasCls( unsigned char valor ) {
    unsigned char *p = pantallaActual;
    int i;
    for ( i = 0; i < 6144; i++ ) {
        *p++ = valor;
    }
}

void radasPintarPixel( unsigned char x, unsigned char y, unsigned char color ) {

    // 0 <= x <= 128
    // 0 <= y <= 96
    // De color solo se usa el nibble bajo
    
    unsigned char valorPixeles;
    
    unsigned char *ptrPixel = ( unsigned char * ) ( pantallaActual + ( ( ( unsigned int ) x ) >> 1 ) + ( ( (  unsigned int ) y ) << 6 ) );

    if ( ! ( x & 1 ) ) {
        color <<= 4;
    }

    valorPixeles = *ptrPixel;

    valorPixeles |= color;

    *ptrPixel = valorPixeles;

}

void radasPintar2Pixels( unsigned char x2, unsigned char y, unsigned char color ) {
    
    // x2 es en pares de pixels, o sea x/2
    // 0 <= x2 <= 64
    // 0 <= y <= 96
    // color tiene los dos nibbles de ambos pixels
    

    *( ( unsigned char * ) ( pantallaActual + ( (  unsigned int ) x2 ) + ( ( (  unsigned int ) y ) << 6 ) ) ) = color;

}

void radasRectangulo( unsigned char x2, unsigned char y, unsigned char ancho2, unsigned char alto, unsigned char valor ) {

    // x2 es en pares de pixels, o sea x/2, al igual que ancho2
    // 0 <= x2 <= 64
    // 0 <= y <= 96
    // 1 <= ancho2 <= 64
    // 1 <= alto <= 96
    // color tiene los dos nibbles para cada par de pixels
    
    unsigned char i, j;
    unsigned char *p = pantallaActual + ( (  unsigned int ) x2 ) + ( ( (  unsigned int ) y ) << 6 );
    unsigned int dx = PANTALLA_X2 - ancho2;
    for ( j = 0; j < alto; j++ ) {
        for ( i = 0; i < ancho2; i++ ) {
            *p++ = valor;
        }
        p += dx;
    }
}

void radasPintarImagen( unsigned char x2, unsigned char y, Imagen *imagen ) {
}

