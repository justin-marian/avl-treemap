# AVL Treemap

## Description

This library offers an accessible and straightforward API, making it simple to manage **AVL trees**, **encrypt** and **decrypt data**, and conduct **range-based queries**. Each module **Tree, Cipher, and Range** is designed with user-friendliness in mind, providing clear functions for complex operations.

## Tree Module

The Tree module is the core of the AVL Treemap library, focusing on providing robust and efficient management of AVL trees—a type of self-balancing binary search tree. This module ensures that operations such as insertions, deletions, and lookups are performed in logarithmic time complexity, making it ideal for applications that require fast data retrieval and manipulation. Here are some highlights:

| Function | Description |
|:--------:|------------|
| `createTree` | Initializes a new AVL tree. It requires function pointers for creating, deleting, and comparing both elements and values, allowing for customized data handling within the tree. |
| `destroyTree` | Frees all memory associated with the tree, including all its nodes and any data attached to them. Ensures that no memory leaks occur when a tree is no longer needed. |
| `createTreeNode` | Creates a new tree node with a specified element and value. allocates memory for a new node and initializes it with the given parameters. |
| `destroyTreeNode` | Deletes a specific node from the tree and frees the memory associated with its element and value. It ensures the tree's integrity by properly reconnecting any child nodes to maintain the AVL balance property. |
| `isEmpty` | Checks if the tree contains no nodes. It returns true if the tree is empty, providing a quick way to check the tree's status. |
| `search` | Searches for a node with a specific element, starting from the provided root node. It returns the node if found, offering an efficient way to locate data in the tree. |
| `minimum` | Finds the node with the smallest element in the tree. It returns minimum value, such as range queries. |
| `maximum` | Identifies the node with the largest element in the tree. Similar to `minimum`, but for finding the maximum value, aiding in range-based operations. |
| `successor` `predecessor`  | Determines the successor of a given node, which is the node with the next-highest value, and for the predecessor of a given node is the next-lowest value. |
| `insertNode` | Inserts a new node with the specified element and value into the tree. This function maintains the AVL balance through rotations if necessary, ensuring optimal tree height. |
| `deleteNode` | Removes a node with a specific element from the tree. It handles the re-balancing of the tree to preserve the AVL property after deletion. |
| `updateHeight` | Recalculates and updates the height of a given node. This is crucial for maintaining the balance of the tree, as it affects the balance factor calculation. |
| `getBalanceTree` | Calculates the balance factor of a node, which is the difference in height between its left and right subtrees. This information is used to decide when and how to rotate the tree to maintain its balance. |
| `avlRotateLeft` `avlRotateRight` | These functions perform left and right rotations on a specified node. Rotations are a critical part of maintaining the AVL tree's balance, ensuring that operations remain efficient. |

## Cipher Module

The Cipher module leverages the structured data within AVL trees to perform encryption and decryption tasks, applying the Vigenere cipher—a method of encrypting alphabetic text by using a simple form of polyalphabetic substitution. This module stands out for:

| Function            | Description                                                                                           |
|:-------------------:|-------------------------------------------------------------------------------------------------------|
| `buildTreeFromFile` | Reads data from a specified file and uses it to construct an AVL tree. The data structure can then be used for fast lookups or to support cryptographic operations.                |
| `printKey`          | Reads a specified file to print or display the encryption/decryption key. Useful for verifying the key used in cryptographic operations.                                   |
| `encrypt`           | Encrypts the contents of an input file using the Vigenere cipher technique, with an element from the AVL tree acting as the key. The encrypted data is then saved to an output file. |
| `decrypt`           | Decrypts the contents of an input file that was previously encrypted with the Vigenere cipher, using the same element as the key for decryption. The decrypted data is saved to an output file. |

## Range Module

The Range module extends the library's functionality by introducing range-based queries on AVL trees, facilitating complex data analysis and retrieval operations. This module is particularly useful for applications that need to extract or analyze subsets of data based on specific criteria. Key functionalities include:

| Function           | Description                                                                                           |
|:------------------:|-------------------------------------------------------------------------------------------------------|
| `levelKeyQuery`    | Performs a level-based key query on an AVL tree. This function is designed to return a Range object that represents a set of values (keys) based on their levels within the tree. It can be used to analyze or process the distribution of keys across different tree levels.         |
| `inorderKeyQuery`  | Executes an inorder traversal of the AVL tree to gather keys within a Range. This method collects keys in a sorted manner, which can be used for sorted data retrieval or analysis.       |
| `rangeKeyQuery`    | Conducts a query for keys within a specified range in the AVL tree, returning a Range object that contains keys falling within the specified bounds. This function is useful for filtering or extracting specific subsets of keys based on certain criteria.       |

## Utils Module

| Function               | Description                                                                                                         |
|:----------------------:|---------------------------------------------------------------------------------------------------------------------|
| `avlFixUp`             | Rebalances the AVL tree after insertion or deletion to maintain its self-balancing properties.                      |
| `levelNode`            | Determines the level (depth) of a node with a specified element within the tree.                                    |
| `freqNode`             | Calculates the frequency of nodes with the same element as the given node within the tree.                          |
| `maxFreqNode`          | Identifies the node whose element occurs most frequently within the tree.                                           |
| `deleteSingleNode`     | Removes a specific node from the tree, adjusting links and rebalancing as necessary.                                |
| `insertIntoLinkedList` | Inserts a node into a linked list structure within the tree, maintaining the order of nodes.                        |
| `insertElement`        | Adds a new element to the tree, creating a node and placing it in the correct position to maintain AVL balance.     |
| `insertWord`           | Inserts a word into the tree, often used for building a lexical tree from text data.                                |
| `processLine`          | Processes a line of text, breaking it into words and inserting each into the tree, updating offsets accordingly.    |
| `transformCharacter`   | Transforms a character for encryption or decryption, using a Vigenere cipher-like method.                           |
| `createRange`          | Initializes a new Range structure, typically used for indexing or storing a range of values.                        |
| `expandRangeIndex`     | Increases the capacity of the Range structure's index array, accommodating more values.                             |
| `addToRangeIndex`      | Adds a new value to the Range structure's index array, expanding it if necessary.                                   |
