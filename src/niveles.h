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

//***********NIVEL 
#ifndef _NIVELES
#define _NIVELES
#include "pacmalo_motor.h" //Funciones de video 
#include"paredes.h" //Definir las paredes 
#include"dot.h" //Clase para las bolitas 
#include"juego_funciones.h" //Funciones que uso..
#include"powerpill.h" //Clase para el crack! 
#include"splot.h" //Sangrerio horrible 
#include"mono_clase.h" //San pacmalo 
#include"ciego_clase.h" //Malo ciego (Eme, uba, hausen) 

//Funcion principal
bool J_nivelUno(int *MAIN_SCORE)
{
//Inicializar variables
	cout<<"Pacmalo,Nivel 1: Inicializando Variables...";
	srand(time(0));
	int vidaCount;
	int scoreCount;
	bool GANASTE=false;
	bool QUIT=false;
	bool pausa=false;
	bool bonus=true;
	bool powerBool=false;
	int count;
	Uint32 colorParedes;
	SDL_Rect bottom;
	bottom.x=0;
	bottom.y=15*pac;
	bottom.w=15*pac;
	bottom.h=2*pac;
	cout<<"OK"<<endl;
	G_init();
	cout<<"Pacmalo,Nivel 1: Inicializando Clases, Timers e Imagen de Nivel..."<<endl;
	Timer fpsTimer;
	Mono pacmalo;
	Timer vidaBonus;
	Timer powerTimer;
	vidaBonus.empieza();
	F_ciego ciego[4];
	Powerpill luna(7*pac,10*pac);
	colorParedes=SDL_MapRGB(pantalla->format,0,0,0);
	//Rect que representa el espacio de juego.
	SDL_Rect rpantalla;
	rpantalla.x=0;
	rpantalla.y=0;
	rpantalla.w=600;
	rpantalla.h=600;
	//Cargar Dots
		int dotx=0;
		int doty=0;
		Bolita dot[170];
		dot[1].posiciona(0,0);
		DOTCOUNT=1;
		for(count=2;count<=170;count++)
		{
		dotx++;
		DOTCOUNT++;
			if(dotx>=13)
			{
			dotx=0;
			doty++;
			}
		dot[count].posiciona(dotx,doty);
		}
		DOTCOUNT-=59;
		cout<<"Dotcount "<<DOTCOUNT<<endl;
	//QUE nazca el(los) powerpill(s)
	luna.nace();
	G_cargarFondo();
	cout<<"OK"<<endl;
	
	vidaCount=pacmalo.vidas;
	scoreCount=SCORE;
	J_definirParedes();
	/*
			//Esto dibuja las paredes, solucion temporal
			colorParedes=SDL_MapRGB(pantalla->format,0,0,255);
			for(count=1;count<=NUMPAREDES;count++)
			{
			SDL_FillRect(pantalla,&pared[count],colorParedes);
			}
	*/	
	J_actualizarBottom(bottom,vidaCount,colorParedes);
	Timer check; //check: para ver cuanto tiempo hiciste
	check.empieza();
//Loop principal del programa


	while(QUIT==false)
	{
	fpsTimer.empieza();
//Actualiza las vidas pricipales con la de pacmalo..
//Recibe input
	while(SDL_PollEvent(&evento))
		{	
		pacmalo.manejar_input();
		if(evento.type==SDL_KEYDOWN)
		{
		switch(evento.key.keysym.sym)
		{
		case SDLK_a:
			DOTCOUNT=0;
			break;
		case SDLK_k:
			QUIT=true;
			break;
		case SDLK_p:
			pausa=true;
			check.para();
			vidaBonus.para();
			if(pacmalo.power==true) powerTimer.para();
			fpsTimer.para();
			break;
		case SDLK_o:
			if(pacmalo.power==true) 
			{
			pacmalo.power=false;
			cout<<"Buuuu"<<endl;
			break;
			}
			if(pacmalo.power==false) 
			{
			pacmalo.power=true;
			cout<<"Poweeeeer"<<endl;
			break;
			}
		}
		}
		if(evento.type==SDL_QUIT)
		{
			QUIT=true;
			SALISTE=true;
		}
	
	}
	


//-----------Ahora reacciona al input----
//Si pausaste esta madre..
	if(pausa==true)
	{
	
		while (pausa==true)
		{
		SDL_FillRect(pantalla,&rpantalla,colorParedes);
		G_imprimirTexto(2*pac,3*pac,40,"***********PAUSA**********");
		SDL_Flip(pantalla);
		while(SDL_PollEvent(&evento))
		{	
		if(evento.type==SDL_KEYDOWN)
		{
		switch(evento.key.keysym.sym)
		{
		case SDLK_p:
			pausa=false;
			check.reanuda();
			vidaBonus.reanuda();
			if(pacmalo.power==true) powerTimer.reanuda();
			fpsTimer.reanuda();
			colorParedes=SDL_MapRGB(pantalla->format,0,0,0);
			SDL_FillRect(pantalla,&rpantalla,colorParedes);
			G_actualizarFondo();
			SDL_Flip(pantalla);
			//Alenta a estos cabrones
				for(int i=0;i<=3;i++)
				{
				ciego[i].lentitud=-4;
				}
		}
		}
		if(evento.type==SDL_QUIT)
		{
			QUIT=true;
			SALISTE=true;
			pausa=false;
		}
		}
		}
	}

		//Comiste la luna??
		if(luna.vivo==false && luna.done==false)
		{
			if(pacmalo.power==false) 
			{
			pacmalo.power=true;
			luna.done=true;
			//powerBool=true;
			}
		}
	//**FUCK!!! HE'S GOT A GUN!!!!
	if(pacmalo.power==true&&powerBool==false)
	{
		//cout<<"POWER"<<endl;	
		powerTimer.empieza();
		for(int i=0;i<=3;i++)
		{
		ciego[i].flee=true;
		ciego[i].lentitud=-4;
		}
		powerBool=true;
	}
	if(powerTimer.tiempo()>=5000)
	{
		for(int i=0;i<=3;i++)
		{
		powerBool=false;
		pacmalo.power=false;
		ciego[i].flee=false;
		ciego[i].lentitud=-0;
		ciego[i].SDLcargate();
		}
		powerTimer.para();
		powerTimer.reset();
		
		
	}

	//Reaccionan los cieguitos..
	pacmalo.reacciona(check);
	for(int i=0;i<=3;i++)
	{
	ciego[i].reacciona(pacmalo.rect,pacmalo.posx,pacmalo.posy);
	}	
	//G_actualizarFondo();
	//Actualiza Dots
		for(count=1;count<=170;count++)
		{
		dot[count].reacciona(pacmalo.rect,pacmalo.posx,pacmalo.posy);
		}
	//Actualiza fondo objetos..
	G_actualizarObjetos();
	luna.actualiza(pacmalo.rect);
	pacmalo.dibujate();
	//Dibuja a los cieguitos..
	//Solo si no estan en el limbo...
		for(int i=0;i<=3;i++)
		{
		if(ciego[i].limbo==false) ciego[i].dibujate();
		}
	
	//G_actualizarFondo();
	//Bono Por tiempo??
		if(vidaBonus.tiempo()>=40000 && bonus==true && pacmalo.vidas <= 6)
		{
		SDL_FillRect(pantalla,&rpantalla,colorParedes);
		pacmalo.vidas=pacmalo.vidas+1;
		G_imprimirTexto(2*pac,6*pac,40,"*******Bono de Tiempo*****");
		G_imprimirTexto(2*pac,7*pac,40,"*******Vida Extra!!*******");
		SDL_Flip(pantalla);
		SDL_Delay(1000);
			
			colorParedes=SDL_MapRGB(pantalla->format,0,0,0);
			SDL_FillRect(pantalla,&rpantalla,colorParedes);
			G_actualizarFondo();
			SDL_Flip(pantalla);
		vidaBonus.empieza();
		vidaBonus.para();
		bonus=false;
		}
	//Comes muerdes o pacmalo te mastica??? (literalmente... no es solamente un chiste malo...)
	for(int i=0;i<=3;i++)
	{
	if(ciego[i].muerde==true)
		{
		if(powerBool==false||ciego[i].flee==false)
		{
		if(pacmalo.inve==false)
		{
		pacmalo.golpe();
		//pacmalo.splot();
		pacmalo.reset();
		ciego[i].reset();
		SCORE=SCORE-1000;
		}
		}
		if(powerBool==true&&ciego[i].flee==true)
		{
		cout<<"FUCK"<<endl;
		ciego[i].reset();
		SCORE=SCORE+1000;
		}
		}
	}


	if(pacmalo.vivo==false) {GANASTE=false; QUIT=true;}
	if(DOTCOUNT==0) {GANASTE=true; QUIT=true;}
	if (vidaCount!=pacmalo.vidas)
		{
		bonus=false;
		vidaCount=pacmalo.vidas;
		J_actualizarBottom(bottom,vidaCount,colorParedes);
		}
	//Para cuando sirva el pinche score..
		//Actualizacion: Ya sirve!! amen, san sprintf
	if(scoreCount!=SCORE)
	{
	scoreCount=SCORE;
	J_actualizarBottom(bottom,vidaCount,colorParedes);
	}
	SDL_Flip(pantalla);

	//Esperemos que esto no pase..
	if(fpsTimer.tiempo()>=1000/FPS) 
	{
	if((fpsTimer.tiempo()-1000/FPS)>50)
	cout<<"Advertencia: Limite de fps peligrosamente abajo de lo óptimo: "<<fpsTimer.tiempo()-1000/FPS<<" ms"<<endl;
	}
	if(fpsTimer.tiempo()<(1000/FPS))
	{
	SDL_Delay((1000/FPS-fpsTimer.tiempo()));
	}
	}
check.para();

	if(SALISTE==true)	goto fin;
	//********No hay papeeeel!!!

//Ganaste!!! Ahora reacciono a la victoria..
	if(GANASTE==true)
	{
		SDL_FillRect(pantalla,&rpantalla,colorParedes);
		G_imprimirTexto((pac/2),pac,40,"**¡¡NIVEL COMPLETADO!!**");
		G_imprimirTexto((pac/2),3*pac,40,"Tu score es: ");
		J_imprimirScore(10*pac,3*pac,colorParedes);	
			SDL_Flip(pantalla);
			SDL_Delay(500);
			
	//Vidas Sobrantes?
		G_imprimirTexto((pac/2),6*pac,40,"Bono por vidas sobrantes");
			char buffer[20];
			sprintf(buffer,"%i",pacmalo.vidas);
		G_imprimirTextoChar(4*pac,7*pac,40,buffer);
		G_imprimirTexto(5*pac,7*pac,40,"x 1000");
			SCORE+=(pacmalo.vidas*1000);
		J_imprimirScore(10*pac,3*pac,colorParedes);
			SDL_Flip(pantalla);
			SDL_Delay(500);

	//Buen tiempo??
		if(check.tiempo()/1000<=50)
		{
		int tiempo=(check.tiempo()/1000);
		cout<<tiempo<<" segundos"<<endl;
		G_imprimirTexto((pac/2),8*pac,40,"Bono por buen tiempo");
			sprintf(buffer,"%i",tiempo);
		SCORE+=((60-(check.tiempo()/1000))*350);
		J_imprimirScore(10*pac,3*pac,colorParedes);
		G_imprimirTextoChar(4*pac,9*pac,40,buffer);
		G_imprimirTexto(5*pac,9*pac,40," segundos");
			tiempo=(50-(check.tiempo()/1000))*350;
			sprintf(buffer,"%i",tiempo);
		G_imprimirTextoChar(4*pac,10*pac,40,buffer);
			SDL_Flip(pantalla);
			SDL_Delay(500);	
		}
	G_imprimirTexto(pac,13*pac,40,"Enter para continuar..");
	 		SDL_Flip(pantalla);

//**Ahora reacciona al input para largarte del juego
	QUIT=false;
	while(QUIT==false)
	{
		while(SDL_PollEvent(&evento))
		{	
		if(evento.type==SDL_KEYDOWN)
		{
		switch(evento.key.keysym.sym)
		{
		case SDLK_RETURN:
			QUIT=true;
			break;
		default: break;
		}		
		}
	
		if(evento.type==SDL_QUIT)
		{
			QUIT=true;
			SALISTE=true;
		}
		}
	}

	}
//Perdiste!! imbecil..
	if(GANASTE==false)
	{
	char buffer[256];
	SDL_FillRect(pantalla,&rpantalla,colorParedes);
	cout<<"*****Perdiste...******"<<endl;
	G_imprimirTexto((pac/2),3*pac,40,"*****¡¡VALISTE MADRES!!***");
	G_imprimirTexto((pac/2),5*pac,40,"****Score:");
			sprintf(buffer,"%i",SCORE);
		G_imprimirTextoChar(6*pac,5*pac,40,buffer);
	SDL_Flip(pantalla);
	cout<<"Tu score fue de: "<<SCORE<<endl;
	cout<<"Hiciste "<<check.tiempo()/1000<<" segundos"<<endl;
	SCORE=0;
		G_imprimirTexto(pac,13*pac,40,"Enter para continuar..");
	 		SDL_Flip(pantalla);

//**Ahora reacciona al input para largarte del juego
	QUIT=false;
	while(QUIT==false)
	{
		while(SDL_PollEvent(&evento))
		{	
		if(evento.type==SDL_KEYDOWN)
		{
		switch(evento.key.keysym.sym)
		{
		case SDLK_RETURN:
			QUIT=true;
			break;
		default: break;
		}		
		}
	
		if(evento.type==SDL_QUIT)
		{
			QUIT=true;
			SALISTE=true;
		}
		}
	}
	}

fin:
VIDAS=pacmalo.vidas;
cout<<"Saliendo.."<<endl;
G_cleanUp();
return GANASTE;
}
#endif
