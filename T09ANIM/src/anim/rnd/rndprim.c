/* FILE NAME : rndprim.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation primitive handle module.
 */

#include <stdio.h>
#include <string.h>

#include "../anim.h"

/***
 * Primitive support
 ***/

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - primitive type
 *       tt6PRIM_TYPE Type;
 *   - vertex attributes array:
 *       tt6VERTEX *V;
 *   - number of vertices:
 *       INT NumOfV;
 *   - index array (for trimesh – by 3 ones, may be NULL)
 *       INT *I;
 *   - number of indices
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID TT6_RndPrimCreate( tt6PRIM *Pr, tt6PRIM_TYPE Type, tt6VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(tt6PRIM));   /* <-- <string.h> */

  if (V != NULL && NumOfV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tt6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(tt6VERTEX),
                          (VOID *)0);                                /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(tt6VERTEX),
                          (VOID *)sizeof(VEC));                      /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(tt6VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2)));     /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(tt6VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
  }

  if (I != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;
  Pr->Trans = MatrIdentity();
  Pr->Type = Type;
} /* End of 'TT6_RndPrimCreate' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 * RETURNS: None.
 */
VOID TT6_RndPrimFree( tt6PRIM *Pr )
{
  glDeleteBuffers(1, &Pr->IBuf);

  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);

  memset(Pr, 0, sizeof(tt6PRIM));
} /* End of 'TT6_RndPrimFree' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - world transformation matrix
 *       MATR World;
 * RETURNS: None.
 */
VOID TT6_RndPrimDraw( tt6PRIM *Pr, MATR World )
{
  INT gl_prim_type = Pr->Type == TT6_RND_PRIM_TRIMESH ? GL_TRIANGLES : GL_TRIANGLE_STRIP;
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, TT6_RndMatrVP);
  INT loc, RndProgId;

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.A[0]);

  RndProgId = TT6_RndMtlApply(Pr->MtlNo);
  if ((loc = glGetUniformLocation(RndProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(RndProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.A[0]);
  if ((loc = glGetUniformLocation(RndProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.A[0]);
  if ((loc = glGetUniformLocation(RndProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &TT6_RndCamLoc.X);

  /* Draw triangles */
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  
  glBindVertexArray(Pr->VA);
  if (Pr->IBuf == 0)
    /* otrisovka (draw) */
    glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
} /* End of 'TT6_RndPrimDraw' function */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       tt6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL TT6_RndPrimLoad( tt6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0, size;
  tt6VERTEX *V;
  INT *Ind;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(tt6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }
  }

  size = sizeof(tt6VERTEX) * nv + sizeof(INT) * nind;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
  memset(V, 0, size);

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      VEC4 c = {0};

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv].C = c;
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%i", &nc);
          if (nc < 0)
            nc = nv + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind[nind++] = n0;
            Ind[nind++] = n1;
            Ind[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }
  fclose(F);

  for (i = 0; i < nv; i++)
    V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < nind; i += 3)
  {
    VEC
      p0 = V[Ind[i]].P,
      p1 = V[Ind[i + 1]].P,
      p2 = V[Ind[i + 2]].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

      V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N);
      V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
      V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
    }
  for (i = 0; i < nv; i++)
    V[i].N = VecNormalize(V[i].N);

  TT6_RndPrimCreate(Pr, TT6_RND_PRIM_TRIMESH, V, nv, Ind, nind);
  free(V);
  return TRUE;
} /* End of 'TT6_RndPrimLoad' function */

BOOL TT6_RndPrimCreateGrid (tt6PRIM *Pr, INT SplitW, INT SplitH)
{
  INT i, j, k;

  /* Set indexes */
  for (k = 0, i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->Ind[k++] = i * SplitW + j;
      Pr->Ind[k++] = i * SplitW + j + 1;
      Pr->Ind[k++] = (i + 1) * SplitW + j;

      
      Pr->Ind[k++] = (i + 1) * SplitW + j; 
      Pr->Ind[k++] = i * SplitW + j + 1;
      Pr->Ind[k++] = (i + 1) * SplitW + j + 1;
    }
    return TRUE;
} /* End of 'TT6_RndPrimCreateGrid' function */

/*
BOOL TT6_RndPrimCreateSphere( tt6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  TT6_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * (SplitH - 1) * 6);
   vertexes 
   indexes 
  for (i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->I[] = (i + 1) * SplitW + j;
    }
} */

BOOL TT6_RndPrintCreatePlane( tt6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH )
{
  INT i, j;
  
  if (!TT6_RndPrimCreateGrid(Pr, SplitW, SplitH))
    return FALSE;

  /* Set vertexes */
  for (i = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++)
      Pr->V[i * SplitW + j].P =
        VecAddVec3(P, VecMulNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / (SplitH - 1.0)));
    return TRUE;  
} /* End of 'TT6_RndPrimCreatePlane' function */

/* END OF 'rndprim.c' FILE */