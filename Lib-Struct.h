#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef char cadena[45];

struct Fecha
{
	int dia;
	int mes;
	int anio;
};

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
	cadena Contrasenea;
};

struct Mascota
{
	char ApellidoyNombre[60];
	char Domicilio[60];
	int DNI_Duenio;
	char Localidad[60];
	Fecha FechadeNac;
	float Peso;
	char Telefono[25];
};

struct Turnos
{
	int Matric_Veterinario;
	Fecha Fecha;
	int DNI_Duenio;
	char Detalle_Atencion[380];
	int atendido;
};
