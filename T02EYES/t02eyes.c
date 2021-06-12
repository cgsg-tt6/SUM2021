/* FILE NAME: t02eyes.c
 * PROGRAMMER: TT6
 * DATE: 10.06.2021 - 12.06.2021
 * PURPOSE: Программа слежение за мышью
 */

#include <windows.h>

#include <stdlib.h>

#include <math.h>

#define WND_CLASS_NAME "My Summer Practice'2021 window class name"

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam );
VOID DrawEye( HDC hDC, INT Cx, INT Cy, INT r, INT r1, INT Mx, INT My );


/* Main program funclion */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevTnstance, 
                    CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /* Заполняем структуру окна */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Регистрация класса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  
  /* Создание окна */
  hWnd =
    CreateWindow(WND_CLASS_NAME,
      "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, 
      NULL,
      NULL,
      hInstance,
      NULL);

  /* Показать и перерисаовать окно */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* Цикл обработки сообщений, пока не будет получено сообщение 'WM_QUIT' */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
  return 30;
} /* End of 'WinMain' funs */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam )
{ 
  PAINTSTRUCT ps;
  POINT pt;
  static HDC hDC;
  static HDC hMemDC;
  static HBITMAP hBm;
  /* static HWND hWnd; */
  static INT x, y;
  static INT w, h;
  static INT x0, y0, a, Cx, Cy, i;
  static INT R, R1;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;

    SetTimer(hWnd, 30, 10, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    /* If there is a picture, delete it */
    if (hBm != NULL)
      DeleteObject(hBm);

    /* Get contect & make a pic */
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
  case WM_TIMER:
    ///hMemDC = GetDC(hWnd);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SelectObject(hMemDC, GetStockObject(BLACK_PEN));
    Rectangle(hMemDC, 0, 0, w, h);   /* Clear background */
     srand(30);
     for (i = 0; i < 102; i++)
     {
      Cx = 200;
      Cy = 200;
      R = 100;
      R1 = 25;
      DrawEye(hMemDC, rand() % w, rand() % h, 50 + rand() % 47, 18 + rand() % 8, pt.x, pt.y);
     }
    ///ReleaseDC(hWnd, hDC);
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    PostQuitMessage(0);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */


VOID DrawEye( HDC hDC, INT Cx, INT Cy, INT r, INT r1, INT Mx, INT My )
{
  INT dx = Mx - Cx, dy = My - Cy, len = (INT)sqrt((Mx - Cx) * (Mx - Cx) + (My - Cy) * (My - Cy));
  INT px = 0, py = 0;

  Ellipse(hDC, Cx - r, Cy - r, Cx + r, Cy + r);

  if (len > r - r1)
  {
    px = dx * (r - r1) / len;
    py = dy * (r - r1) / len;
  }
  else 
  {
    px = dx;
    py = dy;
  }

  SelectObject(hDC, GetStockObject(BLACK_BRUSH));
  Ellipse(hDC, Cx + px - r1, Cy  + py - r1, Cx + px + r1, Cy  + py + r1);
  SelectObject(hDC, GetStockObject(WHITE_BRUSH));
} /* End of 'DrawEye' function */

/* END OF 't02eyes.c' FILE */