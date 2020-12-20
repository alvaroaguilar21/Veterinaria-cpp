#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include "Lib-Struct.h"

struct Usuario1{
	char usuario[10];
	char contrasena[32];
	char puesto[20];
	char apeyNom[60];
	int matricula;
	int atenciones;
};


void registrar(int opc);
void atenciones();
void ranking();
void listar();

main()
{
	int opc,cargo;

	do
	{
		system("cls");
		printf("******************************Administracion******************************************\n");
		printf("****************** 1) Registrar Veterinario ******************************************\n");
		printf("****************** 2) Registrar Usuario **********************************************\n");
		printf("****************** 3) Registrar Atenciones por veterinario ***************************\n");
		printf("****************** 4) Ranking ********************************************************\n");
		printf("****************** 5) Salir **********************************************************\n");
		printf("**************************************************************************************\n");
		scanf("%d", &opc);
	
	switch(opc){
		case 1:
			system("cls");
			cargo=1;
			registrar(opc);
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			cargo=2;
			registrar(opc);
			system("pause");
			system("cls");
			break;	
		case 3:
			system("cls");
			atenciones();
			system("pause");
			system("cls");
			break;	
		case 4:
			system("cls");
			ranking();
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
		    printf("\n\t EXIT 1");
			exit(1);
			break;	
	}
	}while(opc!=5);
}

void registrar(int opc)
{
	FILE *selec;
	FILE *selecc;
	selec=fopen("Usuarios.dat","ab+");
	Usuario1 auxiliar,nuevo;
	int b=1,i=0,a,c,d;
	int caracteres=0,mayus=0,digitos=0,alfa=0,dif=0;
	if(opc==1)
	{
		printf("\n\t******************************");	
		printf("\n\t Registrar veterinario        ");
		printf("\n\t******************************");	
	}
	if(opc==2)
	{
		printf("\n\t*******************************");	
		printf("\n\t Registrar asistente           ");
		printf("\n\t*******************************");	
	}
	_flushall();
	if(opc==1) printf("\n\n\t Nombre y apellido del veterinario: ");
	if(opc==2) printf("\n\n\t Nombre y apellido del asistente: ");
	gets(nuevo.apeyNom);
	_flushall();
	printf("\n\t NOMBRE DE USUARIO: ");
	gets(nuevo.usuario);

	fread(&auxiliar,sizeof(auxiliar),1,selec);

	while(b==1)
	{
		caracteres=0,mayus=0,digitos=0,alfa=0,dif=0;
		b=0;
		while(!feof(selec))
		{
			if(strcmp(nuevo.usuario,auxiliar.usuario)==0)
			{
				printf("\n EL nombre de usuario ya se encuentra registrado, ingrese otro: ");
				_flushall();
				gets(nuevo.usuario);
				b=1;
			}
			else 
			{
				b=0;
				fread(&auxiliar,sizeof(auxiliar),1,selec);			
			}
		}
		if(nuevo.usuario[0]=='x' or nuevo.usuario[0]=='X') exit(1);		
		caracteres=strlen(nuevo.usuario);
		if(b==0)
		{
			if(caracteres<6 || caracteres>10)
			{
				b=1;
				printf("\nEL nombre de usuario debe contener entre 6 y 10 caracteres, intente de nuevo");
				printf("\nIngrese el nombre de usuario: ");
				_flushall();
				gets(nuevo.usuario);
			}
		}

		if(nuevo.usuario[0]=='x' or nuevo.usuario[0]=='X') exit(1);
		i=0;
		while(nuevo.usuario[i]!='\0')
		{
			if(isupper(nuevo.usuario[i])>0) mayus++;
			i++;
		}
		if(b==0)
		{
			if(mayus<2)
			{
				b=1;
				printf("\n\tEl nombre de usuario debe tener al menos 2 letras mayusculas, intente de nuevo");
			    printf("\nIngrese el nombre de usuario: ");
				_flushall();
				gets(nuevo.usuario);
			}
		}
		if(nuevo.usuario[0]=='x' or nuevo.usuario[0]=='X') exit(1);	
		i=0;
		while(nuevo.usuario[i]!='\0')
		{
			if(isdigit(nuevo.usuario[i])!=0) digitos++;
			i++;
		}		
		if(b==0)
		{
			if(digitos>3)
			{
				b=1;
				printf("\n\tEl nombre debe tener 3 digitos como maximo, intente de nuevo:");
				printf("\nIngrese el nombre de usuario: ");
				_flushall();
				gets(nuevo.usuario);
			}
		}
		if(nuevo.usuario[0]=='x' or nuevo.usuario[0]=='X') exit(1);			
	}
	if(b==0) 
	{
	    printf("\n\tNombre registrado: ");
	    puts(nuevo.usuario);
	}
	if(b==0)
	{
		
		printf("\n\t INGRESE CONTRASEÑA:  ");
		_flushall();
			gets(nuevo.contrasena);		
	}
	while(b==0)
	{
		caracteres=0,mayus=0,digitos=0,alfa=0,dif=0;
		caracteres=strlen(nuevo.contrasena);
		if(caracteres>=6 && caracteres<=32) b=1;
		else
		{
		    printf("\n\tLa contraseña debe tener entre 6 y 32 caracteres, intente de nuevo: ");
		    printf("\nIngrese el nombre de usuario: ");
		
			_flushall();
			gets(nuevo.contrasena);	
		}
		i=0;
		while(nuevo.contrasena[i]!='\0')
		{
			if(isupper(nuevo.contrasena[i])>0) a++;
			if(islower(nuevo.contrasena[i])>0) c++;
			if(isdigit(nuevo.contrasena[i])>0) d++;
			i++;
		}
		if(b==1)
		{
			if(a==0 || c==0 || d==0)
			{
		        printf("\n\tLa contraseña debe tener al menos una letra mayuscula, intente de nuevo: ");
		        printf("\nIngrese el nombre de usuario: ");
				
				_flushall();
				gets(nuevo.contrasena);	
				b=0;
			}
		}
		a=0;c=0;d=0;i=0;
		while(nuevo.contrasena[i]!='\0')
		{
			if(isalnum(nuevo.contrasena[i])==0) alfa++;
			i++;
		}
		if(b==1)
		{
			if(alfa!=0) 
			{
		        printf("\n\tLa contraseña no debe tener caracteres alfanumericos, intente de nuevo: ");
		        printf("\nIngrese el nombre de usuario: ");
				_flushall();
				gets(nuevo.contrasena);	
				b=0;
			}
		}
		i=0;
		while(nuevo.usuario[i+3]!='\0')
		{
			if(isdigit(nuevo.contrasena[i])>0 && isdigit(nuevo.contrasena[i+1])>0 && isdigit(nuevo.contrasena[i+2])>0 && isdigit(nuevo.contrasena[i+3])>0)
			{
		        printf("\n\tLa contraseña no puede tener 3 digitos seguidos, intente de nuevo: ");
		        printf("\nIngrese el nombre de usuario: ");
			
				_flushall();
				gets(nuevo.contrasena);	
				b=0;
			}
			i++;
		}
		i=0;
		if(b==1)
		{
			while(nuevo.contrasena[i+1]!='\0')
			{
				if(isalpha(nuevo.contrasena[i])!=0)
				{
					dif=nuevo.contrasena[i+1]-nuevo.contrasena[i];
					if(dif==1)
					{
                    printf("\n\tLA contraseña no debe tener 2 caracteres consecutivos, intente de nuevo: ");
		            printf("\nIngrese el nombre de usuario: ");
					_flushall();
					gets(nuevo.contrasena);	
					b=0;
					}
				}
				i++;
			}
		}		
	}
	nuevo.atenciones=0;
	if(opc==1) strcpy(nuevo.puesto,"Veterinario");
	if(opc==2) strcpy(nuevo.puesto,"Asistente");	
	
	printf("\nIngrese el numero de matricula: ");
	scanf("%d",&nuevo.matricula);
	selecc=fopen("Usuarios.dat","ab+");
	fread(&auxiliar,sizeof(auxiliar),1,selecc);
	while(b==1)
	{
		b=0;
		while(!feof(selecc))
		{
			if(auxiliar.matricula==nuevo.matricula) b=1;
			fread(&auxiliar,sizeof(auxiliar),1,selecc);
		}
		if(b==1)
		{
			printf("Ingrese una matricula distinta:");
			scanf("%d",&nuevo.matricula);
		}
	}
    printf("\n\t Se ha registrado correctamente");
	fwrite(&nuevo,sizeof(nuevo),1,selec);
	fclose(selec);
}
void atenciones()
{
	Usuario1 auxiliar;
	int b=0;
	FILE *selec;
	char buscar[50],cargo[50];
	strcat(cargo,"Veterinario");
	selec=fopen("Usuarios.dat","ab+");
	printf("\n\n\tLista de Usuarios");
	listar();
	printf("\n\tIngrese el usuario del que necesite saber sus atenciones: ");
	printf("\n\t NOMBRE DE USUARIO: ");
	_flushall();
	gets(buscar);
	fread(&auxiliar,sizeof(auxiliar),1,selec);
	
	if(feof(selec)) printf("\n\t***EL ARCHIVO NO TIENE CONTENIDO***");
	
	while(!feof(selec))
	{
			if(strcmp(buscar,auxiliar.usuario)==0)
			{
				printf("\n\t Cantidad de atenciones del usuario: %s",buscar);
				printf(" \n\ttotal de: %d atenciones.",auxiliar.atenciones);
				b=1;
			}
			fread(&auxiliar,sizeof(auxiliar),1,selec);
	}
	if(b==0) printf("\n\t  El usuario no coincide con ningun veterinario.\n\n");
	printf("\n\n");
	fclose(selec);
}
void ranking()
{
	FILE *selec;
	selec=fopen("Usuarios.dat","ab+");
	Usuario1 auxiliar[100],a;
	int i=0,n=0,b=0,j=0,aux;
	
	printf("\n\t\t*********RANKING DE VETERINARIOS*********");
	
	fread(&a,sizeof(a),1,selec);
	i=0;
	while(!feof(selec))
	{
		auxiliar[i]=a;
		fread(&a,sizeof(a),1,selec);
		i++;
	}		
	n=i;
	
	do{
		b=0;
		for(j=0;j<n;j++)
		{
		if(auxiliar[j].atenciones<auxiliar[j+1].atenciones)
		{
		aux=auxiliar[j].atenciones;
		auxiliar[j].atenciones=auxiliar[j+1].atenciones;
		auxiliar[j+1].atenciones=aux;
		}
	}
	}while(b==1);
	printf("\n\n");
	i=0;
	for(j=0;j<n;j++)
	{
		if(strcmp(auxiliar[j].puesto,"Veterinario")==0)
		{
		printf(".-#%d: %d Atenciones: ",i+1,auxiliar[j].atenciones);
		puts(auxiliar[j].apeyNom);
		printf("\t\t  Usuarios: "); puts(auxiliar[j].usuario);
		i++;
		}
	}
	
	printf("\n\n");
}
void listar()
{
	FILE *selec;
	selec=fopen("Usuarios.dat","ab+");
	int i=0;
	Usuario1 auxiliar;
	printf("\n");
	fread(&auxiliar,sizeof(auxiliar),1,selec);	
	while(!feof(selec))
	{	
		if(strcmp(auxiliar.puesto,"Veterinario")==0)
		{
			printf("\nVeterinario: %d",i+1);
			printf("\n Nombre: "); puts(auxiliar.apeyNom);
			printf("\n Usuarios: %d: ",i+1);
			puts(auxiliar.usuario);
			i++;
		}
		fread(&auxiliar,sizeof(auxiliar),1,selec);
	}
	printf("\n\n");
}
