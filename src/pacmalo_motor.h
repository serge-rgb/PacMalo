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

//*************Motor de Pacmalo v.1.0 *****************
//Usa la libreria SDL para controlar cosas como el
//tiempo y graficas en el juego.
//casi todo el codigo está basado en los tutoriales de
//lazyfoo en www.lazyfooproductions.com
//Hay un archivo llamado DICCIONARIO, que contiene todas las
//todas las funciones y clases de este motor, para que se 
//cualquier aplicación.
#ifndef _PACMALO_MOTOR
#define _PACMALO_MOTOR

#include <cstdlib>
#include<cmath>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include<iostream>
#include<string>
using namespace std;
//Inicializar variables: globales
SDL_Surface *SDLPacmalo=NULL;
SDL_Surface *SDLFondo=NULL;
SDL_Surface *SDLObjetos=NULL;
SDL_Surface *SDLParedes=NULL;
SDL_Surface *SDLDot=NULL;
SDL_Surface *pantalla=NULL;
SDL_Event evento; 
int FPS=20;
double DIV=4;
SDL_Rect clip[4];
int pac=40; //Unidades del juego
const int WIDTH=600;
const int HEIGHT=680;//480 para la pantalla de juego pero hay 2 pacs para datos como score y las vidas que quedan.
const int BPP=32;
bool SALISTE=false;
int NIVEL=1;
int SCORE=0;
int VIDAS=4;

//*****************PARTE A: Gráficas************************
//las funciones empiezan con "G_".


//Funcion init
bool G_init()
{
cout<<"pamcalo_motor: Iniciando sistema grafico de Pacmalo"<<endl;
SDL_Init(SDL_INIT_EVERYTHING);
clip[0].x=0;
clip[0].y=0;
clip[0].w=pac;
clip[0].h=pac;
clip[1].x=pac;
clip[1].y=0;
clip[1].w=pac;
clip[1].h=pac;
clip[2].x=0;
clip[2].y=pac;
clip[2].w=pac;
clip[2].h=pac;
clip[3].x=pac;
clip[3].y=pac;
clip[3].w=pac;
clip[3].h=pac;
pantalla=SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE&&SDL_DOUBLEBUF&&SDL_RESIZABLE);
if(pantalla==NULL)
{
cout<<"ERROR: SDL no se pudo inicializar"<<endl;
return false;
}
SDL_WM_SetCaption("Pacmalo",NULL);//El Null puede ser una referencia a una imagen
	return true;
}
//Funcion para cargar una imagen
SDL_Surface * G_cargarImagen(string filename)
{
SDL_Surface *imgTemp=NULL;
SDL_Surface *imgFinal=NULL;
imgTemp=IMG_Load(filename.c_str());
if (imgTemp==NULL)
{
cout<<"Hubo un problema al cargar la imagen "<<filename.c_str()<<endl;
return NULL;
}
imgFinal=SDL_DisplayFormat(imgTemp);
SDL_FreeSurface(imgTemp);
if(imgFinal==NULL)
{
cout<<"Hubo un problema al cambiar la imagen "<<filename.c_str()<<"al formato del juego (640x480 - 32 BPP)"<<endl;
return NULL;
}
return imgFinal;
}
//Crear el clip
void G_clipsDef()
{
clip[0].x=0;
clip[0].y=0;
clip[0].w=pac;
clip[0].h=pac;
clip[1].x=pac;
clip[1].y=0;
clip[1].w=pac;
clip[1].h=pac;
clip[2].x=0;
clip[2].y=pac;
clip[2].w=pac;
clip[2].h=pac;
clip[3].x=pac;
clip[3].y=pac;
clip[3].w=pac;
clip[3].h=pac;
}
//Funcion para aplicar una superficie
//Si tiene un pixel que sea perfectamente azul, lo va a hacer transparente
bool G_aplicarSuperficie(int x,int y, SDL_Surface *fuente, SDL_Surface *destino,SDL_Rect *clip=NULL)
{
SDL_Rect rect;
rect.x=x;
rect.y=y;
Uint32 colorTrans=SDL_MapRGB(pantalla->format,0,0,255);
SDL_SetColorKey(fuente, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorTrans);
if(SDL_BlitSurface(fuente,clip,destino,&rect)==0) return true;
else return false;
}

//Funcion para cargar el fondo
bool G_cargarFondo()
{

SDLFondo=G_cargarImagen("imagenes/fondo.tga");
if(SDLFondo==NULL)
{
cout<<"No se pudo cargar imagen fondo.tga"<<endl;
return false;
}
G_aplicarSuperficie(0,0,SDLFondo,pantalla);
SDLObjetos=G_cargarImagen("imagenes/fondo_objetos.tga");
if(SDLObjetos==NULL)
{
cout<<"No se pudo cargar imagen fondo_objetos.tga"<<endl;
return false;
}
//Ahora hay que cargar el footer
/*
SDLFooter=G_cargarImagen("footer.tga");
if(SDLFondo==NULL)
{
cout<<"No se pudo cargar imagen footer.tga"<<endl;
return false;
}
G_aplicarSuperficie(0,480,SDLFondo,pantalla);*/
return true;
}
bool G_actualizarFondo()
{
return G_aplicarSuperficie(0,0,SDLFondo,pantalla);
}
bool G_actualizarObjetos()
{
return G_aplicarSuperficie(0,0,SDLObjetos,pantalla);
}
//Funcion para el texto1
//Esta funcion puede eliminarse o mejorarse, ya que inicializa y termina el TTF
//y hacerlo cada frame para actualizar el score y las vidas no es lo mejor.
bool G_imprimirTexto(int x,int y,int size,string texto,SDL_Surface *mensaje=NULL)
{
TTF_Init();
SDL_Color color={0,0,255};
TTF_Font *font;
font=TTF_OpenFont("arial.ttf",size);
if (font==NULL)
{
cout<<"No se pudo cargar el font "<<TTF_GetError()<<endl;
return false;
}
SDL_Rect posicion;
posicion.x=x;
posicion.y=y;
mensaje=TTF_RenderText_Solid(font,texto.c_str(),color);
SDL_BlitSurface(mensaje,NULL,pantalla,&posicion);
TTF_CloseFont(font);
TTF_Quit();
return true;
}
bool G_imprimirTextoChar(int x,int y,int size,char *textoChar,SDL_Surface *mensaje=NULL)
{
TTF_Init();
SDL_Color color={0,0,255};
TTF_Font *font;
font=TTF_OpenFont("arial.ttf",size);
if (font==NULL)
{
cout<<"No se pudo cargar el font "<<TTF_GetError()<<endl;
return false;
}
SDL_Rect posicion;
posicion.x=x;
posicion.y=y;
mensaje=TTF_RenderText_Solid(font,textoChar,color);
SDL_BlitSurface(mensaje,NULL,pantalla,&posicion);
TTF_CloseFont(font);
TTF_Quit();
return true;
}
//Limpia todo!
void G_cleanUp()
{
cout<<"pamcalo_motor: Finalizando sistema grafico de Pacmalo..";
if(SDLParedes!=NULL)
{
SDL_FreeSurface(SDLParedes);
}
if(SDLObjetos!=NULL)
{
SDL_FreeSurface(SDLObjetos);
}
if(SDLPacmalo!=NULL)
{
SDL_FreeSurface(SDLPacmalo);
}
if(SDLFondo!=NULL)
{
SDL_FreeSurface(SDLFondo);
}
if(SDLDot!=NULL)
{
SDL_FreeSurface(SDLDot);
}
SDL_Quit();
cout<<"OK"<<endl;
}
//Funcion para checar si hay colision entre rectangulos
//Es recomendable que el rectangulo en movimiento sea el B... si no, no funciona siempre..
//Esta funcion no checa colisiones si los rectángulos están juntos..
bool G_checarColision(SDL_Rect A, SDL_Rect B)
{
bool colx=false;
bool coly=false;
/*if(B.x<A.x)
{
	//if((B.x+B.w)>(B.x+A.x))
	//{
	//colx=true; 
	//}
}*/
if (B.x>A.x)
{
	if((A.x+A.w)>B.x)
	{
	colx=true;
	}
}
if (B.x<A.x)
{
	
	if((B.x+B.w)>A.x)
	{
	colx=true;
	}
	
}
if (B.x==A.x)
{
colx=true;
}
if(B.y>A.y)
{
	if((A.y+A.h)>B.y)
	{
	coly=true;
	}
}
if(B.y<A.y)
{
	if((B.y+B.h)>A.y)
	{
	coly=true;
	}
}
if (B.y==A.y)
{
coly=true;
}
if((colx==true)&&(coly==true))
{
return true;
}
else return false;
}
//***************Fin de PARTE A****************************

//*****************PARTE B: Tiempo***************************
//Esto es básicamente una clase para hacer un timer.
//Este timer usa SDL_GetTicks para saber cuanto tiempo ha 
//pasado. Tiene la capacidad de prenderse y apagarse, sw
// puede usar para controlar el frame rate y para controlar
//los modulos en la inteligencia artificial de los malos
class Timer
{
private:
double empiezaTicks;
bool prendido;
double ticksParado;
public:
Timer();
void empieza();
void para();
void reset();
void reanuda();
double tiempo();
};
Timer::Timer()
{
int empiezaTicks=0;
}
void Timer::empieza()
{
prendido=true;
empiezaTicks=SDL_GetTicks();
}
void Timer::reset()
{
ticksParado=0;
}
void Timer::para()
{
ticksParado=SDL_GetTicks()-empiezaTicks;
prendido=false;
}
void Timer::reanuda()
{
empiezaTicks=ticksParado;
prendido=true;
}
double Timer::tiempo()
{
if(prendido==true)
{
return (SDL_GetTicks() - empiezaTicks);
}
else if (prendido==false)
{
return ticksParado;
}
}
//**************Parte C: Matemáticas*******************
//Aqui estan todas las funciones matemáticas
//M_distancia, M_diferenciaX, M_diferenciaY
double M_distancia(int *px1,int *px2, int *py1, int *py2)
{
double x1= static_cast<double>(*px1);
double x2=static_cast<double>(*px2);
double y1=static_cast<double>(*py1);
double y2=static_cast<double>(*py2);
double dist=sqrt(pow(fabs(x2-x1),2)+pow(fabs(y2-y1),2));
return dist;
}
double M_diferenciaX(int *px1,int *px2)
{
double x1= static_cast<double>(*px1);
double x2=static_cast<double>(*px2);
double dif;
dif=fabs(x2-x1);
return dif;
}
double M_diferenciaY(int *py1, int *py2)
{
double y1=static_cast<double>(*py1);
double y2=static_cast<double>(*py2);
double dif=fabs(y2-y1);
return dif;
}
#endif
