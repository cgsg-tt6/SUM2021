/* FILE NAME : rndres.h
 * PROGRAMMER: TT6
 * DATE      : 24.06.2021
 * PURPOSE   : 3D animation module.
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "../../../def.h"
#include "../../anim.h"

/***
 * SHADERS
 ***/

/* Shaders stock maximum size */
#define TT6_MAX_SHADERS 30
#define TT6_STR_MAX 300

/* Shader program store type */
typedef struct tagtt6SHADER tt6SHADER;
struct tagtt6SHADER
{
  CHAR Name [TT6_STR_MAX]; /* Shader filename prefix */
  INT ProgId;              /* Shader program Id */
}; 

/* Arrary of shaders */
extern tt6SHADER TT6_RndShaders[TT6_MAX_SHADERS];
/* Shaders array store size */
extern INT TT6_RndShadersSize;

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETUNS: None.
 */
VOID TT6_RndShdFree( INT ProgId );

/***
 * Shaders stock functions
 ***/

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndShadersInit( VOID );

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndShadersClose( VOID );

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT TT6_RndShaderAdd( CHAR *FileNamePrefix );

/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndShadersUpdate( VOID );

/***
 * MATERIALS
 ***/

#define TT6_MAX_MATERIALS 300

/* Material store type */
typedef struct tagtt6MATERIAL
{
  CHAR Name[TT6_STR_MAX]; /* Material name */

  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */

  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table (or -1) */

  INT ShdNo;                /* Shader number in shader table */
} tt6MATERIAL;

/* Material stock */
extern tt6MATERIAL TT6_RndMaterials[TT6_MAX_MATERIALS]; /* Array of materials */
extern INT TT6_RndMaterialsSize;                 /* Materials array store size */
VOID TT6_RndMtlInit( VOID );
VOID TT6_RndMtlClose( VOID );
INT TT6_RndMtlAdd( tt6MATERIAL *Mtl );
INT TT6_RndMtlApply( INT MtlNo );
VOID TT6_RndMtlFree( INT MtlNo );
/* Get default material function */
tt6MATERIAL TT6_RndMtlGetDeg( VOID );
/* Get material pointer function */
tt6MATERIAL * TT6_RndMtlGet( INT MtlNo );

/***
 * TEXTURES
 ***/

#define TT6_MAX_TEXTURES 30

typedef struct tagtt6TEXTURES
{
  CHAR Name[TT6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} tt6TEXTURES;

/* Textures stock */
extern tt6TEXTURES TT6_RndTextures[TT6_MAX_TEXTURES]; /* Array of textures */
extern INT TT6_RndTexturesSize;               /* Textures array store size */

VOID TT6_RndTexInit( VOID );
VOID TT6_RndTexClose( VOID );
INT TT6_RndTexAdd( CHAR *FileName );
INT TT6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

/* From 'rndres.c' file */
VOID TT6_RndResInit( VOID );
VOID TT6_RndResClose( VOID );

#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */
