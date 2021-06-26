/* FILE NAME : rndmtl.c
 * PROGRAMMER: TT6
 * DATE      : 26.06.2021
 * PURPOSE   : .
 */

#include "rndres.h"
#include <glew.h>
#include <gl/glu.h>

INT TT6_RndMaterialsSize;
tt6MATERIAL TT6_RndMaterials[TT6_MAX_MATERIALS];

VOID TT6_RndMtlInit( VOID )
{
  INT i;
  tt6MATERIAL mtl = {{0}};

  strcpy(mtl.Name, "DEFAULT");
  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(1);
  mtl.Ks = VecSet1(0.0);
  mtl.Ph = 30;
  mtl.Trans = 1;
  mtl.ShdNo = 0;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;

  TT6_RndMaterialsSize = 0;
  TT6_RndMtlAdd(&mtl);
} /* End of 'TT6_RndMtlInit' function */

VOID TT6_RndMtlClose( VOID )
{
  TT6_RndMaterialsSize = 0;
} /* End of 'TT6_RndMtlClose' function */

INT TT6_RndMtlAdd( tt6MATERIAL *Mtl )
{
  /*
  INT i;
  
  for (i = 0; i < TT6_RndMaterialsSize; i++)
    if (strcmp(Mtl, TT6_RndMaterials[i].Name) == 0)
      return i;
  */
  if (TT6_RndMaterialsSize >= TT6_MAX_MATERIALS)
    return 0;
  TT6_RndMaterials[TT6_RndMaterialsSize] = *Mtl;
  return TT6_RndMaterialsSize++;
} /* End of 'TT6_RndMtlAdd' function */

/* Get default material function */
tt6MATERIAL TT6_RndMtlGetDeg( VOID )
{
  return TT6_RndMaterials[0];
} /* End of 'TT6_RndMtlGetDef' function */

/* Get material pointer function */
tt6MATERIAL * TT6_RndMtlGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo >= TT6_RndMaterialsSize)
    MtlNo = 0;
  return &TT6_RndMaterials[MtlNo];
} /* End of 'TT6_RndMtlGet' function */

INT TT6_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  tt6MATERIAL *mtl;

  /* Set material pointer */
  mtl = TT6_RndMtlGet(MtlNo);

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= TT6_RndShadersSize)
    prg = 0;
  prg = TT6_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, TT6_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, TT6_Anim.GlobalTime);
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";  /* --> shader: uniform bool IsTexture2; */

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, TT6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'TT6_RndMtlApply' function */

VOID TT6_RndMtlFree( INT MtlNo )
{
} /* End of 'TT6_RndMtlFree' function */

/* END OF 'rndmtl.c' FILE */