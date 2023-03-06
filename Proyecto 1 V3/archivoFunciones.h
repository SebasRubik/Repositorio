#ifndef ARCHIVOFUNCIONES_H
#define ARCHIVOFUNCIONES_H
#include "Curiosity.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <ctype.h>


using namespace std;

sComando cargarComando(string linea, int &lineaActual);
sElemento cargarElemento(string linea, int &lineaActual);
void imprimirComandos(list <sComando> comandos);
void imprimirElementos(list <sElemento> elementos);
void menu(Curiosity &Curiosity);    
void helpmenu();
#endif