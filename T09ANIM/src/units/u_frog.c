/* FILE NAME : u_draw.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : Draw cow unit.
 */

#include <stdio.h>

#include "units.h"

typedef struct tagtt6UNIT_FROG tt6UNIT_FROG;
struct tagtt6UNIT_FROG
{
  TT6_UNIT_BASE_FIELDS;
  tt6PRIMS Frog;
  VEC Pos;
  MATR m;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_FROG *Uni, tt6ANIM *Ani )
{
  Uni->m = MatrMulMatr(MatrRotateX(-90), MatrScale(VecSet(2.5, 2.5, 2.5)));

  TT6_RndPrimsLoad(&Uni->Frog, "BIN/MODELS/frog.g3dm");
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_FROG *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsFree(&Uni->Frog);
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_FROG *Uni, tt6ANIM *Ani )
{
  if ((Ani->Keys[VK_LEFT] == 1) || (Ani->Keys[VK_RIGHT] == 1))
    Uni->m = MatrMulMatr(Uni->m, MatrTranslate(VecSet(-(Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]) * Ani->GlobalDeltaTime * 10, 0, 0)));
 
  if ((Ani->Keys[VK_DOWN] == 1) || (Ani->Keys[VK_UP] == 1))
    Uni->m = MatrMulMatr(Uni->m, MatrTranslate(VecSet(0, 0, -(Ani->Keys[VK_DOWN] - Ani->Keys[VK_UP]) * Ani->GlobalDeltaTime * 10)));
  if (Ani->KeysClick[VK_RETURN] == 1)
  {
    Uni->m = MatrMulMatr(Uni->m, MatrRotateZ(10));
    return;
  }
  /* Rotation - should to be changed */
  /// QUESTION
  /* We have to know the coordinates of the frog to count MatrTranslate - HOW? */
  if ((Ani->Keys['R'] == 1) || (Ani->Keys['F'] == 1))
    Uni->m = MatrMulMatr(Uni->m, MatrRotateY(-36 * (Ani->Keys['R'] - Ani->Keys['F']) * Ani->GlobalDeltaTime));
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_FROG *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsDraw(&Uni->Frog, Uni->m);
} /* End of 'TT6_UnitRender' function */

/* Object creation function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateFrog( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_FROG))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateFrog' function */

/* END OF 'u_frog.c' FILE */
