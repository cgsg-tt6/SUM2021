/* FILE NAME  : math.h
 * PROGRAMMER : TT6
 * DATE       : 18.06.2021
 * PURPOSE    : Space math library.
 */

#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#include <windows.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* bazovyu veschestvennyu tip */
typedef DOUBLE DBL;
typedef double FLT;

/* ��� ��� ������� � ����������� */
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

/* Transformation matrix representation type */
typedef struct tagMATR
{
  DBL A[4][4]; /* Matrix elements */
} MATR;

__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */

__inline VEC VecSet1( DBL X )
{
  VEC v;

  v.X = v.Y = v.Z = X;
  return v;
} /* End of 'VecSet' function */

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

__inline VEC VecAddVec3( VEC V1, VEC V2, VEC V3 )
{
  return VecAddVec(VecAddVec(V1, V2), V3);
} /* End of 'VecAddVec3' function */

__inline VEC VecSubVec( VEC V1, VEC V2 ) /* V1 � V2 */
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

__inline VEC VecMulNum( VEC V1, DBL N ) /*  V1 * N */
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

__inline VEC VecDivNum( VEC V1, DBL N ) /*  V1 / N */
{
  N = 1 / N;
  return VecMulNum(V1, N);
} /* End of 'VecDivNum' function */

__inline VEC VecNeg( VEC V )             /*  -V */
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* (vec; vec) */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* [vec x vec] */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  VEC v;

  v.X = V1.Y * V2.Z - V1.Z * V2.Y;
  v.Y = V1.Z * V2.X - V1.X * V2.Z;
  v.Z = V1.X * V2.Y - V1.Y * V2.X;

  return v;
} /* End of 'VecCrossVec' function */

__inline DBL VecLen2( VEC V )
{
  return VecDotVec(V, V);
} /* End of 'VecLen' function */

 /* End of 'VecLen2' function */

__inline DBL VecLen( VEC V )  /* |V| */
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* End of 'VecLen' function */

__inline VEC VecNormalize( VEC V )   /* V/|V| */
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

__inline VEC VecMulMatr( VEC V, MATR M )
{
  VEC v;

  v.X = V.X * M.A[0][0] + V.Y * M.A[0][1] + V.Z * M.A[0][2] + M.A[0][3];
  v.Y = V.X * M.A[1][0] + V.Y * M.A[1][1] + V.Z * M.A[1][2] + M.A[1][3];
  v.Z = V.X * M.A[2][0] + V.Y * M.A[2][1] + V.Z * M.A[2][2] + M.A[2][3];

  return v;
} /* End of 'VecMultMatr' function */

/* ����� �������� �� ������� � ������ ���������� ���� */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
} /* End of 'PointTransform' function */

__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecMulMatr(V, M);
} /* End of 'VectorTransform' function */

/*
  MATR Q = MatrTranspose(MatrInverse(M));
  N1 = VectorTransform(N, Q);
*/

/*** MATRIXS ***/

/* edinichnaya matritsa */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */
/*
MATR MatrTranslate( VECT T )
{
  MATR m = UnitMatrix;
  
  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
} *//* End of 'MatrTranslate' function */

__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };

  return m;
} /* End of 'MatrTranslate' function */

__inline MATR MatrScale( VEC S )
{
  MATR m =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Y, 0},
      {0, 0, 0, 1}
    }
  };
  return m;
} /* End of 'MatrScale' function */

__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M = 
  {
    {
      {co + V.X * V.X * (1 - co), 
        V.X * V.Y * (1 - co) + V.Z * si,
          V.X * V.Z * (1 - co) + V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, 
        co + V.Y * V.Y * (1 - co),
          V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.X * V.Z * (1 - co) + V.Y * si,
          V.Y * V.Z * (1 - co) + V.X * si, 
            co + V.Z * V.Z * (1 - co),     0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotate' function */

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0, -s, c, 0},
      {0, 0, 0, 1}
    }
  };

  return m;
} /* End of 'MatrRotateX' function */

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  VEC R;

  R.X = 0;
  R.Y = 1;
  R.Z = 0;

  return MatrRotate(AngleInDegree, R);
} /* End of 'MatrRotateY' function */

__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  VEC R;

  R.X = 0;
  R.Y = 0;
  R.Z = 1;

  return MatrRotate(AngleInDegree, R);
} /* End of 'MatrRotateZ' function */

__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  INT i, j, k;
  MATR r = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)                        /* ???????????? */
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
} /* End of 'MatrMulMatr' function */

__inline MATR MatrMulMatr3( MATR M1, MATR M2, MATR M3 )
{
  return MatrMulMatr(MatrMulMatr(M1, M2), M3);
} /* End of 'MatrMulMatr3' function */

__inline MATR MatrMulMatr4( MATR M1, MATR M2, MATR M3, MATR M4 )
{
  return MatrMulMatr(MatrMulMatr3(M1, M2, M3), M4);
} /* End of 'MatrMulMatr4' function */

__inline MATR MatrMulMatr5( MATR M1, MATR M2, MATR M3, MATR M4, MATR M5 )
{
  return MatrMulMatr(MatrMulMatr4(M1, M2, M3, M4), M5);
} /* End of 'MatrMulMatr5' function */

__inline MATR MatrTranspose( MATR M )                              /********* ********/
{
  INT i, j;
  MATR r = {{{0}}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[i][j] = M.A[j][i];
  return r;
} /* End of 'MatrMulMatr' function */

__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

__inline DBL MatrDeterm( MATR M )
{
  return
    +M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[2][1], M.A[2][2], M.A[2][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    +M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[2][0], M.A[2][1], M.A[2][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */

__inline MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
  MATR r;

  if (det == 0)
    return MatrIdentity();

  /* ������ �������������� ������� */ /* build adjoint matrix */
  r.A[0][0] =
    +MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][0] =
    +MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;


  r.A[0][2] =
    +MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][2] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3]) / det;
  r.A[1][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]) / det;
  r.A[2][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3]) / det;
  r.A[3][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]) / det;

  return r;
} /* End of 'MatrInverse' function */

/*__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  INT s, i, j, P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};

  if (det == 0)
    return MatrIdentity();

  for (s = 1, i = 0; i < 4; i++)
    for (j = 0; j < 4; j++, s = -s)
      r.A[j][i] =
        s * MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                          M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                          M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
}*/ /* End of 'MatrInverse' function */

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0}, 
      {Right.Y, Up.Y, -Dir.Y, 0}, 
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

__inline MATR MatrFrustum( DBL l, DBL r, DBL b, DBL t, DBL n, DBL f )
{
  MATR m =
  {
    {
      {2 * n / (r - l), 0, 0, 0},
      {0, 2 * n / (t - b), 0, 0},
      {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1},
      {0, 0, -(2 * n * f) / (f - n), 0}
    }
  };

  return m;
} /* End of 'MatrFrustum' function */

/*__inline MATR MatrOrtho( DBL left, DBL right, DBL bottom, DBL top, DBL near, DBL far )
{
  MATR m =
  {
    {
      {2 / (right - left), 0, 0, 0},
      {0, 2 / (top - bottom), 0, 0},
      {0, 0, -2 / (far - near), 0},
      {-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1}
    }
  };

  return m;
}*/ /* End of 'MatrOrtho' function */

#endif /*  __mth_h_ */

/* END OF 'mth.h' FILE */