/* FILE NAME : u_cow.c
 * PROGRAMMER: TT6
 * DATE      : 25.06.2021
 * PURPOSE   : Draw cow unit.
 */

#include <stdio.h>

#include "units.h"

typedef struct tagtt6UNIT_COW tt6UNIT_COW;
struct tagtt6UNIT_COW
{
  TT6_UNIT_BASE_FIELDS;
  tt6PRIMS Cow;
  VEC Pos;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_COW *Uni, tt6ANIM *Ani )
{
  /// TT6_RndPrimLoad(&Uni->Cow, "BIN/MODELS/shrimp.obj");
  TT6_RndPrimsLoad(&Uni->Cow, "BIN/MODELS/frog.g3dm");
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_COW *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsFree(&Uni->Cow);
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_COW *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_COW *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsDraw(&Uni->Cow, MatrMulMatr3(MatrRotateX(-90), MatrScale(VecSet(2.5, 2.5, 2.5)), MatrRotateY(Ani->Time * 30)));
} /* End of 'TT6_UnitRender' function */

/* -- функция создания объекта: */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateCow( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateCow' function */
