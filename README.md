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
## Modify the numbers to apply any sorting algorithm

1. Find the longest number. O(n)
2. Extend all numbers to the length twice that of the number from step 1 by writing them repeatedly, and put them in a tuple with the original number. For example if the longest number is 7767 and there is a 776, write 77677767 and 77677677 for them respectively. O(2kn)
   By writing the numbers this way we basically make the numbers with the highest digits also the highest numbers, which allows us to use any standard sorting algorithm.
3. Because we now have the property we're looking for in the numbers themselves, we can apply an algorithm that is not comparison based.
   This allows us to use radix sort, which in cases of short numbers, very large arrays and no memory limitations theoretically allows us to beat O(n log n), namely we get O(2kn).
4. Just go through the sorted list from highest to lowest and use the saved original values from the tuples to construct the number we're looking for. O(n)

Becase k is a constant in practical applications, this means the runtime of this algorithm would theoretically be O(n). However because the point at which 2k and log n would be equal is at very large array sizes, this approach will rarely outperform n log n.

## Modify the comparison function of a suitable sorting algorithm
