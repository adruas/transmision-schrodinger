//Funciones secundarias implicadas en la detección y colapso de la función de onda
#include "deteccion.hpp"

//Función que me permite determinar la probabilidad de que la función de onda esté a la derecha
double pdcha (complex<double> phi[N])
{
    double suma=0;
    for(int j=4.*N/5; j<N;j++) suma+=norm(phi[j]);
    return suma;
}

//Función que me permite determinar la probabilidad de que la función de onda esté a la izquierda
double pizda (complex<double> phi[N])
{
    double suma=0;
    for(int j=0; j<N/5.; j++) suma +=norm(phi[j]);
    return suma;
}

//Función que colapsa la función a la derecha y renormaliza
void colapsoDcha(complex<double> (&phi)[N])
{
    int j, renorm;
    for(j=4*N/5;j<N;j++) phi[j]=0;
    //Renormalización
    renorm=0;
    for(j=0;j<N;j++) renorm=+norm(phi[j]);
    for(j=0;j<N;j++) phi[j]=phi[j]/sqrt(renorm);
}

//Función que colapsa la función a la izquierda y renormaliza
void colapsoIzda(complex<double> (&phi)[N])
{
    int j, renorm;
    for(j=0;j<N/5.0;j++) phi[j]=0;
    //Renormalización
    renorm=0;
    for(j=0;j<N;j++) renorm=+norm(phi[j]);
    for(j=0;j<N;j++) phi[j]=phi[j]/sqrt(renorm);
}
