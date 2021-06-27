/* FILE NAME : rndbase.c
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : 3D animation rendering global data module.
 */

#include "../anim.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment (lib, "opengl32")

VOID TT6_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };

  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  TT6_hRndWnd = hWnd;
  TT6_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(TT6_hRndDC, &pfd);
  DescribePixelFormat(TT6_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(TT6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  TT6_hRndGLRC = wglCreateContext(TT6_hRndDC);
  wglMakeCurrent(TT6_hRndDC, TT6_hRndGLRC);

  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(TT6_hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(TT6_hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(TT6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(TT6_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(TT6_hRndGLRC);

  TT6_hRndGLRC = hRC;
  wglMakeCurrent(TT6_hRndDC, TT6_hRndGLRC);

  /* Set default OpenGL parameters */
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.30f, 0.47f, 0.8f, 1);
  wglSwapIntervalEXT(0);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  TT6_RndResInit();

  /* Render parameters setup */
  TT6_RndProjSize = 0.1;
  TT6_RndProjDist = TT6_RndProjSize;
  TT6_RndProjFarClip = 300;
  TT6_RndFrameH = 47;
  TT6_RndFrameW = 47;
  TT6_RndCamSet(VecSet(18, 18, 18), VecSet(0, 0, 0), VecSet(0, 1, 0));


} /* End of 'TT6_RndInit' function */

/* Render subsystem deinitialivation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndClose( VOID )
{
  TT6_RndResClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(TT6_hRndGLRC);
  ReleaseDC(TT6_hRndWnd, TT6_hRndDC);
} /* End of 'TT6_RndClose' function */

/* Render subsystem frame resize function.
 * ARGUMENTS: 
 *   - new frame width & height:
 *       INT W, H;
 * RETURNS: None.
 */
VOID TT6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* Setup projection */
  TT6_RndFrameW = W;
  TT6_RndFrameH = H;

  /* Recount projection */
  TT6_RndProjSet();
} /* End of 'TT6_RndResize' function */

VOID TT6_RndCopyFrame( VOID )
{
  /// SwapBuffers(TT6_hRndDC);
  wglSwapLayerBuffers(TT6_hRndDC, WGL_SWAP_MAIN_PLANE);
} /* End of 'TT6_RndCopyFrame' function */

/* Rendering start draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndStart( VOID )
{
  static DBL reload;

  if ((reload += TT6_Anim.GlobalDeltaTime) > 1)
  {
    reload = 0;
    TT6_RndShadersUpdate();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'TT6_RndStart' function */

/* Rendering finalize draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndEnd( VOID )
{
  glFinish();
} /* End of 'TT6_RndEnd' function */

/* Setup rendering project function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID TT6_RndProjSet( VOID )
{
  DOUBLE rx, ry;

  rx = ry = TT6_RndProjSize;

  /* Correct aspect ratio */
  if (TT6_RndFrameW > TT6_RndFrameH)
    rx *= (DBL)TT6_RndFrameW / TT6_RndFrameH;
  else
    ry *= (DBL)TT6_RndFrameH / TT6_RndFrameW;

  /* Setup matrixes */
  TT6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      TT6_RndProjDist, TT6_RndProjFarClip);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_RndProjSet' function */

/* Setup rendering viewer/camera function.
 * ARGUMENTS:
 *   - camera position:
 *       VEC Loc;
 *   - camera point of interest ('look at' point):
 *       VEC At;
 *   - camera upproximatly up direction:
 *       VEC Up;
 * RETURNS: None.
 */
VOID TT6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  TT6_RndCamLoc = Loc;
  TT6_RndMatrView = MatrView(Loc, At, Up);
  TT6_RndMatrVP = MatrMulMatr(TT6_RndMatrView, TT6_RndMatrProj);
} /* End of 'TT6_RndProjSet' function */

/* END OF 'rndbase.c' FILE */
