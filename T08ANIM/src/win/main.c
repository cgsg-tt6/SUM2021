/* FILE NAME: main.c
 * PROGRAMMER: TT6
 * DATE: 18.06.2021
 * PURPOSE: 3D animation startup module.
 */

#include "../anim/rnd/rnd.h"
#include <time.h>

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

  /* Показать и перерисаовать окно */
  ShowWindow(hWnd, ShowCmd);
  /* UpdateWindow(hWnd); */

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


  /* Цикл обработки сообщений, пока не будет получено сообщение 'WM_QUIT' */
  /* PeekMessage */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
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
  static tt6PRIM Pr, PrP, PrF;
  DBL t;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    TT6_RndInit(hWnd);
    TT6_RndPrimCreate(&Pr, 3, 3);
    Pr.V[0].P = VecSet(0, 0, 0);
    Pr.V[1].P = VecSet(0, 0, 0.2);
    Pr.V[2].P = VecSet(0, 0.3, 0);
    Pr.I[0] = 0;
    Pr.I[1] = 1;
    Pr.I[2] = 2;

    TT6_RndPrintCreatePlane(&PrP, VecSet(-0.8, 0, -5), VecSet(1.8, 0, 1.8), VecSet(-1.8, 0, -1.8), 16, 16);
    TT6_RndPrimLoad(&PrF, "cow.obj");
    return 0;

  case WM_SIZE:
    /* Redraw frame */
    TT6_RndResize(LOWORD(lParam) + 1, HIWORD(lParam) + 1);
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;

  case WM_TIMER:
    /* Draw content */
    TT6_RndStart();

    t = clock() / 1000.0;
    TT6_RndCamSet(VecSet(0, 1, 2), VecSet(0, 0, 0), VecSet(0, 10, 0));
    /* TT6_RndPrimDraw(&Pr, MatrIdentity()); */
    /* TT6_RndPrimDraw(&PrP, MatrIdentity()); */
    TT6_RndPrimDraw(&PrF, MatrMulMatr(MatrScale(VecSet1(0.03)), MatrRotateX(10 * sin(t))));

    TT6_RndEnd();

    /* Send repaint message */
    /* InvalidateRect(hWnd, NULL, FALSE); */
    hDC = GetDC(hWnd);
    /* Copy frame to the window */
    TT6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    break;
    
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    /* Copy frame to window */
    TT6_RndCopyFrame(hDC);
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
    TT6_RndPrimFree(&PrF);
    TT6_RndPrimFree(&PrP);
    TT6_RndPrimFree(&Pr);
    TT6_RndClose();
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'TT6_MyWindowFunc' function */

/* END OF 't07globe.c' FILE */