# MPI implementaion on Coulumbs Potential
In molecular dynamics (MD) there is a pairwise interaction between N set of particles.This code is to implement the Coulomb Solver.The simple_sequential.cpp is the sequential code of Coulomb Solver without MPI(Message Passing Interface).
MPI_potential.cpp is the MPI implementation on the simple sequential code.
---
<p> The input file : There are two entities charge q<sub> i </sub> of a particle and x<sub> i </sub>,y<sub> i </sub> and z<sub> i  </sub> are the positon components of i particle.</p>

The distance between the particales can be calculated as 


