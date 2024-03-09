#pragma once

#ifndef _CIPHER_H_
#define _CIPHER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"
#include "Range.h"

// Vigenere keys E(0) / D(26)
#define ENCRYPT 0
#define DECRYPT 26

#define BUFFER_LEN 1024
#define WORD_SEPARATOR ",.? \n\r"
#define TO_UPPER(c) ((c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c)

// Reads data from the specified file and constructs an AVL tree.
void 		buildTreeFromFile		(const char * file, Tree *tree);
// Reads the input file, encrypts its contents using the provided element as a key,
// and saves the encrypted data to the output file (Vigenere CODE - encryptCharacter).
void 		printKey				(const char * file, Range *elem);
// Reads the input file, encrypts its contents using the provided element as a key,
// and saves the encrypted data to the output file (Vigenere CODE - encryptCharacter).
void 		encrypt					(const char * infile, const char * outfile, Range *elem);
// Reads the input encrypted file, decrypts its contents using the provided key,
// and saves the decrypted data to the output file (Vigenere CODE - decryptCharacter).
void 		decrypt					(const char * infile, const char * outfile, Range *elem);

#endif /* _CIPHER_H_ */