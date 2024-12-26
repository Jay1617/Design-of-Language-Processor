
#include <stdio.h>
#include <string.h>

typedef struct {
    int isValid;
    char reason[100];
} Result;

Result solve(char s[]) {
    int n = strlen(s);

    if (n < 3 || s[0] != 'a') {
        Result res = {0, "Invalid: String must start with 'a' and have at least 3 characters."};
        return res;
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] != 'a' && s[i] != 'b') {
            Result res = {0, "Invalid: String contains characters other than 'a' and 'b'."};
            return res;
        }

        if (s[i] == 'b' && i < n - 2) {
            Result res = {0, "Invalid: 'b' found before the last two characters."};
            return res;
        }
    }

    if (s[n - 2] != 'b' || s[n - 1] != 'b') {
        Result res = {0, "Invalid: String must end with 'bb'."};
        return res;
    }

    int hasA = 0;
    for (int i = 0; i < n - 2; ++i) {
        if (s[i] == 'a') {
            hasA = 1;
            break;
        }
    }

    if (!hasA) {
        Result res = {0, "Invalid: String must contain at least one 'a' before 'bb'."};
        return res;
    }

    Result res = {1, "Valid String"};
    return res;
}

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    Result result = solve(s);
    printf("%s\n", result.reason);

    return 0;
}
