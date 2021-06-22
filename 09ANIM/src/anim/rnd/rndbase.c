/* FILE NAME : rndbase.c
 * PROGRAMMER: TT6
 * DATE      : 21.06.2021
 * PURPOSE   : 3D animation rendering global data module.
 */

#include "rnd.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment (lib, "opengl32")

VOID TT6_RndInit( HWND hWnd )
{
  HDC hDC;

  TT6_hRndWnd = hWnd;
  TT6_hRndDCFrame = NULL;
  /* Prepare frame compatible device context */
  hDC = GetDC(TT6_hRndWnd);
  TT6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(TT6_hRndWnd, hDC);

  /* Render parameters setup */
  TT6_RndProjSize = 0.1;
  TT6_RndProjDist = TT6_RndProjSize;
  TT6_RndProjFarClip = 300;
  TT6_RndFrameH = 47;
  TT6_RndFrameW = 47;
  TT6_RndCamSet(VecSet(18, 18, 18), VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'TT6_RndInit' function */

/* Render subsystem deinitialivation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndClose( VOID )
{
  if (TT6_hRndBmFrame != NULL)
    DeleteObject(TT6_hRndBmFrame);
  DeleteDC(TT6_hRndDCFrame);
  /* delete all the resourses */
} /* End of 'TT6_RndClose' function */

/* Render subsystem frame resize function.
 * ARGUMENTS: 
 *   - new frame width & height:
 *       INT W, H;
 * RETURNS: None.
 */
VOID TT6_RndResize( INT W, INT H )
{
  HDC hDC;

  /* Prepare back buffer bitmap */
  if (TT6_hRndBmFrame != NULL)
    DeleteObject(TT6_hRndBmFrame);

  hDC = GetDC(TT6_hRndWnd);
  TT6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(TT6_hRndWnd, hDC);

  SelectObject(TT6_hRndDCFrame, TT6_hRndBmFrame);

  /* Setup projection */
  TT6_RndFrameW = W;
  TT6_RndFrameH = H;

  /* Recount projection */
  TT6_RndProjSet();
} /* End of 'TT6_RndResize' function */

VOID TT6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, TT6_RndFrameW, TT6_RndFrameH,
         TT6_hRndDCFrame, 0, 0, SRCCOPY);
} /* End of 'TT6_RndCopyFrame' function */

/* Rendering start draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndStart( VOID )
{
  /* Clear frame */
  SelectObject(TT6_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(TT6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(TT6_hRndDCFrame, RGB(255, 210, 210));
  Rectangle(TT6_hRndDCFrame, 0, 0, TT6_RndFrameW + 1, TT6_RndFrameH + 1);

  /* Set default pen */
  SelectObject(TT6_hRndDCFrame, GetStockObject(DC_PEN));
  SelectObject(TT6_hRndDCFrame, GetStockObject(NULL_BRUSH));
  SetDCPenColor(TT6_hRndDCFrame, RGB(200, 130, 200));
  /* Ellipse(TT6_hRndDCFrame, TT6_RndFrameW / 2 - 100, TT6_RndFrameH / 2 - 100, TT6_RndFrameW / 2 + 100, TT6_RndFrameH / 2 + 100); */
} /* End of 'TT6_RndStart' function */

/* Rendering finalize draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndEnd( VOID )
{
  /* Nothing for now */
} /* End of 'TT6_RndEnd' function */

/* Setup rendering project function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndProjSet( VOID )
{
  DOUBLE rx, ry;

  rx = ry = TT6_RndProjSize;

  /* Correct aspect ratio */
  if (TT6_RndFrameW > TT6_RndFrameH)
    rx *= (DBL)TT6_RndFrameW / TT6_RndFrameH;
  else
    ry *= (DBL)TT6_RndFrameH / TT6_RndFrameW;

  /* Setup matrixes */
  TT6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      TT6_RndProjDist, TT6_RndProjFarClip);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_RndProjSet' function */

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
VOID TT6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  TT6_RndMatrView = MatrView(Loc, At, Up);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_RndProjSet' function */

/* END OF 'rndbase.c' FILE */
