#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void followfirst(char c, int c1, int c2);
void follow(char c);
void findfirst(char c, int q1, int q2);

// Global variables
int count = 8, n = 0, m = 0;
char calc_first[10][100];
char calc_follow[10][100];
char production[10][10];
char f[10], first[10];

int main() {
    // Initialize the grammar
    strcpy(production[0], "E=TR");
    strcpy(production[1], "R=+TR");
    strcpy(production[2], "R=#");
    strcpy(production[3], "T=FY");
    strcpy(production[4], "Y=*FY");
    strcpy(production[5], "Y=#");
    strcpy(production[6], "F=(E)");
    strcpy(production[7], "F=i");

    // Initialize calc_first and calc_follow arrays
    for (int k = 0; k < 10; k++) {
        memset(calc_first[k], '!', sizeof(calc_first[k]));
        memset(calc_follow[k], '!', sizeof(calc_follow[k]));
    }

    // Calculate First sets
    for (int k = 0; k < count; k++) {
        char c = production[k][0];
        n = 0; // Reset for new First calculation
        findfirst(c, 0, 0);
        printf("First(%c) = { ", c);
        for (int lark = 0; lark < n; lark++) {
            printf("%c", first[lark]);
            if (lark < n - 1) {
                printf(", ");
            }
        }
        printf(" }\n");
    }

    // Calculate Follow sets
    for (int e = 0; e < count; e++) {
        char ck = production[e][0];
        m = 0; // Reset for new Follow calculation
        follow(ck);
        printf("Follow(%c) = { ", ck);
        for (int lark = 0; lark < m; lark++) {
            printf("%c", f[lark]);
            if (lark < m - 1) {
                printf(", ");
            }
        }
        printf(" }\n");
    }

    return 0;
}

void follow(char c) {
    if (production[0][0] == c) {
        f[m++] = '$'; // Add $ to the Follow of the start symbol
    }
    for (int i = 0; i < count; i++) {
        for (int j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    // Calculate the first of the next Non-Terminal in the production
                    followfirst(production[i][j + 1], i, (j + 2));
                }
                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    // Calculate the follow of the Non-Terminal in the L.H.S. of the production
                    follow(production[i][0]);
                }
            }
        }
    }
}

void findfirst(char c, int q1, int q2) {
    if (!isupper(c)) { // The case where we encounter a Terminal
        first[n++] = c; // Add terminal to First set
    }
    for (int j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0') {
                    first[n++] = '#'; // Epsilon
                } else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    // Recursion to calculate First of New Non-Terminal
                    findfirst(production[q1][q2], q1, (q2 + 1));
                } else {
                    first[n++] = '#'; // Epsilon
                }
            } else if (!isupper(production[j][2])) {
                first[n++] = production[j][2]; // Terminal
            } else {
                // Recursion to calculate First of New Non-Terminal
                findfirst(production[j][2], j, 3);
            }
        }
    }
}

void followfirst(char c, int c1, int c2) {
    if (!isupper(c)) {
        f[m++] = c; // Add terminal to Follow set
    } else {
        int i = 0, j = 1;
        for (i = 0; i < count; i++) {
            if (calc_first[i][0] == c) break; // Find First set for c
        }
        while (calc_first[i][j] != '!') {
            if (calc_first[i][j] != '#') {
                f[m++] = calc_first[i][j]; // Add to Follow
            } else {
                if (production[c1][c2] == '\0') {
                    follow(production[c1][0]); // Case where we reach the end of a production
                } else {
                    followfirst(production[c1][c2], c1, c2 + 1); // Recursion
                }
            }
            j++;
        }
    }
}

