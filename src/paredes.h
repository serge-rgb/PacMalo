/*
    Pacmalo(C) 2006, Sergio González.

    Pacmalo is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Pacmalo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pacmalo; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _NIVEL
#define _NIVEL
const int NUMPAREDES=31;
SDL_Rect pared[NUMPAREDES];

void J_definirParedes()
{
pared[1].x=0;
pared[1].y=0;
pared[1].w=pac;
pared[1].h=7*pac;

pared[2].x=pac;
pared[2].y=0;
pared[2].w=6*pac;
pared[2].h=pac;

pared[3].x=8*pac;
pared[3].y=0;
pared[3].w=6*pac;
pared[3].h=pac;

pared[4].x=14*pac;
pared[4].y=0;
pared[4].w=pac;
pared[4].h=7*pac;

pared[5].x=2*pac;
pared[5].y=2*pac;
pared[5].w=3*pac;
pared[5].h=pac;

pared[6].x=6*pac;
pared[6].y=2*pac;
pared[6].w=3*pac;
pared[6].h=pac;

pared[7].x=10*pac;
pared[7].w=3*pac;
pared[7].y=2*pac;
pared[7].h=pac;

pared[8].x=2*pac;
pared[8].y=4*pac;
pared[8].w=pac;
pared[8].h=5*pac;

pared[9].x=4*pac;
pared[9].y=4*pac;
pared[9].w=pac;
pared[9].h=2*pac;

pared[10].x=6*pac;
pared[10].y=4*pac;
pared[10].w=3*pac;
pared[10].h=pac;

pared[11].x=10*pac;
pared[11].y=4*pac;
pared[11].w=pac;
pared[11].h=2*pac;

pared[12].x=12*pac;
pared[12].y=4*pac;
pared[12].w=pac;
pared[12].h=5*pac;

pared[13].x=6*pac;
pared[13].y=5*pac;
pared[13].w=3*pac;
pared[13].h=pac;

pared[14].x=4*pac;
pared[14].y=6*pac;
pared[14].w=pac;
pared[14].h=2*pac;

pared[15].x=10*pac;
pared[15].y=6*pac;
pared[15].w=pac;
pared[15].h=2*pac;

pared[16].x=5*pac;
pared[16].y=7*pac;
pared[16].w=2*pac;
pared[16].h=pac;

pared[17].x=8*pac;
pared[17].y=7*pac;
pared[17].w=2*pac;
pared[17].h=pac;

pared[18].x=0;
pared[18].y=8*pac;
pared[18].w=pac;
pared[18].h=7*pac;

pared[19].x=14*pac;
pared[19].y=8*pac;
pared[19].w=pac;
pared[19].h=7*pac;

pared[20].x=4*pac;
pared[20].y=9*pac;
pared[20].w=pac;
pared[20].h=pac;

pared[21].x=6*pac;
pared[21].y=9*pac;
pared[21].w=pac;
pared[21].h=2*pac;

pared[22].x=8*pac;
pared[22].y=9*pac;
pared[22].h=2*pac;
pared[22].w=pac;

pared[23].x=2*pac;
pared[23].y=10*pac;
pared[23].w=3*pac;
pared[23].h=pac;

pared[24].x=10*pac;
pared[24].y=10*pac;
pared[24].w=3*pac;
pared[24].h=pac;

pared[25].x=2*pac;
pared[25].y=12*pac;
pared[25].w=3*pac;
pared[25].h=pac;

pared[26].x=6*pac;
pared[26].y=12*pac;
pared[26].w=3*pac;
pared[26].h=pac;

pared[27].x=10*pac;
pared[27].y=12*pac;
pared[27].w=3*pac;
pared[27].h=pac;

pared[28].x=pac;
pared[28].y=14*pac;
pared[28].w=6*pac;
pared[28].h=pac;

pared[29].x=8*pac;
pared[29].y=14*pac;
pared[29].w=6*pac;
pared[29].h=pac;

pared[30].x=10*pac;
pared[30].y=9*pac;
pared[30].w=pac;
pared[30].h=pac;
}
#endif
