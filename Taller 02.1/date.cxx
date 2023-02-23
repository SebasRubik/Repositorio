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

vector<string> leerLineaArchivo(string filename){
    ifstream file;
    file.open(filename);
    vector<string> lineas;
    string linea;
    while (getline(file, linea)) {
        lineas.push_back(linea);
    }
    file.close();
    return lineas;
}

void tokenizarLinea(string linea, string *&tokens){
    const char* delimiter = "|";
    char* token = strtok(linea.data(), delimiter);
    int i = 0;
    while (token != nullptr && i < 5) {
        tokens[i] = string(token);
        token = strtok(NULL, delimiter);
        i++;
    }
}

sAutor buscarAutor(set<sAutor>& autores, string nombre){
    for(auto autor: autores){
        if(autor.nombre == nombre){
            return autor;
        }
    }
    return sAutor();
}

sAlbum buscarAlbum(set<sAlbum>& albums, string nombre){
    for(auto album: albums){
        if(album.nombre == nombre){
            return album;
        }
    }
    return sAlbum();
}


void cargarDatos(vector<string> lineas, set<sAutor>& autores)
{
    for (int i = 0; i < lineas.size(); i++) {
        if (i == 0) {
            continue;
        }
        string linea = lineas[i];
        string* tokens = new string[5];
        tokenizarLinea(linea, tokens);
        
        sAutor nuevoAutor;
        nuevoAutor.nombre = tokens[1];

        sAlbum nuevoAlbum;
        nuevoAlbum.nombre = tokens[3];
        nuevoAlbum.anio = stoi(tokens[4]);

        sCancion nuevaCancion;
        nuevaCancion.nombre = tokens[0];
        nuevaCancion.genero = tokens[2];
        
        sAutor itAutor = buscarAutor(autores, nuevoAutor.nombre);

        if (itAutor != sAutor()) {
            autores.erase(itAutor);
            sAlbum itAlbum = buscarAlbum(itAutor.albums, nuevoAlbum.nombre);
            if (itAlbum != sAlbum()) {
                itAlbum.canciones.insert(nuevaCancion);
            } else {
                nuevoAlbum.canciones.insert(nuevaCancion);
                itAutor.albums.insert(nuevoAlbum);
                
            }
            autores.insert(itAutor);
        } else { 
            nuevoAlbum.canciones.insert(nuevaCancion);
            nuevoAutor.albums.insert(nuevoAlbum);
            autores.insert(nuevoAutor);
        }
        
    }
}


void mostrarAutores(set<sAutor> autores){
    for(auto autor: autores){
        cout << autor.nombre << endl;
    }
}

void mostrarCancionesAutor(sAutor a, set<sAutor> autores){
    for(auto autor: autores){
        if(autor.nombre == a.nombre){
            for(auto album: autor.albums){
                for(auto cancion: album.canciones){
                    cout << cancion.nombre << endl;
                }
            }
        }
    }
}

void mostrarAlbumesOrdenadosCronologicamente(set<sAutor> autores){
    for(auto autor: autores){
        for(auto album: autor.albums){
            cout << album.nombre << album.anio <<endl;
        }
    }
}

void mostrarCancionesAlbum(sAlbum a, set<sAutor> autores){
    for(auto autor: autores){
        for(auto album: autor.albums){
            if(album.nombre == a.nombre){
                for(auto cancion: album.canciones){
                    cout << cancion.nombre << endl;
                }
            }
        }
    }
}

void mostrarAlbumesCancion(set<sAutor> autores){
    for(auto autor: autores){
        for(auto album: autor.albums){
            for(auto cancion: album.canciones){
                cout << album.nombre << ':'<< cancion.nombre << '|';
            }
            cout <<endl;
        }
    }
}