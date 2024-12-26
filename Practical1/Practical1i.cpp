#include <stdio.h>
#include <string.h>

typedef struct {
    int isValid;
    char reason[100];
} Result;

Result solve(char *s)
{
    int n = strlen(s);
    if (n < 2) {
        Result res = {0, "Invalid String: Length must be at least 2."};
        return res;
    }

    int b_count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'a' && s[i] != 'b') {
            Result res = {0, "String contains invalid characters."};
            return res;
        }
        if (s[i] == 'b') {
            b_count++;
            if (b_count > 2 || (b_count == 2 && i < n - 2)) {
                Result res = {0, "Only two 'b's are allowed, and they must be at the end."};
                return res;
            }
        }
    }

    if (b_count == 2 && s[n - 1] == 'b' && s[n - 2] == 'b') {
        Result res = {1, "Valid String"};
        return res;
    }

    Result res = {0, "Invalid string: The string must contain exactly two 'b's at the end."};
    return res;
}

int main()
{
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    Result result = solve(s);
    if (result.isValid) {
        printf("Valid String\n");
    } else {
        printf("Not Valid: %s\n", result.reason);
    }

    return 0;
}
