/* FILE NAME : u_ctrl.c
 * PROGRAMMER: TT6
 * DATE      : 22.06.2021
 * PURPOSE   : Control unit.
 */

#include "units.h"

typedef struct
{
  TT6_UNIT_BASE_FIELDS;
  VEC Pos;
  tt6PRIM Pr;
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
  tt6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{2, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 2, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  INT I[] = {0, 1, 2};

  Uni->Pos = VecSet(0, 1, 0);
  TT6_RndPrimCreate(&Uni->Pr, TT6_RND_PRIM_TRIMESH, V, 3, I, 3);
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_BALL *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimFree(&Uni->Pr);
} /* End of 'TT6_UnitClose' function */

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
  Uni->Pos.X += Ani->DeltaTime * 0.5;
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
  TT6_RndPrimDraw(&Uni->Pr, MatrRotateX(270));
  /* DrawSphere(Uni->Pos, 3); */
} /* End of 'TT6_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateBall( VOID )
{
  tt6UNIT *Uni;

  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateBall' function */


/* END OF 'rndshd.c' FILE */

