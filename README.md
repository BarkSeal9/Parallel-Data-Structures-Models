# Parallel Data Structures Models

A set of programs for probabilistic modeling of parallel data structures.

## Parallel FIFO Queues Models

"Custom Queuing" is one of the traffic management strategies in a router. The method proposed in [Sedgewick R. Algorithms in C++, Parts 1-4, 1998] can be considered as a generalization of this queue management strategy. Here, insertions of elements in queues are performed on the odd step, deletions of elements from queues are performed on the even step.

"One after another" is a theoretical method of data structure organization proposed in [Sokolov A.V. Mathematical Models and Algorithms of the Optimal Control of Dynamic Data Structures (RUS), 2002]. Here, two cyclic queues move one after another in shared memory space.

Simulation models are based on Monte-Carlo method.
Mathematical models are based on regular Markov chains.

The model parameters are:

* **m** -- size of the available memory;
* **s** (in *\*_Sedg_x2.c*) or **ox** (in *\*_OAA_x2.c*) -- the number of memory units allocated to the first queue;
* **x** -- size of the first queue;
* **m-s** (in *\*_Sedg_x2.c*) or **oy** (in *\*_OAA_x2.c*) -- the number of memory units allocated to the second queue;
* **y** -- size of the second queue;
* **z** (in *\*_OAA_x2.c*) -- the distance between the end of the first queue and the beginning of the second one;
* **p1** -- probability of insertion in the first queue;
* **p2** -- probability of insertion in the second queue;
* **p12** -- probability of parallel insertion in both queues;
* **q1** -- probability of deletion from the first queue;
* **q2** -- probability of deletion from the second queue;
* **q12** -- probability of parallel deletion from both queues;
* **r1** (first queue) **r2** (second queue) -- probability of absence of an operation.

Utilizing these models, one can solve the problem of finding optimal partition of memory between two queues [Sokolov A.V., Barkovsky E.A. Some Problems of Optimal Control of Two Parallel FIFO-queues // AIP Proceedings of ICNAAM 2014, 2015, V. 1648, P. 520003]. Optimality criterion is the minimum mean share of lost (by an overflow) elements of the queues.

### Queues_Sim_Models:

**Sim_Cust_OAA_x2.c**
Simulation model of two custom queues, moving one after another in a circle.

**Sim_Sedg_x2.c**
Simulation model of two queues based on Sedgewick method.

**Sim_Sedg_OAA_x2.c**
Simulation model of two queues based on Sedgewick method, moving one after another in a circle.

### Queues_Math_Models:

The programs below describe generation of transition probability matrix for a Markov chain.

**Math_Cust_OAA_x2.c**
Mathematical model of two custom queues, moving one after another in a circle.

**Math_Sedg_x2.c**
Mathematical model of two queues based on Sedgewick method.

**Math_Sedg_OAA_x2.c**
Mathematical model of two queues based on Sedgewick method, moving one after another in a circle.

## Work Stealing Deques Models

"Work stealing" is one of the methods of parallel task balancing. In this method, each processor (or a core) has a buffer of tasks: a double ended queue called "deque" [Knuth D. The Art of Computer Programming, Vol. 1, 2001]. A processor uses one end of its deque to store or remove tasks. The other end of the deque is accessible by other processors with empty buffers, so they can "steal" (remove from the deque) "work" (tasks).

Simulation models are based on Monte-Carlo method.

The model parameters are:

* **m** -- size of the available memory;
* **s** -- the number of memory units allocated to the first deque;
* **x** -- size of the first deque;
* **m-s** -- the number of memory units allocated to the second deque;
* **y** -- size of the second deque;
* **o** (in *\*_Redi.c*) -- the number of elements to redistribute;
* **p1** -- probability of insertion in the first deque;
* **p2** -- probability of insertion in the second deque;
* **p12** -- probability of parallel insertion in both deques;
* **q1** -- probability of deletion from the first deque;
* **q2** -- probability of deletion from the second deque;
* **q12** -- probability of parallel deletion from both deques;
* **pq12** -- probability of insertion in the first deque and parallel deletion from the second one;
* **pq21** -- probability of insertion in the second deque and parallel deletion from the first one;
* **r** -- probability of absence of an operation.

The model parameters for *\*_x3_Part\_** are:

* **m** -- size of the available memory;
* **Sk_n** -- the working end of deque **De_n** (a stack);
* **Qe_n** -- the work stealing end of deque **De_n** (a queue);
* **s** -- the part of memory that contains combined work stealing queue **Qe** (**Qe_1**+**Qe_2**+**Qe_3**) and working end **Sk_1**;
* **m-s** -- the part of memory that contains working ends **Sk_2** and **Sk_3**;
* **d** (in *\*_d.py*) -- the part of memory that contains working end **Sk_2**;
* **m-s-d** (in *\*_d.py*) -- the part of memory that contains working end **Sk_3**;
* **p_n** -- probability of insertion in **Sk_n**;
* **q_n** -- probability of deletion from **Sk_n**;
* **w_n** -- probability of stealing from **Qe**;
* **pw_n** -- probability of parallel insertion in **Sk_n** and stealing from **Qe**;
* **qw_n** -- probability of parallel deletion from **Sk_n** and stealing from **Qe**;
* **r_n** -- probability of absence of an operation.

Utilizing these models, one can solve the problem of finding optimal partition or redistribution of memory between two deques [Sokolov A.V., Barkovsky E.A. The Mathematical Model and the Problem of Optimal Partitioning of Shared Memory for Work-Stealing Deques // Proceedings of PaCT 2015, 2015, V. 9251, P. 102-106]. Optimality criterion is the maximum mean time before memory overflow or reallocation.

### Deques_Sim_Models:

**Sim_WS_1_x2_Part.c**
Simulation model of two deques (work stealing of one element). Problem of memory partition.

**Sim_WS_0.5_x2_Part.c**
Simulation model of two deques (work stealing of half the elements). Problem of memory partition.

**Sim_WS_1_x2_Redi.c**
Simulation model of two deques (work stealing of one element). Problem of memory redistribution.

**Sim_WS_0.5_x2_Redi.c**
Simulation model of two deques (work stealing of half the elements). Problem of memory redistribution.

**Sim_WS_1_x3_Part_(seq).py**
Simulation model of three deques (work stealing of one element). Problem of memory partition: finding the optimal value of **s**. (A sequential program.)

**Sim_WS_1_x3_Part_(par).py**
Simulation model of three deques (work stealing of one element). Problem of memory partition: finding the optimal value of **s**. (A parallel program.)

**Sim_WS_1_x3_Part_d.py**
Simulation model of three deques (work stealing of one element). Problem of memory partition: finding the optimal values of **s** and **d**.

## Author

Eugene A. Barkovsky

## License

This project is licensed under the MIT License, see the LICENSE file for details.
