#### MPI implementaion on Coulumbs Potential
---
In molecular dynamics (MD) there is a pairwise interaction between N set of particles.This code is to implement the Coulomb Solver.The simple_sequential.cpp is the sequential code of Coulomb Solver without MPI(Message Passing Interface).
MPI_potential.cpp is the MPI implementation on the simple sequential code.

---
I run this code on [pico](http://www.hpc.cineca.it/hardware/pico) cluster of CINECA supercomputing centre.

How to compile and run the code:-

Module to be loaded:-

If you want to use intel compiler(I used this),any other version can also be used
1. intel/cs-xe-2015--binary
2. intelmpi/5.0.1--binary

If you want to use gnu compiler,any other version can also be used
1. gnu/5.4.0

---
->mpicxx MPI_potential.cpp -o MPI_potential

->mpirun -np 16 ./MPI_potential

---
* I have used only 1 node with 16 cores to run the MPI_potential.cpp
* The sequential code  simple_sequential.cpp you can compile and run normally with gnu or intel compiler
---
*Thank You ________Anurag Dogra*
