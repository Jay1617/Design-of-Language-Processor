#include <stdio.h>
#include <string.h>

int isValid(char s[]) {
    int n = strlen(s);

    if (n < 3 || s[0] != 'a') {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] != 'a' && s[i] != 'b') {
            return 0;
        }

        if (s[i] == 'b' && i < n - 2) {
            return 0;
        }
    }

    if (s[n - 2] != 'b' || s[n - 1] != 'b') {
        return 0;
    }

    for (int i = 0; i < n - 2; ++i) {
        if (s[i] == 'a') {
            return 1;
        }
    }

    return 0;
}

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    if (isValid(s)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}
