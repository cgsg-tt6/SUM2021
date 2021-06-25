/* FILE NAME : rndtex.c
 * PROGRAMMER: TT6
 * DATE      : 25.06.2021
 * PURPOSE   : 3D animation module.
 */

#include "../../anim.h"
#include "rndres.h"

INT TT6_RndTexturesSize;                    /* Textures array store size */

TT6_RndTexInit( VOID );
TT6_RndTexClose( VOID );

INT TT6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
INT TT6_RndTexAdd( CHAR *FileName );


/* END OF 'rndtex.c' FILE */