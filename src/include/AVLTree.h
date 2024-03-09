#pragma once

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Func.h"

#define INIT_LEN 1
#define max(a, b) (((a) >= (b))?(a):(b))

typedef struct TreeNode {
    void *elem;               // Pointer to element.
    void *value;              // Pointer to value.
    int height;           	  // Node height.

    struct TreeNode *parent;  // Parent node.
    struct TreeNode *left;    // Left child.
    struct TreeNode *right;   // Right child.

    struct TreeNode *end;     // Pointer to end node.
    struct TreeNode *next;    // Pointer to next node.
    struct TreeNode *prev;    // Pointer to previous node.
} TreeNode;

typedef struct Tree {
    TreeNode *root;                 /* Pointer to first node in the dictionary. */
	Func 	 lambda;               /* Choose function depending on request.   */
    size_t 	 size;                /* The number of nodes in the dictionary. */
} Tree;

// Similar to lambda functions.
// Requests: create, delete, and compare elements and values.
#define CREATE tree->lambda.create
#define DELETE tree->lambda.delete
#define COMPARE tree->lambda.compare

// Create a new tree with the provided functions for:
// element creation, deletion, value creation, deletion, and comparison.
Tree* 			createTree			(Create createElem, Delete deleteElem,
									 Create createVal,  Delete deleteVal,
									 Compare compare);
// Destroy the entire tree, including all nodes and associated data.
void 			destroyTree			(Tree *tree);
// Create a new tree node with the given element and value.
TreeNode* 		createTreeNode		(Tree *tree, void *elem, void *value);
// Destroy a specific tree node and its associated data.
void 		    destroyTreeNode		(Tree *tree, TreeNode *del);
// Check if the tree is empty (contains no nodes).
int 			isEmpty				(Tree *tree);
// Search for a node with a specific element in the tree starting from the given root.
TreeNode* 		search				(Tree *tree, TreeNode *root, void *elem);
// Find and return the node with the minimum element value in the tree.
TreeNode* 		minimum				(TreeNode *root);
// Find and return the node with the maximum element value in the tree.
TreeNode* 		maximum				(TreeNode *root);
// Find and return the successor node of a given node in the tree.
TreeNode* 		successor			(TreeNode *root);
// Find and return the predecessor node of a given node in the tree.
TreeNode* 		predecessor			(TreeNode *root);
// Insert a new node with the provided element and value into the tree.
void 			insertNode			(Tree *tree, void *elem, void *value);
// Delete a node with a specific element from the tree.
void 			deleteNode			(Tree *tree, void *elem);
// Update the height of a tree node, used for AVL balancing.
void 			updateHeight		(TreeNode *fix_node);
// Get the balance factor of a tree node, used for AVL balancing.
int 			getBalanceTree	    (TreeNode *fix_node);
// Perform a left rotation on the tree to maintain AVL balance.
void 			avlRotateLeft		(Tree *tree, TreeNode *fix_node);
// Perform a right rotation on the tree to maintain AVL balance.
void 			avlRotateRight		(Tree *tree, TreeNode *fix_node);

#endif /* _TREE_H_ */