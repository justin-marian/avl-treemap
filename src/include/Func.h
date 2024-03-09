#pragma once

#ifndef _FUNC_H_
#define _FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH_ELEMENT 5

// Function pointer type definitions.

// Create function for creating elements.
typedef void* 	 (*Create)		 (void *elem);
// Delete function for destroying elements.
typedef void 	 (*Delete)		 (void *elem);
// Compare function for comparing keys.
typedef int      (*Compare)		 (void *elem1, void *elem2);

// Structure to hold function pointers.

typedef struct Functions {
    // Structure for creating elements.
    struct {
        Create createElem;         /* Function to create an elem object */
        Create createVal;          /* Function to create a value object */
    } create;

    // Structure for deleting elements.
    struct {
        Delete deleteElem;         /* Function to destroy an elem object */
        Delete deleteVal;          /* Function to destroy a value object */
    } delete;

    Compare compare;               /* Function to compare two keys */
} Func;

// Functions for creating, destroying, and comparing integers.
void*     createInt       (void* value);
void      destroyInt      (void *value);
int       compareInt      (void *value1, void *value2);
// Functions for creating, destroying, and comparing strings.
void*     createStr       (void *str);
void      destroyStr      (void *str);
int       compareStr      (void *str1, void *str2);
// Functions for creating and destroying integer indexes.
void*     createIdx       (void *index);
void      destroyIdx      (void *index);

#endif /* _FUNC_H_ */