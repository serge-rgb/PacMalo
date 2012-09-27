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

#ifndef _POWERPILL
#define _POWERPILL

class Powerpill
{
private:
	SDL_Surface *SDLPowerpill;
	SDL_Rect rect;
	int posx,posy;
public:
	Powerpill(int,int);
	void nace();
	bool vivo;
	bool done;
	//~Powerpill();
	void actualiza(SDL_Rect);
};

Powerpill::Powerpill(int x, int y)
{
posx=x;
posy=y;
rect.x=posx;
rect.y=posy;
rect.w=pac;
rect.h=pac;
SDLPowerpill=NULL;
done=false;
vivo=true;
}
void Powerpill::nace()
{
	if(vivo==true)
	{
		SDLPowerpill=G_cargarImagen("imagenes/luna.tga");
		if(SDLDot==NULL)
		{
			cout<<"ERROR: No se pudo cargar la imagen luna.tga"<<endl;
		}
		G_aplicarSuperficie(posx,posy,SDLPowerpill,pantalla);	
	}
}


void Powerpill::actualiza(SDL_Rect rectPM)
{
if(G_checarColision(rect,rectPM)==true) vivo=false;
if(vivo==true) G_aplicarSuperficie(posx,posy,SDLPowerpill,pantalla);
}

/*Powerpill::~Powerpill()
{
SDL_FreeSurface(SDLPowerpill);
}*/

#endif
