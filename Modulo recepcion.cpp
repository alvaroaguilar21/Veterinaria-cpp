#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib-Struct.h"


typedef char Cadena[45];

struct Usuario1
{	
	Cadena usuario;
	Cadena contrasena;
	int matricula;
};


bool IniciarSesion(FILE *selec);
void RegistroMascota(FILE *mascotas);
void RegistroTurnos(FILE *turnos, FILE *selec);
void Listado(FILE *turnos);

main(){
	
	FILE *mascotas = fopen("Mascotas.dat", "a+b");
	FILE *turnos = fopen("Turnos.dat", "a+b");
	FILE *selec;
	int opc;
	
	do{
		
		system("cls");
		printf("*********************************Recepcion********************************************\n");
		printf("****************** 1) Iniciar sesion *************************************************\n");
		printf("****************** 2) Registrar mascota **********************************************\n");
		printf("****************** 3) Registrar turnos ***********************************************\n");
		printf("****************** 4) Listado de atenciones por Veterinario y Fecha ******************\n");
		printf("****************** 0) Salir **********************************************************\n");
		printf("**************************************************************************************\n");
		
		scanf("%d", &opc);
		
		switch(opc){
			case 1: IniciarSesion(selec);
					fclose(selec);
			        break;
			        
			case 2: RegistroMascota(mascotas);
					break;
					
			case 3: RegistroTurnos(turnos,selec);
					fclose(selec);
			        break;
			        
			case 4: Listado(turnos);
					break;
					
		}
		system("pause");
		
	}while(opc!=0);
	
};

bool IniciarSesion(FILE *selec){
	Cadena usuario1, contrasenea1;
	
	selec = fopen("Usuarios.dat","rb");
	Usuario1 nuevo;
	fread(&nuevo, sizeof(nuevo), 1, selec);
	
	if(selec == NULL)
	{
		printf("\nSe produjo un error al intentar abrir el archivo ");
		system("pause");
	}
	
	printf("\nIngrese su nombre de usuario: ");
	_flushall();
	gets(usuario1);
	printf("\nIngrese su contraseña de usuario: ");
	gets(contrasenea1);
	
	while(!feof(selec)){
		if (strcmp(usuario1, nuevo.usuario) == 0 && strcmp(contrasenea1, nuevo.contrasena) == 0) 
		printf("\n*********************Bienvenido/a**************************");
		return true;
	}
	
	printf("\nError al iniciar sesion");
	return false;
};

void RegistroMascota(FILE *mascotas){
	rewind(mascotas);
	Mascota m[50];
	char op;
	int B, i=0;
	
	do{
	printf("\nIngrese nombre y apellido de la mascota: "); //apellido de la familia
	gets(m[i].ApellidoyNombre);
	printf("\nIngrese el domicilio: ");
	gets(m[i].Domicilio);
	_flushall;
	printf("\nIngrese su DNI: ");
	scanf("%d", &m[i].DNI_Duenio);
	_flushall;
	printf("\nIngrese la localidad: ");
	gets(m[i].Localidad);
	_flushall;
	printf("\nIngrese la fecha de nacimiento de la mascota: ");
	printf("\nDia: ");
	scanf("%d", &m[i].FechadeNac.dia);
	printf("\nMes: ");
	scanf("%d", &m[i].FechadeNac.mes);
	printf("\nAño: ");
	scanf("%d", &m[i].FechadeNac.anio);
	printf("\nIngrese el peso de la mascota: ");
	scanf("%f", &m[i].Peso);
	_flushall;
	printf("\nIngrese su nro de telefono: ");
	gets(m[i].Telefono);
	_flushall;
	fwrite(&m, sizeof(m), 1, mascotas);
	
	printf("\nDesea seguir registrando mascotas? (s/n) ");
	scanf("%c", &op);
	if(op == 's')
		B=0;
	else
		B=1;

	i++;
	}while(B==0);
	fclose(mascotas);
	
};

void RegistroTurnos(FILE *turnos, FILE *selec){
	rewind(turnos);
	Turnos t[50];
	char op;
	int B, i=0;
	
	selec = fopen("Usuarios.dat","rb");
	Usuario1 auxiliar;
	fread(&auxiliar, sizeof(auxiliar), 1, selec);
	
	if(selec == NULL)
	{
		printf("\nSe produjo un error al intentar abrir el archivo");
		system("pause");
	}
	
	do{	
	do{
	printf("\nIngrese la matricula del veterinario: ");
	scanf("%d", &t[i].Matric_Veterinario);
	}while(t[i].Matric_Veterinario != auxiliar.matricula);
	
	printf("\nIngrese la fecha: ");
	printf("\nDia: ");
	scanf("%d", &t[i].Fecha.dia);
	printf("\nMes: ");
	scanf("%d", &t[i].Fecha.mes);
	printf("\nAño: ");
	scanf("%d", &t[i].Fecha.anio);
	printf("\nIngrese su DNI: ");
	scanf("%d", &t[i].DNI_Duenio);
	_flushall;
	printf("\nIngrese el detalle de atencion: ");
	gets(t[i].Detalle_Atencion);
	fwrite(&t, sizeof(t), 1, turnos);
	
	printf("\nDesea seguir registrando mascotas? (s/n) ");
	scanf("%c", &op);
	if(op == 's')
		B=0;
	else
		B=1;
	
	i++;
	}while(B==0);
	fclose(turnos);
		
};

void Listado(FILE *turnos){
	rewind(turnos);
	Turnos t[50];
	int N,i;
	N=i;
	fread(&t, sizeof(t), 1, turnos);
	
	for(int i=0;i<N;i++){
	while(!feof(turnos)){
		printf("\nMatricula del veterinario: %s", t[i].Matric_Veterinario);
		printf("\nFecha de atencion: %d/%d/%d", t[i].Fecha.dia, t[i].Fecha.mes, t[i].Fecha.anio);
		printf("***************************************************");
		fread(&t, sizeof(t), 1, turnos);
	};
	};
};
