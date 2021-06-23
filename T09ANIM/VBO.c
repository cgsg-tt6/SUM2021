/*                    layout (����� ��������),
��������

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* "���������" ����� */
glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBuf);
/* ������ ���������� ������ ������ */
glBindVertexArray(0);
glDeleteVertexArrays(1, &VA);

���������:

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* ��������� */
glDrawArrays(GL_TRIANGLES, 0, NumOfV);
/* ��������� ������ ������ */
glBindVertexArray(0);

3.�������� ������� �������� � �����������

�������:

����������������� ����

INT IBuf;
. . .
glGenBuffers(1, &IBuf);

������� ������ � ����� ��������:

/* ������ �������� ����� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* ������� ������ (NumOfI - ���������� ��������, I - ������ ��������) */ 
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

��������

glDeleteBuffers(1, &IBuf);

���������:

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* ������ �������� ������ �������� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* ��������� */
glDrawElements(GL_TRIANGLES, NumOfI, GL_UNSIGNED_INT, NULL);
/* ��������� ������ ������ */
glBindVertexArray(0);
/* ��������� ������ �������� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



��������� � �������:

MTH.H + VEC2 VEC4
vg4VERTEX +T N C
VG4_RndPrim: Create Free Draw Load, ***Sphere ...

������� �������� �������� ��������� (�� ���������)

  INT noofv, noofi, size;
  vg4VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(vg4PRIM));

  noofv = . . .;
  noofi = . . .;
  size = sizeof(vg4VERTEX) * noofv + sizeof(INT) * noofi;

  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + noofv);
. . . ��������� ������� V � Ind

  VG4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
