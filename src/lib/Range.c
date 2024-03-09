#include "../include/Range.h"
#include "../utils/Utils.h"

/**
 * @brief Perform a level key query on the AVL tree.
 * Generates a Range containing values based on the level of nodes in the tree.
 * It extracts values from nodes at the same level as the maximum frequency node.
 * 
 * @param tree A pointer to the AVL tree to query.
 * @return A Range containing values based on the level of nodes.
 */
Range* levelKeyQuery(Tree* tree) {
    // Check if input is valid.
    if (!tree || !tree->root) return NULL;
    
    // Create a Range to store the result.
    Range* range = createRange();
    // Find the minimum node in the tree.
    TreeNode* minNode = minimum(tree->root);

    // Get the level of the maximum frequency node.
    int levelMax = levelNode(tree, maxFreqNode(tree)->elem);

    while (minNode) {
        if (levelNode(tree, minNode->elem) != levelMax) {
            minNode = minNode->end->next;
        } else {
            // Add the value from the current node to the Range.
            addToRangeIndex(range, (*(int*)minNode->value) % LETTER_LEN);
            minNode = minNode->next;
        }
    }

    // Return the generated Range.
    return range;
}

/**
 * @brief Perform a range key query on the AVL tree.
 * Generates a Range containing values that fall within the specified range of keys.
 * 
 * @param tree  A pointer to the AVL tree to query.
 * @param left  The left boundary of the key range (inclusive).
 * @param right The right boundary of the key range (inclusive).
 * @return A Range containing values within the specified key range.
 */
Range* rangeKeyQuery(Tree* tree, const char* const left, const char* const right) {
    // Check if input is valid.
    if (!tree || !tree->root) return NULL;

    // Create a Range to store the result.
    Range* range = createRange();
    // Find the minimum node in the tree.
    TreeNode* minNode = minimum(tree->root);

    // Move to the first node with a key greater than or equal to 'left'.
    while (minNode && COMPARE(minNode->elem, (void*)left) < 0) {
        minNode = minNode->end->next;
    }
    // Add values to the Range from nodes within the key range.
    while (minNode && COMPARE(minNode->elem, (void*)right) <= 0) {
        addToRangeIndex(range, (*(int*)minNode->value) % LETTER_LEN);
        minNode = minNode->next;
    }

    // Return the generated Range.
    return range;
}

/**
 * @brief Perform an in-order key query on the AVL tree.
 * Generates a Range containing values by traversing the tree in in-order.
 * 
 * @param tree A pointer to the AVL tree to query.
 * @return A Range containing values based on an in-order traversal of the tree.
 */
Range* inorderKeyQuery(Tree* tree) {
    // Check if input is valid.
    if (!tree || !tree->root) return NULL;

    // Create a Range to store the result.
    Range* range = createRange();
    // Find the minimum node in the tree.
    TreeNode* minNode = minimum(tree->root);

    // Traverse the tree in in-order and add values to the Range.
    while (minNode) {
        addToRangeIndex(range, (*(int*)minNode->value) % LETTER_LEN);
        minNode = minNode->next;
    }

    // Return the generated Range.
    return range;
}
