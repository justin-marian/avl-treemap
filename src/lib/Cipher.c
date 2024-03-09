#include "../include/Cipher.h"
#include "../utils/Utils.h"

/**
 * @brief Build an AVL tree from data stored in a input file.
 * Reads data from the specified file and constructs an AVL tree.
 * 
 * @param file The name of the file to read data from.
 * @param tree A pointer to the AVL tree to build.
 */
void buildTreeFromFile(const char *file, Tree *tree) {
	// Check if input is valid.
    if (!file || !tree) {
        printf("Invalid file or tree pointer.\n");
        return;
    }

    FILE *fin = fopen(file, "r");
    // Handle [ERR]: file opening.
    if (!fin) {
        printf("[ERR]: opening the file for reading.\n");
        return;
    }

    // Determine size of each word.
    int offset = 0;
    char buff[BUFFER_LEN];
    // Each line, and each word from each line is processed and added in AVL tree.
    while (fgets(buff, sizeof(buff), fin))
        processLine(tree, buff, &offset);

    fclose(fin);
}

/**
 * @brief Process the contents of an input file and save the result in an output file.
 * Reads the input file, processes its contents using the provided element as a key,
 * and saves the processed data to the output file.
 * The operation (encryption or decryption) is determined by the `method` parameter.
 * 
 * @param infile   The name of the input file.
 * @param outfile  The name of the output file.
 * @param elem     The element used as the encryption or decryption key.
 * @param method  Set to 1 for encryption, 0 for decryption.
 */
void processFile(const char *infile, const char *outfile, Range *elem, int method) {
    FILE *fin = fopen(infile, "r");
    FILE *fout = fopen(outfile, "w");
    // Handle [ERR]: files opening.
    if (!fin) {
        printf("[ERR]: opening input file.\n");
        return;
    }
    if (!fout) {
        printf("[ERR]: opening output file.\n");
        fclose(fin);
        return;
    }

    size_t idx = 0;
    char *buffer = malloc(BUFFER_LEN + 1);
    // Process all words from the buffer based on a range index.
    while (fgets(buffer, BUFFER_LEN, fin)) {
        for (size_t pos = 0; pos < strlen(buffer); pos++) {
            char processedChar = transformCharacter(buffer[pos], elem, &idx, method);
            fprintf(fout, "%c", processedChar);
        }
    }

    free(buffer);
    fclose(fin);
    fclose(fout);
}

/**
 * @brief Wrapper over the processFile function encrypts the input file with the key `elem`.
 * The result is placed in output file.
 * 
 * @param infile  The name of the input file.
 * @param outfile The name of the output (encrypted) file.
 * @param elem    The element used as the encryption key.
 */
void encrypt(const char *infile, const char *outfile, Range *elem) {
    processFile(infile, outfile, elem, ENCRYPT);
}

/**
 * @brief Wrapper over the processFile function decrypts the input file with the key `elem`.
 * The result is placed in output file.
 * 
 * @param infile  The name of the input (encrypted) file.
 * @param outfile The name of the output (decrypted) file.
 * @param elem    The element used as the decryption key.
 */
void decrypt(const char *infile, const char *outfile, Range *elem) {
    processFile(infile, outfile, elem, DECRYPT);
}

/**
 * @brief Print the decryption key to a file.
 * Prints the decryption element's content to a specified file.
 * 
 * @param file The name of the file to write the key to.
 * @param elem The element containing the decryption key.
 */
void printKey(const char * file, Range *elem) {
	FILE *fin = fopen(file, "w");
    // Handle [ERR]: files opening.
	if (!elem) {
		fprintf(fin, "No element provided!\n");
		fclose(fin);
		return;
	}

	fprintf(fin, "Decryption element of length %lu is:\n", elem->size);

    // Save the encrypted key range as string in a file.
	for (size_t pos = 0; pos < elem->size; pos++) {
		fprintf(fin, "%d ", elem->index[pos] % 26);
		if ((pos + 1) % 10 == 0) {
			fprintf(fin, "\n");
		}
	}

	fclose(fin);
}
