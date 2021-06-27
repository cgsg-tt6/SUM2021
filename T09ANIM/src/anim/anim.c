/* FILE NAME : anim.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation module.
 */

#include "anim.h"

/* Global animation data */
tt6ANIM TT6_Anim;

VOID TT6_AnimInit( HWND hWnd )
{
  memset(&TT6_Anim, 0, sizeof(tt6ANIM));

  /* Fill animation context */
  TT6_Anim.hWnd = hWnd;
  TT6_RndInit(hWnd);
  TT6_Anim.W = TT6_RndFrameW;
  TT6_Anim.H = TT6_RndFrameH;

  TT6_TimerInit();
  TT6_InputInit();
} /* 'TT6_AnimInit' */

VOID TT6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < TT6_Anim.NumOfUnits; i++)
  {
    TT6_Anim.Units[i]->Close(TT6_Anim.Units[i], &TT6_Anim);
    free(TT6_Anim.Units[i]);
  }
  TT6_Anim.NumOfUnits = 0;
  TT6_RndClose();
  memset(&TT6_Anim, 0, sizeof(tt6ANIM));
}

VOID TT6_AnimResize( INT W, INT H )
{
  TT6_RndResize(W, H);
  TT6_Anim.W = W;
  TT6_Anim.H = H;

  TT6_AnimRender();
  TT6_AnimCopyFrame();
}

VOID TT6_AnimCopyFrame( VOID )
{
  TT6_RndCopyFrame();
}

VOID TT6_AnimRender( VOID )
{
  INT i;

  TT6_TimerResponse();
  TT6_InputResponse();

  for (i = 0; i < TT6_Anim.NumOfUnits; i++)
    TT6_Anim.Units[i]->Response(TT6_Anim.Units[i], &TT6_Anim);

  TT6_RndStart();
  for (i = 0; i < TT6_Anim.NumOfUnits; i++)
    TT6_Anim.Units[i]->Render(TT6_Anim.Units[i], &TT6_Anim);
  TT6_RndEnd();
}

VOID TT6_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    IsFullScreen = TRUE;

    /* Goto fullscreen mode */

    /* Store current window size and position */
    GetWindowRect(TT6_Anim.hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(TT6_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(TT6_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(TT6_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    IsFullScreen = FALSE;

    /* Restore window size and position */
    SetWindowPos(TT6_Anim.hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
}

VOID TT6_AnimUnitAdd( tt6UNIT *Uni )
{
  if (TT6_Anim.NumOfUnits < TT6_MAX_UNITS)
    TT6_Anim.Units[TT6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &TT6_Anim);
}

/* END OF 'anim.c' FILE */