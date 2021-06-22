/* FILE NAME: main.c
 * PROGRAMMER: TT6
 * DATE: 18.06.2021
 * PURPOSE: 3D animation startup module.
 */

#include "../anim/rnd/rnd.h"


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

  /* Заполняем структуру окна */
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


  /* Регистрация класса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  
  /* Создание окна */
  hWnd =
    CreateWindow(TT6_WND_CLASS_NAME,
      "Animation System",
      WS_OVERLAPPEDWINDOW,
      100, 100, 400, 400, 
      NULL,
      NULL,
      hInstance,
      NULL);

  /* Показать и перерисаовать окно */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

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

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;

  case WM_CREATE:
    TT6_RndInit(hWnd);
    SetTimer(hWnd, 30, 1, NULL);
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;

  case WM_SIZE:
    TT6_RndResize(LOWORD(lParam), HIWORD(lParam));
    /* Redraw frame */
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:
    TT6_RndStart();
    TT6_RndEnd();
    /* Send repaint message */
    /* InvalidateRect(hWnd, NULL, FALSE); */
    hDC = GetDC(hWnd);
    /* Copy frame to the window */
    TT6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;
    
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    TT6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_DESTROY:
    TT6_RndClose();
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'TT6_MyWindowFunc' function */

/* END OF 't07globe.c' FILE */