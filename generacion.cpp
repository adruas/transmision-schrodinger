//Funciones secundarias implicadas en la generación y evolucion de la función de onda
#include "generacion.hpp"

//Función para descripcion del potencial (barrera)
void potencial (complex<double> (&pot)[N], double k, double lambda)
{
    int j;
    for(j=0; j<N; j++)
    {
        if(j>=2.*N/5 && j<=3.*N/5) pot[j]=lambda*k*k;
        else pot[j]=0.0;
    }
    return;
}

//Función para obtener los coeficientes alpha y gamma
void alpha_y_gamma(complex<double> (&alpha)[N-1], complex<double> (&gamma)[N-1],
                   complex<double> s, complex<double> V[N])
{
    //Defino el numero i
    complex<double> numero_i=complex<double>(0.0,1.0);
    alpha[N-2]=0; //Contorno
    for(int j=N-3;j>=0;j--)
    {
        gamma[j+1]=1.0/(-2.0+(2.0*numero_i/s)-V[j+1]+alpha[j+1]);
        alpha[j]=-gamma[j+1];
    }
    return;
}

//Función que me genera una función de onda (gaussiana)
void inic_onda(complex<double> (&phi)[N], double k)
{
    //Defino el numero i
    complex<double> numero_i=complex<double>(0.0,1.0);
    //normalización
    double normaliz=0;
    phi[0]=0; phi[N-1]=0;//contorno
    for(int j=1;j<N-1;j++) //Función de onda inicial
    {
        phi[j]=exp((numero_i*k*(1.0*j))-(8.0*(4.0*j-N)*(4.0*j-N)/(N*N))); //Gaussiana
        normaliz+=norm(phi[j]); //Contabilizo el coef normalización
    }
    //Normalizo
    for(int j=0; j<N; j++) phi[j]=phi[j]/sqrt(normaliz);
    return;
}

//Algoritmo que permite la descripción de la evolución de la función de onda en el tiempo (pasos)
void algoritmo(int pasos, complex<double> s, complex<double> (&beta)[N-1], complex<double> (&phi)[N],
               complex<double> gamma[N-1], complex<double> alpha[N-1], complex<double> (&ji)[N], int l)
{
    //Defino el numero i
    complex<double> numero_i=complex<double>(0.0,1.0);
        //Calculo beta
        beta[N-2]=0;
        for(int j=N-3;j>=0;j--) beta[j]=gamma[j+1]*((4.0*numero_i*phi[j+1]/s)-beta[j+1]);

        //Calculo ji
        ji[N-1]=0;
        ji[0]=0;
        for(int j=1; j<N-1; j++)
        {
            ji[j]=(alpha[j-1]*ji[j-1])+beta[j-1];
        }

        //Calculo LA FUNCIÓN DE ONDA
        phi[N-1]=0; phi[0]=0;
        for(int j=1;j<N-1;j++) phi[j]=ji[j]-phi[j];

return;
}
