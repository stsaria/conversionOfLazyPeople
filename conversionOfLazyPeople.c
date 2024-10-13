#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <math.h>

int getCharValue(char c) {
    if (isalpha(c)) {
        return tolower(c) - 'a' + 1;
    } else if (isdigit(c)) {
        return (int)round((c - '0' + 1) * 4.67);
    } else {
        return 0;
    }
}

void mixPhrases(const char *str1, const char *str2, char *mixed) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int mixedIndex = 0;
    int index1 = 0, index2 = 0;

    while (index1 < len1 || index2 < len2) {
        char char1 = (index1 < len1) ? str1[index1] : '\0';
        char char2 = (index2 < len2) ? str2[index2] : '\0';

        int value1 = getCharValue(char1);
        int value2 = getCharValue(char2);

        if (value1 > value2) {
            mixed[mixedIndex++] = char1;
            index1++;
        } else if (value1 < value2) {
            mixed[mixedIndex++] = char2;
            index2++;
        } else {
            mixed[mixedIndex++] = char1;
            index1++;
            index2++;
        }
    }
    mixed[mixedIndex] = '\0';
}

void hashPhrase(const char *mixed, unsigned char *hashOutput) {
    SHA256((unsigned char *)mixed, strlen(mixed), hashOutput);
}

void printHash(unsigned char *hashOutput) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashOutput[i]);
    }
    printf("\n");
}

int main() {
    char phrase1[256], phrase2[256];
    char mixed[512];
    unsigned char hashOutput[SHA256_DIGEST_LENGTH];

    printf("please enter the first phrase: ");
    fgets(phrase1, sizeof(phrase1), stdin);
    phrase1[strcspn(phrase1, "\n")] = 0;

    printf("please enter the second phrase: ");
    fgets(phrase2, sizeof(phrase2), stdin);
    phrase2[strcspn(phrase2, "\n")] = 0;

    mixPhrases(phrase1, phrase2, mixed);
    hashPhrase(mixed, hashOutput);

    printf("mixed phrase: %s\n", mixed);
    printf("hash result: ");
    printHash(hashOutput);

    return 0;
}

