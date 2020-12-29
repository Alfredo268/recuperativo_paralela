#define HEADERS_H
#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
//#include "mpi.h"
#include <iostream>
using namespace std;

/*
*
*Cabeceras
*
*/
void read(char *);
void sueldo_minimo_dolar(char *,char *);
int get_year(string);
float get_dolar(string);
float promedio_year(char *,int);
void lista_sueldo_minimo(char *);
float get_sueldo(string);
int get_sueldo_year(string);
float beta(float,float,vector<int>,vector<float>);
float alfa(float,float,float);