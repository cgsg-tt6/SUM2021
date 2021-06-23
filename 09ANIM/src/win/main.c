/* FILE NAME: main.c
 * PROGRAMMER: TT6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation startup module.
 */

#include "../units/units.h"

/* Window class name */
#define TT6_WND_CLASS_NAME "My Summer Practice'2021 window class name"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevTnstance, 
                    CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

  /* Fill window class structure */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hInstance = hInstance;
  wc.lpszClassName = TT6_WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = TT6_MyWindowFunc;


  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  
  /* Window creation */
  hWnd =
    CreateWindow(TT6_WND_CLASS_NAME,
      "Animation System",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      /* 100, 100, 800, 500, */
      NULL,
      NULL,
      hInstance,
      NULL);

  ShowWindow(hWnd, ShowCmd);
  
  /*** Create units ***/
  TT6_AnimUnitAdd(TT6_UnitCreateCow());

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 30, 0);

  return 30;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK TT6_MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam )
{ 
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    TT6_AnimInit(hWnd);
    TT6_InputInit(hWnd);
    return 0;

  case WM_SIZE:
    /* Redraw frame */
    TT6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:
    /* Draw content */
    TT6_AnimRender();

    /* Send repaint message */
    /* InvalidateRect(hWnd, NULL, FALSE); */
    hDC = GetDC(hWnd);
    /* Copy frame to the window */
    TT6_AnimCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    break;
    
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    /* Copy frame to window */
    TT6_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;

  case WM_SYSKEYDOWN:
    if (wParam == VK_RETURN)
    {
      /* FlipFullScreen(hWnd); */
      return 0;
    }
    break;

  case WM_ERASEBKGND:
    return 1;

  case WM_DESTROY:
    TT6_AnimClose();
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'TT6_MyWindowFunc' function */

/* END OF 't07globe.c' FILE */