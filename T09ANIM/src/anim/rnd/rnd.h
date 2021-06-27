/* FILE NAME : rnd.h
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>
#include <gl/glu.h>

#include "res/rndres.h"


/*** References ***/

extern HWND TT6_hRndWnd;                 /* Work window handle */
extern HDC TT6_hRndDC;                   /* Work window memory device context*/
extern HGLRC TT6_hRndGLRC;               /* OpenGL rendering context */
extern INT TT6_RndFrameW, TT6_RndFrameH; /* Work window size */

extern DBL
  TT6_RndProjSize,
  TT6_RndProjDist,
  TT6_RndProjFarClip;
extern MATR
  TT6_RndMatrProj,
  TT6_RndMatrVP,
  TT6_RndMatrView;
extern VEC TT6_RndCamLoc;

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
VOID TT6_RndCopyFrame( VOID );
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
  VEC P;   /* vertex position */
  VEC2 T;  /* texture coordinate */
  VEC N;   /* normal */
  VEC4 C;  /* colour (r,g,b,a) */
} tt6VERTEX;

/* Primitive type */
typedef enum tagtt6PRIM_TYPE
{
  TT6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  TT6_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  TT6_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  TT6_RND_PRIM_POINTS,   /* Arrauy of points */
} tt6PRIM_TYPE;

/* Primitive representation type */
typedef struct tagtt6PRIM
{
  tt6PRIM_TYPE Type; /* Ptimitive type */
  INT 
    VA,              /* OpenGL vertex array number */
    VBuf,            /* OpenGL vertex buffer number */
    IBuf;            /* OpenGL index buffer number */
  INT NumOfElements;
  CHAR Ind[300];
  tt6VERTEX *V;

  MATR Trans;   /* Additional transformation matrix */
  INT MtlNo;
} tt6PRIM;

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - primitive type
 *       tt6PRIM_TYPE Type;
 *   - vertex attributes array:
 *       tt6VERTEX *V;
 *   - number of vertices:
 *       INT NumOfV;
 *   - index array (for trimesh – by 3 ones, may be NULL)
 *       INT *I;
 *   - number of indices
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID TT6_RndPrimCreate( tt6PRIM *Pr, tt6PRIM_TYPE Type, tt6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

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

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       tt6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL TT6_RndPrimLoad( tt6PRIM *Pr, CHAR *FileName );

BOOL TT6_RndPrimCreateGrid (tt6PRIM *Pr, INT SplitW, INT SplitH);
BOOL TT6_RndPrintCreatePlane( tt6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH );

/***
 * Primitive collection support
 ***/

/* Primitive collection data type */
typedef struct tagtt6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  tt6PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
  INT MtlNo;      /* Material number in material array */
} tt6PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TT6_RndPrimsCreate( tt6PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 * RETURNS: None.
 */
VOID TT6_RndPrimsFree( tt6PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID TT6_RndPrimsDraw( tt6PRIMS *Prs, MATR World );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TT6_RndPrimsLoad( tt6PRIMS *Prs, CHAR *FileName );

#endif /*  __rnd_h_ */

/* END OF 'rnd.h' FILE */
