#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Biến toàn cục
bool DebugMode = false;

// Hàm xử lý thông điệp của cửa sổ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: // Menu "Open"
                    MessageBox(hWnd, "You clicked Open!", "Menu", MB_OK);
                    break;
                case 2: // Menu "Exit"
                    DestroyWindow(hWnd);
                    break;
                case 1001: // Button
                    MessageBox(hWnd, "Button clicked!", "Info", MB_OK);
                    break;
            }
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            Rectangle(hdc, 50, 50, 200, 200); // Vẽ hình chữ nhật
            TextOut(hdc, 60, 60, "Hello, World!", 13); // In chữ
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Hàm WinMain
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    HWND hWnd;              // Handle của cửa sổ ứng dụng
    MSG msg;                // Thông điệp của ứng dụng
    WNDCLASS wc = {0};      // Cấu trúc lớp cửa sổ

    // Kiểm tra dòng lệnh để bật chế độ debug
    if (strcmp(lpCmdLine, "-debug") == 0) {
        DebugMode = true;
        AllocConsole(); // Mở một console cho debug
        freopen("CONOUT$", "w", stdout);
        printf("Debug mode active. Application starting...\n");
    }

    // Đăng ký lớp cửa sổ
    wc.lpfnWndProc = WndProc;                     // Hàm xử lý thông điệp
    wc.hInstance = hInstance;                    // Handle của ứng dụng
    wc.lpszClassName = "MyAppClass";             // Tên lớp cửa sổ
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Màu nền cửa sổ
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);    // Con trỏ chuột
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // Biểu tượng mặc định

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_ICONERROR);
        return -1;
    }

    // Tạo cửa sổ chính
    hWnd = CreateWindow(
        "MyAppClass",              // Tên lớp cửa sổ
        "My Application",          // Tiêu đề cửa sổ
        WS_OVERLAPPEDWINDOW,       // Kiểu cửa sổ
        CW_USEDEFAULT,             // Vị trí X
        CW_USEDEFAULT,             // Vị trí Y
        500,                       // Chiều rộng
        400,                       // Chiều cao
        NULL,                      // Không có cửa sổ cha
        NULL,                      // Không có menu
        hInstance,                 // Handle của ứng dụng
        NULL                       // Không có dữ liệu bổ sung
    );

    if (!hWnd) {
        MessageBox(NULL, "Failed to create window", "Error", MB_ICONERROR);
        return -1;
    }

    // Tạo menu cho cửa sổ
    HMENU hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, 1, "Open");
    AppendMenu(hMenu, MF_STRING, 2, "Exit");
    SetMenu(hWnd, hMenu);

    // Tạo nút trên cửa sổ
    HWND hButton = CreateWindow(
        "BUTTON", "Click Me",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hWnd, (HMENU)1001, hInstance, NULL
    );

    // Hiển thị cửa sổ
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    // Vòng lặp xử lý thông điệp
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
