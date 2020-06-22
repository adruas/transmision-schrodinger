//Funciones secundarias implicadas en la detección y colapso de la función de onda
#pragma once
using namespace std;
#include <complex>
#include <cmath>
#define N 1000

//Función que me permite determinar la probabilidad de que la función de onda esté a la derecha
double pdcha (complex<double> phi[N]);
//Función que me permite determinar la probabilidad de que la función de onda esté a la izquierda
double pizda (complex<double> phi[N]);
//Función que colapsa la función a la derecha y renormaliza
void colapsoDcha(complex<double> (&phi)[N]);
//Función que colapsa la función a la izquierda y renormaliza
void colapsoIzda(complex<double> (&phi)[N]);
