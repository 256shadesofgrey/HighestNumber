# About the project
This is a task that was given to me as part of a job interview. This is my solution, and I give no guarantee that it is correct, or efficient as was requested. This is merely my best effort at the time.

# Task
The questions should be answered in C++, in the most efficient way you can, all answers should be explained in detail.

Given an array of integer numbers, arrange the elements of the array in a way that forms the highest possible number. For example, given [10, 7, 76, 415], you should return 77641510.

# Usage
The program can be used in 4 ways.

1. Calling the program with no parameters will make it generate an array of random numbers to combine.

   ex: `./HighestNumber`

2. Piping a sequence of integers to the program will use that sequence as the array to be combined.

   ex: `echo 10 7 76 415 | ./HighestNumber`

3. Passing a list of numbers to the program as parameters will use them as the array to be combined.

   ex: `./HighestNumber 10 7 76 415`

4. You can also generate an array with random numbers with a given length. To do that make first parameter alphanumeric, and give in the second parameter the array length.

   ex: `./HighestNumber set 10`

# Thought process and ideas

