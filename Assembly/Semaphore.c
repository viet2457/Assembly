#include <windows.h>
#include <stdio.h>

HANDLE hSemaphore;

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    // Đợi cho semaphore có sẵn
    WaitForSingleObject(hSemaphore, INFINITE);

    // Truy cập tài nguyên chia sẻ
    printf("Thread %d is accessing the shared resource.\n", GetCurrentThreadId());

    // Giải phóng semaphore
    ReleaseSemaphore(hSemaphore, 1, NULL);
    return 0;
}

int main() {
    // Khởi tạo semaphore, giá trị đếm ban đầu là 2 (cho phép 2 luồng đồng thời truy cập)
    hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);

    // Tạo các luồng
    CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
    CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
    CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);  // Luồng này sẽ phải đợi

    // Đợi các luồng kết thúc
    Sleep(1000);

    CloseHandle(hSemaphore);
    return 0;
}
