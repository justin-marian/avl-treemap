#include "../include/AVLTree.h"
#include "../utils/Utils.h"

/**
 * @brief Create a tree object.
 * 
 * @param createElem Function to create a element object.
 * @param deleteElem Function to destroy a element object.
 * @param createVal  Function to create a value object.
 * @param deleteVal  Function to destroy a value object.
 * @param compare    Function two compare two values/keys.
 * @return Tree* pointer to an allocated tree object or NULL.
 */
Tree* createTree(Create createElem, Delete deleteElem,
                 Create createVal, Delete deleteVal,
                 Compare compare) {
	// Allocate a new tree.
    Tree *tree = (Tree *)malloc(sizeof(Tree));

	// Check if tree was allocated successfully.
    if (tree) {
		// Default values new tree allocated.
        tree->size = 0;
        tree->root = NULL;
        // Assign function pointers using macros.
        CREATE.createElem = createElem;
    	CREATE.createVal = createVal;
        DELETE.deleteElem = deleteElem;
        DELETE.deleteVal = deleteVal;
        COMPARE = compare;
    }

	// Return the new allocated tree.
    return tree;
}

/**
 * @brief Create a tree node object.
 * 
 * @param tree  Pointer to an tree object.
 * @param elem  Pointer to the elem data.
 * @param value Pointer to the value data.
 * @return TreeNode* pointer to allocated tree node object or NULL.
 */
TreeNode* createTreeNode(Tree *tree, void *elem, void *value) {
	// Check if input is valid.
	if (!tree) return NULL;

	// Allocate a new tree node on heap.
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	
	// Check if tree node was allocated successfully.
	if (node) {
		// Default values new tree node allocated.
		node->height = INIT_LEN;
		node->elem = CREATE.createElem(elem);
		node->value = CREATE.createVal(value);
		node->parent = NULL; node->left = NULL; node->right = NULL;
		node->next = NULL; node->prev = NULL; node->end = NULL;
	}
	
	// Return the new allocated tree node.
	return node;
}

/**
 * @brief Check if a tree object is empty.
 * 
 * @param tree Pointer to a tree object.
 * @return 1 if tree is empty, 0 otherwise.
 */
int isEmpty(Tree *tree) {
	return tree && !tree->root;
}

/**
 * @brief Find the minimum tree node starting from `root` given node.
 * 
 * @param root Pointer to a tree node to start searching.
 * @return TreeNode* pointer to a tree node containing the min elem data.
 */
TreeNode* minimum(TreeNode *root) {
	while (root->left)
		root = root->left;
	return root;
}

/**
 * @brief Find the maximum tree node starting from `root` given node.
 * 
 * @param root Pointer to a tree node to start searching.
 * @return TreeNode* pointer to a tree node containing the min elem data.
 */
TreeNode* maximum(TreeNode *root) {
	while (root->right)
		root = root->right;
	return root;
}

/**
 * @brief Free memory for a tree node object.
 * 
 * @param tree Pointer to a tree object.
 * @param del  The tree node object to delete.
 */
void destroyTreeNode(Tree *tree, TreeNode *del) {
	// Check if input is valid.
	if (!tree || !del) return;
	// Destroy content.
	DELETE.deleteElem(del->elem);
	DELETE.deleteVal(del->value);
	// Free memory tree node.
	free(del);
}

/**
 * @brief Free all memory loaded for the tree object.
 * 
 * @param tree Pointer to an allocated tree object.
 */
void destroyTree(Tree *tree) {
	// Check if input is valid.
	if (!tree) return;

	TreeNode *minim = minimum(tree->root);
	// Iterate through all tree nodes and delete them.
	while (minim) {
		TreeNode *delete = minim;
		minim = minim->next;
		// Free tree node `delete`.
		destroyTreeNode(tree, delete);
	}

	// Free memory tree.
	free(tree);
}

/**
 * @brief Find inorder successor of the input tree node.
 * 
 * @param root Pointer to the node to find its successor.
 * @return TreeNode* pointer to inorder successor or NULL.
 */
TreeNode* successor(TreeNode *root) {
	// Check if input is valid.
	if (!root) return NULL;
	// Check if node has a right sub-tree.
	if (root->right) return minimum(root->right);
	
	// Find the succesor.
	TreeNode *find = root->parent;
	while (find && find->right == root)
		root = find, find = find->parent;

	return find;
}

/**
 * @brief Find inorder predecessor of the input tree node.
 * 
 * @param root Pointer to the node to find its predecessor.
 * @return TreeNode* pointer to inorder predecessor or NULL.
 */
TreeNode* predecessor(TreeNode *root) {	
	// Check if input is valid.
	if (!root) return NULL;
	// Check if node has a left sub-tree.
	if (root->left) return maximum(root->left);
	
	// Find the predecessor.
	TreeNode *find = root->parent;
	while (find && find->left == root)
		root = find, find = find->parent;

	return find;
}

/**
 * @brief Search for a desired elem starting from the "root".
* 
 * @param tree  Pointer to a tree object.
 * @param root 	Pointer to a tree node object, node to start searching.
 * @param elem  Pointer to an elem location.
 * @return TreeNode* pointer to a tree node containing the elem data.
 */
TreeNode* search(Tree *tree, TreeNode *root, void *elem) {
	// Check if input is valid.
	if (!tree || !root) return NULL;

	// Find the desired tree node.
	while (root) {
		if (COMPARE(root->elem, elem) >= 1) root = root->left;
		else if (COMPARE(root->elem, elem) <= -1) root = root->right;
		else if (COMPARE(root->elem, elem) == 0) return root;
	}

	// Node wasn't found.
	return NULL;
}

/**
 * @brief Update the height of a rotated tree node.
 * 
 * @param root Pointer to an allocated tree node to fix.
 */
void updateHeight(TreeNode *root) {
	// Check if input is valid.
	if (!root) return;

	int LHeight = 0, RHeight = 0;
	
	// Get left height and right height of each sub-tree.
	if (root->left) LHeight  = root->left->height;
	if (root->right) RHeight = root->right->height;
	
	// Update the tree node height.
	root->height = max(LHeight, RHeight) + 1;
}

/**
 * @brief Left rotate the sub-tree of the treenode `root`.
 *
 *   				 (x)	 LEFT      (y)
 *	 				/  \    ROTATE    /  \
 *  			   a  (y)   ----->   (x)  c
 *	   				  /  \			/  \
 *    				 b    c        a   b
 * -------------------------------------------------------------------
 * @param tree Pointer to a tree object
 * @param root Pointer to an allocated tree node to rotate left.
 */
void avlRotateLeft(Tree *tree, TreeNode *root) {
	// Check if input is valid.
	if (!tree || !root || !root->right) return;

	// NODE c is unchanged during the process (see image)!

	// Switch x with y (right child for x) tree nodes.
	TreeNode *rotate = root->right; // (y)

	// Rotate to left the right side.
	root->right = rotate->left; // (x right child is b)
	if (rotate->left) { // (y left child is b)
		rotate->left->parent = root; // (y left child is x)
	}

	// Restore the links after the rotation of x<->y.
	rotate->left = root; // (y left child is x)
	rotate->parent = root->parent; // (parent of y is the prev parent for x)
	root->parent = rotate; // (parent for x is now y)

	// Update the parent nodes for y.
	if (rotate->parent) {
		// Check on which side y will be the children based on the prev parent of x.
		if (COMPARE(rotate->elem, rotate->parent->elem) >= 1) {
			rotate->parent->right = rotate;
		} else {
			rotate->parent->left = rotate;
		}
	} else {
		tree->root = rotate; // (y is now the root node, x was the root before)
	}

	// Update to all nodes the height.
	updateHeight(root);
	updateHeight(rotate);
}

/**
 * @brief Left rotate the sub-tree of the treenode `root`.
 *
 *     				 (y)    RIGHT      (x)
 *	   				/  \   ROTATE     /  \
 *   			  (x)  c   ----->    a  (y)
 *	 			 /  \		     	   /  \
 *  			a   b                 b   c
 * -------------------------------------------------------------------
 * @param tree Pointer to a tree object
 * @param root Pointer to an allocated tree node to rotate left.
 */
void avlRotateRight(Tree *tree, TreeNode *root) {
	// Check if input is valid.
	if (!tree || !root || !root->left) return;

	// NODE a is unchanged during the process (see image)!

	// Switch y with x (left child for y) tree nodes.
	TreeNode *rotate = root->left;

	// Rotate to right the left side.
	root->left = rotate->right; // (y left child is c)
	if (rotate->right) { // (x right child is b)
		rotate->right->parent = root; // (x right child is y)
	}

	// Restore the links after the rotation of y<->x.
	rotate->right = root; // (x right child is y)
	rotate->parent = root->parent; // (parent of x is the prev parent for y)
	root->parent = rotate; // (parent for y is now x)

	// Update the parent nodes for x.
	if (rotate->parent) {
		// Check on which side x will be the children based on the prev parent of y.
		if (COMPARE(rotate->elem, rotate->parent->elem) >= 1) {
			rotate->parent->right = rotate;
		} else {
			rotate->parent->left = rotate;
		}
	} else {
		tree->root = rotate; // (x is now the root node, y was the root before)
	}

	// Update to all nodes the height.
	updateHeight(root);
	updateHeight(rotate);
}

/**
 * @brief Get the balance factor of the tree.
 * 
 * @param root Pointer to node to find its balance factor.
 * @return the balance factor.
 */
int getBalanceTree(TreeNode *root) {
	if (!root || (!root->left && !root->right)) return 0;
	if (root->left && !root->right) return root->left->height;
	if (!root->left && root->right) return -root->right->height;
	return (root->left->height - root->right->height);
}

/**
 * @brief Insert a new node into the tree obejct.
 * 
 * @param tree  Pointer to a tree object.
 * @param elem  Pointer to a elem data.
 * @param value Pointer to a value data.
 */
void insertNode(Tree *tree, void *elem, void *value) {
	// Check if input is valid.
    if (!tree) return;

	// Create new node with given data.
    TreeNode *node = createTreeNode(tree, elem, value);
    if (!node) return;

	// Tree now has 1 node, the new one.
    if (isEmpty(tree)) {
        node->end = node;
        tree->root = node;
        tree->size = 1;
        return;
    }

	// Pass through each node from tree.
    TreeNode *pass = tree->root;
    TreeNode *parent = NULL;

	// Find position to add new tree node.
    while (pass) {
        parent = pass;
        int comp = COMPARE(elem, pass->elem);
        if (comp > 0) pass = pass->right;
        else if (comp < 0) pass = pass->left;
        else break;
    }

	// Node already exists, insert it in linked list.
    if (pass) {
        insertIntoLinkedList(pass, node);
    } else {
		// Otherwise insert it in the tree.
        node->end = node;
        node->parent = parent;
        insertElement(tree, node, parent);
        // Fix the AVL tree, balance factor moddified.
		avlFixUp(tree, parent);
    }

	// Increment the size of the tree.
    tree->size++;
}

/**
 * @brief Delete a node from tree.
 * 
 * @param tree Pointer to a tree object.
 * @param elem Pointer to element location to delete from tree.
 */
void deleteNode(Tree *tree, void *elem) {
	// Check if input is valid.
    if (!tree || !elem) return;

	// Create find node with given data.
    TreeNode *found = search(tree, tree->root, elem);
    if (!found) return;

	// Check if the found node is the only one.
    if (found->end == found) {
		// The found node has left & right child.
        if (found->left && found->right) {
            TreeNode *minim = minimum(found->right);
			// Delete the found node data.
            DELETE.deleteElem(found->elem);
            DELETE.deleteVal(found->value);
			// Replace found node with the minimum one.
            found->elem = CREATE.createElem(minim->elem);
            found->value = CREATE.createVal(minim->value);
			// Delete the minimum node.
            deleteSingleNode(tree, minim);
        } else {
			// Delete the found node directly otherwise.
			// Don't need to find replacement.
            deleteSingleNode(tree, found);
        }
    } else {
		// If the node is found in the linked list.
        TreeNode *deleteNode = found->end;
		// Remove it from the linked list.
        if (deleteNode->prev) deleteNode->prev->next = deleteNode->next;
        if (deleteNode->next) deleteNode->next->prev = deleteNode->prev;
		// Update end point address with the previous node from list.
	    found->end = deleteNode->prev;
		// Free memory deleted node, value and element.
        destroyTreeNode(tree, deleteNode);
		// Decrement the tree size.
        tree->size--;
    }
}
