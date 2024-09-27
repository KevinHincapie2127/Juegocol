#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Carta.h"

using namespace std;

class Jugador {
private:
		string nombre;
		vector<Carta> cartas;

public:
		Jugador(string nombre) : nombre(nombre) {}

		void agregarCarta(Carta carta) {
				cartas.push_back(carta);
		}

		string obtenerNombre() const {
				return nombre;
		}

		int calcularPuntuacion() const {
				int puntos = 0;

				for (const auto& carta : cartas) {
						if (carta.tipo == Carta::COLOR_CARTA) {
								puntos += 1;
						} else if (carta.tipo == Carta::MAS2) {
								puntos += 2;
						} else if (carta.tipo == Carta::COMODIN) {
								puntos += 5;
						} else if (carta.tipo == Carta::COMODIN_DORADO) {
								puntos += 10;
						}
				}

				return puntos;
		}
};

#endif // JUGADOR_H
