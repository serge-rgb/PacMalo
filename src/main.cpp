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

#include"startup.h"
#include"niveles.h"
//#include"nivel_uno_clase.h"
#include"log.h"
#include<istream>
#include<ostream>
#include<fstream>
#include<cstdlib>

int MAIN_VIDAS;

//***Crear la clase que incluya lo necesario
//La clase del SCORE
class hsdat {
public:
	hsdat();
	void nuevo(char *,int );
	char * nombre;
	int score;
	bool get_to_hs;
};
	//Constructor.
hsdat::hsdat() {
get_to_hs=false;
}
	//Hacer un nuevo registro.
void hsdat::nuevo(char*nombreTMP, int tmpScore){
score=tmpScore;
nombre=nombreTMP;
}

int S_NUMERO_REGISTROS=0;
char NOMBRE[256];

void J_Sc_manageHiScore();
void J_Sc_newHiScore();
void J_Sc_nuevoRegistro(int);
void J_Sc_sustRegistro(int);
void J_Sc_cargarHiScore();

hsdat hiScore[10]; //Reservo 10 registros..


//---------------------------Main loop
int main()
{
	cout<<"Pacmalo v.0.0.2"<<endl<<"(C) 2006 Sergio Gonzalez"<<endl<<"Pacmalo es software libre, distribuido bajo la licencia GNU GPL."<<endl;
/*
	cout<<"Dime tu nombre"<<endl;
	cin>>NOMBRE;
*/

//Ahora voy a asumir que hiScore 1 esta ocupado por DIOS, con 30000
hiScore[1].nombre="DIOS";
hiScore[1].score=30000;

hiScore[2].nombre="Jesus";
hiScore[2].score=10000;

hiScore[2].nombre="Maria";
hiScore[2].score=30;
S_NUMERO_REGISTROS=10;
//Fin



int MAIN_SCORE=0;
bool MAIN_LOOP_QUIT=false;
//Loop Principal
//cin>>*NOMBRE;
enum startUpNum{JUGAR=0,HISCORE=1,AYUDA=2,SALIR=3};
bool JUEGO_QUIT=false;
	while(MAIN_LOOP_QUIT==false)
	{
	switch(J_startUp())
		{
		case JUGAR:
			while(JUEGO_QUIT==false){
			switch(J_nivelUno(&MAIN_SCORE))
			{
				//Ganaste el nivel? 
			case 1: break;
				//Perdiste? 
			case 0: JUEGO_QUIT=true; /*FUNCION_PERDER;*/ break;
			}
			}
			SCORE=0;
			JUEGO_QUIT=false;
			break;
		case SALIR:
				//Descomenta esto cuando el hiscore sirva... 
			/*J_Sc_manageHiScore()*/;
			MAIN_LOOP_QUIT=true;
			break;	
		default:
			break;
		}
	}
return 0;
}



//-************___Definir funciones!____

	//Manage hiScore..
void J_Sc_manageHiScore() {
//Crear un nuevo archivo registro si no existe el archivo
	ifstream hsFile("hiScore.dat",ios::in);
	if(!hsFile){
	J_Sc_newHiScore();
	}
	else J_Sc_cargarHiScore();

//Haz un registro temporal.
	hsdat score;
	score.nuevo(NOMBRE,SCORE);
//Incluir tu registro dentro de la base de datos y organizarla
	J_Sc_nuevoRegistro(score.score);

}


void J_Sc_newHiScore() {
	cout<<"Nuevo archivo hiScore"<<endl;
	ofstream hsFile("hiScore.dat", ios::binary );
	for(int i=1;i<=10;i++){
		hsFile.write(reinterpret_cast<const char*>(&hiScore[i]),sizeof(hsdat));
	}
}

void J_Sc_nuevoRegistro(int score){

//Hacer que esta funcion haga un for, checando cada valor en el hiScore
//Y sustituir un valor menor (o igual)
bool cambialo=false;
int i=1;
//int i=1;
	for(i;i<=(S_NUMERO_REGISTROS+1)&&cambialo==false;i++){
		if(score>=hiScore[i].score) {
		cambialo=true;
		}
	}//Fin de for

//Hacerlo recursivo con el score eliminado! para que se baje...
if(i!=10) J_Sc_sustRegistro(i-1);

	if(cambialo==true){
	i--;
	hiScore[i].nombre=NOMBRE;
	hiScore[i].score=score;
	if(S_NUMERO_REGISTROS<10) S_NUMERO_REGISTROS++;
	}//Fin de if
//Imprimir los registros al flujo de salida
	for(i=1;i<=(S_NUMERO_REGISTROS);i++){
	cout<<"Registro "<<i<<" es "<<hiScore[i].nombre<<" "<<hiScore[i].score<<endl;
	}
}

//Esta funcion es recursiva, mueve todos los scores para que se queden ordenados y se vayan
//limpiando..
void J_Sc_sustRegistro(int i){
	if(i<10 && hiScore[i+1].score>0)
	{
		J_Sc_sustRegistro(i+1);
	}
	if(hiScore[i+1].score==0){
		hiScore[i+1]=hiScore[i];	
		hiScore[i].score=0;
	}
}

void J_Sc_cargarHiScore()
{
	cout<<"Cargando hiScore.dat"<<endl;
//Leer los registros hasta que acabe el archivo
	ifstream hsFile("hsdat.dat",ios::in);
	while(hsFile && !hsFile.eof()) {
	for(int i=1;i<=10;i++){
		hsFile.read(reinterpret_cast<char *>(&hiScore[i]),sizeof(hsdat));//Continuar aqui*****************
	}//Fin de for
	}//Fin de while
}
