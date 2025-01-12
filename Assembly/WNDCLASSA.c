#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = {0};  // Khởi tạo cấu trúc WNDCLASSA
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;         // Hàm xử lý thông điệp
    wc.hInstance = hInstance;         // Instance hiện tại
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "MyWindowClass"; // Tên lớp cửa sổ

    if (!RegisterClassA(&wc)) {
        MessageBox(NULL, "Failed to register window class!", "Error", MB_ICONERROR);
        return 1;
    }

    HWND hWnd = CreateWindowA(
        "MyWindowClass",          // Tên lớp đã đăng ký
        "My First Window",        // Tiêu đề cửa sổ
        WS_OVERLAPPEDWINDOW,      // Kiểu cửa sổ
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, // Vị trí và kích thước
        NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
