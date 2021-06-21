/* FILE NAME : anim.h
 * PROGRAMMER: TT6
 * DATE      : 19.06.2021
 * PURPOSE   : 3D animation module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define TT6_MAX_UNITS 3000

#define TT6_UNIT_BASE_FIELDS \
  VOID (*Init)( tt6UNIT *Uni, tt6ANIM *Ani );      \
  VOID (*Close)( tt6UNIT *Uni, tt6ANIM *Ani );     \
  VOID (*Response)( tt6UNIT *Uni, tt6ANIM *Ani );  \
  VOID (*Render)( tt6UNIT *Uni, tt6ANIM *Ani )

#define VG4_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos – jc.w ## A ## min) / (jc.w ## A ## max – jc.w ## A ## min) - 1)

typedef struct tagtt6UNIT tt6UNIT;
typedef struct tagtt6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  tt6UNIT *Units[TT6_MAX_UNITS];
  INT NumOfUnits;

  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  BYTE Keys[256];
  BYTE KeysClick[256];
  BYTE KeysOld[256];

  INT Mx, My, Mz, Mdx, Mdy, Mdz; /* Mouse data */
  
  BYTE
    JBut[32], JButOld[32], JButClick[32];
  INT JPov;
  DBL
    JX, JY, JZ, JR;
} tt6ANIM;

typedef struct tagtt6UNIT tt6UNIT;
struct tagtt6UNIT
{
  TT6_UNIT_BASE_FIELDS;
};

extern tt6ANIM TT6_Anim;

VOID TT6_AnimInit( HWND hWnd );
VOID TT6_AnimClose( VOID );
VOID TT6_AnimResize( INT W, INT H );
VOID TT6_AnimCopyFrame( HDC hDC );
VOID TT6_AnimRender( VOID );
VOID TT6_AnimFlipFullScreen( VOID );

VOID TT6_AnimUnitAdd( tt6UNIT *Uni );
tt6UNIT * TT6_AnimUnitCreate( INT Size );

VOID TT6_TimerInit( VOID );
VOID TT6_TimerResponse( VOID );

VOID TT6_AnimInputInit( HWND hWnd );
VOID TT6_AnimInputResponse( VOID );

//VOID TT6_AnimKeyboardInit( VOID );  
//VOID TT6_AnimKeyboardResponse( VOID );

VOID TT6_AnimMouseInit( VOID );
VOID TT6_AnimMouseResponse( VOID );

VOID TT6_AnimJoystickInit( VOID );
VOID TT6_AnimJoystickResponse( VOID );

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */
