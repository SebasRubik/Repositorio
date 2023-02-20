#include <iostream>
#include <cstdlib> // para la función rand()
#include <ctime>   // para la función time()
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
#ifndef date_h
#define date_h

// Declaración de la estructura sCliente que contendrá los datos de un cliente
struct sCliente{
    char* nombre= new char[20];
    char* apellido= new char[20];
    int edad;
    char dni [10];
};

int numeroAleatorio();// Función para generar un número aleatorio
void llenarArray(int *&array);// Función para llenar un array de tamaño aleatorio con números aleatorios
int* asignarArray();// Función para asignar memoria dinámicamente a un array
void imprimirArray(int *array);// Función para imprimir los elementos de un array
void imprimirDirecciones(int *array);// Función para imprimir las direcciones de memoria de los elementos de un array
void llenarCliente(sCliente &c);// Función para llenar los datos de un cliente
sCliente* asignarClientes(int n);// Función para asignar a un array de clientes
void escribirArchivo(sCliente *clientes, int n);// Función para escribir los datos de un array de clientes en un archivo de texto

#endif //DATE_H


