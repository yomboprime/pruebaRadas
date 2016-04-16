
#ifndef __MODO_RADASTAN__
#define __MODO_RADASTAN__

#define DIRECCION_PANTALLA0 0x4000U
#define DIRECCION_PANTALLA1 0x6000U
#define PANTALLA_X 128
#define PANTALLA_Y 96
#define PANTALLA_X2 ( PANTALLA_X >> 1 )

typedef struct {
    
    unsigned char ancho2;
    unsigned char alto;
    unsigned char *pixels;
    unsigned char flags;
    
} Imagen;

extern void radasPonerModoRadastan();

extern void radasPonerPaleta( unsigned char *paleta );

extern unsigned char *radasObtenerPantallaActual();

extern unsigned char *radasCambiarPantalla();

extern void radasCls( unsigned char valor );

extern void radasPintarPixel( unsigned char x, unsigned char y, unsigned char color );
extern void radasPintar2Pixels( unsigned char x2, unsigned char y, unsigned char color );

extern void radasRectangulo( unsigned char x2, unsigned char y, unsigned char ancho2, unsigned char alto, unsigned char valor );
extern void radasPintarImagen( unsigned char x2, unsigned char y, Imagen *imagen );

#endif //__MODO_RADASTAN__

