#include <windows.h>

// Hàm xử lý thông điệp
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 10, 10, "Hello, World!", 13); // Vẽ text lên cửa sổ
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0); // Thoát vòng lặp thông điệp
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam); // Xử lý mặc định
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc; // Gán hàm xử lý thông điệp
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";

    // Đăng ký lớp cửa sổ
    if (!RegisterClassA(&wc)) {
        return -1;
    }

    // Tạo cửa sổ
    HWND hwnd = CreateWindowA("MyWindowClass", "My Window",
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                              500, 300, NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Vòng lặp thông điệp
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
