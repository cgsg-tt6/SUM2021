/* FILE NAME: t04perm.c
 * PROGRAMMER: TT6
 * DATE: 12.06.2021
 * PURPOSE: permutation
 */

#include <stdio.h>

#include <windows.h>


VOID Swap( INT *A, INT *B );


/* Permutation array */
#define MAX 5

BOOL IsParity = TRUE;
INT P[MAX];

/* Store permutaton to log file function - write the answer into the file */
VOID Store( VOID )
{
  INT i;
  FILE *F;

  F = fopen("PERM1.TXT", "a");
  if (F == NULL)
    return;

  for (i = 0; i < MAX; i++)
    fprintf(F, "%d ", P[i]);
  fprintf(F, " - parity: %s\n", IsParity ? "even" : "odd");
  
  fclose(F);
} /* End of 'Store' function */


VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

VOID Go( INT Pos )
{
  INT i;

  if (Pos == MAX)
    Store();
  else 
  {
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
    }
  }
} /* End of 'Go' function */

VOID main( VOID )
{
  INT i;

  /* Iznachalno zapolnit' massiv P osnovnoj perestanovkoj */
  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
  /* Permutation function */

} /* End of 'main' function */



