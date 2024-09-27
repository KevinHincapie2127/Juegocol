#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Juego {
private:
		vector<Carta> mazo;
		vector<Jugador> jugadores;
		vector<vector<Carta>> filas;
		Carta ultimaRonda;
		vector<bool> filaTomada;

		void inicializarMazo() {
				vector<char> colores = {'r', 'g', 'b', 'y', 'o', 'p', 'v'};
				for (char color : colores) {
						for (int i = 0; i < 9; i++) {
								mazo.push_back(Carta(color));
						}
				}

				for (int i = 0; i < 10; i++) {
						mazo.push_back(Carta(Carta::MAS2));
				}

				for (int i = 0; i < 2; i++) {
						mazo.push_back(Carta(Carta::COMODIN));
				}

				mazo.push_back(Carta(Carta::COMODIN_DORADO));

				ultimaRonda = Carta(Carta::ULTIMA_RONDA);
				mazo.push_back(ultimaRonda);
				for (int i = 0; i < 15; i++) {
						int randomColorIndex = rand() % colores.size();
						mazo.push_back(Carta(colores[randomColorIndex]));
				}
		}

		void mezclarMazo() {
				srand(static_cast<unsigned int>(time(0)));
				for (int i = 0; i < mazo.size(); i++) {
						int j = rand() % mazo.size();
						swap(mazo[i], mazo[j]);
				}
		}

		void mostrarFilas() const {
				cout << "\nFilas actuales:\n";
				for (int i = 0; i < filas.size(); i++) {
						cout << "Fila " << i + 1 << ": ";
						for (const auto& carta : filas[i]) {
								carta.Mostrar();
						}
						cout << endl;
				}
		}

		void turnoJugador(Jugador& jugador) {
				mostrarFilas();

				cout << jugador.obtenerNombre() << ", es tu turno. Elige una acción:\n";
				cout << "1. Colocar una carta en una fila\n";
				cout << "2. Tomar una fila\n";

				int opcion;
				cin >> opcion;

				if (opcion == 1) {
						Carta carta = mazo.back();
						mazo.pop_back();
						cout << "Has sacado la carta: ";
						carta.Mostrar();
						cout << "\nElige una fila (1-" << filas.size() << "): ";
						int filaElegida;
						cin >> filaElegida;

						if (filas[filaElegida - 1].size() < 3) {
								if (carta.tipo == Carta::ULTIMA_RONDA) {
										cout << "¡Se ha sacado la carta 'Última Ronda'! Esta es la última ronda.\n";
										return;
								}
								filas[filaElegida - 1].push_back(carta);
						} else {
								cout << "La fila está llena. No puedes colocar más cartas aquí.\n";
								mazo.push_back(carta);
						}
				} else if (opcion == 2) {
						cout << "Elige una fila para tomar (1-" << filas.size() << "): ";
						int filaElegida;
						cin >> filaElegida;

						if (filas[filaElegida - 1].empty()) {
								cout << "La fila está vacía. No puedes tomar cartas de aquí.\n";
						} else if (filaTomada[filaElegida - 1]) {
								cout << "Esta fila ya ha sido tomada por otro jugador. No puedes tomar cartas de aquí.\n";
						} else {
								for (const auto& carta : filas[filaElegida - 1]) {
										jugador.agregarCarta(carta);
								}
								filas[filaElegida - 1].clear();
								filaTomada[filaElegida - 1] = true;
								cout << "Has tomado la fila " << filaElegida << ".\n";
						}
				}
		}

		void decidirColoresComodines() {
				for (auto& jugador : jugadores) {
						char nuevoColor;
						cout << "Jugador " << jugador.obtenerNombre() << ", elige un color para tu comodín (r, g, b, y, o, p, v): ";
						cin >> nuevoColor;
				}
		}

public:
		Juego(int numJugadores) : ultimaRonda(Carta(Carta::ULTIMA_RONDA)) {
				inicializarMazo();
				mezclarMazo();

				for (int i = 1; i <= numJugadores; i++) {
						string nombre;
						cout << "Ingrese el nombre del Jugador " << i << ": ";
						cin >> nombre;
						jugadores.push_back(Jugador(nombre));
				}

				filas.resize(3);
				filaTomada.resize(3, false);
		}

		void repartirCartas() {
				for (int i = 0; i < jugadores.size(); i++) {
						for (int j = 0; j < 3; j++) {
								jugadores[i].agregarCarta(mazo.back());
								mazo.pop_back();
						}
				}
		}

		void jugar() {
				cout << "Iniciando el juego" << endl;
				repartirCartas();

				bool juegoTerminado = false;

				while (!juegoTerminado) {
						int jugadoresSinTomarFila = 0;
						for (auto& jugador : jugadores) {
								if (!filaTomada[jugadoresSinTomarFila]) {
										turnoJugador(jugador);
										jugadoresSinTomarFila++;
								}
								if (mazo.empty()) {
										juegoTerminado = true;
										break;
								}
						}
				}

				cout << "¡Fin de la ronda! Es hora de decidir los colores de los comodines.\n";
				decidirColoresComodines();

				mostrarPuntuacion();
		}

		void mostrarPuntuacion() const {
				cout << "\nJuego terminado. Puntuaciones finales:\n";
				for (const auto& jugador : jugadores) {
						cout << jugador.obtenerNombre() << ": " << jugador.calcularPuntuacion() << " puntos.\n";
				}
		}
};

#endif // JUEGO_H
