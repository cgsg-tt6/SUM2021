/* FILE NAME : timer.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : timer.
 */

#include <windows.h>
#include <time.h>

#include "anim.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID TT6_TimerInit( VOID )
{
  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  TT6_Anim.IsPause = FALSE;
  TT6_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID TT6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  TT6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  TT6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (TT6_Anim.IsPause)
  {
    TT6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    TT6_Anim.DeltaTime = TT6_Anim.GlobalDeltaTime;
    TT6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    TT6_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}


/* END OF 'rnd.h' FILE */