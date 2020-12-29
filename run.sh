#!/bin/bash

mpirun --hostfile maquinas.txt ./programa smi.csv dollars.csv
