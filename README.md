# CSCI401A

This repo contains the working code and test cases for solving the Autonomous Intersection Management Problem by repeatedly running A\* on each agent. 

See the DemonstrationTestCases folder test cases and for a description of the input. See Comparison.md for the writeup explaining why the MAPF solver is necessary. See InputTranslation for how to generate AIM MAPF approach input from AIM A\* approach input. 

How to compile the code:

g++ -g MultiAgentAStar.cpp -o MultiAgentAStar

How to run the code:

./MultiAgentAStar <input.txt >output.txt

