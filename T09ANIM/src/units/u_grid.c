/* FILE NAME : u_grid.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : Draw grid-floor-plane unit.
 */

#include <stdio.h>

#include "units.h"

typedef struct tagtt6UNIT_GRID tt6UNIT_GRID;
struct tagtt6UNIT_GRID
{
  TT6_UNIT_BASE_FIELDS;
  tt6PRIMS Grid;
  MATR m;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_GRID *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_GRID *Uni, tt6ANIM *Ani )
{
  Uni->m = MatrMulMatr(MatrRotateX(-90), MatrScale(VecSet(2.5, 2.5, 2.5)));
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_GRID *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_GRID *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsFree(&Uni->Grid);
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_GRID *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_GRID *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_GRID *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_GRID *Uni, tt6ANIM *Ani )
{
  TT6_RndPrimsDraw(&Uni->Grid, Uni->m);
} /* End of 'TT6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitCreateGrid( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_GRID))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitCreateGrid' function */

/* END OF 'u_grid.c' FILE */
