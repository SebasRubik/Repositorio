#ifndef CURIOSITY_H
#define CURIOSITY_H
#define M_Pi 3.14159265359;
#include <string>
#include <list>

using namespace std;

struct sComando {
    struct sMovimiento {
        string tipoMovimiento;
        float magnitud;
        string unidadMedida;
        bool operator != (const sMovimiento &movimiento) const {
            return (tipoMovimiento != movimiento.tipoMovimiento) || (magnitud != movimiento.magnitud) || (unidadMedida != movimiento.unidadMedida);
        }
    };
    sMovimiento movimiento = sMovimiento();
    struct sAnalisis {
        string tipoAnalisis;
        string objeto;
        string comentario;
        bool operator != (const sAnalisis &analisis) const {
            return (tipoAnalisis != analisis.tipoAnalisis) || (objeto != analisis.objeto) || (comentario != analisis.comentario);
        }
    };
    sAnalisis analisis = sAnalisis();
    bool operator != (const sComando &comando) const {
        return (movimiento != comando.movimiento) || (analisis != comando.analisis);
    }
};

struct sElemento {
    string tipoElemento;
    float tamaño;
    string unidadMedida;
    float coorDx;
    float coorDy;
};

class Curiosity {
private:
    list<sComando> comandos;
    list<sElemento> elementos;
    float orientacion=0;
    //X es la posicion 0 y Y es la posicion 1
    float coords[2] = {1,1};

public:
    Curiosity();
    Curiosity(list<sComando> comandos, list<sElemento> elementos);
    list<sComando> getComandos();
    list<sElemento> getElementos();
    void cargarComandos(string namefile);
    void agregarComando(sComando comando);
    void cargarElementos(string namefile);
    void agregarElemento(sElemento elemento);
    void actualizarOrientacion(float nuevaorientacion);
    void simularComandos();
    void setComandos(list<sComando> comandos);
    void setElementos(list<sElemento> elementos);
    void setOrientacion(float orientacion);
    void setCoords(float cordX, float cordY);
    void guardar(string namefile, string typefile);

};




#endif //CURIOSITY_H