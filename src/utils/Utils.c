#include "Utils.h"

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Fix the tree object after insertion of one node.
 * 
 * @param tree Pointer to a tree object.
 * @param root Pointer to a tree node, address to start fixing the AVL Tree.
 */
void avlFixUp(Tree *tree, TreeNode *root) {
	// Check if input is valid.
	if (!tree || !root) return;

	while (root) {
		updateHeight(root);
		// Balance factor of each root node and sub-trees.
		int balance = getBalanceTree(root);
		int leftBalance = getBalanceTree(root->left);
		int rightBalance = getBalanceTree(root->right);
		// Left sub-tree is unbalanced.
		if (balance > 1 && leftBalance >= 0) {
			avlRotateRight(tree, root);
		}
		// Right sub-tree is unbalanced.
		if (balance < -1 && rightBalance <= 0) {
			avlRotateLeft(tree, root);
		}
		// Left-Right sub-tree is unbalanced.
		if (balance > 1 && leftBalance < 0) {
			avlRotateLeft(tree, root->left);
			avlRotateRight(tree, root);
		}
		// Right-Left sub-tree is unbalanced.
		if (balance < -1 && rightBalance > 0) {
			avlRotateRight(tree, root->right);
			avlRotateLeft(tree, root);
		}
		root = root->parent;
	}
}

/**
 * @brief Calculate the frequency of a node with the same element in the tree.
 * Counts the number of nodes in the tree that have the same element as the provided root node.
 * 
 * @param tree Pointer to an tree object.
 * @param root The root node to compare elements with.
 * @return The frequency of nodes with the same element as root in the tree.
 */
int freqNode(Tree *tree, TreeNode *root) {
	// Corner case.
    if (root) return 0;

	int freq = 0;
	TreeNode *pass = root;
    // Pass through nodes and calculate frequency of the given `root` node.
	while (pass && !COMPARE(pass->elem, root->elem))
		++freq, pass = pass->next;

    // Return the frequency.
	return freq;
}

/**
 * @brief Find the node with the maximum frequency of occurrence in the tree.
 * Searches the tree and identifies the node with the maximum frequency of occurrence of its element.
 * 
 * @param tree Pointer to an tree object.
 * @return The node with the maximum frequency of occurrence, or NULL if the tree is empty.
 */
TreeNode* maxFreqNode(Tree *tree) {
	// Check if input is valid.
    if (!tree || !tree->root) return NULL;

	int maxFreq = -1;
	TreeNode *maxFreqNode = NULL;
	TreeNode *minNode = minimum(tree->root);

    // Start to find in increasing order the node with maximum frequency from minimum to maximum.
	while (minNode) {
		int freq = freqNode(tree, minNode);

		if (freq >= maxFreq) {
			maxFreqNode = minNode;
			maxFreq = freq;
		}

		minNode = minNode->end->next;
	}

    // Return the maximum frequency.
	return maxFreqNode;
}

/**
 * @brief Calculate the level of a node with a specified element in the tree.
 * Determines the level of a node in the tree with the provided element.
 * 
 * @param tree Pointer to an tree object.
 * @param elem The element whose level needs to be calculated.
 * @return The level of the node with the given element, or 0 if the element is not found in the tree.
 */
int levelNode(Tree *tree,  void *elem) {
    // Corner case.
	if (!tree || !tree->root) return 0;

	int level = 1;
	TreeNode *pass = tree->root;

    // Pass through nodes and calculate the level of the given `root` node.
	while (pass) {
		if (COMPARE(pass->elem, elem) > 0) pass = pass->left, level++;
		else if (COMPARE(pass->elem, elem) < 0) pass = pass->right, level++;
		else return level;
	}

    // Node is not found.
	return 0;
}

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Transform a character based on a given element and operation (encryption/decryption).
 * Performs a character transformation using the provided element as a key.
 * The `encrypt` parameter determines whether to perform encryption or decryption.
 * 
 * @param character The character to be transformed.
 * @param elem      The element used as the encryption or decryption key.
 * @param idx       A pointer to the index within the element for key rotation.
 * @param method    Set to 0 for encryption, 26 for decryption.
 * @return The transformed character ENCRYPTED/DECRYPTED.
 */
char transformCharacter(char character, Range *elem, size_t *idx, int method) {
    // Check if the character is not: a space, a newline, or a carriage return.
    if ((character != ' ') && (character != '\n') && (character != '\r')) {
        // Calculate the shift amount based on encryption / decryption.
        int shift = method ? elem->index[*idx] : -elem->index[*idx];
        // Apply the shift to the character, ensuring it stays within the range of uppercase letters.
        char transformedChar = ((TO_UPPER(character) - 'A' + shift + 26) % 26) + 'A';
        (*idx)++;
        // Wrap the index if it exceeds the size of the element.
        if (*idx == elem->size) {
            *idx = 0;
        }
        return transformedChar;
    }
    return character;
}

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Deletes a single node from the tree.
 * Removes a single node from the tree, updating its parent and child pointers
 * as well as the linked list of nodes.
 * 
 * @param tree The tree from which to delete the node.
 * @param node The node to be deleted.
 */
void deleteSingleNode(Tree *tree, TreeNode *node) {
    // Get the parent and the child of the node to be deleted.
    TreeNode *parent = node->parent;
    TreeNode *child = (node->left) ? node->left : node->right;

    // Update the parent's child pointer to point to the appropriate child
    // (or NULL if there's no child).
    if (parent)
        (parent->right == node) ? (parent->right = child) : (parent->left = child);
    else
        tree->root = child;

    // Update the child's parent pointer to point to the parent
    // (or NULL if there's no parent).
    if (child) child->parent = parent;

    // Update the linked list of nodes, removing the node from it.
    node->prev ? (node->prev->next = node->next) : (tree->root = node->next);
    if (node->next) node->next->prev = node->prev;

    // Destroy the node and rebalance the AVL tree.
    destroyTreeNode(tree, node);
    avlFixUp(tree, parent);

    // Decrease the size of the tree.
    tree->size--;
}

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Inserts a node into a linked list.
 * Inserts a node into a linked list, maintaining the order of the list.
 * 
 * @param list The linked list where the node should be inserted.
 * @param node The node to be inserted.
 */
void insertIntoLinkedList(TreeNode *list, TreeNode *node) {
    // Set the next pointer of the new node to the current first node in the list.
    node->next = list->end->next;
    // If there is a next node, update its previous pointer to point to the new node.
    if (node->next) node->next->prev = node;
    // Update the list's end to the new node.
    list->end->next = node;
    // Update the previous pointer of the new node to point to the list's end.
    node->prev = list->end;
    // Update the list's end to be the new node.
    list->end = node;
}

/**
 * @brief Inserts an element into the tree.
 * Inserts a node into the tree as a child of the parent node.
 * The insertion maintains the order of elements in the tree.
 * 
 * @param tree   The tree where the element should be inserted.
 * @param node   The node to be inserted.
 * @param parent The parent node to which the element should be attached.
 */
void insertElement(Tree *tree, TreeNode *node, TreeNode *parent) {
    // Compare the elements to determine:
    // if the new node should be placed as the left or right child.
    if (COMPARE(parent->elem, node->elem) > 0) {
        parent->left = node;
        // Update the next and previous pointers of the new node.
        // Maintain the linked list.
        node->next = parent;
        node->prev = parent->prev;

        // If there's a previous node.
        // Update its next pointer to point to the new node.
        if (parent->prev) parent->prev->next = node;
        // Update the parent's previous pointer to point to the new node.
        parent->prev = node;
    } else {
        parent->right = node;
        // Update the previous and next pointers of the new node.
        // Maintain the linked list.
        node->prev = parent;
        node->next = parent->end->next;

        // If there's a next node.
        // Update its previous pointer to point to the new node.
        if (parent->end->next) parent->end->next->prev = node;
        // Update the parent's linked list end to be the new node.
        parent->end->next = node;
    }
}

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Insert a word into the AVL tree.
 * Inserts a word (string) into the AVL tree, associating it with an offset value.
 * 
 * @param tree   Pointer to an tree object.
 * @param word   The word (string) to insert into the tree.
 * @param offset A pointer to an integer that represents the offset value to associate with the word.
 */
void insertWord(Tree *tree, const char *word, int *offset) {
    insertNode(tree, (void *)word, (void *)offset);
    // After the word is inserted, modify the offset.
    *offset += (int)strlen(word);
}

/**
 * @brief Process a line of text and insert words into the AVL tree.
 * Processes a line of text, tokenizes it into words, and inserts each word into the AVL tree.
 * It also updates the offset value for each inserted word.
 * 
 * @param tree   Pointer to an tree object.
 * @param line   The line of text to process.
 * @param offset A pointer to an integer that represents the current offset value.
 */
void processLine(Tree *tree, const char *line, int *offset) {
    // Make a copy of the line to avoid modifying the original string.
    char *lineCopy = strdup(line);

    if (!lineCopy) {
        // Handle memory allocation [ERR]:.
        printf("[ERR]: at strdup...\n");
        exit(EXIT_FAILURE);
    }

    char *word = NULL;
    word = strtok(lineCopy, WORD_SEPARATOR);

    while (word) {
        // Insert the word into the tree.
        insertWord(tree, word, offset);
        // Get the next word.
        word = strtok(NULL, WORD_SEPARATOR);
    }

    // Free the copy of the line.
    free(lineCopy);
}

/* -------------------------------------------------------------------------------------------------------- */

/**
 * @brief Create a new Range structure.
 * Allocates memory for a Range structure and initializes its fields.
 * 
 * @return A pointer to the newly created Range structure, or NULL if memory allocation fails.
 */
Range* createRange(void) {
    Range* range =(Range *)malloc(sizeof(*range));

	// Check if range was allocated successfully.
    if (range) {
		// Default values new range allocated.
        range->size = 0;
        range->capacity = INIT_LEN;
        range->index = malloc(sizeof(*range->index) * range->capacity);
        // Handle [ERR]: reallocation.
        if (!range->index) {
            printf("[ERR]: at malloc...\n");
            exit(EXIT_FAILURE);
        }
    }

    return range;
}

/**
 * @brief Expand the index array of a Range structure.
 * Increases the capacity of the index array in a Range structure by doubling its size.
 * 
 * @param range A pointer to the Range structure to expand.
 */
void expandRangeIndex(Range* range) {
    // Double capacity size and reallocate range size.
    range->capacity *= 2;
    range->index = realloc(range->index, sizeof(*range->index) * range->capacity);
    // Handle [ERR]: reallocation.
    if (!range->index) {
        printf("[ERR]: at realloc...\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Add a value to the index array of a Range structure.
 * Adds an integer value to the index array of a Range structure,
 * automatically expanding the array if it's already at capacity.
 * 
 * @param range A pointer to the Range structure to which the value should be added.
 * @param value The integer value to add to the index array.
 */
void addToRangeIndex(Range* range, int value) {
    // The maximum capacity was 
    if (range->size == range->capacity) {
        expandRangeIndex(range);
    }
    range->index[range->size] = value;
    range->size++;
}

/* -------------------------------------------------------------------------------------------------------- */
