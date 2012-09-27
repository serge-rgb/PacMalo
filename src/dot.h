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
#ifndef _BOLITA
#define _BOLITA
int DOTCOUNT;
//La pinche bolita..
class Bolita
{
public:
	Bolita();
	//~Bolita();
	void posiciona(int,int);
	void reacciona(SDL_Rect,int,int);
	int posx, posy;
	SDL_Rect rect;
	bool vivo;
private:
	int c;
	bool colision;
	bool libreDibujo;
};
Bolita::Bolita()
{
	vivo=true;
	colision=false;
	libreDibujo=false;
	posx=pac;
	posy=pac;
	rect.x=posx;
	rect.y=posy;
	rect.w=pac;
	rect.h=pac;

}

void Bolita::posiciona(int x,int y)
{
	posx=posx+(pac*x);
	posy=pac+(pac*y);
	rect.x=posx;
	rect.y=posy;

	rect.x=posx;
	rect.y=posy;
	if(vivo==true)
	{
		SDLDot=G_cargarImagen("imagenes/dot.tga");
		if(SDLDot==NULL)
		{
			cout<<"ERROR: No se pudo cargar la imagen dot.tga"<<endl;
		}
		G_aplicarSuperficie(posx,posy,SDLDot,pantalla);	
	}
}

void Bolita::reacciona(SDL_Rect rectPM,int posxPM, int posyPM)
{
	/*for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true; 
	}
	if(colision==true) vivo=false;*/

if(vivo==true)
{
/*if(G_checarColision(rect,rectPM)==true)
{
SCORE=SCORE+100;
vivo=false;
}*/
if(posxPM==posx&&posyPM==posy)
{
SCORE=SCORE+100;
DOTCOUNT--;
vivo=false;
}
if(vivo==true) G_aplicarSuperficie(posx,posy,SDLDot,pantalla);
}
}
#endif
