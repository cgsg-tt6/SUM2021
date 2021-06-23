/*                    layout (номер атрибута),
удаление

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* "отцепляем" буфер */
glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBuf);
/* делаем неактивным массив вершин */
glBindVertexArray(0);
glDeleteVertexArrays(1, &VA);

Отрисовка:

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* отрисовка */
glDrawArrays(GL_TRIANGLES, 0, NumOfV);
/* выключили массив вершин */
glBindVertexArray(0);

3.Передача массива индексов в видеопамять

Индексы:

инициализационный этап

INT IBuf;
. . .
glGenBuffers(1, &IBuf);

заносим данные в буфер индексов:

/* делаем активным буфер */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* сливаем данные (NumOfI - количество индексов, I - массив индексов) */ 
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

удаление

glDeleteBuffers(1, &IBuf);

Отрисовка:

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* делаем активным массив индексов */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* отрисовка */
glDrawElements(GL_TRIANGLES, NumOfI, GL_UNSIGNED_INT, NULL);
/* выключили массив вершин */
glBindVertexArray(0);
/* выключили массив индексов */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



Изменения в проекте:

MTH.H + VEC2 VEC4
vg4VERTEX +T N C
VG4_RndPrim: Create Free Draw Load, ***Sphere ...

типовой фрагмент создания примитива (из геометрии)

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
. . . заполнили массивы V и Ind

  VG4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
