Grigoriy Redozubov
Coding Assignment 2


How to compile:
The makefile is written so that the program can be compiled with a simple "make".

How to run:
Run by calling "./BestFirstSearch <input.txt> <output.txt>.

Input and output files are formated as described in the assignment.


Data Structures:
- an self written item object to store the individual items and their weights and prices
- a self written node object to store all information necessary to store between item decisions
- a self written binary tree of nodes, to demonstrate how the items are selected and the information stored about them
- a std::priority queue to organize the order that nodes are examined (based on their p/w ration)
- several std::vectors to store items, and relevant information (such as selected items)


Computation Time:
- Each knapsack iteration (done once for each node):
	- O(lgn): priority queue insertion
	- O(n): KWF
	- total: O(n +lgn) = O(n)

total possible nodes: 2^n
	- (2^n) * O(n) = O(n*2^n)

There will almost always be less tha 2^n nodes searched, but I cannot find a more accurate way to approximate



Classes:
- I used a class to define nodes and items
- Each class stored the information discussed in class about their respective objects





“I, Grigoriy Redozubov, have done this assignment completely on my own. I have not copied it, nor
have I given my solution to anyone else. I understand that if I am involved in plagiarism or
cheating I will have to sign an official form that I have cheated and that this form will be stored in
my official university record. I also understand that I will receive a grade of 0 for the involved
assignment for my first offense and that I will receive a grade of “F” for the course for any
additional offense.” 
