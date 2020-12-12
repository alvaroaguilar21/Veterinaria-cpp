#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib-Struct"



bool IniciarSesion(FILE *usuarios);
void RegistroMascota(FILE *mascotas);
void RegistroTurnos(FILE *turnos);

main(){
	
	FILE *usuarios = fopen("usuarios.dat", "a+b");
	FILE *mascotas = fopen("Mascotas.dat", "a+b");
	FILE *turnos = fopen("Turnos.dat", "a+b");
	int opc;
	
	do{
		
		system("cls");
		printf("*********************************Recepcion********************************************\n");
		printf("****************** 1) Inicio sesion **************************************************\n");
		printf("****************** 2) Registrar mascota **********************************************\n");
		printf("****************** 3) Registrar turnos ***********************************************\n");
		printf("****************** 4) Listado de atenciones por Veterinario y Fecha ******************\n");
		printf("****************** 0) Salir **********************************************************\n");
		printf("**************************************************************************************\n");
		
		scanf("%d", &opc);
		
		switch(opc){
			case 1: IniciarSesion(usuarios);
			        break;
			        
			case 2: RegistroMascota(mascotas);
					break;
					
			case 3: RegistroTurnos(turnos);
			        break;
			        
			case 4: Listado(usuarios,mascotas,turnos);
					break;
					
		}
		system("pause");
		
	}while(opc!=0);
	
};

bool IniciarSesion(FILE *usuarios){
	rewind(usuarios);
	Usuarios u;
	Cadena usuario, contrasenea;
	
	printf("\nIngrese su nombre de usuario: ");
	_flushall();
	gets(nombre);
	printf("\nIngrese su contraseña de usuario: ");
	gets(clave);
	fread(&u, sizeof(u), 1, usuarios);
	
	while(!feof(usuarios)){
		if (strcmp(u.usuario, nombre) == 0 && strcmp(u.contrasenea, clave) == 0) 
		printf("\nBienvenido/a");
		return true;
		fread(&u, sizeof(u), 1, usuarios);
	}
	
	printf("\nError al iniciar sesion");
	return false;
};

void RegistroMascota(FILE *mascotas){
	rewind(mascotas);
	Mascota m;
	
	printf("\nIngrese nombre y apellido de la mascota: "); //apellido de la familia
	gets(m.ApellidoyNombre);
	printf("\nIngrese el domicilio: ");
	gets(m.Domicilio);
	_flushall;
	printf("\nIngrese su DNI: ");
	scanf("%d", &m.DNI_Duenio);
	_flushall;
	printf("\nIngrese la localidad: ");
	gets(m.Localidad);
	_flushall;
	printf("\nIngrese la fecha de nacimiento de la mascota: ");
	printf("\nDia: ");
	scanf("%d", &m.FechadeNac.dia);
	printf("\nMes: ");
	scanf("%d", &m.FechadeNac.mes);
	printf("\nAño: ");
	scanf("%d", &m.FechadeNac.anio);
	printf("\nIngrese el peso de la mascota: ");
	scanf("%f", &m.Peso);
	_flushall;
	printf("\nIngrese su nro de telefono: ");
	gets(m.Telefono);
	
	fwrite(&m, sizeof(m), 1, mascotas);
};

void RegistroTurnos(FILE *turnos){
	rewind(turnos);
	Turnos t;
	
	printf("\nIngrese la matricula del veterinario: ");
	scanf("%d", &t.Matric_Veterinario);
	printf("\nIngrese la fecha: ");
	printf("\nDia: ");
	scanf("%d", &t.Fecha.dia);
	printf("\nMes: ");
	scanf("%d", &t.Fecha.mes);
	printf("\nAño: ");
	scanf("%d", &t.Fecha.anio);
	printf("\nIngrese su DNI: ");
	scanf("%d", &t.DNI_Duenio);
	_flushall;
	printf("\nIngrese el detalle de atencion: ");
	gets(t.Detalle_Atencion);
	
	fwrite(&t, sizeof(t), 1, turnos);
};

void Listado(FILE *turnos){
	rewind(turnos);
	Turnos t;
	fread(&t, sizeof(t), 1, turnos);
	
	while(!feof(turnos)){
		printf("\nMatricula del veterinario: %s", t.Matric_Veterinario);
		printf("\nFecha de atencion: %d/%d/%d", t.Fecha.dia, t.Fecha.mes, t.Fecha.anio);
		fread(&t, sizeof(t), 1, turnos);
	};
	
};
