/* FILE NAME : units.h
 * PROGRAMMER: TT6
 * DATE      : 27.06.2021
 * PURPOSE   : .
 */

#ifndef __units_h_
#define __units_h_

#include "../anim/anim.h"

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (tt6UNIT *) pointer to created unit.
 */
tt6UNIT * TT6_UnitControl( VOID );
tt6UNIT * TT6_UnitCreateGrid( VOID ); 
tt6UNIT * TT6_UnitCreateFrog( VOID );
tt6UNIT * TT6_UnitCreateShrimp( VOID );
tt6UNIT * TT6_UnitCreateBall( VOID );


#endif __units_h_

/* END OF 'units.h' FILE */