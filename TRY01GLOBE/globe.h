/* FILE NAME: globe.h
 * PROGRAMMER: TT6
 * DATE: 16.06.2021
 * PURPOSE: draw 3D spher
 */ 

#include <time.h>
#include "timer.h"
#include "mth.h"

#define r 1

/* typedef DOUBLE DBL; */

static INT WinW, WinH;

/* Forward references */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam,LPARAM lParam );
VOID GlobeDraw( HDC hDC );
VOID GlobeSet( INT W, INT H, DBL R );
VEC RotateZ( VEC V, DBL Angle );
VEC RotateY( VEC V, DBL Angle );
VEC RotateX( VEC V, DBL Angle );

/* END OF 'globe.h' FILE */