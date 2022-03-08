#include "buscaminas.h"
#include <iostream>
#include <vector>
#include <cassert>


#define GRIS(p) "\x1B[90m" p "\x1B[0m"
#define VERDE(p) "\x1B[32m" p "\x1B[0m"
#define NARANJA(p) "\x1B[93m" p "\x1B[0m"
#define ROJO(p) "\x1B[31m" p "\x1B[0m"
#define AZUL(p) "\x1B[34m" p "\x1B[0m"
#define NEGRO(p) "\x1B[30m" p "\x1B[0m"
#define ROJO2(p) "\x1B[91m" p "\x1B[0m"

using namespace std;


Buscaminas::Buscaminas(int filas, int columnas, int bombas){
  num_filas = filas;
  num_columnas = columnas;
  num_bombas = bombas;
  num_casillas_descubiertas = 0;
  bombas_colocadas=false;

  srand (time(NULL));

  assert(bombas<=(filas*columnas-9));

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

  //Buscaminas::ColocarBombas();


}



void Buscaminas::ColocarBombas(int fila, int columna){
  int n1, n2;

  for(int k=0; k< num_bombas; k++){

    do{
      n1 = rand() % num_filas;
      n2 = rand() % num_columnas;

    }while(tablero[n1][n2].bomba || ((n1 >=fila-1 && n1<=fila+1) && (n2>=columna-1 && n2<=columna+1)) );

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
  num_casillas_descubiertas++;
  if(!bombas_colocadas){
    ColocarBombas(fila, columna);
    bombas_colocadas=true;
  }
  if(tablero[fila][columna].bomba){
    explosion = true;
    cout << "\nEXPLOSION" << endl;
    Derrota();
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
          if(tablero[i][j].descubierta==false){
            tablero[i][j].descubierta=true;
            num_casillas_descubiertas++;
            if(tablero[i][j].num_ady==0 )
              AbrirTablero(i,j);
          }
        }
      }
    }
  }

}

bool Buscaminas::Pulsar(int fila, int columna){

  int numero_banderas=0;
  bool explosion = false;

  if(tablero[fila][columna].descubierta){
    for(int i=fila-1; i<=fila+1;i++){
      if(i>=0 && i<num_filas){
        for(int j=columna-1; j<=columna+1;j++){
          if(j>=0 && j<num_columnas){
            if(tablero[i][j].marca){
              numero_banderas++;
            }
          }
        }
      }
    }
  }

  if(numero_banderas==tablero[fila][columna].num_ady){
    for(int i=fila-1; i<=fila+1;i++){
      if(i>=0 && i<num_filas){
        for(int j=columna-1; j<=columna+1;j++){
          if(j>=0 && j<num_columnas){
            if(!tablero[i][j].marca && !tablero[i][j].descubierta){
              explosion = Descubrir(i,j);
            }
          }
        }
      }
    }
  }

  return explosion;

}

void Buscaminas::Jugar(){

  bool seguir=true;
  MostrarTablero();

  do{
    int opcion;

    cout << "Que quieres hacer:\n- Descubrir(1)\n- Marcar(2)\n- Pulsar(3)\n- Terminar(4)" << endl;
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
      int fila, columna;
      cout << "Que fila quieres" << endl;
      cin >> fila;
      cout << "Que columna quieres" << endl;
      cin >> columna;

      seguir = !Pulsar(fila, columna);
    }
    else if(opcion==4){
      seguir=false;
    }
    else{
      cout << "Has introducido un caracter incorrecto, vuelve a intentarlo" << endl;
    }

    if(num_casillas_descubiertas==(num_filas*num_columnas-num_bombas)){
      cout << "\n\n\tVICTORIA!\n" << endl;
      seguir = false;
      Victoria();
    }

    MostrarTablero();

  }while(seguir);

}


void Buscaminas::Victoria(){
  for(int i=0; i<num_filas; i++){
    for(int j=0; j<num_columnas; j++){
      if(tablero[i][j].bomba && !tablero[i][j].marca){
        tablero[i][j].marca=true;
      }
    }
  }
}

void Buscaminas::Derrota(){
  for(int i=0; i<num_filas; i++){
    for(int j=0; j<num_columnas; j++){
      if(tablero[i][j].bomba && !tablero[i][j].marca){
        tablero[i][j].descubierta=true;
      }
    }
  }

}


void Buscaminas::MostrarTablero(){
  cout << "  ";
  for(int j=0; j<num_columnas; j++){
    cout << "   " << j;
  }
  cout << endl;
  cout << "    ";
  for(int j=0; j<num_columnas; j++){
    cout << VERDE("----");
  }
  cout << endl;
  for(int i=0; i<num_filas; i++){
    cout << i << VERDE(" ||");
    for(int j=0; j<num_columnas; j++){
      cout << " " << mostrarCasilla(tablero[i][j]) << " " << VERDE("|");
    }
    cout << VERDE("|") << endl << "    ";
    for(int j=0; j<num_columnas; j++){
      cout << VERDE("----");
    }
    cout << endl;

  }
}

string Buscaminas::mostrarCasilla(Casilla casilla){
  string salida;
  if(casilla.descubierta){
    salida = casilla.mostrar;
    switch (casilla.num_ady) {
      case -1:
        salida = ROJO2("X");
        break;
      case 0:
        salida = GRIS("0");
        break;
      case 1:
        salida = AZUL("1");
        break;
      case 2:
        salida = VERDE("2");
        break;
      case 3:
        salida = ROJO("3");
        break;
      case 4:
        salida = AZUL("4");
        break;
      case 5:
        salida = ROJO("5");
        break;
      case 6:
        salida = AZUL("6");
        break;
      case 7:
        salida = NEGRO("7");
        break;
      case 8:
        salida = NEGRO("8");
        break;

      }
  }else{
    if(casilla.marca){
      salida = NARANJA("B");
    }
    else{
      salida = '#';
    }
  }
  return salida;
}
