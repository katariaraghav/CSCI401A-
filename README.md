# CSCI401A

This repo contains the working code and test cases for solving the Autonomous Intersection Management Problem by repeatedly running A\* on each agent. 
See the DemonstrationTestCases folder for a description of the input. See Comparison.md for the writeup explaining why the MAPF solver is necessary. 
Input.txt contains a working test case. Deadlock.txt is a sample deadlock case.

How to compile the code:

g++ -g MultiAgentAStar.cpp -o MultiAgentAStar

How to run the code:

./MultiAgentAStar <input.txt >output.txt
