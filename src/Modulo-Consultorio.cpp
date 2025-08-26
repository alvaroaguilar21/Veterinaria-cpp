#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib-Struct.h"

typedef char cadena[45];

// Archivos usados en el módulo
FILE *usuario;
FILE *mascotas;
FILE *turnos;

// Prototipos
int menuVet();
bool IniciarSesion(FILE *usuario);
void Listar_turno(FILE *turnos);
void evolMasc(FILE *mascotas, FILE *turnos);

int main() {
    bool Ingreso = false;
    int opc;

    do {
        opc = menuVet();
        switch(opc) {
            case 1:
                Ingreso = IniciarSesion(usuario);
                if (Ingreso) {
                    printf("¡Bienvenido!\n");
                } else {
                    printf("Error al iniciar sesion...\n");
                }
                system("pause");
                break;

            case 2:
                if (!Ingreso) {
                    printf("Debe iniciar sesion primero.\n");
                } else {
                    Listar_turno(turnos);
                }
                system("pause");
                break;

            case 3:
                if (!Ingreso) {
                    printf("Debe iniciar sesion primero.\n");
                } else {
                    evolMasc(mascotas, turnos);
                }
                system("pause");
                break;

            case 4:
                printf("Saliendo del consultorio...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }
    } while(opc != 4);

    if (usuario) fclose(usuario);
    if (turnos) fclose(turnos);
    if (mascotas) fclose(mascotas);

    return 0;
}

// ---------------- MENÚ ----------------
int menuVet() {
    int opc = 0;
    system("cls");
    printf("********************************* Consultorio *********************************\n");
    printf("1) Iniciar sesion\n");
    printf("2) Visualizar lista de espera de turnos (informe)\n");
    printf("3) Registrar evolucion de la mascota\n");
    printf("4) Salir\n");
    printf("********************************************************************************\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opc);
    getchar(); // limpiar buffer
    return opc;
}

// ---------------- LOGIN ----------------
bool IniciarSesion(FILE *usuario) {
    usuario = fopen("Usuarios.dat", "rb");
    if (usuario == NULL) {
        printf("\nERROR: No se pudo abrir Usuarios.dat\n");
        return false;
    }

    int Matr;
    char contr[45];
    Usuario1 vet;
    bool encontrado = false;

    printf("\nINICIO DE SESION\n");
    printf("Matricula: ");
    scanf("%d", &Matr); getchar();
    printf("Clave: ");
    fgets(contr, 45, stdin); contr[strcspn(contr, "\n")] = 0;

    while (fread(&vet, sizeof(vet), 1, usuario)) {
        if (vet.matricula == Matr && strcmp(vet.contrasena, contr) == 0) {
            printf("\nBienvenido Dr. %s\n", vet.usuario);
            encontrado = true;
            break;
        }
    }

    fclose(usuario);
    return encontrado;
}

// ---------------- LISTADO DE TURNOS ----------------
void Listar_turno(FILE *turnos) {
    Turnos turn;
    Mascota masc;
    int dia, mes, anio;
    int matric;

    turnos = fopen("Turnos.dat", "rb");
    mascotas = fopen("Mascotas.dat", "rb");

    if (!turnos || !mascotas) {
        printf("\nERROR al abrir archivos de turnos o mascotas.\n");
        return;
    }

    printf("Ingrese fecha (dd mm aaaa): ");
    scanf("%d %d %d", &dia, &mes, &anio);
    printf("Ingrese su Matricula: ");
    scanf("%d", &matric);

    printf("\nTurnos del dia %d/%d/%d\n", dia, mes, anio);
    printf("------------------------------------------------\n");

    while (fread(&turn, sizeof(Turnos), 1, turnos)) {
        if (matric == turn.Matric_Veterinario &&
            dia == turn.Fecha.dia &&
            mes == turn.Fecha.mes &&
            anio == turn.Fecha.anio) {

            rewind(mascotas);
            while (fread(&masc, sizeof(Mascota), 1, mascotas)) {
                if (masc.DNI_Duenio == turn.DNI_Duenio) {
                    printf("\nDueño: %s", masc.ApellidoyNombre);
                    printf("\nDNI: %d", masc.DNI_Duenio);
                    printf("\nDomicilio: %s", masc.Domicilio);
                    printf("\nTelefono: %s", masc.Telefono);
                    printf("\nPeso mascota: %.2f kg\n", masc.Peso);
                    printf("------------------------------------------------\n");
                }
            }
        }
    }

    fclose(turnos);
    fclose(mascotas);
}

// ---------------- EVOLUCIÓN DE MASCOTA ----------------
void evolMasc(FILE *mascotas, FILE *turnos) {
    turnos = fopen("Turnos.dat", "r+b");
    if (!turnos) {
        printf("\nERROR al abrir Turnos.dat\n");
        return;
    }

    int dni;
    bool encontrado = false;
    Turnos turno;

    printf("Ingrese el DNI del dueño de la mascota: ");
    scanf("%d", &dni); getchar();

    while (fread(&turno, sizeof(Turnos), 1, turnos)) {
        if (turno.DNI_Duenio == dni && strlen(turno.Detalle_Atencion) == 0) {
            printf("Evolucion de la mascota: ");
            fgets(turno.Detalle_Atencion, sizeof(turno.Detalle_Atencion), stdin);
            turno.Detalle_Atencion[strcspn(turno.Detalle_Atencion, "\n")] = 0;

            fseek(turnos, -sizeof(Turnos), SEEK_CUR);
            fwrite(&turno, sizeof(Turnos), 1, turnos);
            encontrado = true;
            printf("Evolucion registrada con exito.\n");
            break;
        }
    }

    if (!encontrado) {
    		printf("ERROR. No se encontro un turno pendiente para ese DNI.\n");
    }

    fclose(turnos);
}