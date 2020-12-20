#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib-Struct.h"

typedef char Cadena[45];

struct Usuario1
{	
	Cadena usuario1;
	Cadena contrasenea1;
};


bool IniciarSesion(FILE *usuario);
void RegistroMascota(FILE *mascotas);
void RegistroTurnos(FILE *turnos);
void Listado(FILE *turnos);

main(){
	
	FILE *usuarios = fopen("usuarios.dat", "a+b");
	FILE *mascotas = fopen("Mascotas.dat", "a+b");
	FILE *turnos = fopen("Turnos.dat", "a+b");
	
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
			case 1: usuarios = fopen("Usuarios.dat","rb");
					IniciarSesion(usuarios);
					fclose(usuarios);
			        break;
			        
			case 2: RegistroMascota(mascotas);
					break;
					
			case 3: veterinario = fopen("Veterinarios.dat","rb");
					RegistroTurnos(turnos,veterinario);
					fclose(veterinario);
			        break;
			        
			case 4: Listado(turnos);
					break;
					
		}
		system("pause");
		
	}while(opc!=0);
	
};

bool IniciarSesion(FILE *usuario){
	Cadena usuario1, contrasenea1;

	rewind(usuario);
	Usuarios U;
	//cadena usuario, contrasenea;
	fread(&U, sizeof(U), 1, usuario);
	
	if(usuario == NULL)
	{
		printf("\nSe produjo un error al intentar abrir el archivo ");
		system("pause");
	}
	
	printf("\nIngrese su nombre de usuario: ");
	_flushall();
	gets(usuario1);
	printf("\nIngrese su contraseña de usuario: ");
	gets(contrasenea1);
	
	while(!feof(usuario)){
		if (strcmp(usuario1, U.usuario) == 0 && strcmp(contrasenea1, U.contrasenea) == 0) 
		printf("\n*********************Bienvenido/a**************************");
		return true;
	}
	
	printf("\nError al iniciar sesion");
	return false;
};

void RegistroMascota(FILE *mascotas,  int &n){
	rewind(mascotas);
	Mascota m;
	Mascota vec[100];
	Mascota aux;
	char op;
	int B;
	
	
	
	do{
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
	_flushall;
	fwrite(&m, sizeof(m), 1, mascotas);
	
	printf("\nDesea seguir registrando mascotas? (s/n) ");
	scanf("%c", &op);
	if(op == 's')
		B=0;
	else
		B=1;
	
	}while(B==0);
	
	//Pasa los registros a un array
    
    fread(&m, sizeof(Mascota),1 ,mascotas); 
	 
    int i=0, n;
    
    while(feof(mascotas)==0)
    {     
       vec[i]=m;
       i++;
       fread(&m, sizeof(Mascota),1 ,mascotas);       
    } 
    n=i;
	
	//Ordena los registros del array
    do
    {
        int b=0;
        for (i=0;i<n-1;i++)
        {
            if (vec[i].ApellidoyNombre > vec[i+1].ApellidoyNombre )
            {
                aux=vec[i];
                vec[i]=vec[i+1];
                vec[i+1]=aux;
                b=1;
            }
        }
    }
    while (b==1);
    
    fclose(mascotas);
    
    //Pasa los registros del array al archivo
     
    for (i=0; i<n; i++)
    {      
       m= vec[i];
       fwrite(&m, sizeof(Mascota), 1, mascotas);           
    } 
    system("pause");  
	
	
	fclose(mascotas);
	
};

void RegistroTurnos(FILE *turnos, FILE *veterinario){
	rewind(turnos);
	Turnos t;
	char op;
	int B;
	
	rewind(veterinario);
	Veterinario v;
	fread(&v, sizeof(v), 1, veterinario);
	
	if(veterinario == NULL)
	{
		printf("\nSe produjo un error al intentar abrir el archivo");
		system("pause");
	}
	
	do{	
	do{
	printf("\nIngrese la matricula del veterinario: ");
	scanf("%d", &t.Matric_Veterinario);
	}while(t.Matric_Veterinario != v.Matricula);
	
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
	
	printf("\nDesea seguir registrando mascotas? (s/n) ");
	scanf("%c", &op);
	if(op == 's')
		B=0;
	else
		B=1;
	
	}while(B==0);
	fclose(turnos);
		
};

void Listado(FILE *turnos){
	rewind(turnos);
	Turnos t;
	fread(&t, sizeof(t), 1, turnos);
	
	while(!feof(turnos)){
		printf("\nMatricula del veterinario: %s", t.Matric_Veterinario);
		printf("\nFecha de atencion: %d/%d/%d", t.Fecha.dia, t.Fecha.mes, t.Fecha.anio);
		printf("***************************************************");
		fread(&t, sizeof(t), 1, turnos);
	};
	
};
