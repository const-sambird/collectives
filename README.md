# collectives

just having a look at some MPI collective communication results; in particular, how quick different implementations of some common MPI collectives are in relation to each other.

I explore 7 different operations:
* broadcast
* reduce
* scatter
* gather
* allgather
* reduce-scatter
* allreduce

Each operation has three different implementations:
* 'short' optimised for short vectors
* 'long' optimised for long vectors
* 'builtin' which exclusively uses built-in MPI operations (calls to `MPI_Bcast`, `MPI_Scatter`, etc)

The algorithms in this repository are given in the following paper:

> Chan, E., Heimlich, M., Purkayastha, A. and van de Geijn, R. (2007), Collective communication: theory, practice, and experience. Concurrency Computat.: Pract. Exper., 19: 1749-1783. https://doi.org/10.1002/cpe.1206

The computing for this project was performed at the OU Supercomputing Center for Education & Research (OSCER) at the University of Oklahoma.

Consequently, the shell scripts to build the project are built for that system.
