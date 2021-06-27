/* FILE NAME : unit.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : .
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitRender' function */

/* -- функция создания объекта: */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_AnimUnitCreate( INT Size )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(tt6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = TT6_UnitInit;
  Uni->Close = TT6_UnitClose;
  Uni->Response = TT6_UnitResponse;
  Uni->Render = TT6_UnitRender;

  return Uni;
} /* End of 'TT6_AnimUnitCreate' function */


/* END OF 'unit.c' FILE */