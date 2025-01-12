#include <windows.h>
#include <stdio.h>
HANDLE hMutex;

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    // Đợi cho mutex có sẵn
    WaitForSingleObject(hMutex, INFINITE);

    // Tài nguyên chia sẻ được truy cập
    printf("Thread %d is accessing the shared resource.\n", GetCurrentThreadId());

    // Giải phóng mutex
    ReleaseMutex(hMutex);
    return 0;
}

int main() {
    hMutex = CreateMutex(NULL, FALSE, NULL);

    // Tạo các luồng
    CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
    CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);

    // Đợi các luồng kết thúc
    Sleep(1000);

    CloseHandle(hMutex);
    return 0;
}
