#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "date.h"

using namespace std;

int main() {

    set<sAutor> autores;
    vector<string> lineas = leerLineaArchivo("songs.txt");
    string linea = lineas[1];
    string* tokens= new string[5];
    tokenizarLinea(linea, tokens);
    cargarDatos(lineas, autores);
    bool bandera=true;
    while(bandera){
    int opcion = 0;
    while (opcion != 6) {
        cout << "1. Mostrar autores" << endl;
        cout << "2. Mostrar canciones de un autor" << endl;
        cout << "3. Mostrar albumes ordenados cronologicamente" << endl;
        cout << "4. Mostrar canciones de un album" << endl;
        cout << "5. Mostrar albumes y canciones" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:{
            mostrarAutores(autores);
        }
            break;
        case 2:{
            cout << "Ingrese el nombre del autor" << endl;
            string nombreAutor;
            cin >> nombreAutor;
            sAutor autor;
            autor.nombre = nombreAutor;
            mostrarCancionesAutor(autor, autores);
        }
            break;
        case 3:
        {
            mostrarAlbumesOrdenadosCronologicamente(autores);
        }
            break;
        case 4:{
            cout << "Ingrese el nombre del album" << endl;
            string nombreAlbum;
            cin >> nombreAlbum;
            sAlbum album;
            album.nombre = nombreAlbum;
            mostrarCancionesAlbum(album, autores);
        }
            break;
        case 5:
        {
            mostrarAlbumesCancion(autores);
        }
            break;
        case 6:
        {
            cout << "Adios" << endl;
            bandera=false;
        }
            break;
        default:{
            cout << "Opcion invalida" << endl;
        }
            break;
            }
        }
    }
    return 0;
}
