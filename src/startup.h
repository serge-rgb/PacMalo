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

#ifndef _STARTUP
#define _STARTUP
#include"pacmalo_motor.h"
#include<ctime>

SDL_Surface *S_fondo;
SDL_Surface *lion;
SDL_Surface *eme;
SDL_Surface *hausen;
SDL_Surface *uba;

SDL_Event S_evento;


//Nota: resetear toda superficie a NULL y borrar las creadas..

bool S_G_Init()
{
	pantalla=SDL_SetVideoMode(600,360,BPP,SDL_HWSURFACE&&SDL_DOUBLEBUF&&SDL_RESIZABLE);
	if(pantalla==NULL)
	{
	cout<<"ERROR: Startup: SDL no se pudo inicializar"<<endl;
	return false;
	}
	SDL_WM_SetCaption("Pacmalo",NULL);
	S_fondo=G_cargarImagen("imagenes/inicio_fondo.tga");
	lion=G_cargarImagen("imagenes/lion.tga");
	eme=G_cargarImagen("imagenes/eme.tga");
	hausen=G_cargarImagen("imagenes/hausen.tga");
	uba=G_cargarImagen("imagenes/uba.tga");
	G_aplicarSuperficie(0,0,S_fondo,pantalla);
}
void J_actualizarGUI()
{
	G_aplicarSuperficie(0,0,S_fondo,pantalla);
	G_imprimirTexto(.5*pac,6.5*pac,20,"Iniciar                HiScore                Ayuda                Salir");
}
int J_startUp()
{
	Timer startTimer;
	bool QUIT=false;
	S_G_Init();
	G_imprimirTexto(.5*pac,6.5*pac,20,"Iniciar                HiScore                Ayuda                Salir");
	G_imprimirTexto(pac,pac,20,"Beta 1");
//Que chingados quieres hacer??
	int opcion=0;
	bool eleccion=false;
	startTimer.empieza();
	while(QUIT==false)
	{
//----Recibe input----
while(SDL_PollEvent(&S_evento))
		{	
		if(S_evento.type==SDL_KEYDOWN)
		{
			switch(S_evento.key.keysym.sym)
			{
			case SDLK_RIGHT:
				opcion +=1;
				break;
	
			case SDLK_LEFT:
				opcion -=1;
				break;
			case SDLK_RETURN:
				eleccion=true;
				QUIT=true;
				break;
			default: break;
			}
		}
		//Uno nunca sabe que puede pasar cuando aprietas una tecla en el menu!!
		if(S_evento.type==SDL_QUIT)
		{
		QUIT=true;;
		}
		
		}
//Reacciona al input-----
if(opcion>3) opcion=0;
if(opcion<0) opcion=3;
	switch(opcion)
	{
	case 0: 
		J_actualizarGUI();
		G_aplicarSuperficie(.5*pac,5*pac,lion,pantalla);
	break;
	case 1: 
		J_actualizarGUI();
		G_aplicarSuperficie(4.5*pac,5*pac,eme,pantalla);
		break;
	case 2:
		J_actualizarGUI();
		G_aplicarSuperficie(8.5*pac,5*pac,uba,pantalla);
 		break;
	case 3: 
		J_actualizarGUI();
		G_aplicarSuperficie(12.5*pac,5*pac,hausen,pantalla);
		break;
	default: break; /*Esto no deberia pasar*/
	}
	SDL_Flip(pantalla);
	//No puede estar ahi por mas de 60 segundos... causa pedos..
	if(startTimer.tiempo()>60000)
	{
	QUIT=true;
	}
	}
	
	//Mamaaaaaaaa me limpias?
	SDL_FreeSurface(S_fondo);
	SDL_FreeSurface(lion);
	SDL_FreeSurface(eme);
	SDL_FreeSurface(hausen);
	SDL_FreeSurface(uba);
	//Si elejiste algo..
	if(eleccion==true)
	{

	return opcion;
	
	}
//Limpiate puerco!!

return 3;
}
#endif
