#!/bin/bash
#SBATCH --ntasks 100
#SBATCH --time 1:00:00
#SBATCH --qos bearchal03
#SBATCH --reservation BearChallenge
#SBATCH --output=batch.out

module purge
module load bluebear
module load bear-apps/2018a
module load iomkl/2018a

mpicc main.c -o main

input_num=$(shuf -i 1-1000000 -n 1)

echo "================================================================================================" >> batch.out
echo "================================================================================================" >> batch.out
echo "                    Testing on batch of 5 with NUM_ATTEMPTS = $input_num                        " >> batch.out    
echo "================================================================================================" >> batch.out


for i in 1 2 3 4 5
do
    mpirun main $input_num
done
