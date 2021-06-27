/* FILE NAME : rndtex.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation module.
 */

#include "../../anim.h"
#include "rndres.h"

tt6TEXTURES TT6_RndTextures[TT6_MAX_TEXTURES]; /* Array of textures */
INT TT6_RndTexturesSize;                    /* Textures array store size */

VOID TT6_RndTexInit( VOID )
{
  TT6_RndTexturesSize = 0;
} /* End of 'TT6_RndTexInit' function */

VOID TT6_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < TT6_RndTexturesSize; i++)
    glDeleteTextures(1, &TT6_RndTextures[i].TexId);
} /* End of 'TT6_RndTexClose' function */

INT TT6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT MipLevels;

  if (TT6_RndTexturesSize >= TT6_MAX_TEXTURES)
    return -1;
  strncpy(TT6_RndTextures[TT6_RndTexturesSize].Name, Name, TT6_STR_MAX - 1);
  TT6_RndTextures[TT6_RndTexturesSize].W = W;
  TT6_RndTextures[TT6_RndTexturesSize].H = H;

  /* Move image to GPU memory */
  glGenTextures(1, &TT6_RndTextures[TT6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, TT6_RndTextures[TT6_RndTexturesSize].TexId);

  MipLevels = log(W < H ? W : H) / log(2);
  MipLevels = MipLevels < 1 ? 1 : MipLevels;
  glTexStorage2D(GL_TEXTURE_2D, MipLevels, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
    C == 4 ? GL_RGBA : C == 3 ? GL_RGB : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);
  return TT6_RndTexturesSize++;
} /* End of 'TT6_RndTexAddImg' function */

INT TT6_RndTexAdd( CHAR *FileName )
{
  return -1;
} /* End of 'TT6_RndTexAdd' function */

/* END OF 'rndtex.c' FILE */