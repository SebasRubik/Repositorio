#include "date.h"

int main() {
    // Se inicializa la semilla para generar números aleatorios
    srand(time(NULL));

    int opcion;
    // Se muestra un menú para que el usuario elija una opción
    cout << "1. Ejercicio 1" << endl;
    cout << "2. Ejercicio 2" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;
    switch (opcion) {
        case 1:{
            // Se asigna un array de 10 enteros y se llena con números aleatorios
            int *array = asignarArray();
            // Se imprime el contenido del array
            imprimirArray(array);
            // Se imprimen las direcciones de memoria de cada elemento del array
            imprimirDirecciones(array);
        }
            break;
        case 2:{
            int n;
            // Se solicita al usuario la cantidad de clientes que desea ingresar
            cout << "Ingrese la cantidad de clientes: ";
            cin >> n;
            // Se asigna un array de estructuras sCliente y se llenan los datos de cada cliente
            sCliente *clientes = asignarClientes(n);
            // Se escribe la información de los clientes en un archivo de texto
            escribirArchivo(clientes, n);
        }
            break;
    }
    return 0;
}
