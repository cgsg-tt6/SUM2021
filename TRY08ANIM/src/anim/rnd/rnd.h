/* FILE NAME : rnd.h
 * PROGRAMMER: TT6
 * DATE      : 18.06.2021
 * PURPOSE   : ???
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"

/*** References ***/

extern HWND TT6_hRndWnd;
extern HDC TT6_hRndDCFrame;
extern HBITMAP TT6_hRndBmFrame;
extern INT TT6_RndFrameW, TT6_RndFrameH;

extern DBL
  TT6_RndProjSize,
  TT6_RndProjDist,
  TT6_RndProjFarClip;
extern MATR
  TT6_RndMatrProj,
  TT6_RndMatrVP,
  TT6_RndMatrView;


/* From 'rndbase.c' file */
VOID TT6_RndInit( HWND hWnd );
VOID TT6_RndClose( VOID );
VOID TT6_RndResize( INT W, INT H );
VOID TT6_RndStart( VOID );
VOID TT6_RndEnd( VOID );
VOID TT6_RndCopyFrame( HDC hDC );
VOID TT6_RndStart( VOID );
VOID TT6_RndEnd( VOID );
VOID TT6_RndProjSet( VOID );

#endif /*  __rnd_h_ */

/* END OF 'rnd.h' FILE */
