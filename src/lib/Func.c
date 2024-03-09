#include "../include/Func.h"
#include "../utils/Utils.h"

/**
 * @brief Create an integer value.
 * 
 * @param value A pointer to the integer value.
 * @return A pointer to the created integer value.
 */
void* createInt(void* value) {
	int *l = malloc(sizeof(int));
	*l = *((int *) (value));
	return l;
}

/**
 * @brief Destroy an integer value.
 * 
 * @param value A pointer to the integer value to destroy.
 */
void destroyInt(void *value) {
	free((int*)value);
}

/**
 * @brief Compare two integer values.
 * 
 * @param value1 A pointer to the first integer value.
 * @param value2 A pointer to the second integer value.
 * @return -1 if value1 < value2, 0 if value1 == value2, 1 if value1 > value2.
 */
int compareInt(void *value1, void *value2) {
	if(*(int*)value1 < *(int*)value2) return -1;
	if(*(int*)value1 > *(int*)value2) return  1;
	return 0;
}

/**
 * @brief Create a string element with a specified length.
 * 
 * @param str A pointer to the string.
 * @return A pointer to the created string element.
 */
void* createStr(void *str){
	char *elem = malloc(LENGTH_ELEMENT + 1);
	strncpy(elem, (char *)str, LENGTH_ELEMENT);
	elem[LENGTH_ELEMENT] = '\0';
	return elem;
}

/**
 * @brief Destroy a string element.
 * 
 * @param str A pointer to the string element to destroy.
 */
void destroyStr(void *str){
	free((char *)str);
}

/**
 * @brief Compare two string elements.
 * 
 * @param str1 A pointer to the first string element.
 * @param str2 A pointer to the second string element.
 * @return -1 if str1 < str2, 0 if str1 == str2, 1 if str1 > str2.
 */
int compareStr(void *str1, void *str2) {
	if (strncmp((char *)str1,(char *)str2, LENGTH_ELEMENT) > 0)
		return 1;
	else if (strncmp((char *)str1,(char *)str2, LENGTH_ELEMENT) < 0)
		return -1;
	return 0;
}

/**
 * @brief Create an integer index.
 * 
 * @param index A pointer to the integer index.
 * @return A pointer to the created integer index.
 */
void* createIdx(void *index){
	int *idx = (int*) malloc(sizeof(int));
	*idx = *((int*) index);
	return idx;
}

/**
 * @brief Destroy an integer index.
 * 
 * @param index A pointer to the integer index to destroy.
 */
void destroyIdx(void *index){
	free(index);
}
