# CSCI401A-

Input.txt contains a working test case. Deadlock.txt is a sample deadlock case.

Description of deadlock.txt input:

3 8         // [#rows] [#cols]

00000000    // Description of intersection, 0 represents obstacle, . represents open path

........

.00.000.


1           // At time 0, 1 agent arrives

1 0 2 7     // 1st agent arriving at time 0 has start row = 1, start col = 0, goal row = 2, goal col = 7

0           // at time 1, 0 agents arrive

0           // at time 2, 0 agents arrive

0           // at time 3, 0 agents arrive

0           // at time 4, 0 agents arrive

0           // at time 5, 0 agents arrive

1           // at time 1, 1 agent arrives

1 7 2 0     // this agent has start row = 1, start col = 7, goal row = 2, goal col = 0
