/* FILE NAME : rndres.c
 * PROGRAMMER: TT6
 * DATE      : 24.06.2021
 * PURPOSE   : .
 */

#include "rndres.h"

/* Zdes dolzhno byt Init i Close dlya resoursov 
 * - shaders, textures and materials */

VOID TT6_RndResInit( VOID )
{
  TT6_RndTexInit();
  TT6_RndShadersInit();
  TT6_RndMtlInit();
} /* End of 'TT6_RndResInit' function */

VOID TT6_RndResClose( VOID )
{
  TT6_RndMtlClose();
  TT6_RndShadersClose();
  TT6_RndTexClose();
} /* End of 'TT6_RndResClose' function */
 
/* END OF 'rndres.c' FILE */