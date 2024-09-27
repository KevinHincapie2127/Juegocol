#ifndef CARTA_H
#define CARTA_H

#include <iostream>

using namespace std;

class Carta {
public:
		static const int COLOR_CARTA = 0;
		static const int MAS2 = 1;
		static const int COMODIN = 2;
		static const int COMODIN_DORADO = 3;
		static const int ULTIMA_RONDA = 4;

		char color;
		int tipo;

		Carta(char color) : color(color), tipo(COLOR_CARTA) {}
		Carta(int tipo) : tipo(tipo) {
				color = ' ';
		}

		void Mostrar() const {
				if (tipo == COLOR_CARTA) {
						cout << color << " ";
				} else if (tipo == MAS2) {
						cout << "+2 ";
				} else if (tipo == COMODIN) {
						cout << "Comodín ";
				} else if (tipo == COMODIN_DORADO) {
						cout << "Comodín Dorado ";
				} else if (tipo == ULTIMA_RONDA) {
						cout << "Última Ronda ";
				}
		}
};

#endif // CARTA_H
