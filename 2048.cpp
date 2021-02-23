/*
Programa: Proyecto Final (2048)
Autores: Juan David Guevara Garcia, Sebastian Garavito Camacho, Roger Gomez Torres.
Fecha: 14/01/2021
*/

//Declaracion de las librerías
#include<iostream>
#include<locale.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string>
#include<windows.h>



using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define A 65

//Prototipo funciones

void clearMatriz(int list[4][4]);
void spawnNumber(int list[4][4]);
void printMatriz(int list[4][4]);
int verifMatriz(int list[4][4], bool *x);
void movArriba(int list[4][4], int *x);
void movAbajo(int list[4][4], int *x);
void movIzquierda(int list[4][4], int *x);
void movDerecha(int list[4][4], int *x);
void spawnNumber_dos(int list[4][4]);
void color(int k);
//void colorTablero(int a);
void controles();
void cuadro();
void gotoxy(int x, int y);

//----------Persistencia----------------

int menu(FILE *fichero);
void insertarPuntaje(FILE *fichero,int puntaje);
void verPuntaje(FILE *fichero);

//Estructura
struct registroP{
	
	char nombre[15]="\0";
	int puntaje=0;
} registro;

//variables globales

bool jugada = false;
int exitGame=0;

int main ()
{ 
	int i, j;
	bool full;
	int score=0;
	setlocale(LC_CTYPE,"spanish");
	system("ClS");
 	int opcion,tipoMenu,valorSalida;
  int exitMenu=0;
	int numeros[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};//{{1,2,3,4},{5,6,6,8},{9,10,11,0},{13,14,0,16}};
	FILE*fichero;
  while(!exitMenu){
    system("ClS");
    tipoMenu=menu(fichero);
    cin>>opcion;
    if(opcion==3){
      if(tipoMenu==1){
        system("CLS");
        cout<<"Aun no se ha guardado ningun puntaje"<<endl;
        getch();
        system("CLS");
        tipoMenu=menu(fichero);
        cin>>opcion;
      }
    }
    switch(opcion){
      case 1: {
        system("cls");
        spawnNumber_dos(numeros);
        spawnNumber_dos(numeros);
        printMatriz(numeros);
        cuadro();
        cout<<endl<<endl<<"   P U N T A J E\t"<<score;
        cout<<endl<<"==================";	
        cout<<verifMatriz(numeros, &full);
        int c = 0; 
        while(c!=27 && exitGame!=1){
              c = 0;
              switch((c=getch())) {
                case KEY_UP:
                  //cout << endl << "Arriba" << endl;//key up
                  movArriba(numeros, &score);
                  if(jugada==true){
                    system("CLS");            	
                    spawnNumber_dos(numeros);  
                    printMatriz(numeros);
                    cuadro();
                    cout<<endl<<endl<<"   P U N T A J E\t"<<score;
                    cout<<endl<<"==================";	
                    verifMatriz(numeros, &full);
                    valorSalida=verifMatriz(numeros, &full);
                    if(valorSalida==1){
                      exitGame=1;
                    }				      		
                  } 
                
                  break;
                case KEY_DOWN:
                  //cout << endl << "Abajo" << endl;   // key down
                  movAbajo(numeros, &score);
                  if(jugada==true){
                    system("CLS");            	
                    spawnNumber_dos(numeros);  
                    printMatriz(numeros);
                    cuadro();
                    cout<<endl<<endl<<"   P U N T A J E\t"<<score;
                    cout<<endl<<"==================";	
                    verifMatriz(numeros, &full);
                    valorSalida=verifMatriz(numeros, &full);
                    if(valorSalida==1){
                      exitGame=1;
                    }			      		
                  } 
                
                  break;
                case KEY_LEFT:
                  //cout << endl << "Izquierda" << endl;  // key left
                  movIzquierda(numeros, &score);
                  if(jugada==true){
                    system("CLS");            	
                    spawnNumber_dos(numeros);  
                    printMatriz(numeros);
                    cuadro();
                    cout<<endl<<endl<<"   P U N T A J E\t"<<score;
                    cout<<endl<<"==================";	
                    verifMatriz(numeros, &full);
                    valorSalida=verifMatriz(numeros, &full);
                    if(valorSalida==1){
                      exitGame=1;
                    }				      		
                  } 
                
                  break;
                case KEY_RIGHT:
                  //cout << endl << "Derecha" << endl;  // key right
                  movDerecha(numeros, &score);
                  if(jugada==true){
                    system("CLS");            	
                    spawnNumber_dos(numeros);  
                    printMatriz(numeros);
                    cuadro();
                    cout<<endl<<endl<<"   P U N T A J E\t"<<score;
                    cout<<endl<<"==================";	
                    verifMatriz(numeros, &full);
                    valorSalida=verifMatriz(numeros, &full);
                    if(valorSalida==1){
                      exitGame=1;
                    }		      		
                  }  
                  break;
              }
          }
        insertarPuntaje(fichero,score);
        
      }
        break;
      case 2: {
        //ver controles
        system("ClS");
        controles();
        getch();
      }
        break;
      case 3: {
        //ver puntajes
        system("ClS");
        verPuntaje(fichero);
        getch();
      }
        break;
      case 4: {
        //salir
        exitMenu=1;
      }
        break;

    }
  }
	system("PAUSE");
	return 0;	
}
//Desarrollo funciones


//-------------------------Tablero----------------------------------------

//Limpiar la matriz
void clearMatriz(int list[4][4])
{
	for(int i=0; i<4; i++)
	{
		for(int j=0;j<4;j++)
		{
			list[i][j]=0;
		}
		printMatriz(list);
	}
	
}
//Generar los numeros en el tablero
void spawnNumber(int list[4][4])
{
	bool val=false;
	do {
		//Elegir al azar
		//Recordar Modificar la probabilidad de los números
		int lista[2]={2,4};
		srand (time(NULL));
		int fil=rand() % 4;
		int col=rand() % 4;
		
		//Llenar si esta libre
		if (list[fil][col]==0){
			list[fil][col]=lista[(rand() % 2)];
			val=true;
		}
	}
	while(val!=true);
}
void spawnNumber_dos(int list[4][4]){
	bool val=false;
	int i, j, k=0, sum=0;//contadores
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(list[i][j]==0){
				sum++;
			}
		}
	}
	int aux[sum][2];//Matriz auxliar guarda las posiciones donde hay cero
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(list[i][j]==0){
				aux[k][0]=i;
				aux[k][1]=j;
				k++;
			}
		}
	}

	//Elegir al azar
	//Recordar Modificar la probabilidad de los números
	int lista[2]={2,4};
	srand (time(NULL));
	int fil=rand() % sum;
	//int col=rand() % 2;
  
	//Llenar si esta libre
	
	//list[fil][col]=lista[(rand() % 2)];
	i=aux[fil][0];
	j=aux[fil][1];
	list[i][j]=lista[(rand() % 2)];
	
}

//Imprimir la Matriz
void printMatriz(int list[4][4]){
	cout<<endl<<endl<<endl<<endl;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){	
      		if(list[i][j]!=0){
      			cout<<"\t"<<list[i][j];
			}
			else{
				cout<<"\t"<<" ";
			}
		}
		cout<<endl<<endl<<endl<<endl;
	}
  
} 
//Imprimir controles
void controles(){
  cout<<"\tControles:"<<endl;
 	cout<<"\tMovimiento: Flechas del teclado"<<endl;
  cout<<"\tSalir en culquier momento: Esc"<<endl;
}
//-------------------------------------------------------------------------

//-------------------Verificación de la matriz-----------------------------
int verifMatriz(int list[4][4], bool *x){
	int i, j, mid=0, aris=0, aux=0, cero=0;
	*x=false;
	//Busca si hay cero
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(list[i][j]==0){
				cero=1;
			}
		}
	}
	//Compara las casillas del centro
	for(i=1;i<3;i++){
		for(j=1;j<3;j++){
			if(list[i][j]!=list[i][j+1] and list[i][j]!=list[i][j-1] and list[i][j]!=list[i+1][j] and list[i][j]!=list[i-1][j]){
				aux++;
			}
		}
	}
	if(aux==4){
		mid=1;
	}
	aux=0;
	//Comparación de las aristas horizontales
	for(i=0;i<4;i=i+3){
		for(j=1;j<3;j++){
			if(list[i][j]!=list[i][j+1] and list[i][j]!=list[i][j-1]){
				aux++;
			}
		}
	}
	//Comparación de las aristas verticales
	for(i=0;i<4;i=i+3){
		for(j=1;j<3;j++){
			if(list[j][i]!=list[j+1][i] and list[j][i]!=list[j-1][i]){
				aux++;
			}
		}
	}
	if(aux==8){
		aris=1;
	}
	aux=0;
	if(aris==1 and mid==1 and cero==0){
		*x=true;
    return(1);
	}
	else{
		*x=false;
    return(0);
	}
}

//---------------------Movimientos y Fusión---------------------------------
void movDerecha(int list[4][4], int *x)
{
	int cont=0, i, j;
	jugada=false;
	int aux=0;
	while (cont!=3) {
		for (int i=0; i<4; i++){
			for (int j=2; j>-1; j--){
				 
			 	if(list[i][j+1]==0 && list[i][j]!=0){
			 		list[i][j+1]=list[i][j];
			 		list[i][j]=0;
					aux=1;
				}
			}
		}
		cont=cont+1;
	}
	for (i=0;i<4;i++){ //fusión
		for (j=3;j>0;j--){
			if(list[i][j]==list[i][j-1] && list[i][j]!=0){
				list[i][j]=2*list[i][j];
				*x = *x + list[i][j];
				list[i][j-1]=0;
				aux=1;
			}
		}
	}
	cont=0;
	while (cont!=3) {
		for (int i=0; i<4; i++){
			for (int j=2; j>-1; j--){
				 
			 	if(list[i][j+1]==0){
			 		list[i][j+1]=list[i][j];
			 		list[i][j]=0;
				}
			}
		}
		cont=cont+1;
	}
	if(aux==1){
		jugada=true;
	}
	else{
		jugada=false;
	}
	
}

void movIzquierda(int list[4][4], int *x)
{
	int cont=0, i, j;
	int aux=0;
	while (cont!=3) {
		for (int i=0; i<4; i++){
			for (int j=1; j<4; j++){
				 
			 	if(list[i][j-1]==0 && list[i][j]!=0){
			 		list[i][j-1]=list[i][j];
			 		list[i][j]=0;
			 		aux=1;
				}
			}
		}
		cont=cont+1;
	}
	for (i=0;i<4;i++){//fusión
		for (j=0;j<3;j++){
			if(list[i][j]==list[i][j+1] && list[i][j]!=0){
				list[i][j]=2*list[i][j];
				*x = *x + list[i][j];
				list[i][j+1]=0;
				aux=1;
			}
		}
	}
	cont=0;
	while (cont!=3) {
		for (int i=0; i<4; i++){
			for (int j=1; j<4; j++){
				 
			 	if(list[i][j-1]==0){
			 		list[i][j-1]=list[i][j];
			 		list[i][j]=0;
				}
			}
		}
		cont=cont+1;
	}
	if(aux==1){
		jugada=true;
	}
	else{
		jugada=false;
	}		
}

void movArriba(int list[4][4], int *x)
{
	int cont=0, i, j;
	int aux=0;
	while (cont!=3) {
		for (int j=0; j<4; j++){
			for (int i=1; i<4; i++){
				 
			 	if(list[i-1][j]==0 && list[i][j]!=0){
			 		list[i-1][j]=list[i][j];
			 		list[i][j]=0;
			 		aux=1;
				}
			}
		}
		cont=cont+1;
	}
	for(j=0;j<4;j++){//Fusión
		for(i=0;i<3;i++){
			if(list[i][j]==list[i+1][j] && list[i][j]!=0){
				list[i][j]=2*list[i][j];
				*x = *x + list[i][j];
				list[i+1][j]=0;
				aux=1;
			}
		}
	}
	cont=0;
	while (cont!=3) {
		for (int j=0; j<4; j++){
			for (int i=1; i<4; i++){
				 
			 	if(list[i-1][j]==0){
			 		list[i-1][j]=list[i][j];
			 		list[i][j]=0;
				}
			}
		}
		cont=cont+1;
	}	
	if(aux==1){
		jugada=true;
	}
	else{
		jugada=false;
	}	
}

void movAbajo(int list[4][4], int *x)
{
	int cont=0, i, j;
	int aux=0;
	while (cont!=3) {
		for (int j=0; j<4; j++){
			for (int i=2; i>-1; i--){
				 
			 	if(list[i+1][j]==0 && list[i][j]!=0){
			 		list[i+1][j]=list[i][j];
			 		list[i][j]=0;
			 		aux=1;
				}
			}
		}
		cont=cont+1;
	}
	for(j=0;j<4;j++){//Fusión
		for(i=3;i>0;i--){
			if(list[i][j]==list[i-1][j] && list[i][j]!=0){
				list[i][j]=2*list[i][j];
				*x = *x + list[i][j];
				list[i-1][j]=0;
				aux=1;
			}
		}
	}
	cont=0;
	while (cont!=3) {
		for (int j=0; j<4; j++){
			for (int i=2; i>-1; i--){
				 
			 	if(list[i+1][j]==0){
			 		list[i+1][j]=list[i][j];
			 		list[i][j]=0;
				}
			}
		}
		cont=cont+1;
	}
	if(aux==1){
		jugada=true;
	}
	else{
		jugada=false;
	}		
}
//---------------------------------------------------------------------

//---------------------------Ficheros----------------------------------
int menu(FILE*fichero){
	int comp=0;
	fichero= fopen("Puntaje","r");
	if(!fichero){	
		cout<<"Menu:"<<endl;
 		cout<<"\t1. Jugar"<<endl;
    	cout<<"\t2. Ver controles"<<endl;
 		cout<<"\t3. Ver puntajes (Sin puntajes)"<<endl;
 		cout<<"\t4. Salir"<<endl;
    comp=1;
	}
	else{
		cout<<"Menu:"<<endl;
 		cout<<"\t1. Jugar"<<endl;
 		cout<<"\t2. Ver controles"<<endl;
 		cout<<"\t3. Ver puntajes"<<endl;
 		cout<<"\t4. Salir"<<endl;
    	comp=2;
	}
	fclose(fichero);
  return comp;
}
void insertarPuntaje(FILE *fichero,int puntaje)
{
	string buffer;
	fichero= fopen("Puntaje","r");
	if(!fichero){
		fichero= fopen("Puntaje","w");
	}
	else{
		//fclose(fichero);
		fichero= fopen("Puntaje", "a+");
	}
	//Entrada de datos
	cout<<"Digite su nombre para guardar el puntaje: "<<endl;
	cin.ignore();
	getline(cin,buffer);
	for(int i=0;i<15;i++){
		registro.nombre[i]=buffer[i];
	}
 	registro.puntaje=puntaje;
	fwrite(&registro, sizeof(struct registroP), 1, fichero);
	fclose(fichero);
}
void verPuntaje(FILE*fichero){
	fichero= fopen("Puntaje","r");
	
	//Impresion de puntajes
	cout<<"-----------Puntajes-----------"<<endl;
	fread(&registro, sizeof(struct registroP), 1, fichero);
	while(!feof(fichero)){
		cout<<registro.nombre<<" : "<<registro.puntaje<<endl;
		fread(&registro, sizeof(struct registroP), 1, fichero);
	}
	fclose(fichero);
}

//--------Cosas Estéticas-------
void gotoxy(int x, int y){
	HANDLE xd= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD posicion;
	posicion.X=x;
	posicion.Y=y;
	SetConsoleCursorPosition(xd, posicion);
}
void cuadro(){
	int j, i;
	//Esquinas superiores
	gotoxy(4,2);
	printf("%c",201);
	gotoxy(4,18);
	printf("%c", 200);
	//Margenes horizontales
	for(int i=5;i<37;i++){//37
		if(i==12 or i==20 or i==28){
			gotoxy(i,2);
			printf("%c",203);
			gotoxy(i,18);
			printf("%c",202);			
						
		}
		else{
			gotoxy(i,2);
			printf("%c",205);
			gotoxy(i,18);
			printf("%c",205);			
		}
	
	}
	//Margenes verticales
	for (i=3;i<18;i++){
		if(i==6 or i==10 or i==14){
			gotoxy(4,i);
			printf("%c",204);
			gotoxy(36,i);
			printf("%c",185);			
		}
		else{
			gotoxy(4,i);
			printf("%c",186);
			gotoxy(36,i);
			printf("%c",186);
		}
	}
	//Cruces
	for(i=6; i<=14; i=i+4){
		for(j=12; j<=28; j=j+8){
			gotoxy(j,i);
			printf("%c",206);
		}
	}
	//Horizontales interiores
	for (j= 6; j<18; j=j+4){
		for(int i=5;i<36;i++){//37
			if(i!=12 and i!=20 and i!=28){
				gotoxy(i,j);
				printf("%c",205);
			
			}
		}		
	}
	//Verticales interiores
	for (j=12; j<=28; j=j+8){
		for (i=3;i<18;i++){
			if(i!=6 and i!=10 and i!=14){
				gotoxy(j,i);
				printf("%c",186);		
			}
	
		}		
	}	
	//Esquinas inferiores			
	gotoxy(36,2);
	printf("%c",187);
	gotoxy(36,18);
	printf("%c",188);	
	
	cout<<endl<<endl<<endl;
}

void color(int k){//--------------------------------------
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

/*void colorTablero (int a)
{
	switch (a){
		
		case 0:
			color(136);
			break;
			
		case 2:
			color(112);
			break;
			
		case 4:
			color(240);
			break;
			
		case 8:
			color(176);
			break;
		
		case 16:
			color(48);
			break;
		
		case 32:
			color(159);
			break;
		
		case 64:
			color(31);
			break;
		
		case 128:
			color(95);
			break;
		
		case 256:
			color(223);
			break;
		
		case 512:
			color(207);
			break;
		
		case 1024:
			color(79);
			break;
		
		case 2048:
			color(111);
			break;
		
		default:
			color (15);
			break;	
	}
}
*/
