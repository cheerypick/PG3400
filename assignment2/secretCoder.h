/* This library has three functions. Two implement encoding with and without d condition and one to decode encoded message.
Encoded messages are based on 0-indexing, that means, the letter on position 1 in key file will get encoded as [0].
Library uses randomly chosen indexes to encode letters, so the same letter can get different indexes each time to exclude frequency analysis-based crack.
Method signatures as follow:
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <dirent.h> 

char *encode( char *inputMessageFile,  char *keyFile, int *status); // This form returns char * array of encoded stream and status into the
// reference.

char *encodeWithD(char *messageFile, char *keyFile, int d, int *status); //This forms returns char *array of encoded stream and status into the reference, 
//as well it uses different d-conditions for adjacent codes. Previous function encode uses this implementation with d set to 0 by default.

char *decode(char *encodedMessage, char *keyFile, int *status); //This functions takes char array as encoded message and returns the decoded variant, and status as the reference.

char *getStringFromFile(char *fileName);

char *filterInput(char *key);

char *findFirstWordByLength(char *stringToSearch, int minLength);
