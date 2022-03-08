#include <iostream>
#include "buscaminas.h"

int main(int argc, char ** argv){

  int filas, columnas, bombas;

  if(argc!=1 && argc!=4){
    cout << "Error, el fichero tiene que tener <filas> <columnas> <bombas> o nada " << endl;
    exit(-1);
  }
  else{
    if(argc==4){
      filas = atoi(argv[1]);
      columnas = atoi(argv[2]);
      bombas = atoi(argv[3]);
    }
    else{
      do{
        cout << "Numero de filas: ";
        cin >> filas;
        cout << "Numero de columnas: ";
        cin >> columnas;
        cout << "Numero de bombas: ";
        cin >> bombas;

      } while(bombas>(filas*columnas-9));
    }
  }


  Buscaminas buscaminas(filas,columnas,bombas);
  buscaminas.Jugar();

}
