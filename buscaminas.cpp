#include "buscaminas.h"
#include <iostream>
#include <vector>
#include <cassert>


using namespace std;


Buscaminas::Buscaminas(int filas, int columnas, int bombas){
  num_filas = filas;
  num_columnas = columnas;
  num_bombas = bombas;

  assert(bombas<filas*columnas);

  for(int i=0; i<filas; i++){
    vector<Casilla> aux;
    for(int j=0; j<columnas; j++){
      Casilla casilla;
      casilla.num_ady=0;
      casilla.mostrar=to_string(casilla.num_ady);
      casilla.bomba=false;
      casilla.descubierta=false;
      casilla.marca=false;
      aux.push_back(casilla);
    }
    tablero.push_back(aux);
  }

  Buscaminas::ColocarBombas();


}



void Buscaminas::ColocarBombas(){
  int n1, n2;

  for(int k=0; k< num_bombas; k++){
    do{
      n1 = rand() % num_filas;
      n2 = rand() % num_columnas;
    }while(tablero[n1][n2].bomba);

    tablero[n1][n2].bomba=true;
    tablero[n1][n2].num_ady=-1;
    tablero[n1][n2].mostrar='X';

    for(int i=n1-1; i<=n1+1;i++){
      if(i>=0 && i<num_filas){
        for(int j=n2-1; j<=n2+1;j++){
          if(j>=0 && j<num_columnas){
            if(!tablero[i][j].bomba){
              tablero[i][j].num_ady++;
              tablero[i][j].mostrar=to_string(tablero[i][j].num_ady);
            }
          }
        }
      }
    }

  }

}


bool Buscaminas::Descubrir(int fila, int columna){
  bool explosion=false;
  tablero[fila][columna].descubierta=true;
  if(tablero[fila][columna].bomba){
    explosion = true;
    cout << "\nEXPLOSION" << endl;
  }
  else{
    if(tablero[fila][columna].num_ady==0)
      AbrirTablero(fila,columna);
  }

  return explosion;
}


void Buscaminas::AbrirTablero(int fila, int columna){

  for(int i=fila-1; i<=fila+1;i++){
    if(i>=0 && i<num_filas){
      for(int j=columna-1; j<=columna+1;j++){
        if(j>=0 && j<num_columnas){
          tablero[i][j].descubierta=true;
          if(tablero[i][j].num_ady==0 && tablero[i][j].descubierta==false)
            AbrirTablero(i,j);

        }
      }
    }
  }

}

void Buscaminas::Jugar(){

  bool seguir=true;
  MostrarTablero();

  do{
    int opcion;

    cout << "Que quieres hacer:\n- Descubrir(1)\n- Marcar(2)\n- Terminar(3)" << endl;
    cin >> opcion;

    if(opcion==1){
      int fila, columna;
      cout << "Que fila quieres" << endl;
      cin >> fila;
      cout << "Que columna quieres" << endl;
      cin >> columna;

      seguir = !Descubrir(fila, columna);

    }
    else if(opcion==2){
      int fila, columna;
      cout << "Que fila quieres" << endl;
      cin >> fila;
      cout << "Que columna quieres" << endl;
      cin >> columna;

      tablero[fila][columna].marca = !tablero[fila][columna].marca;
    }
    else if(opcion==3){
      seguir=false;
    }
    else{
      cout << "Has introducido un caracter incorrecto, vuelve a intentarlo" << endl;
    }

    MostrarTablero();

  }while(seguir);

}



void Buscaminas::MostrarTablero(){
  cout << "  ";
  for(int j=0; j<num_columnas; j++){
    cout << "   " << j;
  }
  cout << endl;
  cout << "    ";
  for(int j=0; j<num_columnas; j++){
    cout << "----";
  }
  cout << endl;
  for(int i=0; i<num_filas; i++){
    cout << i << " ||";
    for(int j=0; j<num_columnas; j++){
      cout << " " << mostrarCasilla(tablero[i][j]) << " |";
    }
    cout << "|" << endl << "    ";
    for(int j=0; j<num_columnas; j++){
      cout << "----";
    }
    cout << endl;

  }
}

string Buscaminas::mostrarCasilla(Casilla casilla){
  string salida;
  if(casilla.descubierta){
    salida = casilla.mostrar;
  }else{
    if(casilla.marca){
      salida = 'B';
    }
    else{
      salida = '#';
    }
  }
  return salida;
}
