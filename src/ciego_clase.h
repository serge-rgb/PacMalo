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
#ifndef _CIEGO
#define _CIEGO
enum fantasmaNum {CIEGO=0,CAZADOR=1,HIJODE=2};
class F_ciego
{
public:
	F_ciego();
	~F_ciego();
	bool muerde;
	bool limbo;
	bool flee;	
	void reacciona(SDL_Rect,int,int);
	void dibujate();
	void SDLcargate();
	void reset();
	double lentitud;
	int velx, vely;
private:
	Timer resetTimer;
	SDL_Surface *SDLCiego;
	SDL_Rect rColision;
	void muevete();
	void huye(int,int);
	void huyeX(int , int );
	void huyeY(int,int);
	int checarY();
	int checarX();
	SDL_Rect rect;
	Uint32 color;
	bool colision;
	bool recienNacido;
	int choose;
	int c;
	int posx,posy;
};

F_ciego::F_ciego()
{
	resetTimer.empieza();
	flee=false;
	muerde=false;
	colision=false;
	 recienNacido=true;
	limbo=false;
	choose=0;
	lentitud=-0;
	posx=6*pac;
	posy=6*pac;
	velx=0;
	vely=0;
	rect.x=posx;
	rect.y=posy;
	rect.w=pac;
	rect.h=pac;
//El rectangulo de colision mas pequeño que la superficie
// para reducir pedos..
	rColision.x=posx+10;
	rColision.y=posy+10;
	rColision.w=20;
	rColision.h=20;	
	color=SDL_MapRGB(pantalla->format,0,0,0);
//Dibuja

	choose=1+rand()%3;
	switch(choose)
	{
		case 1:
	SDLCiego=G_cargarImagen("imagenes/eme.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen eme.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	break;

		case 2:
	SDLCiego=G_cargarImagen("imagenes/uba.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen uba.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	
	break;
		case 3:
	SDLCiego=G_cargarImagen("imagenes/hausen.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen uba.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	
	break;
	}

}
//******Resetear
void F_ciego::reset()
{
recienNacido=false;
rect.x=posx;
rect.y=posy;
//SDL_FillRect(pantalla,&rect,color);
velx=0;
vely=0;
muerde=false;
flee=false;
posx=6*pac;
posy=6*pac;
rect.x=posx;
rect.y=posy;
SDLCiego=NULL;
SDLcargate();
lentitud=-0;
resetTimer.empieza();
limbo=true;
}	

int F_ciego::checarY()
{
	int intRes=0;
	rect.y=posy-pac/(DIV-lentitud);
	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true; 
	}
	if(colision==false) intRes=intRes+1;
	
	rect.y=posy+pac/(DIV-lentitud);
	colision=false;
		
	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true; 
	}
	if(colision==false) intRes=intRes+2;
	rect.x=posx;
	rect.y=posy;
	colision=false;
	return intRes;
}

int F_ciego::checarX()
{
	int intRes=0;
	//rect.x=(posx+pac);
	rect.x=posx+pac/(DIV-lentitud);

	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true; 
	}
	if(colision==false) intRes=intRes+1;
	
	//rect.x=(posx-pac);
	rect.x=posx-pac/(DIV-lentitud);
	colision=false;
		
	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true; 
	}
	if(colision==false) intRes=intRes+2;
	rect.x=posx;
	rect.y=posy;
	colision=false;
	return intRes;
}
void F_ciego::muevete()
{

	if(vely==0 && velx==0)
	{
//Checar Y
	if(checarY()!=0)
	{
	switch(checarY())
	{
	case 1:
			choose=1+rand()%2; 
			switch(choose)
			{
			case 1: vely=-1; velx=0; break;
			case 2: break;
			}
	case 2: 	choose=1+rand()%2;
			switch(choose)
			{
			case 1: vely=1; velx=0; break;
			case 2: break;
			}
	case 3: 	choose=1+rand()%3;
			switch(choose)
			{
			case 1: break;
			case 2: vely=1; velx=0; break;
			case 3: vely=-1; velx=0; break;
			}
	}
	}
//Si puede moverse en Y, moverse
//Checar X
//Hacer una desicion al azar, para ver si quiere continuar
	choose=1+rand()%2;
	switch(choose)
	{
		case 1:
			break;
		case 2:
//Si puede moverse en X, moverse
	if(checarY()==0)
	{
	switch(checarX())
	{
	case 1:
			choose=1+rand()%2; 
			switch(choose)
			{
			case 1: velx=-1; vely=0; break;
			case 2: break;
			}
	case 2: 	choose=1+rand()%2;
			switch(choose)
			{
			case 1: velx=1; vely=0; break;
			case 2: break;
			}
	case 3: 	choose=1+rand()%3;
			switch(choose)
			{
			case 1: break;
			case 2: velx=1; vely=0; break;
			case 3: velx=-1; vely=0; break;
			}
	}
	}
			break;
	}

	}
	
//Si va a la derecha o izquierda
	if(velx!=0)
	{
		if(checarY()==1)
		{
		choose=1+rand()%2;
			switch(choose)
			{
			case 1: vely=-1; velx=0; break;
			case 2: break;
			}
		}
		if(checarY()==2)
		{
		choose=1+rand()%2;
			switch(choose)
			{
			case 1: vely=1; velx=0; break;
			case 2: break;
			}
		}	
		if(checarY()==3)
		{
		choose=1+rand()%3;
			switch(choose)
			{
			case 1: break;
			case 2: vely=1; velx=0; break;
			case 3: vely=-1; velx=0; break;
			}
		}
	}
//Si va hacia arriba o abajo..
	if(vely!=0)
	{
		if(checarX()==1)
		{
			choose=1+rand()%2;
			switch(choose)
			{
			case 1: velx=1; vely=0; break;
			case 2: break;
			}
		}
		if(checarX()==2)
		{
			choose=1+rand()%2;
			switch(choose)
			{
			case 1: velx=-1; vely=0; break;
			case 2: break;
			}
		}
		if(checarX()==3)
		{
			choose=1+rand()%3;
			switch(choose)
			{
			case 1: break;
			case 2: velx=1; vely=0; break;
			case 3: velx=-1; vely=0; break;
			}
		}
	}


}
void F_ciego::huyeX(int posxPM, int posyPM)
{
	if(posx>posxPM)
	{
	velx=1;
	rect.x=posx+(velx*pac)/DIV-lentitud;
	rect.y=posy+(vely*pac)/DIV-lentitud;
	colision=false;
	rect.x=posx;
	rect.y=posy;
	}

	if(posx<posxPM)
	{
	velx=-1;
	rect.x=posx;
	rect.y=posy;
	colision=false;
	}
}
void F_ciego::huyeY(int posxPM, int posyPM)
{
	if(posy>posyPM)
	{
	vely=1;
	rect.x=posx;
	rect.y=posy;
	colision=false;
	}
	colision=false;
	if(posy<posyPM)
	{
	vely=-1;
	rect.x=posx;
	rect.y=posy;
	colision=false;
	}
}
void F_ciego::huye(int posxPM, int posyPM)
{
	colision=false;
	long int distancia=M_distancia(&posx,&posxPM,&posy,&posyPM);
 	if(distancia>4*pac)
	{
//****AZ****

	if(velx==0 && vely==0)
	{
		int choose=1+rand()%4;
		if(velx==0 && vely==0)
		{
		switch(choose)
		{
		case 1:
			velx=1;
			vely=0;
			break;
		case 2:
			velx=-1;
			vely=0;
			break;
		case 3:
			velx=0;
			vely=1;
		break;
		case 4:	
			velx=0;
			vely=-1;
			break;
		}
		}
	}
	}

//******AI
 	if(distancia<=4*pac)
	{

		if(M_diferenciaX(&posx,&posxPM)>M_diferenciaY(&posy,&posyPM))
		{
		huyeX(posxPM,posyPM);
		}
		else 
		{
		huyeY(posxPM,posyPM);
		}
	
//Colision??
	rect.x=(posx+(velx*pac)/(DIV-lentitud));
	rect.y=(posy+(vely*pac)/(DIV-lentitud));
	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true;
	}
	if(colision==true)
	{
	velx=0;
	vely=0;
	}
	rect.x=posx;
	rect.y=posy;
	}
		
}
void F_ciego::SDLcargate()
{	
	choose=1+rand()%3;
	switch(choose)
	{
		case 1:
	SDLCiego=G_cargarImagen("imagenes/eme.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen eme.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	break;

		case 2:
	SDLCiego=G_cargarImagen("imagenes/uba.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen uba.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	
	break;
		case 3:
	SDLCiego=G_cargarImagen("imagenes/hausen.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen uba.tga"<<endl;
		break;
	}
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	
	break;
	}
}
void F_ciego::reacciona(SDL_Rect rectPM, int posxPM, int posyPM)
{
	if(resetTimer.tiempo()!=0)
	{
		if(resetTimer.tiempo()<5000 && recienNacido==false) goto _NO_REACCIONES;
		if(resetTimer.tiempo()>=5000)
		{
			resetTimer.para();
			resetTimer.reset();
			limbo=false;
		}
	
	}//fin de if
	muerde=false;
	
	if(flee==false) muevete();
	else 
	{
	SDLCiego=G_cargarImagen("imagenes/sick.tga");
	if(SDLCiego==NULL)
	{
		cout<<"ERROR: No se pudo cargar la imagen sick.tga"<<endl;
	}
	huye(posxPM,posyPM);
	}

//Colision?
	rect.x=(posx+(velx*pac)/(DIV-lentitud));
	rect.y=(posy+(vely*pac)/(DIV-lentitud));
	for(c=1;c<=NUMPAREDES;c++)
	{
		if((G_checarColision(pared[c],rect))==true) colision=true;
	}
	if(colision==true)
	{
		velx=0;
		vely=0;
	}
	rect.x=posx;
	rect.y=posy;
	
	rColision.x=posx+10;
	rColision.y=posy+10;
	rColision.w=20;
	rColision.h=20;	
//Muerde??
	if(G_checarColision(rColision,rectPM)==true)	muerde=true;
	//if(G_checarColision(rectPM,rColision)==true)	muerde=true;

	//if(posx==posxPM&&posy==posyPM) muerde=true;

//LLenar de negro su posicion.. y dibujar..
	rect.x=posx;
	rect.y=posy;
	rColision.x=posx+10;
	rColision.y=posy+10;
	rColision.w=20;
	rColision.h=20;	
	//SDL_FillRect(pantalla,&rect,color);
	posx+=(pac*velx)/(DIV-lentitud);
	posy+=(pac*vely)/(DIV-lentitud);
	if (posx>=15*pac) posx=0;
	if(posx<0) posx=14*pac;
	if(posy<0) posy=14*pac;
	if(posy>=15*pac) posy=0;
	_NO_REACCIONES:
	G_actualizarFondo();
	//Te vas a dibujar usando dibujate()
	//G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
	
	colision=false;
}
void F_ciego::dibujate()
{
	G_aplicarSuperficie(posx,posy,SDLCiego,pantalla);
}
F_ciego::~F_ciego()
{
	if(SDLCiego!=NULL) SDL_FreeSurface(SDLCiego);
}

#endif
