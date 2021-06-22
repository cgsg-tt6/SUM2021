/* FILE NAME : u_ctrl.c
 * PROGRAMMER: TT6
 * DATE      : 22.06.2021
 * PURPOSE   : Control unit.
 */

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

static VOID TT6_UnitInit( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  Uni->CamLoc = VecSet(0, 3, 5);
  Uni->Speed = 5;
  Uni->AngleSpeed = 5;
  Uni->At = VecSet(0, 0, 0);
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
  TT6_RndCamSet(VecSet(15.0, 30.0, 15.0), VecSet(0.0, 1.0, 0.0), VecSet(0.0, 1.0, 0.0));
} /* End of 'TT6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
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
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitResponse( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  /* if (VazFlag) */
  if ((Ani->Keys[VK_UP]) || (Ani->Keys[VK_DOWN]))
  {
    Uni->CamLoc.Y += Ani->DeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
    Uni->At.Y += Ani->DeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
  }
} /* End of 'TT6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       tt6UNIT_COW *Uni;
 *   - animation context:
 *       tt6ANIM *Ani;
 * RETURNS: None.
 */
static VOID TT6_UnitRender( tt6UNIT_CTRL *Uni, tt6ANIM *Ani )
{
  //TT6_RndMatrView = MatrView(CamLoc, CamDir, CamUp);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
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

#if 0
static VOID TT6_UnitResponse( tt6UNIT_CAM *Uni, tt6ANIM *Ani )
{
  Uni->CamLoc = 
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->DeltaTime /* * Uni->Speed */ * 
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));
} /* End of 'TT6_UnitResponse' function */

tt6UNIT * TT6_UnitSetCam( VOID )
{
  tt6UNIT *Uni;

  /* Memory allocation */
  if ((Uni = TT6_AnimUnitCreate(sizeof(tt6UNIT_CAM))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)TT6_UnitInit;
  Uni->Close = (VOID *)TT6_UnitClose;
  Uni->Response = (VOID *)TT6_UnitResponse;
  Uni->Render = (VOID *)TT6_UnitRender;

  return Uni;
} /* End of 'TT6_UnitSetCam' function */
#endif /* 0 */

/* END OF 'u_ctrl.c' FILE */