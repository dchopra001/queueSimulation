Network Queue Simulation
================================

Data in communication networks (ex. telephone, internet) is transferred via packets. A key component that helps manage these packets as they travel from source to destination is a queue. This project aims to build a model representing a queue that simulates a network. Then, based on different input parameters, the network performance can be analyzed. 

This program will simulate a FIFO queue, described via Kendall notation (ex G/G/1/K/FIFO). Specifically, it will simulate a M/M/1 and M/M/1/K queue.

A brief note on Kendall notation
-----------------------------------
Consider the following queue: M/M/1/K/FIFO

*The first and second "M"s describe the packet arrival and service process (Memoryless or Markovian). It can be further  Other possible options are 
*The "1" describes the number of servers
*The "K" describes the buffer size (maximum number of packets that can be waiting to be served in the queue at any time). If this parameter is not present, then the buffer size is infinite.
*FIFO: First In First Out: Service style

Image
------------------------------------
The image below shows an example of a FIFO Queue and its key components.

[Fifo Queue] (fifoQueue.JPG)

Basics
-----------------------------------
In order to achieve good simulation results, packets need to arrive into the queue realistically (random). A good way to achieve this is by generating a Random Variable in the range (0,1). (allows us to have uniformity)

The simulation itself is a mathematical relationship between the input and output. A simulation experiment will simply generate several instances of input variables and of the corresponding output variables. The output variables can then be used to estimate the performance of the system.


Random Variable Generation
----------------------------------
In order to simulate packet arrival realistically, I have written a random variable generator. The RandomVariable class serves as an interface to creating random variables. The ExponentialRV is one such implementation of this interface. It defines additional fields that describe a random variable function, and can then implements functions defined in the RandomVariable class that provide common calculations for that function (e.x. Variance, Mean).

How do we find a random variable X?
---------------------------------------
If we have a random variable X with distribution function F(x), We can obtain X by calculating X=F^(-1) (X). In other words, by finding the inverse of F(x). 
To obtain a random variable value between 0 and 1, we can first generate a random number, U,  between 0 and 1, and then evalute that value using X=F^(-1)(U)

The distribution function for the Exponential Random Variable defined in this simulation is 1 - e^(-Lx), where L is the coefficient lambda (specified by the user). 

Simulator Design
---------------------------------------


