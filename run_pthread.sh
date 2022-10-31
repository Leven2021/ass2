#!/bin/bash
#SBATCH --job-name=your_job_name # Job name
#SBATCH --nodes=1                    # Run all processes on a single node	
#SBATCH --ntasks=20                   # number of processes = 20
#SBATCH --cpus-per-task=1            # Number of CPU cores allocated to each process
#SBATCH --partition=Project            # Partition name: Project or Debug (Debug is default)

# ./pthread $X_RESN $Y_RESN $max_iteration $n_thd
# ./pthreadg $X_RESN $Y_RESN $max_iteration $n_thd

./pthread 1000 1000 100 4
# ./pthreadg 2000 1000 100 4