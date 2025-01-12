#include <windows.h>
#include <stdio.h>

// Hàm xử lý thông điệp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: { // Xử lý vẽ nội dung cửa sổ
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Vẽ văn bản
        TextOut(hdc, 20, 20, "Hello, Windows!", 15);

        // Vẽ hình chữ nhật
        Rectangle(hdc, 50, 50, 200, 150);

        // Vẽ hình elip
        Ellipse(hdc, 250, 50, 400, 150);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN: { // Xử lý sự kiện nhấn chuột trái
        int xPos = LOWORD(lParam); // Tọa độ X
        int yPos = HIWORD(lParam); // Tọa độ Y
        char buffer[50];
        sprintf(buffer, "Mouse clicked at (%d, %d)", xPos, yPos);
        MessageBoxA(hWnd, buffer, "Mouse Click", MB_OK);
        break;
    }
    case WM_KEYDOWN: { // Xử lý phím nhấn
        if (wParam == VK_ESCAPE) { // Thoát khi nhấn ESC
            DestroyWindow(hWnd);
        } else if (wParam == 'H') { // Hiện thông báo khi nhấn phím H
            MessageBoxA(hWnd, "You pressed H!", "Key Press", MB_OK);
        }
        break;
    }
    case WM_COMMAND: { // Xử lý menu
        switch (LOWORD(wParam)) {
        case 1: // About
            MessageBoxA(hWnd, "My First Window Application\nVersion 1.0", "About", MB_OK);
            break;
        case 2: // Exit
            DestroyWindow(hWnd);
            break;
        }
        break;
    }
    case WM_DESTROY: { // Xử lý khi cửa sổ đóng
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Hàm WinMain: Điểm vào chính của chương trình Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Tạo menu
    HMENU hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, 1, "About");
    AppendMenu(hMenu, MF_STRING, 2, "Exit");

    // Khởi tạo cấu trúc WNDCLASSA
    WNDCLASSA wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;         // Hàm xử lý thông điệp
    wc.hInstance = hInstance;         // Instance hiện tại
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "MyWindowClass"; // Tên lớp cửa sổ

    // Đăng ký lớp cửa sổ
    if (!RegisterClassA(&wc)) {
        MessageBox(NULL, "Failed to register window class!", "Error", MB_ICONERROR);
        return 1;
    }

    // Tạo cửa sổ
    HWND hWnd = CreateWindowA(
        "MyWindowClass",           // Tên lớp đã đăng ký
        "My First Window",         // Tiêu đề cửa sổ
        WS_OVERLAPPEDWINDOW,       // Kiểu cửa sổ
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, // Vị trí và kích thước
        NULL, hMenu, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // Hiển thị và cập nhật cửa sổ
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Vòng lặp thông điệp
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
