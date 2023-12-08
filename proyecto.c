// ERIKA AMASTAL XOCHIMITL Y MIGUEL ANGEL CRUZ REYES
// PROGRAMACION I
// 30/11/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 20
#define N 5

typedef struct
{
    int salarioPorSemana;
    int horasTrabajadas;
} Semana;

typedef struct
{
    char nombre[T];
    char fecha_nacimiento[T];
    int edad;
    Semana semanas[5];
} Empleado;

typedef struct nodo
{
    Empleado trabajador;
    struct nodo *siguiente;
} NODO;

NODO *crearlista()
{
    NODO *raiz = NULL;
    return raiz;
}

NODO *crearNODO(Empleado trabajador)
{
    NODO *nuevo;
    nuevo = (NODO *)malloc(sizeof(NODO));

    if (nuevo != NULL)
    {
        nuevo->trabajador = trabajador;
        nuevo->siguiente = NULL;
    }

    return nuevo;
}

void insertarNodo(NODO **raiz, Empleado trabajador)
{
    NODO *nuevo = crearNODO(trabajador);

    if (nuevo != NULL)
    {
        if (*raiz == NULL || strcmp((*raiz)->trabajador.nombre, trabajador.nombre) > 0)
        {
            nuevo->siguiente = *raiz;
            *raiz = nuevo;
        }
        else
        {
            NODO *actual = *raiz;
            NODO *anterior = NULL;

            while (actual != NULL && strcmp(actual->trabajador.nombre, trabajador.nombre) <= 0)
            {
                anterior = actual;
                actual = actual->siguiente;
            }

            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
        }
    }
}

NODO *buscarEmpleado(NODO *raiz, char nombre[])
{

    if (raiz == NULL)
    {
        printf("\n- Lista vacia.\n");
        return NULL;
    }

    NODO *aux = raiz;
    while (aux != NULL)
    {
        // ? Cuando es igual a 0 las dos cadenas son iguales.
        if (strcmp(aux->trabajador.nombre, nombre) == 0)
            return aux;

        aux = aux->siguiente;
    }

    return NULL;
}

void eliminarNodo(NODO **raiz, char nombre[])
{
    NODO *actual = *raiz;
    NODO *anterior = NULL;

    while ((actual != NULL) && strcmp(actual->trabajador.nombre, nombre))
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {

        if (*raiz == NULL)
            printf("\n- La lista se ecuentra vacia.\n");
        else
            printf("\n- El elemento no fue encontrado.\n");
    }
    else
    {

        if (*raiz == actual)
            *raiz = actual->siguiente;
        else
            anterior->siguiente = actual->siguiente;

        free(actual);
        printf("\n- Empleado eliminado con exito.\n");
    }
}

void imprimirDatosEmpleado(NODO *raiz)
{
    if (raiz == NULL)
    {
        printf("\n- La lista se encuentra vacia.\n");
        return;
    }

    NODO *temp = raiz;

    printf("\n======================= Informe de Empleados =======================\n");

    while (temp != NULL)
    {
        printf("\nNombre del empleado: %s", temp->trabajador.nombre);
        printf("Fecha de nacimiento: %s", temp->trabajador.fecha_nacimiento);
        printf("Edad del empleado: %d\n\n", temp->trabajador.edad);
        printf("Horas trabajadas por semana:\n");

        for (int i = 0; i < N; ++i)
        {
            printf("\t- Semana %d: %d horas, Salario: $%d\n", i + 1,
                   temp->trabajador.semanas[i].horasTrabajadas,
                   temp->trabajador.semanas[i].salarioPorSemana);
        }

        printf("\n--------------------------------------------------------------------\n");

        temp = temp->siguiente;
    }

    printf("\n=====================================================================\n");
}

int validacionHorasSalario()
{
    char respuesta;
    printf("\n>> Ingresar horas y salario ahora o iniciar en cero [S/N]? ");

    scanf(" %c", &respuesta);

    return (respuesta == 'S' || respuesta == 's') ? 1 : 0;
}

int validarOpcion()
{
    char respuesta;
    printf("\n>> Desea continuar [S/N]? ");
    scanf(" %c", &respuesta);

    return (respuesta == 'S' || respuesta == 's') ? 1 : 0;
}

void inicializarSemanas(Empleado *trabajador)
{

    for (int i = 0; i < N; i++)
    {
        trabajador->semanas[i].horasTrabajadas = 0;
        trabajador->semanas[i].salarioPorSemana = 0;
    }
}

void calcularSalario(Empleado *trabajador)
{

    for (int i = 0; i < N; ++i)
    {
        int salario = trabajador->semanas[i].horasTrabajadas * 150;

        if (trabajador->semanas[i].horasTrabajadas >= 30)
            salario += 1000;

        trabajador->semanas[i].salarioPorSemana = salario;
    }
}

int main()
{
    NODO *raiz = crearlista();
    Empleado trabajador;
    FILE *archivoDatos;

    archivoDatos = fopen("Datos.txt", "r");

    if (archivoDatos == NULL)
        archivoDatos = fopen("Datos.txt", "wt");

    fclose(archivoDatos);

    int salir = 1;
    while (salir != 0)
    {
        printf("\n================= MENU =================\n\n");
        printf("1. Alta empleado\n");
        printf("2. Agregar horas trabajadas en semana 'x'\n");
        printf("3. Eliminar empleado\n");
        printf("4. Eliminar horas semana 'x' de un empleado\n");
        printf("5. Salario semanal empleado\n");
        printf("6. Semana mayor salario para empleado 'y'\n");
        printf("7. Mostrar todo\n");
        printf("8. Salvar informacion\n");
        printf("9. Salir\n");

        int opcion = 0;
        printf("\n>> Ingrese la opcion que desea realizar: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            if (validarOpcion() != 1)
                break;

            char tipoLectura;
            printf("\n>> La lectura sera por teclado o por archivo [T/A]? ");
            scanf(" %c", &tipoLectura);
            if (tipoLectura == 't' || tipoLectura == 'T')
            {
                printf("\n>> Ingrese los datos del empleado: \n");
                printf("       - Nombre completo: ");
                getchar();
                fgets(trabajador.nombre, sizeof(trabajador.nombre), stdin);
                printf("       - Fecha de nacimiento: ");
                fgets(trabajador.fecha_nacimiento, sizeof(trabajador.fecha_nacimiento), stdin);
                printf("       - Edad: ");
                scanf("%d", &trabajador.edad);

                if (validacionHorasSalario() == 1)
                {
                    for (int i = 0; i < N; ++i)
                    {
                        printf("       - Horas trabajadas en la semana %d: ", i + 1);
                        scanf("%d", &trabajador.semanas[i].horasTrabajadas);
                    }
                }
                else
                    inicializarSemanas(&trabajador);

                calcularSalario(&trabajador);
                insertarNodo(&raiz, trabajador);
            }
            else
            {
                archivoDatos = fopen("Datos.txt", "r+");

                if (archivoDatos == NULL)
                {
                    perror("Error en la apertura del archivo. \n");
                    fclose(archivoDatos);
                    return 1;
                }

                fseek(archivoDatos, 0, SEEK_END);
                long tamaño = ftell(archivoDatos);

                if (tamaño == 0)
                {
                    printf("El archivo está vacío.\n");
                    fclose(archivoDatos);
                    break;
                }

                fseek(archivoDatos, 0, SEEK_SET);

                while (!feof(archivoDatos))
                {
                    fscanf(archivoDatos, "Nombre: %[^\n]\n", trabajador.nombre);
                    fscanf(archivoDatos, "Fecha de nacimiento: %s\n", trabajador.fecha_nacimiento);
                    fscanf(archivoDatos, "Edad: %d\n", &trabajador.edad);

                    strcat(trabajador.nombre, "\n");
                    strcat(trabajador.fecha_nacimiento, "\n");

                    fscanf(archivoDatos, "%*[^\n]\n");

                    for (int i = 0; i < N; i++)
                        fscanf(archivoDatos, "Semana %*d: %d%*[^\n]\n\n", &trabajador.semanas[i].horasTrabajadas);

                    fscanf(archivoDatos, "\n");
                    fscanf(archivoDatos, "\n");

                    calcularSalario(&trabajador);
                    insertarNodo(&raiz, trabajador);
                }

                fclose(archivoDatos);
            }
            break;
        case 2:
            if (validarOpcion() != 1)
                break;

            char nombreEmpleado[T];
            int horasTrabajadas;
            printf("\n>> Ingrese el nombre del empleado: ");
            getchar();
            fgets(nombreEmpleado, sizeof(nombreEmpleado), stdin);
            printf("\n>> Ingrese las horas trabajadas del empleado: ");
            scanf("%d", &horasTrabajadas);

            NODO *empleadoEncontrado = buscarEmpleado(raiz, nombreEmpleado);
            if (empleadoEncontrado != NULL)
            {
                int semanaEscogida = 0;
                printf("\n>> Ingrese la semana en la cual quiere agregar las horas: ");
                scanf("%d", &semanaEscogida);

                if (semanaEscogida > 5 || semanaEscogida <= 0)
                {
                    printf("- Semana no valida.\n");
                    break;
                }

                empleadoEncontrado->trabajador.semanas[semanaEscogida - 1].horasTrabajadas += horasTrabajadas;

                calcularSalario(&empleadoEncontrado->trabajador);

                printf("\n- Horas agregadas correctamente.\n");
            }
            else
            {
                printf("\n- Empleado no encontrado.\n");
            }
            break;
            
        case 3:
            if (validarOpcion() != 1)
                break;

            char empleadoAEliminar[T];

            printf("\n>> Ingrese el nombre del empleado a eliminar: ");
            getchar();
            fgets(empleadoAEliminar, sizeof(empleadoAEliminar), stdin);

            eliminarNodo(&raiz, empleadoAEliminar);

            break;
        case 4:
            if (validarOpcion() != 1)
                break;

            char nombreAbuscar[T];
            int semEmp = 0;
            printf("\n>> Ingrese el nombre del empleado: ");
            getchar();
            fgets(nombreAbuscar, sizeof(nombreAbuscar), stdin);

            printf("\n>> Ingrese el numero de semana: ");
            scanf("%d", &semEmp);

            if (semEmp > 5 || semEmp <= 0)
            {
                printf("\n- Semana no valida.\n");
                break;
            }

            NODO *empEncon = buscarEmpleado(raiz, nombreAbuscar);

            if (empEncon != NULL)
            {
                empEncon->trabajador.semanas[semEmp - 1].horasTrabajadas = 0;
                empEncon->trabajador.semanas[semEmp - 1].salarioPorSemana = 0;

                printf("\n- Horas eliminadas exitosamente.\n");
            }

            break;
        case 5:
            if (validarOpcion() != 1)
                break;

            char nombreEmp[T];
            int semanaEmp = 0;
            printf("\n>> Ingrese el nombre del empleado: ");
            getchar();
            fgets(nombreEmp, sizeof(nombreEmp), stdin);

            printf("\n>> Ingrese el numero de semana: ");
            scanf("%d", &semanaEmp);

            if (semanaEmp > 5 || semanaEmp <= 0)
            {
                printf("\n- Semana no valida.\n");
                break;
            }

            NODO *empEncontrado = buscarEmpleado(raiz, nombreEmp);

            if (empEncontrado != NULL)
            {
                printf("\n========== Detalles del Salario ==========\n\n");
                printf("Semana: %d\n", semanaEmp);
                printf("Horas trabajadas: %d\n", empEncontrado->trabajador.semanas[semanaEmp - 1].horasTrabajadas);
                printf("Salario: $%d\n", empEncontrado->trabajador.semanas[semanaEmp - 1].salarioPorSemana);
            }

            break;
        case 6:
            if (validarOpcion() != 1)
                break;

            char nombre[T];
            printf("\n>> Ingrese el nombre del empleado: ");
            getchar();
            fgets(nombre, sizeof(nombre), stdin);

            NODO *empleadoMayorSalario = buscarEmpleado(raiz, nombre);

            if (empleadoMayorSalario != NULL)
            {
                int semanaMayorSalario = 1;
                int salarioMaximo = 0;

                for (int i = 0; i < N; i++)
                {
                    if (empleadoMayorSalario->trabajador.semanas[i].salarioPorSemana >= salarioMaximo)
                    {
                        salarioMaximo = empleadoMayorSalario->trabajador.semanas[i].salarioPorSemana;
                        semanaMayorSalario = i + 1;
                    }
                }
                printf("\n======== Informacion sobre Salarios ========\n\n");
                printf("Empleado: %s", nombre);
                printf("Semana con el mayor salario: %d\n", semanaMayorSalario);
                printf("Salario maximo: $%d\n", salarioMaximo);
            }
            else
                printf("\n- Empleado no encontrado.\n");

            break;
        case 7:
            if (validarOpcion() != 1)
                break;
            imprimirDatosEmpleado(raiz);
            break;
        case 8:
            if (validarOpcion() != 1)
                break;

            archivoDatos = fopen("Datos.txt", "w");

            if (archivoDatos == NULL)
            {
                perror("Error en la apertura del archivo. \n");
                return 1;
            }

            NODO *temp = raiz;

            while (temp != NULL)
            {
                fprintf(archivoDatos, "Nombre: %s", temp->trabajador.nombre);
                fprintf(archivoDatos, "Fecha de nacimiento: %s", temp->trabajador.fecha_nacimiento);
                fprintf(archivoDatos, "Edad: %d\n", temp->trabajador.edad);

                fprintf(archivoDatos, "Horas trabajadas por semana:\n");

                for (int i = 0; i < N; i++)
                {
                    fprintf(archivoDatos, "    Semana %d: %d horas, Salario: $%d\n", i + 1, temp->trabajador.semanas[i].horasTrabajadas, temp->trabajador.semanas[i].salarioPorSemana);
                }

                fprintf(archivoDatos, "\n");
                fprintf(archivoDatos, "\n");

                temp = temp->siguiente;
            }

            fclose(archivoDatos);
            printf("\n- Información guardada en el archivo correctamente.\n");

            break;
        case 9:
            if (validarOpcion() != 1)
                break;
            salir = 0;
            break;
        default:
            if (opcion < 1 || opcion > 9)
                printf("\n*** La opcion ingresada no es valida. \n");

            break;
        }
    }
}