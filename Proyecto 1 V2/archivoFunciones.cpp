#include "Curiosity.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <algorithm>

using namespace std;

sComando cargarComando(string linea, int &lineaActual){
    sComando comando;
    char* linea2= new char[linea.length()+1];
    strcpy(linea2, linea.c_str());
    int tipo= atoi(strtok(linea2, "|"));
    if(tipo !=0 && tipo !=1){
        cerr<<"Error en el tipo de comando"<<endl;
        return sComando();
    }
    if(tipo == 0){
        sComando::sMovimiento movimiento;
        char* token= strtok(NULL, "|");
        if(strcmp(token,"avanzar")!=0 && strcmp(token,"girar")!=0){
            cerr<<"Error en el tipo de movimiento en la linea: "<<lineaActual <<endl;
            return sComando();
        }
        movimiento.tipoMovimiento= token;
        token= strtok(NULL, "|");
        if(atof(token)==0){
            cerr<<"Error en la magnitud del movimiento en la linea "<<lineaActual <<endl;
        }
        movimiento.magnitud= atof(token);
        token= strtok(NULL, "|");
        if(strcmp(token,"metros")!=0 && strcmp(token,"grados")!=0){
            cerr<<"Error en la unidad de medida del movimiento en la linea "<<lineaActual <<endl;
            return sComando();
        }
        movimiento.unidadMedida = token;
        comando.movimiento = movimiento;
    }
    else if(tipo==1){
        sComando::sAnalisis analisis;
        char* token= strtok(NULL, "|");
        if(strcmp(token,"fotografiar")!=0 && strcmp(token,"perforar")!=0 && strcmp(token,"composicion")!=0){
            cerr<<"Error en el tipo de analisis en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.tipoAnalisis= token;
        token= strtok(NULL, "|");
        if(strcmp(token,"roca")!=0 && strcmp(token,"arena")!=0 && strcmp(token,"monticulo")!=0){
            cerr<<"Error en el objeto a analizar en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.objeto= token;
        token= strtok(NULL, "|");
        if(sizeof(token)==0){
            cerr<<"Error en el comentario del analisis en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.comentario= token;
        comando.analisis= analisis;
    }
    else{
        cerr<<"Error en el tipo de comando"<<endl;
        return sComando();
    }
    return comando;
}

sElemento cargarElemento(string linea, int &lineaActual){
    
    sElemento elemento;
    char* linea2= new char[linea.length()+1];
    strcpy(linea2, linea.c_str());
    char* token= strtok(linea2, "|");
    if(strcmp(token,"roca")!=0 && strcmp(token,"duna")!=0 && strcmp(token,"monticulo")!=0 && strcmp(token,"crater")!=0){
        cerr<<"Error en el tipo de elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.tipoElemento=token;
    token= strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en el tama??o del elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.tamanio=atof(token);
    token= strtok(NULL, "|");
    if(strcmp(token,"metros")!=0){
        cerr<<"Error en la unidad de medida del elemento en la linea: "<< lineaActual <<endl;
        return sElemento();
    }
    elemento.unidadMedida=token; 
    token= strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en la coordenada X del elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.coorDx=atof(token);
    token= strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en la coordenada Y del elemento en la linea: " <<lineaActual <<endl;
        return sElemento();
    }
    elemento.coorDy=atof(token);
    return elemento;
}


void imprimirComandos(list <sComando> comandos){
    for(auto it = comandos.begin(); it!= comandos.end(); it++){
        if(it->movimiento != sComando::sMovimiento()){
        cout<<it->movimiento.tipoMovimiento << ',';
        cout<<it->movimiento.magnitud << ',';
        cout<<it->movimiento.unidadMedida << endl;
        continue;
        }
        else{
        cout << it->analisis.tipoAnalisis <<',';
        cout << it->analisis.objeto << ',';
        cout << it->analisis.comentario <<endl;
        continue;
        }
    }
}


void imprimirElementos(list <sElemento> elementos){
    for(auto it=elementos.begin();it!=elementos.end();it++){
        cout<<"Elemento: "<<it->tipoElemento<<endl;
        cout<<"Tama??o: " <<it->tamanio << " "<<it->unidadMedida<<endl;
        cout<<"Coordenada X: "<<it->coorDx<<endl;
        cout<<"Coordenada Y: "<<it->coorDy<<endl;
    }
}


bool openFile(string &n_a){
    ifstream archivo;
    n_a+=".txt";
    archivo.open(n_a, ios::in);
    archivo.seekg(0, std::ios::end);
    streampos tamano = archivo.tellg();
    if(archivo.fail()){
        cerr<<"Error, '" <<n_a <<"' no se encuentra o no puede leerse" <<endl;
        return false;
    }
    else if(tamano == 0){
        cerr<<"Error, '" <<n_a <<"' esta vacio."<<endl;
        return false;
    }
    else{
        return true;
    }
    
}

void helpmenu(){
    cout<<"Lista de comandos: "<<endl;
        cout<<"cargar_elementos: Carga en memoria los datos de los elementos contenidos en el archivo"
            <<"identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar"
            <<"la informaci??n de los elementos en memoria. Si dentro de la misma sesi??n de trabajo ya se han cargado"
            <<"otros archivos de puntos de inter??s (usando el comando cargar_elementos), la informaci??n debe"
            <<"sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes "
            <<"archivos.\n\n";
        cout<<"agregar_movimiento: Agrega el comando de movimiento descrito a la lista de comandos del robot ???Curios-"
            <<"ity???. El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del"
            <<"movimiento; si es avanzar, el n??mero de unidades que se espera avanzar, si es girar la cantidad de grados"
            <<"que debe girar. La unidad de medida corresponde a la convenci??n con la que se mide la magnitud del"
            <<"movimiento (centimetros, metros, grados, ...). Si no se env??a la informaci??n completa y adecuada"
            <<"del comando de movimiento, ??ste no puede agregarse a la lista de los comandos que se enviar??n al robot "
            <<"desde la tierra.\n\n";
        cout<<"agregar_analisis: Agrega el comando de an??lisis descrito a la lista de comandos del robot ???Curiosity???. El "
            <<"an??lisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del "
            <<"elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar "
            <<"m??s informaci??n sobre el elemento o el an??lisis, este comentario estar?? encerrado entre comillas simples "
            <<"(ejemplo: ???roca_cuadrante_32???). Si no se env??a la informaci??n completa y adecuada del comando de "
            <<"an??lisis, ??ste no puede agregarse a la lista de los comandos que se enviar??n al robot desde la tierra.\n\n";
        cout<<"agregar_elemento: Agrega el componente o elemento descrito a la lista de puntos de inter??s del robot ???Cu-"
            <<"riosity???. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tama??o "
            <<"es un valor real que da cuenta de qu?? tan grande es el elemento; y la unidad de medida complementa "
            <<"este valor con la convenci??n que se us?? para su medici??n (centimetros, metros, ...). Finalmente, las "
            <<"coordenadas x y y corresponden a n??meros reales que permiten conocer la ubicaci??n del elemento en "
            <<"el sistema de coordenadas del suelo marciano utilizado por el veh??culo. Si no se env??a la informaci??n "
            <<"completa y adecuada del elemento, ??ste no puede agregarse a la lista de puntos de inter??s que se enviar??n "
            <<"al robot desde la tierra.\n\n";
        cout<<"guardar: Guarda en el archivo con el nombre proporcionado por el usuario la informaci??n solicitada de acuerdo al tipo de "
            <<"archivo: comandos almacena en el archivo la informaci??n de comandos de movimiento y de an??lisis que "
            <<"debe ejecutar el robot, elementos almacena en el archivo la informaci??n de los componentes o puntos "
            <<"de inter??s conocidos en el suelo marciano.\n\n";
        cout<<"simular_comandos: Permite simular el resultado de los comandos de movimiento que se enviar??n al robot "
            <<"???Curiosity??? desde la Tierra, facilitando asi la validaci??n de la nueva posici??n en la que podr??a ubicarse. "
            <<"Para ejecutarse adecuadamente, requiere conocer la posici??n actual (coordenadas x y y) del veh??culo. "
            <<"Hay que tener en cuenta que s??lo los comandos de movimiento son necesarios, no los de an??lisis.\n\n";
        cout<<"ubicar_elementos: El comando debe utilizar la informaci??n de puntos de inter??s almacenada en memoria "
            <<"para ubicarlos en una estructura de datos jer??rquica adecuada, que permita luego realizar consultas "
            <<"geogr??ficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe "
            <<"generarse un mensaje de error, pero deben terminarse de procesar todos los elementos almacenados en "
            <<"memoria\n\n";
        cout<<"en_cuadrante:Permite utilizar la estructura creada con el comando anterior para retornar una lista de "
            <<"los componentes o elementos que est??n dentro del cuadrante geogr??fico descrito por los l??mites de co-"
            <<"ordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar "
            <<"la b??squeda por cuadrantes. Los l??mites de coordenadas deben garantizar que coordX1 <coordX2 y "
            <<"coordY1 <coordY2 \n\n";
        cout<<"crear_mapa: El comando debe utilizar la informaci??n de puntos de inter??s almacenada en memoria para "
            <<"ubicarlos en una estructura no lineal y conectarlos entre s?? teniendo en cuenta el coeficiente de conec- "
            <<"tividad dado. El objetivo es que cada elemento est?? conectado a los dem??s elementos m??s cercanos a "
            <<"el, midiendo la cercan??a a trav??s de la distancia euclidiana entre los elementos. Esta distancia euclidiana "
            <<"tambi??n se utiliza como el peso o etiqueta de la conexi??n entre los elementos. Con el coeficiente de "
            <<"conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el "
            <<"total de elementos que se ubicar??n en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente "
            <<"de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14).\n\n";
        cout<<"ruta_mas_larga: Con el mapa ya creado, el comando permite identificar los dos componentes m??s alejados "
            <<"entre s?? de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los ele- "
            <<"mentos m??s alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que "
            <<"est??n a mayor distancia euclidiana entre s??. Al encontrar esa ruta m??s larga dentro del mapa, el comando "
            <<"imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de "
            <<"elementos que hay que seguir para ir del elemento origen al elemento destino.\n";
}

char* toLowerCase(char* str) {
    int i = 0;
    while (str[i]) {   // Recorrer la cadena hasta llegar al car??cter nulo '\0'
        str[i] = tolower(str[i]);   // Convertir cada letra a min??scula
        i++;
    }
    return str;
}

void menu(Curiosity &Curiosity){
string archivo;
bool of;
list<char*> entrada;
    char* s = new char[200]; // Asignar memoria para s
    cout <<"$";
    fflush(stdin); // Ignorar el salto de l??nea
    cin.getline(s, 200, '\n');
    char* token = strtok(s, " ");
    while (token != NULL) {         
        entrada.push_back(token);    
        token = strtok(NULL, " ");           
    }
    list<char*>::iterator it = entrada.begin();
    char* comando = *it;
    comando = toLowerCase(comando);
    if(strcmp(comando,"help")==0){
        helpmenu();        
    }
    else if(strcmp(*it,"cargar_comandos") == 0){
        int i = 0;
        for(it = entrada.begin(); it != entrada.end(); it++){
            i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            archivo=entrada.back();
            of=openFile(archivo);
            if(of==true){
            Curiosity.cargarComandos(archivo);
            }
            return;
        }
    }
    else if(strcmp(*it,"cargar_elementos") == 0){
        int i = 0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            archivo=entrada.back();
            of=openFile(archivo);
            if(of==true){
            Curiosity.cargarElementos(archivo);
            }
            return;
        }
    }//agregar_movimiento avanzar 10 metros
    else if(strcmp(*it,"agregar_movimiento")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 4){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 4){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            auto it = entrada.begin();
            it++;
            sComando comando;
            sComando::sMovimiento movimiento;
            if(strcmp(*it,"avanzar")==0 ||strcmp(*it,"girar")==0){
                movimiento.tipoMovimiento = *it;
            }
            else{
                cerr << "Error: el tipo de movimiento no es v??lido\n";
                return;
            }
            it++;
            if(atof(*it)!=0){
                movimiento.magnitud = atof(*it);
            }
            else{
                cerr << "Error: la magnitud no es v??lida\n";
                return;
            }
            it++;
            if(strcmp(*it,"metros")==0 ||strcmp(*it,"grados")==0){
                movimiento.unidadMedida = *it;
            }
            else{
                cerr << "Error: la unidad de medida no es v??lida\n";
                return;
            }
            comando.movimiento = movimiento;
            Curiosity.agregarComando(comando);  
            cout << "Movimiento agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"agregar_analisis")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 4){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 4){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }    
        else {//agregar_analisis fotografiar roca foto_de_roca
            auto it = entrada.begin();
            it++;
            sComando comando;
            sComando::sAnalisis analisis;
            if(strcmp(*it,"fotografiar")==0 ||strcmp(*it,"perforar")==0 || strcmp(*it,"composicion")==0){
                analisis.tipoAnalisis = *it;
            }
            else{
                cerr << "Error: el tipo de an??lisis no es v??lido\n";
                return;
            }
            it++;
            if(strcmp(*it,"roca")==0 ||strcmp(*it,"arena")==0 || strcmp(*it,"monticulo")==0){
                analisis.objeto = *it;
            }
            else{
                cerr << "Error: el tipo de an??lisis no es v??lido\n";
                return;
            }
            it++;
            if(sizeof(*it)>0){
                //problema espacios comentario
                analisis.comentario = *it;
            }
            else{
                cerr << "Error: el comentario no es v??lido\n";
                return;
            }
            comando.analisis = analisis;
            Curiosity.agregarComando(comando);
            cout << "An??lisis agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"agregar_elemento")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 6){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 6){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {

            auto it = entrada.begin();
            it++;
            sElemento elemento;
            if(strcmp(*it,"roca")==0 || strcmp(*it,"duna")==0 || strcmp(*it,"monticulo")==0 || strcmp(*it,"crater")==0){
                elemento.tipoElemento = *it;
            }
            else{
                cerr << "Error: el tipo de elemento no es v??lido\n";
                return;
            }
            it++;
            if(atof(*it)>0){
                elemento.tamanio = atof(*it);
            }
            else{
                cerr << "Error: el tama??o no es v??lido\n";
                return;
            }
            it++;
            if(strcmp(*it,"metros")==0){
                elemento.unidadMedida = *it;
            }
            else{
                cerr << "Error: la unidad de medida no es v??lida\n";
                return;
            }
            it++;
            if(atof(*it) != 0){
                elemento.coorDx = atof(*it);
            }
            else{
                cerr << "Error: la posici??n en X no es v??lida\n";
                return;
            }
            it++;
            if(atof(*it) != 0){
                elemento.coorDy = atof(*it);
            }
            else{
                cerr << "Error: la posici??n en Y no es v??lida\n";
                return;
            }
            Curiosity.agregarElemento(elemento);
            cout << "Elemento agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"guardar")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            string t_a;
            archivo=entrada.back();
            list<char*>::iterator it = entrada.begin();
            advance(it, 1);
            t_a=*it;
            of=openFile(archivo);
            if(of==true){
            Curiosity.guardar(archivo,t_a);
            }
            return;
        }    
    }
    else if(strcmp(*it,"simular_comandos")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else if(Curiosity.getComandos().size()==0){
            cerr << "Error: no hay comandos para simular\n";
            return;
        }
        else {
            auto it = entrada.begin();
            advance(it, 1);
            Curiosity.setCoords(atof(*(it)),atof(*(it++)));
            Curiosity.simularComandos();
            return;
        }    
    }
    else if(strcmp(*it,"ubicar_elementos")==0){
            cout<<"Descripci??n de la funci??n:\nEl comando debe utilizar la informaci??n de puntos de inter??s almacenada en memoria"
            <<"para ubicarlos en una estructura de datos jer??rquica adecuada, que permita luego realizar consultas"
            <<"geogr??ficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe"
            <<"generarse un mensaje de error, pero deben terminarse de procesar todos los elementos almacenados en"
            <<"memoria\n";
            return;  
    }
    else if(strcmp(*it,"en_cuadrante")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 5){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 5){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            cout<<"Permite utilizar la estructura creada con el comando anterior para retornar una lista de"
            <<"los componentes o elementos que est??n dentro del cuadrante geogr??fico descrito por los l??mites de co-"
            <<"ordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar"
            <<"la b??squeda por cuadrantes. Los l??mites de coordenadas deben garantizar que coordX1 <coordX2 y"
            <<"coordY1 <coordY2 \n";
            return;
        }    
    }
    else if(strcmp(*it,"crear_mapa")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            cout<<"Descripci??n de la funci??n:\nEl comando debe utilizar la informaci??n de puntos de inter??s almacenada en memoria para"
            <<"ubicarlos en una estructura no lineal y conectarlos entre s?? teniendo en cuenta el coeficiente de conec-"
            <<"tividad dado. El objetivo es que cada elemento est?? conectado a los dem??s elementos m??s cercanos a"
            <<"el, midiendo la cercan??a a trav??s de la distancia euclidiana entre los elementos. Esta distancia euclidiana"
            <<"tambi??n se utiliza como el peso o etiqueta de la conexi??n entre los elementos. Con el coeficiente de"
            <<"conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el"
            <<"total de elementos que se ubicar??n en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente"
               <<"de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14).\n";
            return;
        }    
    }
    else if(strcmp(*it,"ruta_mas_larga")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            cout<<"Descripci??n de la funci??n:\nCon el mapa ya creado, el comando permite identificar los dos componentes m??s alejados"
            <<"entre s?? de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los ele-"
            <<"mentos m??s alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que"
            <<"est??n a mayor distancia euclidiana entre s??. Al encontrar esa ruta m??s larga dentro del mapa, el comando"
            <<"imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de"
            <<"elementos que hay que seguir para ir del elemento origen al elemento destino.\n";
            
            return;
        }    
    }
    else if(strcmp(*it,"salir") ==0 || strcmp(*it,"exit")==0){
        exit(0);
    }
    else{
        cerr<<"Error: comando no reconocido\n";
        return;
    }
}