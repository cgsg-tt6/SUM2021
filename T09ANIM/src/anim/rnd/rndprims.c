/* FILE NAME: rndprims.c
 * PROGRAMMER: TT6
 * DATE: 24.06.2021
 * PURPOSE: 3D animation primitive collection handle module.
 */

#include <stdio.h>
#include <string.h>

#include "rnd.h"

/***
 * Primitive collection support
 ***/

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TT6_RndPrimsCreate( tt6PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(tt6PRIMS));

  if ((Prs->Prims = malloc(sizeof(tt6PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(tt6PRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'TT6_RndPrimsCreate' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 * RETURNS: None.
 */
VOID TT6_RndPrimsFree( tt6PRIMS *Prs )
{
  if (Prs->Prims != NULL)
    free(Prs->Prims);
  memset(Prs, 0, sizeof(tt6PRIMS));
} /* End of 'TT6_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID TT6_RndPrimsDraw( tt6PRIMS *Prs, MATR World )
{
  INT i;

  World = MatrMulMatr(Prs->Trans, World);
  for (i = 0; i < Prs->NumOfPrims; i++)
    TT6_RndPrimDraw(&Prs->Prims[i], World);
} /* End of 'TT6_RndPrimsDraw' function */

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       tt6PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL TT6_RndPrimsLoad( tt6PRIMS *Prs, CHAR *FileName )
{
  BYTE *mem, *ptr;
  INT flen;
  FILE *F;
  DWORD Sign; /* == "G3DM" */
  INT p, m, t;
  DWORD 
    NumOfPrims,
    NumOfMaterials,
    NumOfTextures;

  struct tagG3DMMTL
  {
    CHAR Name[300]; /* Material name */
    /* Illumination coefficients */
    VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
    FLT Ph;             /* Phong power coefficient – shininess */
    FLT Trans;          /* Transparency factor */
    DWORD Tex[8];       /* Texture references 
                        * (8 time: texture number in G3DM file, -1 if no texture) */
    /* Shader information */
    CHAR ShaderString[300]; /* Additional shader information */
    DWORD Shader;       /* Shader number (uses after load into memory) */
  } *mtls;

  memset(Prs, 0, sizeof(tt6PRIMS));

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory and load whole file to memory */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }

  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  if (!TT6_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }

  /* Primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD 
      NumOfVertexes,
      NumOfFacetIndexes,  /* num of facets * 3 */
      MtlNo;              /* Material number in table below (in material section) */
    tt6VERTEX *V;
    INT *Ind;

    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;
    V = (tt6VERTEX *)ptr;
    ptr += sizeof(tt6VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;
    TT6_RndPrimCreate(&Prs->Prims[p], TT6_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = TT6_RndMaterialsSize + MtlNo;
  }

  mtls = (struct tagG3DMMTL *)ptr;
  ptr += sizeof(struct tagG3DMMTL) * NumOfMaterials;
  for (m = 0; m < NumOfMaterials; m++)
  {
    tt6MATERIAL mtl;

    strcpy(mtl.Name, mtls[m].Name);
    mtl.Ka = mtls[m].Ka;
    mtl.Kd = mtls[m].Kd;
    mtl.Ks = mtls[m].Ks;
    mtl.Ph = mtls[m].Ph;
    mtl.Trans = mtls[m].Trans;
    for (t = 0; t < 8; t++)
      mtl.Tex[t] = mtls[m].Tex[t] == -1 ? -1 : TT6_RndTexturesSize + mtls[m].Tex[t];
    TT6_RndMtlAdd(&mtl);
  }

  for (t = 0; t < NumOfTextures; t++)
  {
    struct
    {
      CHAR Name[300]; /* Texture name */
      DWORD W, H;     /* Texture image size */
      DWORD C;        /* Texture image pixel component count */
    } *tex = (VOID *)ptr;
    ptr += sizeof(*tex);
    TT6_RndTexAddImg(tex->Name, tex->W, tex->H, tex->C, ptr);
    ptr += tex->W * tex->H * tex->C;
  }

  free(mem);
  return TRUE;
} /* End of 'TT6_RndPrimsDraw' function */

/* END OF 'rndprims.c' FILE */
