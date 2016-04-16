
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <spectrum.h>

#include "modoRadastan.h"

void pintarDegradado() {
    
    unsigned char i, j, v;
    unsigned char *p = radasObtenerPantallaActual();
    
    for ( j = 0; j < PANTALLA_Y; j++ ) {

        v = j / 6;
        
        v = v | ( v << 4 );
        
        for ( i = 0; i < PANTALLA_X2; i++ ) {
            *p++ = v;
        }
    }

}

void rotarPaletaAdelante( unsigned char *paleta ) {
    unsigned char i;
    unsigned char v1 = paleta[ 0 ];
    unsigned char v2;
    for ( i = 1; i < 16; i++ ) {
        v2 = paleta[ i ];
        paleta[ i ] = v1;
        v1 = v2;
    }
    paleta[ 0 ] = v1;
}

typedef struct {
    // Todas las posiciones y tamaños en el eje x están en pares de pixels (divididas por dos)
    int x, y;
    int xant, yant;
    int xant2, yant2;
    int tamx, tamy;
    int velx, vely;
    unsigned char color;
} Sprite;

#define NUM_SPRITES 5
Sprite sprites[ NUM_SPRITES ];

void main( void ) {

    int i, j, n;
    unsigned char v;
    
    // fixed 8.8:
    int x, y;
    
    int tecla;
    long pausa = 100;

    static unsigned char paleta [] = {
        
        // gggrrrbb
        
        0x04,
        0x08,
        0x0C,
        0x10,
        0x14,
        0x18,
        0x1C,
        0xBC,
        0xFC,
        0xF0,
        0xE0,
        0xE3,
        0xA3,
        0x23,
        0x0F,
        0x92,
    };
    
    unsigned char flagCambiarPantalla = 1;

    radasCls( 0 );

    radasPonerModoRadastan();

    radasPonerPaleta( paleta );




    sprites[ 0 ].x = 45;
    sprites[ 0 ].y = 3;
    sprites[ 0 ].tamx = 5;
    sprites[ 0 ].tamy = 5;
    sprites[ 0 ].velx = 1;
    sprites[ 0 ].vely = 0;
    sprites[ 0 ].color = 0x88;

    sprites[ 1 ].x = 35;
    sprites[ 1 ].y = 10;
    sprites[ 1 ].tamx = 10;
    sprites[ 1 ].tamy = 10;
    sprites[ 1 ].velx = 1;
    sprites[ 1 ].vely = 0;
    sprites[ 1 ].color = 0x44;

    sprites[ 2 ].x = 20;
    sprites[ 2 ].y = 20;
    sprites[ 2 ].tamx = 6;
    sprites[ 2 ].tamy = 6;
    sprites[ 2 ].velx = -1;
    sprites[ 2 ].vely = 0;
    sprites[ 2 ].color = 0x66;
    
    sprites[ 3 ].x = 16;
    sprites[ 3 ].y = 30;
    sprites[ 3 ].tamx = 8;
    sprites[ 3 ].tamy = 4;
    sprites[ 3 ].velx = 1;
    sprites[ 3 ].vely = 0;
    sprites[ 3 ].color = 0x99;
    
    sprites[ 4 ].x = 26;
    sprites[ 4 ].y = 40;
    sprites[ 4 ].tamx = 4;
    sprites[ 4 ].tamy = 5;
    sprites[ 4 ].velx = -1;
    sprites[ 4 ].vely = 0;
    sprites[ 4 ].color = 0xBB;

    
    for ( i = 0; i < NUM_SPRITES; i++ ) {
        Sprite *s = &sprites[ i ];
        s->xant = s->x;
        s->yant = s->y;
        s->xant2 = s->x;
        s->yant2 = s->y;
    }
    
    
    
    
    //pintarDegradado();

    srand( 1234 );
    n = 0;
/*
    for ( n = 0; n < 16; n++ ) {

        x = rand() & 0x7FFF;
        y = rand() & 0x3FFF;
        
        
        pintarPixel( x >> 8, y >> 8, n );
        
    }    
*/

    //    radasRectangulo( 3, 7, 10, 20, 0x48 );


    // Bucle principal
    
    x = 4;
//    y = 12;
    v = 0xFE;
    tecla = getk();
    tecla = 0;
    while ( tecla != ' ' ) {

        ula_sync();
        

        for ( i = 0; i < NUM_SPRITES; i++ ) {
            Sprite *s = &sprites[ i ];
            radasRectangulo( s->xant2, s->yant2, s->tamx, s->tamy, 0 );
        }

        for ( i = 0; i < NUM_SPRITES; i++ ) {
            Sprite *s = &sprites[ i ];

            int nx = s->x + s->velx;
            if ( ( nx + s->tamx >= PANTALLA_X2 ) || ( nx < 0 ) ) {
                s->velx = - s->velx;
            }
            else {
                s->x = nx;
            }
            
            s->xant2 = s->xant;
            s->yant2 = s->yant;
            s->xant = s->x;
            s->yant = s->y;

            radasRectangulo( s->x, s->y, s->tamx, s->tamy, s->color );
            
        }
        
        if ( flagCambiarPantalla ) {
            radasCambiarPantalla();
        }


/*
        x = rand() & 0x003B;
        y = rand() & 0x003B;
        v = rand() & 0x00FF;
//        v = v | ( v << 4 );
        radasRectangulo( x, y, 3, 4, v );
*/
/*        
        x = rand() & 0x007F;
        y = rand() & 0x003F;
        pintarPixel( x, y, n++ );

        rotarPaletaAdelante( paleta );
        radasPonerPaleta( paleta );
*/

        tecla = getk();
        
        if ( tecla ) {
            switch ( tecla ) {
                case 'x':
                    flagCambiarPantalla = 0;
                    break;
                case 'c':
                    flagCambiarPantalla = 1;
                    break;
                default:
                    break;
            }
        }
    }

    // Fin del programa
    radasCls( 0 );
    radasPonerModoNormal();
    radasCls( 0 );

}

