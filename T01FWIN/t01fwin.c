/* FILE NAME: t01fwin.c
 * PROGRAMMER: TT6
 * DATE: 10.06.2021
 * PURPOSE: Создание и поддержка простейшего окна
 */

#include <windows.h>

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
  wc.style = 0;                            /* Стиль окна */
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.lpszMenuName = NULL;                  /* Имя ресурса меню */
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;      /* Class name */

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
  static HDC hDC;
  HPEN hPen, hPenOld;
  LOGBRUSH lb;
  static INT x, y;
  static INT w, h;
  POINT pt;
  INT i;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 1, 30, NULL);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;
  case WM_LBUTTONDOWN:
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    hDC = GetDC(hWnd);
    Ellipse(hDC, x, y, x + 40, y + 40);

    ReleaseDC(hWnd, hDC);

    return 0;
  case WM_TIMER:
    
    hDC = GetDC(hWnd);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    MoveToEx(hDC, w / 2, h / 2, NULL);
    LineTo(hDC, pt.x, pt.y);
    ReleaseDC(hWnd, hDC);
    break;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    SetBkMode(hDC, OPAQUE);
    SetBkColor(hDC, RGB(255, 255, 0));
    
    lb.lbStyle = BS_SOLID;
    lb.lbHatch = HS_BDIAGONAL;
    lb.lbColor = RGB(255, 0, 0);

    hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); 
    //hPen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 8, &lb, 0, NULL);
    hPenOld = SelectObject(hDC, hPen);

    //MoveToEx(hDC, 30, 300, NULL);
    //LineTo(hDC, 230, 300);
    //LineTo(hDC, 330, 400);

    //Rectangle(hDC, 10, 10, 300, 400);
    //Ellipse(hDC, 10, 10, 300, 300);

    

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    MoveToEx(hDC, w / 2, h / 2, NULL);
    LineTo(hDC, pt.x, pt.y);

    SelectObject(hDC, hPenOld);
    DeleteObject(hPen);

    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 't01fwin.c' FILE */