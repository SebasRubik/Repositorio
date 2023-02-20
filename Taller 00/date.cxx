#include "date.h"

// Función que genera un número aleatorio entre 0 y 25
int numeroAleatorio(){
    int numero = rand() % 26;
    return numero;
}

// Función que llena un array dinámico de enteros de 10 posiciones con números aleatorios
void llenarArray(int *&array){
    for (int i = 0; i < 10; ++i) {
        *(array+i) = numeroAleatorio();
    }
}

// Función que crea un array dinámico de enteros de 10 posiciones, lo llena con números aleatorios
// y devuelve un puntero al array
int* asignarArray(){
    int *array = new int[10];
    llenarArray(array);
    return array;
}

// Función que imprime los valores de un array dinámico de enteros
void imprimirArray(int *array){
    for (int i = 0; i < 10; ++i) {
        cout << *(array+i) << " ";
    }
    cout << endl;
}

// Función que imprime las direcciones de memoria de los elementos de un array dinámico de enteros
void imprimirDirecciones(int *array){
    for (int i = 0; i < 10; ++i) {
        cout << array+i << " ";
    }
    cout << endl;
}

// Función que pide al usuario que ingrese los datos de un cliente y los guarda en una estructura sCliente
void llenarCliente(sCliente &c){
    string nombre, apellido, dni;
    cout << "Ingrese el nombre: ";
    cin >> nombre;
    // Convierte el string a un array de caracteres y lo guarda en la estructura sCliente
    strcpy(c.nombre, nombre.c_str());
    cout << "Ingrese el apellido: ";
    cin >> apellido;
    strcpy(c.apellido, apellido.c_str());
    cout << "Ingrese el DNI: ";
    cin >> dni;
    strcpy(c.dni, dni.c_str());
    cin.ignore();
    cout << "Ingrese la edad: ";
    cin >> c.edad;
}

// Función que crea un array dinámico de estructuras sCliente de tamaño n, y llena cada una de ellas
// con los datos ingresados por el usuario
sCliente* asignarClientes(int n){
    sCliente *clientes = new sCliente[n];
    for (int i = 0; i < n; i++) {
        cout << "Cliente numero: " << i+1 << endl;
        llenarCliente(*(clientes+i));
    }
    return clientes;
}

// Función que escribe los datos de un array dinámico de estructuras sCliente en un archivo de texto
void escribirArchivo(sCliente *clientes, int n) {
    ofstream archivo("clientes.txt");
    for (sCliente *ptr = clientes; ptr < clientes + n; ++ptr) {
        archivo << ptr->nombre << "-" << ptr->apellido << "-" << ptr->edad << "-" << ptr->dni << endl;
    }
    cout << "Archivo creado con exito" << endl;
    archivo.close();
}
