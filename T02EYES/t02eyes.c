/* FILE NAME: t02eyes.c
 * PROGRAMMER: TT6
 * DATE: 10.06.2021
 * PURPOSE: ��������� �������� �� �����
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

  /* ��������� ��������� ���� */
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

  /* ����������� ������ � ������� */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  
  /* �������� ���� */
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

  /* �������� � ������������� ���� */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* ���� ��������� ���������, ���� �� ����� �������� ��������� 'WM_QUIT' */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
  return 30;
} /* End of 'WinMain' funs */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam )
{ 
  POINT pt;
  static HDC hDC;
  static INT x, y;
  static INT w, h;
  static INT x0, y0, a, Cx, Cy, i;
  static INT R, R1;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;
  case WM_TIMER:
    hDC = GetDC(hWnd);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    Rectangle(hDC, 0, 0, w, h);   /* Clear background */
     srand(30);
     for (i = 0; i < 102; i++)
     {
      Cx = 200;
      Cy = 200;
      R = 100;
      R1 = 25;
      ///Ellipse(hDC, Cx - R, Cy - R, Cx + R, Cy + R);
      DrawEye(hDC, rand() % w, rand() % h, 50 + rand() % 47, 18 + rand() % 8, pt.x, pt.y);
     }
    ReleaseDC(hWnd, hDC);
    break;
 
  case WM_DESTROY:
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