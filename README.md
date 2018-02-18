# Relational-Data-Model
Project for Formal Systems Course

Part 1
1. Implement a database containing the relations (tables) shown in FOCS Figure 8.1 and 8.2 (also seen in class). Use the method described in Section 8.2 in the section “Representing Relations” and elaborated in Section 8.4 “Primary Storage Structures for Relations.” Describe your implementation briefly but clearly in your writeup.
2. Implement the basic single-relation insert, delete, and lookup operations as func- tions. Describe your implementation briefly but clearly in your writeup.
3. Use your insert method to populate the tables with (at least) the data given in the figures. Demonstrate the operations with some examples using this data. Be sure that your program explains itself when run (using informative printed messages).
4. Implement functions for saving your database to one or more files, and loading from the same. Demonstrate this functionality also.

Part 2
1. Write a function to answer the query “What grade did StudentName get in Course- Name?” as described in Section 8.6 “Navigation Among Relations.” Demonstrate this functionality
2. Write a function to answer the query “Where is StudentName at Time on Day?” (assuming they are in some course). Demonstrate this functionality also.

Part 3
1. Implement the Relational Algebra operations as described in Section 8.8. Describe your implementation briefly but clearly in your writeup.
2. Use your implementation to do the operations on the “registrar” database de- scribed in Examples 8.12 (Selection), 8.13 (Projection), 8.14 (Join), and 8.15 (all three). You may also throw in any additional examples you feel illustrate relevant aspects of your implementation.
3. Note that some of the Relational Algebra operations create a relation with a new schema from that of their operands. (You should know which these are. . . ) But if tuples are implemented using structs, how do you create instances of these new “on-the-fly” relations? The answer is that you should solve the problem yourself by hand so that you know the schemas needed by your examples. Then add appropriate structure definitions to your program to allow you to do the examples. This is one of many differences between what you need to do for this project and a real database framework.
