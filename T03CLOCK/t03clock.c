/* FILE NAME: t03clock.c
 * PROGRAMMER: TT6
 * DATE: 11.06.2021
 * PURPOSE: Вывод часов на экран
 */

#include <windows.h>

#include <stdlib.h>

#include <math.h>

#define pi 3.14159265358979323846264

#define WND_CLASS_NAME "My Summer Practice'2021 window class name"

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam );

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
      "Title",
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
  /* HFONT hFnt, hFntOld; */
  POINT pt;
  SYSTEMTIME st;
  /* INT r; */
  RECT rc;
  static BITMAP bm;
  static HDC hMemDCFrame, hMemDCClock;
  static HBITMAP hBmFrame, hBmClock;
  static INT w, h;
  static DOUBLE angle;
  static INT Cx, Cy, LenS, LenM, LenH;
  static HPEN hPen;
  POINT pnts;
  /* static CHAR WD[7]; */

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);

    hDC = GetDC(hWnd);
    hMemDCClock = CreateCompatibleDC(hDC);
    hMemDCFrame = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    /* Load logo image */
    hBmClock = LoadImage(NULL, "chass.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    
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
    
    /*
    static CHAR *WD[] = 
    {
      "ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ"
    };
    TextOut(hMemDCFrame, 200, h / 2, WD[st.wDayOfWeek], 2);
    */
    
    ///sprintf(Buf, "%02d.%02d.%d");

    TextOut(hMemDCFrame, 200, h - 30, "CGSG'2021", 9);
     

    /* second hand  */
    ///GetLocalTime(&st);
    angle = (st.wSecond + st.wMilliseconds / 1000) * 2 * pi / 60;
    SelectObject(hMemDCFrame, GetStockObject(BLACK_PEN));
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenS * sin(angle)), Cy - (INT)(LenS * cos(angle)));

    /* minute hand  */
    angle = (st.wMinute + st.wSecond / 60) * 2 * pi / 60;
    SelectObject(hMemDCFrame, hPen);
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenM * sin(angle)), Cy - (INT)(LenM * cos(angle)));

    /* hour hand  */
    angle = ((st.wHour) + st.wMinute / 60) * 4 * pi / 24;
    MoveToEx(hMemDCFrame, Cx, Cy, NULL);
    LineTo(hMemDCFrame, Cx + (INT)(LenH * sin(angle)), Cy - (INT)(LenH * cos(angle)));


    /*hFntOld = SelectObject(hDCFrame, hFnt);*/

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

/* VOID DrawSecondHand( HDC hDC, INT Cx, INT Cy, INT r, ... ) */

/* END OF 't03clock.c' FILE */
