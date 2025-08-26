#ifndef LIB_STRUCT_H
#define LIB_STRUCT_H

typedef char Cadena[45];

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Usuario1 {
    Cadena usuario;
    Cadena contrasena;
    Cadena apeyNom;
    int matricula;
    int atenciones;
    char puesto[20]; // "Veterinario" o "Asistente"
};

struct Mascota {
    Cadena ApellidoyNombre;
    Cadena Domicilio;
    int DNI_Duenio;
    Cadena Localidad;
    Fecha FechadeNac;
    float Peso;
    Cadena Telefono;
};

struct Turnos {
    int Matric_Veterinario;
    int DNI_Duenio;
    Fecha Fecha;
    char Detalle_Atencion[100];
};

#endif
