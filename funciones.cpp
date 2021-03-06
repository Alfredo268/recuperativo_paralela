#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "headers.h"
using namespace std;

float beta(float x_bar, float y_bar, vector<int> x,vector<float> y){
    float sxy=0, sxx=0;
    for(int i=0;i<x.size();i++){
        sxy += (x[i]-x_bar)*(y[i]-y_bar);
        sxx += (x[i]-x_bar)*(x[i]-x_bar);
    }
    return sxy/sxx;
}

float alfa(float beta, float x_bar, float y_bar){
    return y_bar - beta*x_bar;
}
//funcion para obtener sueldo minimo en dolar y mostrar la regresion lineal 
void sueldo_minimo_dolar(char *archivo_1,char *archivo_2,int rank){

    ifstream infile(archivo_1);
    string line = "";
    vector<string> datos_csv;
    vector<float> sueldo_finales;
    vector<int> years_finales;
    while(getline(infile, line)){
        stringstream strstr(line);
        string word="";
        while(getline(strstr,word,',')){
            datos_csv.push_back(word);    
        }  
    }

    int e=1;
    for (int i=1995;i<2020;i++)
    {   
        sueldo_finales.push_back(get_sueldo(datos_csv.at(e))/(promedio_year(archivo_2,i)));
        e=e+1;
        years_finales.push_back(i);
    }
    float promediox = 0, promedioy = 0;
    for (int i = 0; i < years_finales.size(); i++)
    {
        promediox += years_finales[i]/years_finales.size();
        promedioy += sueldo_finales[i]/sueldo_finales.size();
    }
    if (rank==1)
    {
        float beta_coef = beta(promediox,promedioy,years_finales,sueldo_finales);
        float alfa_coef = alfa(beta_coef,promediox,promedioy);
        MPI_Send(&alfa_coef,1,MPI_FLOAT,0,1,MPI_COMM_WORLD);
        MPI_Send(&beta_coef,1,MPI_FLOAT,0,2,MPI_COMM_WORLD);
    }
    
    

    if(rank==0){

        float alfa_coef;
        float beta_coef;
        MPI_Recv(&alfa_coef,1,MPI_FLOAT,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&beta_coef,1,MPI_FLOAT,1,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        cout<<"--------------RESULTADO---------------"<<endl<<'\n';
        cout<<"y = "<<alfa_coef<<" + "<<beta_coef<<"x"<<endl<<'\n';
        cout<<"-------------INTEGRANTES------------"<<endl<<'\n';
        cout<<"------ALFREDO ANTONIO GARCES ULLOA------"<<endl;
    }
    


}



//promedio por año
float promedio_year(char *archivo,int year){
    ifstream infile(archivo);
    float prom=0;
    string line = "";
    vector<string> datos_csv;
    while(getline(infile, line)){
        stringstream strstr(line);
        string word="";
        float suma=0;
        int cont=0;
        while(getline(strstr,word,',')){
            datos_csv.push_back(word);    
        }
        for (int i = 0; i < datos_csv.size(); i++)
        {
            if(get_year(datos_csv.at(i))==year){
                suma=suma+get_dolar(datos_csv.at(i));
                cont=cont+1;
            }
            else
            {
                prom=suma/cont;
            }
            
        }
    }
    return prom;
    
    
}

//funcion para obtener el año de una linea de dollars.csv
int get_year(string line){
    int year;
    char e[4];
    int d=0;
    for (int i=1; i<5; i++){
        e[d]=line[i];
        d=d+1;
    }
    year=atoi(e);
    //cout<<year;
    return year;
}
//funcion para obtener el monto de una linea de dollars.csv
float get_dolar(string line){
    char d[6];
    float dolar;
    int e=0;
    for (int i=14; i<20; i++){
        d[e]=line[i];
        e=e+1;
        }
    dolar=atof(d);
    return dolar;
}
//obtiene el sueldo a partir de una linea del .csv
float get_sueldo(string line){
    char d[8];
    float sueldo;
    int e=0;
    for (int i=8; i<16; i++){
        d[e]=line[i];
        e=e+1;
        }
    sueldo=atof(d);
    return sueldo;
}
//obtiene el año a partir de una linea del .csv
int get_sueldo_year(string line){
    char d[4];
    int year;
    int e=0;
    for (int i=1; i<5; i++){
        d[e]=line[i];
        e=e+1;
        }
    year=atoi(d);
    return year;
}