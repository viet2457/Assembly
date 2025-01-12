#include <stdio.h>
#include <stdlib.h>

int main() {
    // Cấp phát bộ nhớ cho một chuỗi
    char *str = (char *)malloc(10 * sizeof(char));
    
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Đặt giá trị cho chuỗi
    snprintf(str, 10, "Hello");

    // In chuỗi ra màn hình
    printf("String: %s\n", str);
    
    // Giải phóng bộ nhớ
    free(str);
    
    return 0;
}
