/*Programa que simula la interacción de una función de onda con una barrera
de potencial, y obtiene mediante diversas pruebas el coeficiente de transmisión
de dicha onda frente a dicha barrera.*/

//BIBLIOTECAS
using namespace std;
#include <iostream>
#include <fstream>
#include <random>
#include "generacion.hpp" //Funciones secundarias implicadas en la generación y evolucion de la función de onda
#include "deteccion.hpp" //Funciones secundarias implicadas en la detección y colapso de la función de onda

const double pi=3.14159265358979323846;
#define m_max 100000

//Para generar números aleatorios
default_random_engine& prng()
{
    static thread_local default_random_engine gen(random_device{}());
    return gen;
}

//FUNCIÓN PRINCIPAL
int main (void)
{   
    //Declaración de variables
    int n, j, l, p, pasos, m, mT=0, i, experimento;
    double lambda, k, K[m_max],norma,x, P_d, P_i, media, desviacion, suma;
    complex<double> phi[N], alpha[N-1], beta[N-1], s, ji[N], V[N], numero_i, gamma[N-1];
    //ofstream sal_phi2, sal_norma;
    ofstream sal_coef, sal_estadistica;

    /*
    //Lectura de datos por consola
    cout << "Introduzca el número pasos del algoritmo: ";
    cin >> pasos;
    cout << "Introduzca el valor de lambda: ";
    cin >> lambda;
    cout << "Introduzca el número de ciclos: ";
    cin >> n;
    cout << "Introduzca el número de funciones de onda generadas por experimento: ";
    cin >> m;
    cout << "Introduzca el número de veces que desea repetir el experimento: ";
    cin >> experimento;
    */

    //Datos a mano
    pasos=600; 
    lambda=0.5;
    n=70;
    m=1000;
    experimento=100;

    //Defino la constante k
    k=2.*pi*n/N;

    //Cálculo del potencial reducido y lo escribo en fichero
    potencial(V,k,lambda);

    //Cálculo de alpha y gamma
    s=1./(4*k*k); //Defino la constante s
    alpha_y_gamma(alpha, gamma, s, V); //Llamo a la función

    //Abro los ficheros de escritura
    sal_coef.open("coeficientes.txt");
    sal_estadistica.open("estadistica.txt");
    if(!(sal_coef.is_open()||sal_estadistica.is_open())) cout << "\n\nError al abrir un fichero\n\n";
    sal_coef << "#Experimento nº"<<"\t"<<"Coeficiente de transmisión\n";
    sal_estadistica << "#Media del coef transmisión"<<"\t"<<"Desviación del coef de transmisión\n";



    uniform_real_distribution<double> aleat(0,1);
    //Realizo el experimento un número de veces para poder usar estadistica:
    for (j=1;j<=experimento;j++)
    {
        
        //Algoritmo de detección m veces, "m funciones de onda generadas"
        for(i=1;i<=m;i++)
        {   
           //Generación de la onda inicial cada vez que se ejecuta un nuevo "for"
           inic_onda(phi,k);

           do //do-while x>P_i
           {
               //Evoluciono la onda unos determinados pasos
                for(l=1; l<=pasos; l++)   algoritmo(pasos,s,beta,phi,gamma,alpha,ji,l);

               //Compruebo que está a la derecha con número aleatorio
               x=aleat(prng());
               P_d=pdcha(phi);

               //Si está a la derecha
               if(x<P_d)
               {
                   mT++; //Aumento el numero de veces detectado a la derecha
                   P_i=1; //Para poder salir del do-while y volver a generar onda nueva
               }

               //Si no está a la derecha
               else
               {
                   //Colapso de la función de onda a la derecha
                   colapsoDcha(phi);

                   //Compruebo que está a la izda con número aleatorio
                   x=aleat(prng());
                   P_i=pizda(phi);

                   //Si no está a la izda
                   if(x>P_i) colapsoIzda(phi); //Si esto se cumple, no salgo del do-while, y vuelvo al if
               }
           }while(x>P_i);   
        }
        cout << "Experimento "<<j<<" completado!"<<endl;
        //Para ver la convergencia del coeficiente de transmisión:
        K[j]=1.0*mT/m;
        sal_coef<<j<<"\t"<<K[j]<<endl;
        //Restauro mT=0 para empezar un nuevo experimento
        mT=0;
    }

    //Media
    suma=0;
    for(i=1;i<=experimento;i++) suma+=K[i];
    media=suma/experimento;

    //Desviación estándar
    suma=0;
    for(i=1;i<=experimento;i++) suma+=(K[i]-media)*(K[i]-media);
    desviacion=sqrt(suma/experimento);

    //Escritura
    sal_estadistica<<media<<"\t"<<desviacion<<endl;

    //Cierro ficheros
    sal_coef.close(); sal_estadistica.close();
    return 0;
}   
