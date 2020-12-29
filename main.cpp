#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#define PC_1 1
#define PC_2 2
#define PC_3 3
#define PC_4 4
#include "headers.h"
#include "funciones.cpp"


int main(int argc, char* argv[])
{   
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    sueldo_minimo_dolar(argv[1],argv[2]);
    /*if (rank == MASTER){
        cout<<"Proceso master"<<endl;
        promedio_all_year(argv[2]);
    }*/
        
    


    //promedio_all_year(argv[2]);
    //read(argv[1]);
    //read(argv[]);
    //lista_sueldo_minimo(argv[1]);
    MPI_Finalize();
    return 0;
}
/*
*
*Funciones
*
*/
//funcion para leer una linea

