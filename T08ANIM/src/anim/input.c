/* FILE NAME : input.c
 * PROGRAMMER: TT6
 * DATE      : 21.06.2021
 * PURPOSE   : 3D animation module.
 */

#include <string.h>
#include "anim.h"
//#include <mmsystem.h>

#define VG4_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos – jc.w ## A ## min) / (jc.w ## A ## max – jc.w ## A ## min) - 1)


INT TT6_MouseWheel;

static VOID TT6_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(TT6_Anim.hWnd, &pt);

  /* Coordinate changing  */
  TT6_Anim.Mdx = 0;
  TT6_Anim.Mdy = 0;
  /* Absolut quantity */
  TT6_Anim.Mx = pt.x;
  TT6_Anim.My = pt.y;
}

static VOID TT6_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(TT6_Anim.hWnd, &pt);

  /* Priraschenie koordinat na ekrane */
  TT6_Anim.Mdx = pt.x - TT6_Anim.Mx;
  TT6_Anim.Mdy = pt.y - TT6_Anim.My;
  /* Absolytnue znacheniya */
  TT6_Anim.Mx = pt.x;
  TT6_Anim.My = pt.y;

  TT6_Anim.Mdz = TT6_MouseWheel;
  TT6_Anim.Mz += TT6_MouseWheel;
  TT6_MouseWheel = 0;
}
#if 0
static VOID TT6_AnimJoystickResponse( VOID )
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
static VOID TT6_AnimJoystickInit( VOID );
#endif /* 0 */

static VOID TT6_AnimKeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(TT6_Anim.Keys);
  for (i = 0; i < 256; i++)
    TT6_Anim.Keys[i] >>= 7;
  memcpy(TT6_Anim.KeysOld, TT6_Anim.Keys, 256);
  memset(TT6_Anim.KeysClick, 0, 256);
}

static VOID TT6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(TT6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    TT6_Anim.Keys[i] >>= 7;
    TT6_Anim.KeysClick[i] = TT6_Anim.Keys[i] && !TT6_Anim.KeysOld[i];
  }
  memcpy(TT6_Anim.KeysOld, TT6_Anim.Keys, 256);
  memset(TT6_Anim.KeysClick, 0, 256);
}

VOID TT6_AnimInputInit( VOID )
{   
  TT6_AnimMouseInit();
  TT6_AnimKeyboardInit();
  /* TT6_AnimJoystickInit(); */
}

VOID TT6_AnimInputResponse( VOID )
{ 
  TT6_AnimMouseResponse();
  TT6_AnimKeyboardResponse();
}

/* END OF 'input.c' FILE */