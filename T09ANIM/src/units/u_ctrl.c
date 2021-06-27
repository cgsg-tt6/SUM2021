/* FILE NAME : u_ctrl.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation control unit.
 */

#include <stdio.h>
#include "units.h"

typedef struct tagtt6UNIT_CTRL tt6UNIT_CTRL;
struct tagtt6UNIT_CTRL
{
  TT6_UNIT_BASE_FIELDS;
  tt6PRIM Ctrl;
  VEC 
    CamLoc, Dir, At, Right;
  INT Speed;
  DBL AngleSpeed;
};

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitInit( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  Uni->CamLoc = VecSet(0, 25, 35);
  Uni->At = VecSet(0, 0, 0);
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
  Uni->Speed = 15;
  Uni->AngleSpeed = 5;
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitClose( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
} /* End of 'TT6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  CHAR Buf[100];

  sprintf(Buf, "FPS: %.3f", Ani->FPS);
  SetWindowText(Ani->hWnd, Buf);

  /* Move camera nearer-farer with mousewheel */
  Uni->CamLoc = VecAddVec(Uni->CamLoc, 
      VecMulNum(Uni->Dir, Ani->DeltaTime * Uni->Speed * TT6_Anim.Mdz));
  TT6_RndCamSet(Uni->CamLoc, Uni->At, VecSet(0, 1, 0));
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_FROG *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitControl( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_CTRL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitControl' function */

/* END OF 'u_ctrl.c' FILE */