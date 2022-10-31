#!/bin/bash
#SBATCH --job-name=your_job_name # Job name
#SBATCH --nodes=1                    # Run all processes on a single node	
#SBATCH --ntasks=20                   # number of processes = 20
#SBATCH --cpus-per-task=1            # Number of CPU cores allocated to each process
#SBATCH --partition=Project            # Partition name: Project or Debug (Debug is default)

# mpirun -np $n_proc ./mpi $X_RESN $Y_RESN $max_iteration
# mpirun -np $n_proc ./mpig $X_RESN $Y_RESN $max_iteration

mpirun -np 4 ./mpi 1000 1000 100
# mpirun -np 4 ./mpig 1000 1000 100