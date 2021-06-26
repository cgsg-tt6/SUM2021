/* FILE NAME : u_Shrimp.c
 * PROGRAMMER: TT6
 * DATE      : 21.06.2021
 * PURPOSE   : Draw Shrimp unit.
 */

#include <stdio.h>

#include "units.h"

typedef struct tagtt6UNIT_Shrimp tt6UNIT_Shrimp;
struct tagtt6UNIT_Shrimp
{
  TT6_UNIT_BASE_FIELDS;
  tt6PRIMS Shrimp;
  VEC Pos;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_Shrimp *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_Shrimp *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsLoad(&Uni->Shrimp, "BIN/MODELS/shrimp.g3dm");
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_Shrimp *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_Shrimp *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsFree(&Uni->Shrimp);
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_Shrimp *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_Shrimp *Uni, tt6ANIM *Ani )
{
  CHAR Buf[100];

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_Shrimp *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_Shrimp *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsDraw(&Uni->Shrimp, MatrMulMatr3(MatrScale(VecSet1(0.5)), MatrRotateY(Ani->Time * 30), MatrTranslate(VecSet(-13, 0, 0))));
} /* End of 'TT6_UnitRender' function */

/* funkcia sozdania objecta */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateShrimp( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_Shrimp))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateShrimp' function */
