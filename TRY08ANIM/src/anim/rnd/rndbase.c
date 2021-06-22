/* FILE NAME : rndbase.c
 * PROGRAMMER: TT6
 * DATE      : 18.06.2021
 * PURPOSE   : global data
 */

#include "rnd.h"

/* - ����� � �������������, ��������������� � �.�. */
VOID TT6_RndInit( HWND hWnd )
{
  HDC hDC;

  /* -- �������� ���� hWnd->VG4_hRndWnd;
  -- ������� �������� VG4_hRndDCFrame
  -- ������������� ��������� �� ��������� */
  TT6_hRndWnd = hWnd;
  hDC = GetDC(TT6_hRndWnd);
  TT6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(TT6_hRndWnd, hDC);
} /* End of 'TT6_RndInit' function */

VOID TT6_RndClose( VOID )
{
  DeleteObject(TT6_hRndBmFrame);
  DeleteDC(TT6_hRndDCFrame);
  /* -- ���������� ��� ������� */
} /* End of 'TT6_RndClose' function */

VOID TT6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(TT6_hRndWnd);

  if (TT6_hRndBmFrame != NULL)
    DeleteObject(TT6_hRndBmFrame);
  TT6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(TT6_hRndWnd, hDC);
  SelectObject(TT6_hRndDCFrame, TT6_hRndBmFrame);

  /* ��������� ������� */
  TT6_RndFrameW = W;
  TT6_RndFrameH = H;

  /* ������������� ������� */
  TT6_RndProjSet();
} /* End of 'TT6_RndResize' function */

VOID TT6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, TT6_RndFrameW, TT6_RndFrameH,
         TT6_hRndDCFrame, 0, 0, SRCCOPY);
} /* End of 'TT6_RndCopyFrame' function */

/* Rendering */
VOID TT6_RndStart( VOID )
{
  /* -- ������� ����� � ������ (���-������) �� ��������� ��� ����������� */
  Rectangle(TT6_hRndDCFrame, 0, 0, TT6_RndFrameW, TT6_RndFrameH);
  Ellipse(TT6_hRndDCFrame, TT6_RndFrameW / 2 - 100, TT6_RndFrameH / 2 - 100, TT6_RndFrameW / 2 + 100, TT6_RndFrameH / 2 + 100);
} /* End of 'TT6_RndStart' function */

VOID TT6_RndEnd( VOID )
{
  /* -- ���� ������ */
} /* End of 'TT6_RndEnd' function */

VOID TT6_RndProjSet( VOID )
{
  DOUBLE rx, ry;

  rx = ry = TT6_RndProjSize;

  /* Correct aspect ratio */
  if (TT6_RndFrameW > TT6_RndFrameH)
    rx *= (DBL)TT6_RndFrameW / TT6_RndFrameH;
  else
    ry *= (DBL)TT6_RndFrameH / TT6_RndFrameW;

  TT6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      TT6_RndProjDist, TT6_RndProjFarClip);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_RndProjSet' function */



/* END OF 'rndbase.c' FILE */
