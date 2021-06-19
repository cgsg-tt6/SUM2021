/* FILE NAME: globe.c
 * PROGRAMMER: TT6
 * DATE: 16.06.2021
 * PURPOSE: draw 3D spher
 */ 

#include "globe.h"

/*** Globe global data ***/

/* Globe sphere grid size */
#define GRID_H 15
#define GRID_W 16

static VEC Geom[GRID_H][GRID_W];
static INT WinW, WinH;

VOID GlobeDraw( HDC hDC )
{
  INT i, j, s = 3, k;
  static POINT pnts[GRID_H][GRID_W], pts[GRID_H][GRID_W];
  static DBL Z[GRID_H][GRID_W];

  DBL t = clock() / (DBL)CLOCKS_PER_SEC;
  INT r1 = WinW < WinH ? WinW : WinH;

  /* Project all points to screen */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = Geom[i][j];

      /* Point transformation */
      p = RotateX(p, t * 40);
      p = RotateY(p, t * 30);
      p = RotateZ(p, t * 18);
      p.Y += 0.3 * sin(2 * t);
      
      /* Point projection */
      Z[i][j] = p.Z;
      pnts[i][j].x = WinW / 2 + p.X * r1 * 0.47 + sin(t);
      pnts[i][j].y = WinH / 2 - p.Y * r1 * 0.47 + cos(t);
    }

#if 0
  /* Draw all points */
  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
                   pnts[i][j].x + s, pnts[i][j].y + s);
    } 

  /* Draw by lines */
  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      MoveToEx(hDC, pnts[i][j].x, pnts[i][j].y, NULL);
      LineTo(hDC, pnts[i + 1][j].x, pnts[i + 1][j].y);
      LineTo(hDC, pnts[i + 1][j + 1].x, pnts[i + 1][j + 1].y);
    }    
#endif /* 0 */

  /* By facets */
  srand(47);
  for (k = 0; k < 2; k++)
  {
    if (k == 0)
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCPenColor(hDC, RGB(130, 130, 130));
      SetDCBrushColor(hDC, RGB(200, 200, 200));
    }
    else 
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(NULL_BRUSH));
      SetDCPenColor(hDC, RGB(0, 0, 0));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
    }

    for (i = 0; i < GRID_H - 1; i++)
      for (j = 0; j < GRID_W - 1; j++)
      {
        POINT pts[4];
        INT coef;

        pts[0] = pnts[i][j];
        pts[1] = pnts[i][j + 1];
        pts[2] = pnts[i + 1][j + 1];
        pts[3] = pnts[i + 1][j];

        /* SetDCBrushColor(hDC, RGB(80, 55, 40)); */
        SetDCBrushColor(hDC, RGB(rand(), rand(), rand()));
        
        coef = (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
               (pts[1].x - pts[2].x) * (pts[1].y + pts[2].y) +
               (pts[2].x - pts[3].x) * (pts[2].y + pts[3].y) +
               (pts[3].x - pts[0].x) * (pts[3].y + pts[0].y);
        if (coef < 0 && k == 0 || coef > 0 && k == 1)
          continue; 

        Polygon(hDC, pts, 4);
      }   
  }   
} /* End of 'GlobeDraw' function */

VOID GlobeSet( INT W, INT H, DBL R )
{
  INT i, j;
  DBL theta, phi;

  WinW = W;
  WinH = H;

  for (i = 0, theta = 0; i < GRID_H; i++, theta += PI / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * PI / (GRID_W - 1))
    {
      DBL a = 0.8, b = 0.5;

      Geom[i][j].X = 0.8 * R * sin(theta) * sin(phi);
      Geom[i][j].Y = 0.37 * R * cos(theta) /* * cos(theta) * cos(theta) * cos(theta) * cos(theta) * cos(theta) * cos(theta) * cos(theta) * cos(theta) * cos(theta)*/;
      Geom[i][j].Z =  0.8 * R * sin(theta) * cos(phi); 
    }
} /* End of 'GlobeDraw' function */ 

VEC RotateZ( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
  VEC f;

  f.X = V.X * co - V.Y * si;
  f.Y = V.X * si + V.Y * co;
  f.Z = V.Z;
  return f;
} /* End of 'RotateZ' function */

VEC RotateY( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
  VEC f;

  f.Z = V.Z * co - V.X * si;
  f.X = V.Z * si + V.X * co;
  f.Y = V.Y;
  return f;
} /* End of 'RotateY' function */

VEC RotateX( VEC V, DBL Angle )
{
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
  VEC f;

  f.Y = V.Y * co - V.Z * si;
  f.Z = V.Y * si + V.Z * co;
  f.X = V.X;
  return f;
} /* End of 'RotateX' function */

/* END OF 'globe.c' FILE */