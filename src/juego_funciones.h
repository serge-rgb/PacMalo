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

#ifndef _JUEGO_FUNCIONES
#define _JUEGO_FUNCIONES
#include<cstdio>
void J_actualizarBottom(SDL_Rect bottom, int vidas,Uint32 colorParedes)
{
int count;
colorParedes=SDL_MapRGB(pantalla->format,0,0,0);
SDL_FillRect(pantalla,&bottom,colorParedes);
G_imprimirTexto(0.5*pac,15.5*pac,25,"Vidas:");
G_imprimirTexto(10*pac,15.5*pac,25,"Score:");
//Este es buffer de 10 elementos que va a contener el SCORE
char buffer[10];
sprintf(buffer,"%i",SCORE);
G_imprimirTextoChar(12*pac,15.5*pac,25,buffer);
for(count=1;count<=vidas;count++)
{
G_aplicarSuperficie(count*pac+2*pac,15.5*pac,SDLPacmalo,pantalla,&clip[0]);
}

}
void J_imprimirScore(int x,int y,Uint32 colorParedes)
{	
	SDL_Rect rBuffer;
	rBuffer.x=x;
	rBuffer.y=y;
	rBuffer.w=5*pac;
	rBuffer.h=pac;
	SDL_FillRect(pantalla,&rBuffer,colorParedes);
	char buffer[10];
	sprintf(buffer,"%i",SCORE);
	G_imprimirTextoChar(x,y,40,buffer);
}
#endif
