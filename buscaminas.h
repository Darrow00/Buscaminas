#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H
#include <vector>
#include <string>
using namespace std;


struct Casilla{
  bool bomba;
  int num_ady;
  string mostrar;
  bool descubierta;
  bool marca;
};


class Buscaminas{

  private:
    vector< vector <Casilla> > tablero;
    int num_filas, num_columnas;
    int num_bombas;

    void Explosion();
    void Victoria();
    void ColocarBombas();
    string mostrarCasilla(Casilla casilla);

  public:

    // Crea el tablero y coloca las bombas
    Buscaminas(int filas, int columnas, int bombas);


    // Descubrir
    bool Descubrir(int fila, int columna);
    void PonerBandera(int fila, int columna);
    void AbrirTablero(int fila, int columna);

    void MostrarTablero();

    void Jugar();

};



#endif
