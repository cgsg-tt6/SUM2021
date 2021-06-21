/* FILE NAME : input.c
 * PROGRAMMER: TT6
 * DATE      : 21.06.2021
 * PURPOSE   : 3D animation module.
 */

#include <string.h>
#include "anim.h"
//#include <mmsystem.h>

extern INT TT6_MouseWheel;
POINT pt;

VOID TT6_AnimMouseInit( HWND hWnd )
{
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  TT6_Anim.Mx = pt.x;
  TT6_Anim.My = pt.y;
}

VOID TT6_AnimMouseResponse( VOID )
{
  TT6_Anim.Mx = pt.x;
  TT6_Anim.My = pt.y;
}
#if 0
VOID TT6_AnimJoystickResponse( VOID )
{
  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;                                     

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          JBut[i] = (ji.dwButtons >> i) & 1;
          JButClick[i] = JBut[i] && !JButOld[i];
          JButOld[i] = JBut[i];
        }
        /* Axes */
        JX = VG4_GET_JOYSTIC_AXIS(X);
        JY = VG4_GET_JOYSTIC_AXIS(Y);
        JZ = VG4_GET_JOYSTIC_AXIS(Z);
        JR = VG4_GET_JOYSTIC_AXIS(R);
        /* Point of view */
        JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}
VOID TT6_AnimJoystickInit( VOID );
#endif /* 0 */

/* VOID TT6_AnimKeyboardInit( VOID );
VOID TT6_AnimKeyboardResponse( VOID ); */


VOID TT6_AnimInputInit( HWND hWnd )
{   
  TT6_AnimMouseInit(hWnd);
  /* TT6_AnimJoystickInit(); */
}

VOID TT6_AnimInputResponse( VOID )
{ 
  TT6_AnimMouseResponse();
}

/* END OF 'input.c' FILE */