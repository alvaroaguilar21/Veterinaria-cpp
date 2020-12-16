#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib-Struct.h"

typedef char cadena[45];

FILE *usuario;
FILE *ArchVet;
FILE *mascotas;
FILE *turnos;


struct Usuarios
{	
	cadena usuario;
	cadena contrasenea;
	char ApellidoyNombre[60];
	
};


struct Veterinario
{
	char ApellidoyNombre[60];
	int Matricula;
	int Dni;
	char Telefono[25];
	
};

int menuVet();
bool IniciarSesion(FILE *ArchVet);
//void Listar_turno(FILE *turnos);
void evolMasc(FILE *mascotas, FILE *turnos);


main(){
    
	bool ingreso = false;

	int opc;
	do{
		opc=menuVet();
		switch(opc){
			case 1:   if(ingreso == true){
				
			          IniciarSesion(ArchVet);
                    }
                    else{
                    	printf("Inicie sesion");
					}
			          system("cls");
			          break;
			
			case 2: if(ingreso == true){
				
			          //falta funcion listar turnos
                    }
                    else{
                    	printf("Inicie sesion");
					}
			         
			          system("PAUSE");
			          system("cls");
			          break;
			
			case 3: if(ingreso == true){
				
			         evolMasc(mascotas, turnos);
                    }
                    else{
                    	printf("Inicie sesion");
					}
			         
			          system("cls");
			          break;
			          
			case 4:   
			          system("cls");
			          break;
			
	
			
			
			system("PAUSE");
		}
		
	}while(opc != 5);
	
	fclose(arch);
	
	system("pause");
 
 



}


int menuVet(){
	int op=0;
	system("cls");
	printf("   Modulo Consultorio veterinario");
	printf("\t=================================\n");
	printf("\t 1.- Iniciar sesion\n");
	printf("\t 2.- Visualizar lista de espera de turnos(informe)\n");
	printf("\t 3.- Registrar evolución de la mascota\n");
	printf("\t 4.- Cerrar la aplicación\n");
	printf("\t------------------------------------------\n");
	printf("\nIngrese una opcion: ");
	int opc;
	scanf("%d", &opc);
	return opc;
	
}

bool IniciarSesion(FILE *ArchVet){
   
   ArchVet= fopen("Veterinario.dat", "rb");
   Usuarios usuar;
   int Matr;
   cadena contr;
   Veterinario vet;
   
  
   printf("INICIO DE SESION\n");
   printf("---------------");
   printf("Matricula: ");
   _flushall();
   scanf("%d", &Matr);
   printf("Clave: ");
   gets(contr);
   
    fread(&vet, sizeof(vet), 1, ArchVet);
    while(!feof(ArchVet)){
        if(vet.Matricula == Matr && strcmp(vet.contra, contr) == 0){
         	
         	printf("\nBienvenido\n");
         	return true;
		}
		 else{
		 	printf("\nError al iniciar sesion\n");
		 	printf("Vuelva a intentarlo\n");
		 }
		 	 
    }
 
     return false;
 
}

void evolMasc(FILE *mascotas, FILE *turnos){ //Falta completar
	
	mascotas = fopen("Mascotas.dat", "r+b");
	turnos = fopen("Turnos.dat", "r+b");
	
	Mascota masc;
	Turnos turno;
	char nomMasc[45];
	bool bandera = false;
	
	printf("Ingrese el nombre de la mascota: ");
	_flushall();
	gets(nomMasc);
	
	fread(&masc, sizeof(Mascota), 1, mascotas);
	while(!feof(mascotas)){
		if(strcmp(masc.ApellidoyNombre, nomMasc) == 0){
			
		fread(&turno, sizeof(Turnos), 1, turnos);	
			
			while(!feof(turnos)){
				
				if(masc.DNI_Duenio == turno.DNI_Duenio && turno.atendido == false){
				
				
				printf("Evolucion de la mascota: ");
				_flushall();
				gets(turno.Detalle_Atencion)
				
				bandera = true;
				turno.atendido = true;
				
				fseek(turnos, sizeof(turnos), SEEK_CUR);
				fwrite(&turno, sizeof(turnos), 1, turnos);
				
			}
				fread(&turno, sizeof(turnos), 1, turnos);
				
			}
			
			fread(&masc, sizeof(Mascota), 1, mascotas);
		}
		
		if(bandera == false){
			
			printf("EEROR. El nombre ingresado no se encuentra registrado.");
		}
		
	}
    
	fclose(mascotas);
	fclose(turnos);
	
	
}



