/* FILE NAME : rndprim.c
 * PROGRAMMER: TT6
 * DATE      : 18.06.2021
 * PURPOSE   : 3D animation primitive handle module.
 */

#include <stdio.h>
#include <string.h>

#include "rnd.h"

/***
 * Primitive support
 ***/

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 *   - number of vertexes and indexes:
 *       INT NoofV, NoofI;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE if not enough memory.
 */
BOOL TT6_RndPrimCreate( tt6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(tt6PRIM));   /* <-- <string.h> */
  /* Calculate memory size for primitive data */
  size = sizeof(tt6VERTEX) * NoofV + sizeof(INT) * NoofI;
  /* Allocate memory */
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);
  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);
  /* Store data sizes */
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'TT6_RndPrimCreate' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       tt6PRIM *Pr;
 * RETURNS: None.
 */
VOID TT6_RndPrimFree( tt6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
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
  MATR wvp = MatrMulMatr3(Pr->Trans, World, TT6_RndMatrVP);
  POINT *pnts;
  INT i;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return; 

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * TT6_RndFrameW / 2); 
    pnts[i].y = (INT)((-p.Y + 1) * TT6_RndFrameH / 2);
  }

  /* Draw triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(TT6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(TT6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(TT6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(TT6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
} /* End of 'TT6_RndPrimDraw' function */

/* ARGUMENTS:
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
  INT i, nv = 0, nind = 0;
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

  if (!TT6_RndPrimCreate(Pr, nv, nind))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
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
            Pr->I[nind++] = n0;
            Pr->I[nind++] = n1;
            Pr->I[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }

  fclose(F);
  return TRUE;
} /* End of 'TT6_RndPrimLoad' function */

BOOL TT6_RndPrimCreateGrid (tt6PRIM *Pr, INT SplitW, INT SplitH)
{
  INT i, j, k;

  if (!TT6_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * (SplitH - 1) * 6))
    return FALSE;

  /* Set indexes */
  for (k = 0, i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->I[k++] = i * SplitW + j;
      Pr->I[k++] = i * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j;

      
      Pr->I[k++] = (i + 1) * SplitW + j; 
      Pr->I[k++] = i * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j + 1;
    }
    return TRUE;
} /* End of 'TT6_RndPrimCreateGrid' function */

/*BOOL TT6_RndPrimCreateSphere( tt6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
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

  /* set vertexes */
  for (i = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++)
      Pr->V[i * SplitW + j].P =
        VecAddVec3(P, VecMulNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / (SplitH - 1.0)));
    return TRUE;
} /* End of 'TT6_RndPrimCreatePlane' function */

/* END OF 'rndprim.c' FILE */