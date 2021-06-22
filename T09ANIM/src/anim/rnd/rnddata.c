/* FILE NAME : rnddata.c
 * PROGRAMMER: TT6
 * DATE      : 21.06.2021
 * PURPOSE   : 3D animation rendering global data module. */

#include "rnd.h"

HWND TT6_hRndWnd;
HDC TT6_hRndDC;
HGLRC TT6_hRndGLRC;
INT TT6_RndFrameW, TT6_RndFrameH;

DBL
  TT6_RndProjSize = 0.1,
  TT6_RndProjDist = 0.1,
  TT6_RndProjFarClip = 300;
MATR
  TT6_RndMatrProj,
  TT6_RndMatrVP,
  TT6_RndMatrView;

/* END OF 'rnddata.c' FILE */