#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


//registros, instruccion, valor
int AX,BX,CX,DX,valor;
char instruccion[3];
//inicializo las variables
//AX=0;BX=0;CX=0;DX=0;
//PID=0;
char estado[]="Ejecucion";


//funcion para leer el teclado
int KeyBoardHit(void){
	struct timeval tv;
	fd_set read_fd;
	tv.tv_sec=0;
	tv.tv_usec=0;
	FD_ZERO(&read_fd);
	FD_SET(0,&read_fd);
	if(select(1,&read_fd,NULL,NULL,&tv)==-1)
		return 0;
	if(FD_ISSET(0,&read_fd))
	return 1;
}
 

void operaciones(int instr, int val, int reg ){
//MOV=1,ADD=2,SUB=3,MUL=4,DIV=5,INC=6,DEC=7,END=8
	switch(instr)
	{
		case 1:
	          if(reg==1){
	            AX=val;
	          }else if(reg==2){
	            BX=val;
	          }else if(reg==3){
	            CX=val;
	          }else if(reg==4){
	            DX=val;
	          }
			break;
		case 2:
	          if(reg==1){
	            AX+=val;
	          }else if(reg==2){
	            BX+=val;
	          }else if(reg==3){
	            CX+=val;
	          }else if(reg==4){
	            DX+=val;
	          }
			break;
		case 3:
	          if(reg==1){
	            AX-=val;
	          }else if(reg==2){
	            BX-=val;
	          }else if(reg==3){
	            CX-=val;
	          }else if(reg==4){
	            DX-=val;
	          }
			break;
		case 4:
	          if(reg==1){
	            AX*=val;
	          }else if(reg==2){
	            BX*=val;
	          }else if(reg==3){
	            CX*=val;
	          }else if(reg==4){
	            DX*=val;
	          }
			break;
		case 5:
	          if(reg==1){
	            AX/=val;
	          }else if(reg==2){
	            BX/=val;
	          }else if(reg==3){
	            CX/=val;
	          }else if(reg==4){
	            DX/=val;
	          }
			break;
		case 6:
	          if(reg==1){
	            AX+=1;
	          }else if(reg==2){
	            BX+=1;
	          }else if(reg==3){
	            CX+=1;
	          }else if(reg==4){
	            DX+=1;
	          }
			break;
		case 7:
	          if(reg==1){
	            AX-=1;
	          }else if(reg==2){
	            BX-=1;
	          }else if(reg==3){
	            CX-=1;
	          }else if(reg==4){
	            DX-=1;
	          }
			break;
		case 8:
			strcpy(estado,"Terminado");
			break;
		default: break;		
	}
}

int instruccionLee(char instruccion[])
	{
		int operacion=0;
		if(strcmp(instruccion,"MOV")==0){operacion=1;
		}else if(strcmp(instruccion,"ADD")==0){operacion=2;
		}else if(strcmp(instruccion,"SUB")==0){operacion=3;
		}else if(strcmp(instruccion,"MUL")==0){operacion=4;
		}else if(strcmp(instruccion,"DIV")==0){operacion=5;
		}else if(strcmp(instruccion,"INC")==0){operacion=6;
		}else if(strcmp(instruccion,"DEC")==0){operacion=7;
		}else if(strcmp(instruccion,"END")==0){operacion=8;
		}
		return operacion;
}

int registroLee(char instruccion[])
	{
			int regi=0;
		if(strcmp(instruccion,"AX")==0){regi=1;
		}else if(strcmp(instruccion,"BX")==0){regi=2;
		}else if(strcmp(instruccion,"CX")==0){regi=3;
		}else if(strcmp(instruccion,"DX")==0){regi=4;}
		return regi;
}

int main(int argc, char** argv)
{

	FILE *filePrograma;
	//variables del archivo programa
	char instrucProgram[10];
	char registroProgram[10];
	int datoProgram;
	char comando[10],archivo[10];
	int PID;
	PID=1;

	initscr();
	mvprintw(0,0,"Ever$");
	mvprintw(1,2,"PID\t ESTADO\t\tAX\tBX\tCX\tDX\tIMAGEN\n");

while(comando != "salir"){
	move(0,6);
	refresh();
	if(KeyBoardHit())
		{
			mvscanw(0,6,"%s %s",comando, archivo);
			mvprintw(0,5,"\t\t\t");
		}

	if(strcasecmp(comando,"salir")==0){
		break;
	}

	if (strcasecmp(comando,"ejecutar")==0)
		{
			filePrograma = fopen ( archivo, "r" );        

			if (filePrograma==NULL)
				{;}
				// {fputs ("File error",stderr); exit (1);}
			else{
				while (fscanf( filePrograma,"%s%d%s",instrucProgram,&datoProgram,registroProgram)!=EOF)
   					{
   						operaciones(instruccionLee(instrucProgram),datoProgram,registroLee(registroProgram));

	      				mvprintw(2,2,"%d\t %s\t %d\t%d\t %d\t %d\t %s\t\n",PID,estado,AX,BX,CX,DX,archivo);
						refresh();
						sleep(2);
   						//erase();//borramos cada printw que vamos haciendo 
   						PID+=1;
   					}
   					//devolver valores iniciales a los registros
   					PID=0;
   					AX=0;BX=0;CX=0;DX=0;
   					strcpy(estado,"Ejecucion");
   					//
   				fclose ( filePrograma );
   				mvprintw(2,2,"\t\t\t\t\t\t\t\t\t\t");
   				strcpy(comando," ");//cambio el valor de comando para volver a solicitar el comando

				}
		}
	}

	endwin();
	return 0;
}

	

	// else
	// 	{
 //   			//para dar color a la terminal color amarillo para el texto y azul para el fondo
 //   			if (has_colors())
 //   				start_color();
 //   				init_pair(1, COLOR_YELLOW, COLOR_BLUE);
 //   				attron(COLOR_PAIR(1));//termina ciclo para el color
   				
   		
	// 	}	

	

