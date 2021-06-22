/* FILE NAME : u_ctrl.c
 * PROGRAMMER: TT6
 * DATE      : 22.06.2021
 * PURPOSE   : Control unit.
 */

#include "units.h"
#if 0
typedef struct
{
  TT6_UNIT_BASE_FIELDS;
  VEC Pos;
} tt6UNIT_BALL;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_BALL *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_BALL *Uni, tt6ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} /* End of 'TT6_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_BALL *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_BALL *Uni, tt6ANIM *Ani )
{
  Uni->Pos.X += Ani->DeltaTime * 2.5;
} /* End of 'TT6_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_BALL *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_BALL *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimDraw(&Pr, MatrRotateX(270));
} /* End of 'TT6_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateBall( VOID )
{
  tt6UNIT *Uni;

  if ((Uni = (tt6UNIT_BALL *)TT6_AnimUnitCreate(sizeof(tt6UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateBall' function */
#endif /* 0 */

