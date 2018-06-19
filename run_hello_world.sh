#!/bin/bash
#SBATCH --ntasks 100
#SBATCH --time 1:00:00
#SBATCH --qos bearchal07
#SBATCH --reservation BearChallenge

module purge
module load bluebear
module load bear-apps/2018a
module load iomkl/2018a

mpicc hello_world.c -o hello_world

mpirun hello_world

