#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <typeinfo>

using namespace std;

#ifndef DATE_H
#define DATE_H

struct sCancion{
    string nombre;
    string genero;
    bool operator <(const sCancion& other)const{
        return nombre < other.nombre;
    }
};

struct sAlbum{
    string nombre;
    int anio;
    set<sCancion> canciones;
    bool operator <(const sAlbum& other)const{
        return nombre < other.nombre;
    }
    bool operator!=(const sAlbum& other)const{
        return nombre != other.nombre;
    }
};

struct sAutor{
    string nombre;
    set <sAlbum> albums; 
    bool operator <(const sAutor& other)const{
        return nombre < other.nombre;
    }
    bool operator!=(const sAutor& other)const{
        return nombre != other.nombre;
    }
};

vector<string> leerLineaArchivo(string filename);
void tokenizarLinea(string linea, string *&tokens);
sAutor buscarAutor(set<sAutor>& autores, string nombre);
sAlbum buscarAlbum(set<sAlbum>& albums, string nombre);
void cargarDatos(vector<string> lineas, set<sAutor>& autores);
void mostrarAutores(set<sAutor> autores);
void mostrarCancionesAutor(sAutor autor, set<sAutor> autores);
void mostrarAlbumesOrdenadosCronologicamente(set<sAutor> autores);
void mostrarCancionesAlbum(sAlbum album, set<sAutor> autores);
void mostrarAlbumesCancion(set<sAutor> autores);


#endif