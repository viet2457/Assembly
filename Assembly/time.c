#include <stdio.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *tm_info;
    char buffer[26];

    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Thoi gian he thong hien tai: %s\n", buffer);
    return 0;
}