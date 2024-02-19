#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX 42
using namespace std;

void CrearTablero(char tablero[][MAX], int N, int serpF[65], int serpC[65]);
void ImprimeTablero(char tablero[][MAX], int N);
void AgregarComida(char tablero[][MAX], int N);
void MovSerpiente(char tablero[][MAX], int N, int serpF[65], int serpC[65], int movimiento, int tamaño);
void VerificarComida(char tablero[][MAX], int N, int* tamaño, int agregarcola);
void ColocarSerpiente(char tablero[][MAX], int N, int serpF[65], int serpC[65], int tamaño);
int VerificarPerder(int serpF[65], int serpC[65], int N, int tamaño);

void main() {
	char nivel;
	int s, agregarcola, N = 40, movimiento, tamaño = 1, perder;
	char tablero[MAX][MAX];
	int serpienteF[65], serpienteC[65];
	//N = filas y columnas
	//F: fila
	//C: columna

	srand(time(NULL));

	cout << "Bienvenido al juego de Snake LPOO" << endl;
	cout << "Los niveles son: " << endl;
	cout << " (P) Nivel Principiante" << endl;
	cout << " (I) Nivel Intermedio" << endl;
	cout << " (A) Nivel Avanzado" << endl;
	cout << "Ingrese el nivel: ";

	do {
		cin >> nivel;
		if ((nivel == 'P') || (nivel == 'I') || (nivel == 'A')) {
			s = 0;
		}
		else {
			s = 1;
			cout << "Seleccion incorrecta. Ingrese un nuevo nivel: ";
		}
	} while (s);

	switch (nivel) {
		case 'P': {
			agregarcola = 1;
			break;
		}
		case 'I': {
			agregarcola = 2;
			break;
		}
		case 'A': {
			agregarcola = 3;
			break;
		}
	}

	CrearTablero(tablero, N, serpienteF, serpienteC);

	while (1) {

		AgregarComida(tablero, N);
		ImprimeTablero(tablero, N);

		cout << endl;
		cout << "La serpiente se puede mover en: Arriba(8), Abajo(2), Izquierda(4), Derecha(6)" << endl;
		cout << "Ingrese el movimiento: ";
		do {
			cin >> movimiento;
			if ((movimiento == 2) || (movimiento == 4) || (movimiento == 6) || (movimiento == 8)) {
				s = 0;
			}
			else {
			cout << "Movimiento no valido. Ingrese un nuevo movimiento: ";
			s = 1;
			}
		} while (s);

		MovSerpiente(tablero, N, serpienteF, serpienteC, movimiento, tamaño);
		VerificarComida(tablero, N, &tamaño, agregarcola);
		ColocarSerpiente(tablero, N, serpienteF, serpienteC, tamaño);

		if (tamaño >= 60) {
			cout << endl;
			cout << "Enhorabuena, has ganado." << endl;;
			break;
		}

		perder = VerificarPerder(serpienteF, serpienteC, N, tamaño);

		if (perder) {
			cout << endl;
			cout << "Lastima, has perdido." << endl;;
			break;
		}
	}

}

void CrearTablero(char tablero[][MAX], int N, int serpF[65], int serpC[65]) {
	int randF, randC;

	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			tablero[i][j] = ' ';
		}
	}

	/*Vamos a colocar los bordes del tablero*/
	for (int j = 0; j < N + 2; j++) {
		tablero[0][j] = '#';
		tablero[N + 1][j] = '#';
	}

	/*Vamos a colocar los bordes del tablero*/
	for (int i = 0; i < N + 2; i++) {
		tablero[i][0] = '#';
		tablero[i][N + 1] = '#';
	}

	/*Coloca jugador*/
	randF = rand() % 40;
	randC = rand() % 40;
	tablero[randF + 1][randC + 1] = 'S';
	serpC[0] = randC + 1;
	serpF[0] = randF + 1;
}

void ImprimeTablero(char tablero[][MAX], int N) {
	for (int i = 0; i < (N + 2); i++) {
		for (int j = 0; j < (N + 2); j++) {
			cout << tablero[i][j];
		}
		cout << endl;
	}
}

void AgregarComida(char tablero[][MAX], int N) {
	int agregar = 1, ArandF, ArandC;;

	for (int i = 0; i < (N + 2); i++) {
		for (int j = 0; j < (N + 2); j++) {
			if (tablero[i][j] == 'A') {
				agregar = 0;
			}
		}
		cout << endl;
	}

	if (agregar) {
		do {
			ArandF = rand() % 40;
			ArandC = rand() % 40;

			if (tablero[ArandF + 1][ArandC + 1] == ' ') {
				tablero[ArandF + 1][ArandC + 1] = 'A';
				agregar = 0;
			}
		} while (agregar);
	}

}

void MovSerpiente(char tablero[][MAX], int N, int serpF[65], int serpC[65], int movimiento, int tamaño) {

	//Valores Iniciales
	for (int ind = 0; ind < 3; ind++) {
		serpF[tamaño + ind] = 1;
		serpC[tamaño + ind] = 1;
	}

	for (int a = 0; a < tamaño + 3; a++) {
		serpF[tamaño + 3 - a] = serpF[tamaño + 3 - a - 1];
		serpC[tamaño + 3 - a] = serpC[tamaño + 3 - a - 1];
	}

	if (movimiento == 2) {
		serpF[0] = serpF[0] + 1;
	}
	if (movimiento == 8) {
		serpF[0] = serpF[0] - 1;
	}
	if (movimiento == 4) {
		serpC[0] = serpC[0] - 1;
	}
	if (movimiento == 6) {
		serpC[0] = serpC[0] + 1;
	}

	tablero[serpF[0]][serpC[0]] = 'S';
	tablero[serpF[tamaño]][serpC[tamaño]] = ' ';
}

void VerificarComida(char tablero[][MAX], int N, int* tamaño, int agregarcola){
	int agregar = 1;

	for (int i = 0; i < (N + 2); i++) {
		for (int j = 0; j < (N + 2); j++) {
			if (tablero[i][j] == 'A') {
				agregar = 0;
			}
		}
		cout << endl;
	}

	if (agregar) {
		*tamaño = *tamaño + agregarcola;
	}
}

void ColocarSerpiente(char tablero[][MAX], int N, int serpF[65], int serpC[65], int tamaño) {
	for (int i = 0; i < tamaño; i++) {
		tablero[serpF[i]][serpC[i]] = 'S';
		tablero[1][1] = ' ';
	}
}

int VerificarPerder(int serpF[65], int serpC[65], int N, int tamaño) {
	int resultado = 0;

	for (int ind = 1; ind < tamaño; ind++) {
		if ((serpF[0] == serpF[ind]) && (serpC[0] == serpC[ind])) {
			resultado = 1;
		}
	}

	if ((serpF[0] == 0) || (serpC[0] == 0)) {
		resultado = 1;
	}
	
	return resultado;
}