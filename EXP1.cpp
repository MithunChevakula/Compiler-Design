#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Returns 'true' if the character is a DELIMITER
bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
            ch == '%');
}

// Returns 'true' if the character is an OPERATOR
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' || ch == '=');
}

// Returns 'true' if the string is a VALID IDENTIFIER
bool validIdentifier(char* str) {
    // An identifier cannot start with a digit or a delimiter
    if (str[0] >= '0' && str[0] <= '9') return false;
    return true;
}

// Returns 'true' if the string is a KEYWORD
bool isKeyword(char* str) {
    return (!strcmp(str, "if") || !strcmp(str, "else") ||
            !strcmp(str, "while") || !strcmp(str, "do") ||
            !strcmp(str, "break") || !strcmp(str, "continue") ||
            !strcmp(str, "int") || !strcmp(str, "double") ||
            !strcmp(str, "float") || !strcmp(str, "return") ||
            !strcmp(str, "char") || !strcmp(str, "case") ||
            !strcmp(str, "sizeof") || !strcmp(str, "long") ||
            !strcmp(str, "short") || !strcmp(str, "typedef") ||
            !strcmp(str, "switch") || !strcmp(str, "unsigned") ||
            !strcmp(str, "void") || !strcmp(str, "static") ||
            !strcmp(str, "struct") || !strcmp(str, "goto"));
}

// Returns 'true' if the string is an INTEGER
bool isInteger(char* str) {
    int i, len = strlen(str);
    if (len == 0) return false;

    for (i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

// Returns 'true' if the string is a REAL NUMBER
bool isRealNumber(char* str) {
    int i, len = strlen(str);
    bool hasDecimal = false;
    if (len == 0) return false;

    for (i = 0; i < len; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') return false;
        if (str[i] == '.') {
            if (hasDecimal) return false; // Multiple decimals
            hasDecimal = true;
        }
    }
    return hasDecimal; // Must have at least one decimal point
}

// Extracts the SUBSTRING
char* subString(char* str, int left, int right) {
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

// Parsing the input STRING
void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right])) right++;

        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]))
                printf("'%c' IS AN OPERATOR\n", str[right]);
            right++;
            left = right;
        } else if (isDelimiter(str[right]) && left != right || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr))
                printf("'%s' IS A KEYWORD\n", subStr);
            else if (isInteger(subStr))
                printf("'%s' IS AN INTEGER\n", subStr);
            else if (isRealNumber(subStr))
                printf("'%s' IS A REAL NUMBER\n", subStr);
            else if (validIdentifier(subStr))
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            else
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);

            left = right;
            free(subStr); // Free the allocated memory
        }
    }
}

// DRIVER FUNCTION
int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%[^\n]s", str);
    parse(str); // Calling the parse function

    return 0;
}

