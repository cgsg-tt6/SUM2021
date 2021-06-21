/* FILE NAME  : timer.c
 * PROGRAMMER : TT6
 * DATE       : 16.06.2021
 * PURPOSE    : count time
 */

#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/*
DOUBLE GLB_Time       -- общее время в секундах
DOUBLE GLB_DeltaTime  -- межкадровое время в секундах
DOUBLE GLB_FPS        -- количество кадров в секунду
BOOL GLB_IsPause   -- флаг паузы	дополнительно запоминаем (в "тиках"-"клоках"):
LONG StartTime     -- время начала программы
LONG OldTime       -- время предыдущего кадра
LONG PauseTime     -- время простоя в паузе
LONG OldFPSTime    -- время предыдущего
                      замера FPS
LONG FrameCount    -- счетчик кадров для FPS
*/

DOUBLE GLB_Time,       
       GLB_DeltaTime,
       GLB_FPS;
BOOL   GLB_IsPause;   
static LONG   StartTime,
       OldTime,       
       PauseTime,     
       OldFPSTime,
       FrameCount;    

  VOID GLB_TimerInit( VOID )      /* initialization of the timer */
  {
    StartTime = OldTime = OldFPSTime = clock();
    FrameCount = 0;
    GLB_IsPause = FALSE;
  }

  VOID GLB_TimerResponse( VOID )  /* obnovlenie tajmera */
  {
    LONG t = clock();

    if (!GLB_IsPause)
    {
      GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
      GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
    }
    else
    {
      PauseTime += t - OldTime;
      GLB_DeltaTime = 0;
    }
    FrameCount++;
    if (t - OldFPSTime > CLOCKS_PER_SEC)
    {
      GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
      OldFPSTime = t;
      FrameCount = 0;
    }
  OldTime = t;  
  }
/* TIMER.C/TIMER.H */

/* END OF 'timer.c' FILE */