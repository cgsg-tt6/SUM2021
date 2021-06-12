/* FILE NAME: t05det.c
 * PROGRAMMER: TT6
 * DATE: 12.06.2021
 * PURPOSE: count det
 */                           

#include <stdio.h>

#include <windows.h>

typedef DOUBLE DBL;

#define MAX 10
DBL A[MAX][MAX];
INT N = 0;

INT P[MAX];
BOOL IsParity = TRUE;

DBL Determinant = 0;


BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  /* If we can't open the file 
   * or there is no space in Memory etc, return 0 */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;      

  /* Get N from the file */
  fscanf(F, "%d", &N);

  /* Sdelaem tak, chtobyu N prinimalo dopustimyuje znachenija */
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  /* Read the matrix from the file. Now we have a matrix */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
    {
      fscanf(F, "%lf", &A[i][j]);
      /* printf("/%lf/", A[i][j]); */
    }

  /* Close the file*/
  fclose(F);

  /* To let me know that everything is ok, return 1 */
  return TRUE;
} /* End of 'LoadMatrix' function */

///////////////////////////////////////////////////////////////


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
    Determinant += (IsParity * 2 - 1) * prod; /* Uznali znak opredelitelya */
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
    printf("p%d\n", P[i]);
  }
  Go(0);   
  printf("p%d\n", P[i]);
}
  /* Permutation function */

/* ////////////////////////////////////////////////////////// */


VOID main( VOID )
{
  LoadMatrix("IN.TXT");
  Mass(N);

  printf("det%f\n", Determinant);

  getchar();
  getchar();
} /* End of 'main' function */

/* END OF 't05det.c' FILE */