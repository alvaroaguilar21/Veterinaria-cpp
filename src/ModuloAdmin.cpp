#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Lib-Struct.h"

// Prototipos
void registrar(int opc);
void atenciones();
void ranking();
void listar();

int main() {
    int opc;

    do {
        system("cls");
        printf("****************************** Administracion ******************************\n");
        printf("1) Registrar Veterinario\n");
        printf("2) Registrar Usuario (Asistente)\n");
        printf("3) Consultar atenciones por veterinario\n");
        printf("4) Ranking de veterinarios\n");
        printf("5) Salir\n");
        printf("****************************************************************************\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opc);
        getchar(); // limpiar buffer

        switch(opc) {
            case 1:
                registrar(1); // veterinario
                system("pause");
                break;
            case 2:
                registrar(2); // asistente
                system("pause");
                break;
            case 3:
                atenciones();
                system("pause");
                break;
            case 4:
                ranking();
                system("pause");
                break;
            case 5:
                printf("\nSaliendo del sistema de administracion...\n");
                break;
            default:
                printf("\nOpcion invalida.\n");
                system("pause");
        }
    } while(opc != 5);

    return 0;
}

// ---------------- REGISTRAR USUARIOS ----------------
void registrar(int opc) {
    FILE *archivo = fopen("Usuarios.dat", "ab+");
    if (!archivo) {
        printf("ERROR al abrir Usuarios.dat\n");
        return;
    }

    Usuario1 nuevo, aux;
    int valido = 0;

    printf("\n******************************\n");
    if (opc == 1) printf(" Registrar Veterinario\n");
    else printf(" Registrar Asistente\n");
    printf("******************************\n");

    // Leer nombre completo
    printf("\nNombre y apellido: ");
    fgets(nuevo.apeyNom, sizeof(nuevo.apeyNom), stdin);
    nuevo.apeyNom[strcspn(nuevo.apeyNom, "\n")] = 0;

    // Leer usuario con validaciones
    do {
        valido = 1;
        printf("Nombre de usuario: ");
        fgets(nuevo.usuario, sizeof(nuevo.usuario), stdin);
        nuevo.usuario[strcspn(nuevo.usuario, "\n")] = 0;

        // Verificar longitud
        int len = strlen(nuevo.usuario);
        if (len < 6 || len > 10) {
            printf("Debe tener entre 6 y 10 caracteres.\n");
            valido = 0;
            continue;
        }

        // Verificar mayúsculas
        int mayus = 0, digitos = 0;
        for (int i = 0; i < len; i++) {
            if (isupper(nuevo.usuario[i])) mayus++;
            if (isdigit(nuevo.usuario[i])) digitos++;
        }
        if (mayus < 2) {
            printf("Debe tener al menos 2 mayusculas.\n");
            valido = 0;
        }
        if (digitos > 3) {
            printf("No puede tener mas de 3 digitos.\n");
            valido = 0;
        }

        // Verificar duplicados
        rewind(archivo);
        while (fread(&aux, sizeof(aux), 1, archivo)) {
            if (strcmp(nuevo.usuario, aux.usuario) == 0) {
                printf("Ese usuario ya existe.\n");
                valido = 0;
                break;
            }
        }
    } while (!valido);

    // Leer contraseña con validaciones básicas
    do {
        valido = 1;
        printf("Contraseña: ");
        fgets(nuevo.contrasena, sizeof(nuevo.contrasena), stdin);
        nuevo.contrasena[strcspn(nuevo.contrasena, "\n")] = 0;

        int len = strlen(nuevo.contrasena);
        if (len < 6 || len > 32) {
            printf("Debe tener entre 6 y 32 caracteres.\n");
            valido = 0;
        }
    } while (!valido);

    // Inicializar datos adicionales
    nuevo.atenciones = 0;
    if (opc == 1) strcpy(nuevo.puesto, "Veterinario");
    else strcpy(nuevo.puesto, "Asistente");

    printf("Numero de matricula: ");
    scanf("%d", &nuevo.matricula);
    getchar();

    // Guardar en archivo
    fwrite(&nuevo, sizeof(nuevo), 1, archivo);
    fclose(archivo);

    printf("\nUsuario registrado con exito.\n");
}

// ---------------- CONSULTAR ATENCIONES ----------------
void atenciones() {
    FILE *archivo = fopen("Usuarios.dat", "rb");
    if (!archivo) {
        printf("ERROR al abrir Usuarios.dat\n");
        return;
    }

    char buscar[50];
    Usuario1 aux;
    int encontrado = 0;

    listar(); // mostrar todos los veterinarios

    printf("\nIngrese el usuario a consultar: ");
    fgets(buscar, sizeof(buscar), stdin);
    buscar[strcspn(buscar, "\n")] = 0;

    while (fread(&aux, sizeof(aux), 1, archivo)) {
        if (strcmp(buscar, aux.usuario) == 0 && strcmp(aux.puesto, "Veterinario") == 0) {
            printf("\nVeterinario: %s", aux.apeyNom);
            printf("\nUsuario: %s", aux.usuario);
            printf("\nAtenciones: %d\n", aux.atenciones);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNo se encontro un veterinario con ese usuario.\n");
    }

    fclose(archivo);
}

// ---------------- RANKING ----------------
void ranking() {
    FILE *archivo = fopen("Usuarios.dat", "rb");
    if (!archivo) {
        printf("ERROR al abrir Usuarios.dat\n");
        return;
    }

    Usuario1 lista[100];
    int n = 0;

    while (fread(&lista[n], sizeof(Usuario1), 1, archivo)) {
        if (strcmp(lista[n].puesto, "Veterinario") == 0) {
            n++;
        }
    }
    fclose(archivo);

    // Ordenar por burbuja (de mayor a menor atenciones)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (lista[j].atenciones < lista[j+1].atenciones) {
                Usuario1 temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    printf("\n********* Ranking de Veterinarios *********\n");
    for (int i = 0; i < n; i++) {
        printf("#%d: %s (%s) - %d atenciones\n",
               i+1, lista[i].apeyNom, lista[i].usuario, lista[i].atenciones);
    }
}

// ---------------- LISTAR VETERINARIOS ----------------
void listar() {
    FILE *archivo = fopen("Usuarios.dat", "rb");
    if (!archivo) {
        printf("ERROR al abrir Usuarios.dat\n");
        return;
    }

    Usuario1 aux;
    int i = 1;
    printf("\n--- Lista de Veterinarios ---\n");

    while (fread(&aux, sizeof(aux), 1, archivo)) {
        if (strcmp(aux.puesto, "Veterinario") == 0) {
            printf("%d) %s - Usuario: %s\n", i, aux.apeyNom, aux.usuario);
            i++;
        }
    }
    fclose(archivo);
}
