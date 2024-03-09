#pragma once

#ifndef _RANGE_H_
#define _RANGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"

#define INIT_LEN 1
#define LETTER_LEN 26

// Structure to represent a range of values.

typedef struct Range {
	int *index;          /* Array of integer values.   */
	size_t size;	    /* Current size of the range. */
	size_t capacity;   /* Capacity of the range.     */	
} Range;

// Function to perform a level-based key query on a tree.
Range* 		levelKeyQuery		(Tree* tree);
// Function to perform an inorder key query on a tree.
Range* 		inorderKeyQuery		(Tree* tree);
// Function to perform a range-based key query on a tree.
Range* 		rangeKeyQuery		(Tree* tree, const char* const left, const char* const right);

#endif /* _RANGE_H_ */