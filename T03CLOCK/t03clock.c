/* FILE NAME: t03clock.c
 * PROGRAMMER: TT6
 * DATE: 11.06.2021
 * PURPOSE: Вывод часов на экран
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define pi 3.14159265358979323846264

#define WND_CLASS_NAME "My Summer Practice'2021 window class name"

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam );
VOID DrawHand( HDC hDC, INT X0, INT Y0, DOUBLE angle, INT W, INT L );

POINT pnts[4], pnts1[4];

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
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL; 
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Регистрация класса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  
  /* Создание окна */
  hWnd =
    CreateWindow(WND_CLASS_NAME,
      "Clock",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, 
      NULL,
      NULL,
      hInstance,
      NULL);

  /* Показать и перерисаовать окно */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  
  /* Цикл обработки сообщений, пока не будет получено сообщение 'WM_QUIT' */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
} /* End of 'WinMain' funs */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  SYSTEMTIME st;
  /* INT r; */
//  RECT rc;
  
  static BITMAP bm;
  static HDC hMemDCFrame, hMemDCClock;
  static HBITMAP hBmFrame, hBmClock;
  static INT w, h;
  static DOUBLE angle;
  static INT Cx, Cy, LenS, LenM, LenH;
  static HPEN hPen;
  INT W = 50, L = 100;

  /* INT i; */
  /* static CHAR WD[7]; */

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);

    hDC = GetDC(hWnd);
    hMemDCClock = CreateCompatibleDC(hDC);
    hMemDCFrame = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hPen = SelectObject(hMemDCClock, GetStockObject(BLACK_PEN));

    Ellipse(hMemDCClock, w / 2 - 200, h / 2 - 200, w / 2 + 200, h / 2 + 200);
    /* Load logo image */
    hBmFrame = LoadImage(NULL, "chass.bmp", IMAGE_BITMAP, h / 2, w / 2, LR_LOADFROMFILE);

    hPen = CreatePen(PS_SOLID, 5, RGB(200, 0, 250));
    
    GetObject(hBmClock, sizeof(BITMAP), &bm);
    SelectObject(hMemDCClock, hBmClock);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBmFrame != 0)
      DeleteObject(hBmFrame);
    hDC = GetDC(hWnd);
    hBmFrame = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDCFrame, hBmFrame);
    //Ellipse(hMemDCFrame, w / 2 - 200, h / 2 - 200, w / 2 + 200, h / 2 + 200);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
    /*
  case WM_KEYDOWN:
    VK_ESCAPE;
    DestroyWindow(hWnd);
    */
  case WM_TIMER:
    Cx = w / 2;
    Cy = h / 2;
    LenM = 150;
    LenS = 200;
    LenH = 100;    
    
    /* Clear background */
    SelectObject(hMemDCFrame, GetStockObject(WHITE_PEN));
    SelectObject(hMemDCFrame, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDCFrame, 0, 0, w + 1, h + 1);

    /* Draw clockface */
    BitBlt(hMemDCFrame, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);
    
    GetLocalTime(&st);

    /* Write smth */
    /*static CHAR *WD[] = 
    {
      "ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ"
    };
    TextOut(hMemDCFrame, 200, h / 2, WD[st.wDayOfWeek], 2);
    
    ///sprintf(Buf, "%02d.%02d.%d"); */

    TextOut(hMemDCFrame, 200, h - 30, "CGSG'2021", 9); 

    /* second hand  */
    /*
    GetLocalTime(&st);
    angle = (st.wSecond + st.wMilliseconds / 1000.0) * 2 * pi / 60;
    SelectObject(hMemDCFrame, GetStockObject(BLACK_PEN));
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenS * sin(angle)), Cy - (INT)(LenS * cos(angle)));
    */
    
    /* minute hand  */
    angle = (st.wMinute + st.wSecond / 60.0) * 2 * pi / 60;
    SelectObject(hMemDCFrame, hPen);
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenM * sin(angle)), Cy - (INT)(LenM * cos(angle)));

    /* hour hand  */
    angle = ((st.wHour % 12) + st.wMinute / 60.0) * 2 * pi / 12;
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenH * sin(angle)), Cy - (INT)(LenH * cos(angle)));
    Ellipse(hMemDCClock, w / 2 - 200, h / 2 - 200, w / 2 + 200, h / 2 + 200);
    ///angle = (st.wSecond + st.wMilliseconds / 1000.0) * 2 * pi / 60; 
    angle = (st.wSecond % 60 + st.wMilliseconds / 1000.0) * 2 * pi; 

    DrawHand(hMemDCFrame, w / 2, h / 2, angle, 10, 200);

    /* Polygon(hMemDCFrame, pnts, 4);   */
    
    /* pnts1[sizeof(pnts) / sizeof(0)]; */
    /*
    for (i = 0; i < sizeof(pnts) / sizeof(pnts[0]); i++)
    {
      pnts1[i].x = pnts[i].x * co + pnts[i].y * si;
      pnts1[i].y = pnts[i].y * co - pnts[i].x * si;
    }
    */
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    GetLocalTime(&st);

    InvalidateRect(hWnd, NULL, FALSE);
    break;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDCFrame, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    if (hBmFrame != NULL)
      DeleteObject(hBmFrame);
    if (hBmClock != NULL)
      DeleteObject(hBmClock);
    DeleteDC(hMemDCFrame);
    DeleteDC(hMemDCClock);
    DeleteObject(hPen);
    PostQuitMessage(30);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

VOID DrawHand( HDC hDC, INT X0, INT Y0, DOUBLE angle, INT W, INT L ) 
{
  INT i;
  DOUBLE a, co, si;

  a = angle * pi / 180;
  co = cos(a);
  si = sin(a);

  pnts[0].x = -W;
  pnts[0].y = 0;
  pnts[1].x = 0;
  pnts[1].y = -L;
  pnts[2].x = W;
  pnts[2].y = 0;
  pnts[3].x = 0;
  pnts[3].y = W;

  for (i = 0; i < 4; i++)
  {
    pnts1[i].x = pnts[i].x * co - pnts[i].y * si + X0;
    pnts1[i].y = pnts[i].y * co + pnts[i].x * si + Y0;
  }
  SelectObject(hDC, GetStockObject(BLACK_PEN));
  SelectObject(hDC, GetStockObject(GRAY_BRUSH));
  Polygon(hDC, pnts1, 4);
}

/* END OF 't03clock.c' FILE */
