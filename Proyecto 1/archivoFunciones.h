#ifndef ARCHIVOFUNCIONES_H
#define ARCHIVOFUNCIONES_H
#include "Curiosity.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
using namespace std;

sComando cargarComando(string linea);
sElemento cargarElemento(string linea);
void imprimirComandos(list <sComando> comandos);
void imprimirElementos(list <sElemento> elementos);
void menu(Curiosity &Curiosity);    
void helpmenu();
#endif