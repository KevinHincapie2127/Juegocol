#include <iostream>
#include "Juego.h"

using namespace std;

int main() {
		int numJugadores;
		cout << "Bienvenido a Coloretto\n";
		
		do {
				cout << "Ingrese el número de jugadores (máximo 5): ";
				cin >> numJugadores;

				if (numJugadores < 2 || numJugadores > 5) {
						cout << "Número de jugadores inválido. Deben ser entre 2 y 5 jugadores.\n";
				}
		} while (numJugadores < 2 || numJugadores > 5);

		Juego juego(numJugadores);
		juego.jugar();

		return 0;
}
