# AlgorithmProblems
Contains three solutions of well known algorthmic problems
# Data Structures and Algorithms Repository

This repository contains solutions for various data structures and algorithms exercises implemented in C. The solutions are organized into three folders: `c202`, `c204`, and `c206`, each focusing on a specific topic.

## Folder Structure

- `c202`: Stack Implemented by Array
    - This folder contains solutions and implementations for a stack data structure using an array. You will find source code and documentation for creating and manipulating a stack using an array-based approach.

- `c204`: Infix to Postfix Conversion
    - Inside this folder, you can explore solutions and code for converting infix expressions to postfix notation. There are implementations and explanations of the algorithm used for this conversion.

- `c206`: Double Linked List
    - The `c206` folder is dedicated to solutions related to a double linked list. It includes source code for creating, traversing, and manipulating a double linked list data structure.

# `c202`: Stack Implemented by Array in C

This repository contains C code for implementing a stack data structure using an array. The code is a solution to the assignment `c202 - Zásobník znaků v poli` as part of the Algorithms (IAL) course at FIT VUT in Brno. The reference implementation was provided by Petr Přikryl in 1994, and it has been modified and improved by various contributors over the years.

## Introduction

The code in this repository implements a character stack using a dynamic array. The stack is represented by a `Stack` data structure, with the dynamic array `array` indexed up to a maximum value of `STACK_SIZE`. The `topIndex` field points to the top element of the stack.

## Folder Structure

- `c202`: Stack Implemented by Array
  - This folder contains the C code for implementing a stack using an array.
  - The code includes functions for initialization, checking if the stack is empty, checking if the stack is full, getting the top element, popping elements from the stack, pushing elements onto the stack, and disposing of the stack.
  - The code also includes error handling to detect and report stack-related errors.
# c204.c - Infix to Postfix Expression Converter

## Introduction
`c204.c` is an implementation of a C program for converting an infix mathematical expression into a postfix expression. This program utilizes a stack data structure, which is implemented in the `c202.h` and `c202.c` files. It assumes that you have successfully implemented the stack operations using the provided stack ADT (Abstract Data Type) from `c202.c`.

This program is part of the "Algorithms and Data Structures (IAL)" course at FIT VUT in Brno. The goal is to demonstrate your understanding of stack-based expression conversion.

## Implementation Details
The `c204.c` file contains the following functions:

1. `infix2postfix`: Converts an infix expression into a postfix expression. The result is stored as a character array.

2. `untilLeftPar`: A helper function to empty the stack until a left parenthesis is encountered.

3. `doOperation`: A helper function to handle operators and their priorities.

4. `eval`: Evaluates the result of a postfix expression, taking variable values into account.

## Usage
- Include the necessary header files, including `c202.h`.
- Implement the `infix2postfix` function by following the provided algorithm.
- The program is designed to handle expressions containing addition, subtraction, multiplication, division, variables, numbers, and parentheses.

## Important Notes
- Ensure that the stack operations provided in `c202.c` are correctly implemented, as this program relies on them.
- Make sure to initialize the stack correctly using the `Stack_Init` function.
- Handle memory allocation and deallocation appropriately to avoid memory leaks.

# `c206`: Doubly Linked List 

This repository contains the implementation of a doubly linked list (DLL) data structure in the C programming language. The code defines a set of functions to manipulate and manage a DLL.

## Functions

The code provides the following functions for working with the doubly linked list:

- **DLL_Init**: Initializes an empty doubly linked list.
- **DLL_Dispose**: Deletes all elements in the list and deallocates memory.
- **DLL_InsertFirst**: Inserts a new element at the beginning of the list.
- **DLL_InsertLast**: Inserts a new element at the end of the list.
- **DLL_First**: Sets the first element as the active element.
- **DLL_Last**: Sets the last element as the active element.
- **DLL_GetFirst**: Retrieves the value of the first element.
- **DLL_GetLast**: Retrieves the value of the last element.
- **DLL_DeleteFirst**: Deletes the first element.
- **DLL_DeleteLast**: Deletes the last element.
- **DLL_DeleteAfter**: Deletes the element after the active element.
- **DLL_DeleteBefore**: Deletes the element before the active element.
- **DLL_InsertAfter**: Inserts a new element after the active element.
- **DLL_InsertBefore**: Inserts a new element before the active element.
- **DLL_GetValue**: Retrieves the value of the active element.
- **DLL_SetValue**: Modifies the value of the active element.
- **DLL_Next**: Moves the activity to the next element.
- **DLL_Previous**: Moves the activity to the previous element.
- **DLL_IsActive**: Checks if the list is active.

## Error Handling

The code uses the `DLL_Error` function to handle errors. If an illegal operation is performed, the `DLL_Error` function is called to print an error message.

## Usage

You can use this doubly linked list implementation in your C programs by including the provided header file and using the functions defined in this source file.

Example usage:

```c
#include "c206.h"

int main() {
    DLList myList;
    DLL_Init(&myList);
    
    // Insert, manipulate, and manage the list using the functions.

    DLL_Dispose(&myList); // Clean up the list when done.
    
    return 0;
}


