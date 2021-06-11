/* FILE NAME: t03clock.c
 * PROGRAMMER: TT6
 * DATE: 11.06.2021
 * PURPOSE: Вывод часов на экран
 */

#include <windows.h>
#include <math.h>

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
  /* SYSTEMTIME st; */
  /* INT r; */
  static BITMAP bm;
  static HDC hMemDCFrame, hMemDCClock;
  static HBITMAP hBmFrame, hBmClock;
  static INT w, h;
  static LPSYSTEMTIME st;

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
    GetObject(hBmClock, sizeof(BITMAP), &bm);
    SelectObject(hMemDCClock, hBmClock);
    GetLocalTime(&st);

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
  case WM_TIMER:
    /* Clear background */
    SelectObject(hMemDCFrame, GetStockObject(WHITE_PEN));
    SelectObject(hMemDCFrame, GetStockObject(NULL_BRUSH));
    Rectangle(hMemDCFrame, 0, 0, w + 1, h + 1);

    /* Draw clockface */
    BitBlt(hMemDCFrame, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);

    TextOut(hMemDCFrame, 200, h - 30, "CGSG'2021", 9);

    /*
    hFntOld = SelectObject(hDCFrame, hFnt);
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
    DeleteObject(hBmClock);
    DeleteDC(hMemDCFrame);
    DeleteDC(hMemDCClock);

    PostQuitMessage(30);
    KillTimer(hWnd, 30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}

/* END OF 't03clock.c' FILE */
