#include <stdio.h>
#include <windows.h>

int main() {
    SYSTEMTIME st;
    GetLocalTime(&st);  // Lấy thời gian địa phương
    printf("Thoi gian dia phuong : %02d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);
    return 0;
    
}