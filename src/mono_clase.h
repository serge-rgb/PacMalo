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

//Clase Mono
//Esta clase sirve para crear un Pacmalo... le puse mono porque
//probablemente usare el nombre pacmalo para nombrarlo..
//reacciona con cualquier arreglo de SDL_Rect que se llame "pared"
//el numero de paredes debe ser especificado en la funcion reacciona()
#ifndef _MONO_CLASE
#define _MONO_CLASE
class Mono
{
public:
	Mono();
	~Mono();
	void reset();
	//void splot();
	void manejar_input();
	void dibujate();
	void reacciona(/*SDL_Rect rectMaion*/Timer tiempo);
	void golpe();
	void powerPill();
	void actualizarSplot();
	bool vivo;
	bool power;
	bool inve;
	bool turn;
	int score;
	SDL_Rect rect;
	int vidas;
	int posx,posy;
	long double velx, vely;
	Timer inveTimer;
private:
	Splot splot[8];
	int NUMSPLOTS;
	int Pclip;
	Uint32 color;
	bool colision;
	bool choque;
	double now;
	double then;
	long double stackx, stacky;
};
//Constructor
Mono::Mono()
{
Pclip=0;
now=0;
then=0;
score=0;
color=SDL_MapRGB(pantalla->format,0,0,0);
colision=false;
choque=false;
vidas=VIDAS;
vivo=true;
inve=false;
power=false;
NUMSPLOTS=0;
velx=0;
vely=0;
stackx=0;
stacky=0;
posx=7*pac;
posy=pac;
rect.w=pac;
rect.h=pac;
SDLPacmalo=G_cargarImagen("imagenes/pacmalo.tga");
if(SDLPacmalo==NULL)
{
cout<<"ERROR: No se pudo cargar la imagen pacmalo.tga"<<endl;
}
G_aplicarSuperficie(posx,posy,SDLPacmalo,pantalla,&clip[Pclip]);
}
//~Destructor
Mono::~Mono()
{

}
void Mono::actualizarSplot()
{
	for(int i=0;i<NUMSPLOTS;i++)
	{
	splot[i].actualiza();
	}
}
//Resetear su posicion
void Mono::reset()
{
power=false;
inve=true;
inveTimer.empieza();
rect.x=posx; rect.y=posy;
//SDL_FillRect(pantalla,&rect,color);
velx=0;
vely=0;
stackx=0;
stacky=0;
posx=7*pac;
posy=pac;
for(int i=0;i<=NUMSPLOTS;i++)
{
splot[i].actualiza();
}
G_aplicarSuperficie(posx,posy,SDLPacmalo,pantalla,&clip[0]);
}
//Lo mordio un fantasma
void Mono::golpe()
{
splot[NUMSPLOTS].nace(posx,posy);
NUMSPLOTS++;
vidas--;
}
//Tomó una pastilla
void Mono::powerPill()
{
power=true;
}
//Reaccionar ante las teclas
void Mono::manejar_input()
{

if(evento.type==SDL_KEYDOWN)
{
	switch(evento.key.keysym.sym)
	{

	case SDLK_UP:
		Pclip=2;
		//stacky--; if(stacky<-1) stacky=-1;
		stacky=-1;
		stackx=0;
		if (stacky==0);
		break;
	case SDLK_DOWN:
		Pclip=3;
		//stacky++; if(stacky>1) stacky=1;
		stacky=1;
		stackx=0;
		if (stacky==0);
		break;
	
	case SDLK_RIGHT:
		Pclip=0;
		//stackx++; if(stackx>1) stackx=1;
		stackx=1;
		stacky=0;
		if (stackx==0);
		break;
	
	case SDLK_LEFT:
		Pclip=1;
		//stackx--; if(stackx<-1) stackx=-1;
		stackx=-1;
		stacky=0;
		break;
		if (stackx==0);
	default: break;
	}

		//Uno nunca sabe que puede pasar si aprietas teclas en el menu!
		if(evento.type==SDL_KEYDOWN)
		{
		switch(evento.key.keysym.sym)
		{
		default: break;
		}
		}
		if(evento.type==SDL_QUIT)
		{
			//quit=true;
			//SALISTE=true;
		}
		}

}
//Moverse y todo lo demas
void Mono::reacciona(/*SDL_Rect rectMaion*/Timer check)
{
if(inveTimer.tiempo()!=0)
{
if(inveTimer.tiempo()>=3000)
{
	inve=false;
	inveTimer.para();
	inveTimer.reset();
}
}

if(vidas==0) vivo=false;
int c=1;
rect.x=posx;
rect.y=posy;
//.... Ahora ver si apretaste una tecla y dejar que se mueva hasta que sea posible
rect.x=posx+(pac*stackx)/DIV;
rect.y=posy+(pac*stacky)/DIV;
for(c=1;c<=NUMPAREDES;c++)
{
if((G_checarColision(pared[c],rect))==true) colision=true;
}
if(colision==false) 
{
velx=stackx;
vely=stacky;
}
rect.x=posx;
rect.y=posy;

rect.x=posx+(pac*velx)/DIV;
for(c=1;c<=NUMPAREDES;c++)
{
if((G_checarColision(pared[c],rect))==true) velx=0;
}
rect.x=posx;
rect.y=posy+(vely*pac)/DIV;
for(c=1;c<=NUMPAREDES;c++)
{
if((G_checarColision(pared[c],rect))==true) vely=0;
}
rect.y=posy;

//..Mover al mono segun la velocidad
now=check.tiempo();
//cout<<check.tiempo()<<endl;
//DIV=((now-then)*pac)/1000;
//cout<<"DIV= "<<DIV<<endl;
then=check.tiempo();
posx+=(pac*velx)/DIV;
posy+=(pac*vely)/DIV;

//Dibujar de negro a nuestro rect
//SDL_FillRect(pantalla,&rect,color);
//Si se pasa del ancho de pantalla..
if (posx>=15*pac) posx=0;
if(posx<0) posx=14*pac;
if(posy<0) posy=14*pac;
if(posy>=15*pac) posy=0;

//**Ahora te dibujas usando dibujate();
//G_actualizarFondo();
//for(int i=0;i<NUMSPLOTS;i++)
//{
//splot[i].actualiza();
//}
//Finalmente dibujarlo y decir que ya no hay colisión.
//G_aplicarSuperficie(posx,posy,SDLPacmalo,pantalla,&clip[Pclip]);
colision=false;

}
void Mono::dibujate()
{
for(int i=0;i<=NUMSPLOTS;i++)
{
splot[i].actualiza();
}
G_aplicarSuperficie(posx,posy,SDLPacmalo,pantalla,&clip[Pclip]);
}
#endif
