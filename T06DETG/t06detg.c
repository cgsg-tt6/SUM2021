/* FILE NAME: t06detg.c
 * PROGRAMMER: TT6
 * DATE: 14.06.2021
 * PURPOSE: count det usind Gauss's method
 */ 
#include <stdio.h>

#include <math.h>

#include <windows.h>

#define MAX 10

typedef DOUBLE DBL;

DBL det = 1;
DBL A[MAX][MAX];
INT P[MAX];
BOOL IsParity = TRUE;
INT N = 0;

/* References */
DBL Det( VOID );
VOID DSwap( DBL *A, DBL *B );
VOID Swap( INT *A, INT *B );
VOID Go( INT Pos );
VOID Mass( INT N );
BOOL LoadMatrix( CHAR *FileName );
                                  
DBL Det( VOID )
{
  INT i, k = 0, x, y;
  INT max_row, max_col;
  DBL coef;

  for (i = 0; i < N; i++)
  {
    /* Look for the maximum matrix element */
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
        {
          max_row = y;
          max_col = x;
        }
    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }
    if (max_row != i)
    {
    /* Swap max_row and i row (elements / columns: [i..N-1]) */
      for (x = i; x < N; x++)
        DSwap(&A[max_row][x], &A[i][x]);
      det = -det;
    }

    if (max_col != i)
    {
    /* Swap max_col and i column (elements / columns: [0..N-1]) */
       for (y = i; y < N; y++)
        DSwap(&A[y][max_col], &A[y][i]);
      det = -det;
    }
    /* Substract from every row k: [i+1..N-1] row [i] multiplied by (A[k][i] / A[i][i]) */
    
    for (k = i; k < N; k++)
    {
      coef = A[k][i] / A[i][i];
      A[k][i] = 0;
      for (x = i + 1; x < N; x++)
      A[k][x] -= A[i][x] * coef;
    }
    det *= A[i][i];
  }
  return det;
} /* End of 'Detg' function */
///////////////////////////////////////////

VOID DSwap( DBL *A, DBL *B )
{
  DBL tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'DSwap' function */

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

VOID Go( INT Pos )
{
  INT i;

  if (Pos == N)
  {
    DBL prod = 1;

    for (i = 0; i < N; i++)
      prod *= A[i][P[i]];
    det += (IsParity * 2 - 1) * prod;
  }
  else 
  {
    Go(Pos + 1);
    for (i = Pos + 1; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
    }
  }
} /* End of 'Go' function */

VOID Mass( INT N )
{
  INT i;

  /* Iznachalno zapolnit' massiv P osnovnoj perestanovkoj */
  for (i = 0; i < N; i++)
  {
    P[i] = i;
  }
  Go(0);
} /* End of 'Mass' function */


////////////////////////////////////////////


/* Get the matrix from the file */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;  

  fscanf(F, "%d", &N);

  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
    {
      fscanf(F, "%lf", &A[i][j]);
    }
  fclose(F);
  return TRUE;
} /* End of 'LoadMatrix' function */

VOID main( VOID )
{
  LoadMatrix("DETG.TXT");
  Mass(N);
  Det();
  printf("det: %f\n", det);
  getchar();
} /* End of 'main' function */

/*END OF 't06detg.c' FILE */