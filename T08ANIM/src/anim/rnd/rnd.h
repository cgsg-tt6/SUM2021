/* FILE NAME : rnd.h
 * PROGRAMMER: TT6
 * DATE      : 18.06.2021
 * PURPOSE   : 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"

/*** References ***/

extern HWND TT6_hRndWnd;        /* Work window handle */
extern HDC TT6_hRndDCFrame;     /* Work window memory device context*/
extern HBITMAP TT6_hRndBmFrame; /* Work window background bitmap handle */
extern INT TT6_RndFrameW, TT6_RndFrameH; /* Work window size */

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

/* Render subsystem deinitialivation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndClose( VOID );

/* Render subsystem frame resize function.
 * ARGUMENTS: 
 *   - new frame width & height:
 *       INT W, H;
 * RETURNS: None.
 */
VOID TT6_RndResize( INT W, INT H );

/* Rendering start draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndStart( VOID );

/* Rendering finalize draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndEnd( VOID );
VOID TT6_RndCopyFrame( HDC hDC );
VOID TT6_RndStart( VOID );
VOID TT6_RndEnd( VOID );

/* Setup rendering project function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndProjSet( VOID );

/* Setup rendering viewer/camera function.
 * ARGUMENTS:
 *   - camera position:
 *       VEC Loc;
 *   - camera point of interest ('look at' point):
 *       VEC At;
 *   - camera upproximatly up direction:
 *       VEC Up;
 * RETURNS: None.
 */
VOID TT6_RndCamSet( VEC Loc, VEC At, VEC Up );

/***
 * Primitive support
 ***/
/* Vertex representation type */
typedef struct tagtt6VERTEX
{
  VEC P;  /* Vertex position */
} tt6VERTEX;

/* Primitive representation type */
typedef struct tagtt6PRIM
{
  tt6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh ? by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} tt6PRIM;

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - number of vertexes and indexes:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE if not enough memory.
 */
BOOL TT6_RndPrimCreate( tt6PRIM *Pr, INT NoofV, INT NoofI );

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 * RETURNS: None.
 */
VOID TT6_RndPrimFree( tt6PRIM *Pr );

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - world transformation matrix
 *       MATR World;
 * RETURNS: None.
 */
VOID TT6_RndPrimDraw( tt6PRIM *Pr, MATR World );

/* ARGUMENTS:
 *   - pointer to primitive to load:
 *       tt6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL TT6_RndPrimLoad( tt6PRIM *Pr, CHAR *FileName );

BOOL TT6_RndPrintCreatePlane( tt6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH );

#endif /*  __rnd_h_ */

/* END OF 'rnd.h' FILE */
