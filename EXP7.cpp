#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[10], gram[10][10], input[10];
int size, sizei, sizes;

// Function to get grammar rules from user
void getGram() { 
    int i;
    char ch;
    printf("\nEnter Number of Rules: "); 
    scanf("%d", &size); 
    printf("\nEnter Rules as 'E=E+T': \n"); 
    for (i = 0; i < size; i++) {
        scanf("%s%c", gram[i], &ch); 
    } 
    for (i = 0; i < size; i++) {
        printf("\n%s", gram[i]);
    }
}

// Function to get input string from user
void getInput() { 
    char ch; 
    printf("\nEnter size of input by element: "); 
    scanf("%d", &sizei); 
    sizei += 1; // To include the '$'
    printf("\nEnter Input as 'a+b' followed by '$': "); 
    scanf("%s%c", input, &ch);
    printf("\nInput is %s", input); 
}

// Function to validate and check the top of the stack
char validate() {
    int i, flag = 0, pos;
    char ch = 'q'; 

    printf("\n\tStackTop: %c\n\tStack: %s", stack[sizes - 1], stack);

    for (i = 0; i < size; i++) {
        if (stack[sizes - 1] == gram[i][2]) {
            flag = 1; 
            pos = i; 
            break; 
        } 
    }

    if (flag == 1) {
        ch = gram[pos][0]; // Get the non-terminal on the left side of the production
        printf("\nReduce %s", gram[pos]); 
    }

    return ch; 
}

// Function to apply the operation of shifting and reducing
void applyOp() { 
    char ch;
    sizes = 1; // Initialize stack size
    stack[0] = '$'; // Initialize stack with the bottom symbol

    for (int i = 0; i < sizei; i++) {
        if (input[i] != '$') {
            stack[sizes] = input[i];
            printf("\nShift %c", input[i]);
            input[i] = ' '; // Mark as processed
            sizes++; // Increment stack size
        }

        // Validate the top of the stack for reduction
        ch = validate();
        if (ch != 'q') {
            sizes--; // Reduce stack size
            stack[sizes - 1] = ch; // Replace the top of the stack with the non-terminal
        }
    }

    // Final state of the stack after processing all input
    printf("\nFinal Stack: %s\n", stack);
}

// Main function
int main() {
    stack[0] = '$'; // Initialize stack with the bottom symbol
    sizes = 1; // Start stack size with the bottom symbol
    getGram();
    getInput(); 
    applyOp();

    return 0;
}

