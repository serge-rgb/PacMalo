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

#ifndef _SPLOT
#define _SPLOT
//Hazlo sangriento
class Splot
{
public:
	Splot();
	~Splot();
	void nace(int,int);
	void actualiza();
private:
	bool vivo;
	int x,y;
	SDL_Surface *SDLSplot;
};
	Splot::Splot()
	{
	vivo=false;
	}

	void Splot::nace(int xi, int yi)
	{
	x=xi;
	y=yi;
	int choose=1+rand()%6;
	switch(choose)
	{
	case 1:	
		SDLSplot=G_cargarImagen("imagenes/splot_uno.tga");
		break;
	case 2:
		SDLSplot=G_cargarImagen("imagenes/splot_dos.tga");
		break;
	case 3:
		SDLSplot=G_cargarImagen("imagenes/splot_tres.tga");
		break;
	case 4:
		SDLSplot=G_cargarImagen("imagenes/splot_cuatro.tga");
		break;
	case 5:
		SDLSplot=G_cargarImagen("imagenes/splot_cinco.tga");
		break;
	case 6:
		SDLSplot=G_cargarImagen("imagenes/splot_cinco.tga");
		break;
	default:
		SDLSplot=G_cargarImagen("imagenes/splot_seis.tga");
		break;
	}
	if(SDLSplot==NULL) cout<<"Splot: Error: No se puede cargar imagen para sangrerio"<<endl;
	vivo=true;
	}
	
	void Splot::actualiza()
{
	if(vivo==true) G_aplicarSuperficie(x,y,SDLSplot,pantalla);
}	

	Splot::~Splot()
	{
	if(vivo==true) SDL_FreeSurface(SDLSplot);
	}

#endif
