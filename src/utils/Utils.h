#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/AVLTree.h"
#include "../include/Cipher.h"
#include "../include/Range.h"

// AVLTree 
void avlFixUp(Tree *tree, TreeNode *root);
int levelNode(Tree *tree, void *elem);

int freqNode(Tree *tree, TreeNode *root);
TreeNode* maxFreqNode(Tree *tree);

void deleteSingleNode(Tree *tree, TreeNode *node);
void insertIntoLinkedList(TreeNode *list, TreeNode *node);
void insertElement(Tree *tree, TreeNode *node, TreeNode *parent);

// Range
void insertWord(Tree *tree, const char *word, int *startOffset);
void processLine(Tree *tree, const char *line, int *startOffset);

char transformCharacter(char character, Range *elem, size_t *idx, int encrypt);

Range* createRange(void);
void expandRangeIndex(Range* range);
void addToRangeIndex(Range* range, int value);

#endif /* _UTILS_H_ */
