//Funciones secundarias implicadas en la generación y evolucion de la función de onda
#pragma once
using namespace std;
#include <complex>
#include <cmath>
#include <fstream>
#include <iostream>
#define N 1000

//Función para descripcion del potencial (barrera)
void potencial (complex<double> (&pot)[N], double k, double lambda);
//Función para obtener los coeficientes alpha y gamma
void alpha_y_gamma(complex<double> (&alpha)[N-1], complex<double> (&gamma)[N-1],
                   complex<double> s, complex<double> V[N]);
//Función que me genera una función de onda (gaussiana)
void inic_onda(complex<double> (&phi)[N], double k);
//Algoritmo que permite la descripción de la evolución de la función de onda en el tiempo (pasos)
void algoritmo(int pasos, complex<double> s, complex<double> (&beta)[N-1], complex<double> (&phi)[N],
               complex<double> gamma[N-1], complex<double> alpha[N-1], complex<double> (&ji)[N], int l);

