#include "Curiosity.h"
#include "archivoFunciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <string.h>
#include <math.h>
/*CREAR LA IMPLEMENTACION DE LAS FUNCIONES DE CURIOSITY*/

Curiosity::Curiosity() {
    this->orientacion = 0;
}

Curiosity::Curiosity(list<sComando> comandos, list<sElemento> elementos) {
    this->comandos = comandos;
    this->elementos = elementos;
    this->orientacion = 0;
}

list<sComando> Curiosity::getComandos() {
    return this->comandos;
}

list<sElemento> Curiosity::getElementos() {
    return this->elementos;
}

void Curiosity::agregarComando(sComando comando) {
    this->comandos.push_back(comando);
}

void Curiosity::agregarElemento(sElemento elemento){
    this->elementos.push_back(elemento);

}

void Curiosity::cargarComandos(string namefile) {
    ifstream archivo;
    archivo.open(namefile);
    string linea;
    while (getline(archivo, linea)) { 
        this->agregarComando(cargarComando(linea));
    }
    cout << "Comandos cargados: " << endl;
    imprimirComandos(this->comandos);
    archivo.close();
}

void Curiosity::cargarElementos(string namefile){
    ifstream archivo;
    archivo.open(namefile);
    string linea;
    while (getline(archivo, linea)) {
        sElemento elemento = cargarElemento(linea);
        this->agregarElemento(elemento);
    }
    cout << "Elementos cargados: " << endl;
    imprimirElementos(this->elementos);
    archivo.close();
}

void Curiosity::guardar(string namefile, string typefile){
    ofstream archivo;
    int opt;
    cout << "Desea sobreescribir o reescribir el archivo? 1. Reescribir 2. Sobreescribir" << endl;
    cin >> opt;
    if(opt=1){
        archivo.open(namefile, ios::out);
        if(typefile == "comandos"){
            for(auto it = comandos.begin();it!=comandos.end();it++){
            archivo <<endl<< it->movimiento.tipoMovimiento << "|" << it->movimiento.magnitud << "|" << it->movimiento.unidadMedida << "|" << it->analisis.tipoAnalisis << "|" << it->analisis.objeto << "|" << it->analisis.comentario;
        }
        }
        else if(typefile=="elementos"){
            for(auto it = elementos.begin();it!=elementos.end();it++){
            archivo << endl <<it->tipoElemento << "|" << it->tamaño << "|" << it->unidadMedida << "|" << it->coorDx << "|" << it->coorDy;
        }
        }
        archivo.close();
    }
    else if(opt=2){
        archivo.open(namefile, ios::app);
        if(typefile == "comandos"){
            for(auto it = comandos.begin();it!=comandos.end();it++){
            archivo <<endl<< it->movimiento.tipoMovimiento << "|" << it->movimiento.magnitud << "|" << it->movimiento.unidadMedida << "|" << it->analisis.tipoAnalisis << "|" << it->analisis.objeto << "|" << it->analisis.comentario;
            }
        }
        else if(typefile=="elementos"){
            for(auto it = elementos.begin();it!=elementos.end();it++){
            archivo << endl <<it->tipoElemento << "|" << it->tamaño << "|" << it->unidadMedida << "|" << it->coorDx << "|" << it->coorDy;
        }
    }
    archivo.close();
    }
    else{
        cerr<<"Error: Opcion no valida";
        return;
    }
}



void Curiosity::setCoords(float cordX, float cordY) {
    this->coords[0] = cordX;
    this->coords[1] = cordY;
}

void Curiosity::simularComandos(){
    for(auto it = this->comandos.begin();it!=this->comandos.end();it++){
        if(it->movimiento != sComando::sMovimiento()){
            if(it->movimiento.tipoMovimiento == "avanzar"){
                if(it->movimiento.unidadMedida == "metros"){
                    //orientacion en radianes
                    this->coords[0] += it->movimiento.magnitud * cos(this->orientacion);
                    this->coords[1] += it->movimiento.magnitud * sin(this->orientacion);
                cout << "Coordenadas actuales: " << this->coords[0] << " " << this->coords[1] << endl;
                }
            }
            else if(it->movimiento.tipoMovimiento == "girar"){
                if(it->movimiento.unidadMedida == "grados"){
                    this->orientacion += it->movimiento.magnitud * M_PI / 180;
                    cout << "Orientacion actual: " << this->orientacion << endl;
                }
            }
        }
        if(it->analisis != sComando::sAnalisis()){
            if(it->analisis.tipoAnalisis == "tomar foto"){
                if(it->analisis.objeto == "roca"){
                    for(auto it2 = this->elementos.begin();it2!=this->elementos.end();it2++){
                        if(it2->coorDx == this->coords[0] && it2->coorDy == this->coords[1]){
                            cout << "Elemento encontrado: " << it2->tipoElemento << " " << it2->tamaño << " " << it2->unidadMedida << endl;
                        }
                    }
                }
            }
            if(it->analisis.tipoAnalisis == "perforar"){
                if(it->analisis.objeto == "roca"){
                    for(auto it2 = this->elementos.begin();it2!=this->elementos.end();it2++){
                        if(it2->coorDx == this->coords[0] && it2->coorDy == this->coords[1]){
                            cout << "Elemento encontrado: " << it2->tipoElemento << " " << it2->tamaño << " " << it2->unidadMedida << endl;
                        }
                    }
                }
            }
        }
    }
}