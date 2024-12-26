#include <stdio.h>
#include <string.h>

int checkString(char *input) {
    int len = strlen(input);
    if (len < 2) {
        return 0;
    }

    int countB = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] != 'a' && input[i] != 'b') {
            return 0;
        }
        if (input[i] == 'b') {
            countB++;
            if (countB > 2 || (countB == 2 && i < len - 2)) {
                return 0;
            }
        }
    }

    return countB == 2 && input[len - 1] == 'b' && input[len - 2] == 'b';
}

int main() {
    char input[100];
    printf("Input: ");
    scanf("%s", input);

    if (checkString(input)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}
