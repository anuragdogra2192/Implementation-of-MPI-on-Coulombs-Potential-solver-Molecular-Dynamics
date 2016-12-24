# MPI implementaion on Coulumbs Potential
In molecular dynamics (MD) there is a pairwise interaction between N set of particles.This code is to implement the Coulomb Solver.The simple_sequential.cpp is the sequential code of Coulomb Solver without MPI(Message Passing Interface).
MPI_potential.cpp is the MPI implementation on the simple sequential code.
---
<p> The input file : There are two entities charge q<sub> i </sub> of a particle and x<sub> i </sub>,y<sub> i </sub> and z<sub> i  </sub> are the positon components of i particle,with i = 1..N.</p>
---
---
The distance between the particales can be calculated as

![distance](https://cloud.githubusercontent.com/assets/19593595/21468830/164518aa-ca2a-11e6-9169-352c3ab70abf.png)
---
---
<p> The Coulomb Force <bold>F</bold><sub>i</sub> acting on all the particles due to presence of all particles with i=1.....N acting on each particle via</p> 
![forces](https://cloud.githubusercontent.com/assets/19593595/21468883/e22558de-ca2c-11e6-95ee-96ad1f403654.png)
---
---
<p>The Coulomb potential has been calculated at each particle position via  </p>
![potential](https://cloud.githubusercontent.com/assets/19593595/21468939/7500c574-ca2f-11e6-80cb-62a37af455a0.png)
---
---
<p>The Coulomb Energy has been calculated via </p>
![energy](https://cloud.githubusercontent.com/assets/19593595/21468942/cf2badd4-ca2f-11e6-9131-701459c267e0.png)
---

