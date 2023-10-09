// sp_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "sp_1.h"

// library for ALPHABLEND
#pragma comment(lib, "Msimg32.lib")


#define MAX_LOADSTRING 100

#define IDT_TIMER_UP  1
#define IDT_TIMER_DOWN 2
#define IDT_TIMER_RIGHT 3
#define IDT_TIMER_LEFT 4





// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
// my Global Variables
HBITMAP hBmp;

class Sprite {

public:
    int x = 200;
    int y = 100;
    int width = 100;
    int height = 137;
    CONST int SPEED = 20;

    BOOL inBounce = FALSE;
    CONST int BOUNCE_SPEED = 20;
    CONST int BOUNCE_LENGTH = 80;


    BOOL isBmp = FALSE;

    void moveUp(LONG topBound, HWND hwnd) {
        if (y - SPEED <= topBound)
        {
            y = 0;
            InvalidateRect(hwnd, NULL, TRUE);


            SetTimer(hwnd,             // handle to main window 
                IDT_TIMER_UP,            // timer identifier 
                40,                 // 10-second interval 01.sec 
                (TIMERPROC)NULL);     // no timer callback
            inBounce = TRUE;

        }
        else
        {
            y -= SPEED;
        }
    }

    void moveDown(LONG downBound, HWND hwnd) {

        if (y + height + SPEED >= downBound)
        {
            y = downBound - height;
            InvalidateRect(hwnd, NULL, TRUE);

            SetTimer(hwnd, IDT_TIMER_DOWN, 40, (TIMERPROC)NULL);
            inBounce = TRUE;

        }
        else
        {
            y += SPEED;
        }

    }

    void moveRight(LONG rightBound, HWND hwnd) {
        if (x + width + SPEED >= rightBound)
        {
            x = rightBound - width;
            InvalidateRect(hwnd, NULL, TRUE);

            SetTimer(hwnd, IDT_TIMER_RIGHT, 40, (TIMERPROC)NULL);   
            inBounce = TRUE;

        }
        else
        {
            x += SPEED;
        }
    }

    void moveLeft(LONG leftBound, HWND hwnd) {
        if (x - SPEED <= leftBound)
        {
            x = 0;
            InvalidateRect(hwnd, NULL, TRUE);


            SetTimer(hwnd, IDT_TIMER_LEFT, 40, (TIMERPROC)NULL);
            inBounce = TRUE;

        }
        else
        {
            x -= SPEED;
        }
    }

};

Sprite sprite;







// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SP1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SP1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SP1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(80, 110, 78));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SP1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}







//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CREATE:
        {
            // Load bitmap to the global variable only once 
            hBmp = (HBITMAP)LoadImage(NULL, L"../sprite_witch.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hBmp == NULL)
            {
                // Show message if bitmap wasn`t found
                ::MessageBox(NULL, __T("Load image failed"), __T("Error"), MB_OK);
            }
            else
            {
                // Remember that bitmap wasn`t found so then draw rectangle instead
                sprite.isBmp = true;
            }

            sprite.x = 200;
            sprite.y = 200;

        }
        break;
    case WM_GETMINMAXINFO:
        {
            MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;

            pMinMax->ptMinTrackSize.x = 1200;
            pMinMax->ptMinTrackSize.y = 837;
        }
        break;
    case WM_TIMER:
        {

            RECT rcClientRect;
            GetClientRect(hWnd, &rcClientRect);

            switch (wParam)
            {

                case IDT_TIMER_UP:
                    if (sprite.y == rcClientRect.top + sprite.BOUNCE_LENGTH)
                    {
                        KillTimer(hWnd, IDT_TIMER_UP);
                        sprite.inBounce = FALSE;
                    }
                    else {
                        sprite.y += sprite.BOUNCE_SPEED;
                        InvalidateRect(hWnd, NULL, TRUE);
                    }
                    return 0;

                case IDT_TIMER_DOWN:
                    if (sprite.y == rcClientRect.bottom - sprite.height - sprite.BOUNCE_LENGTH)
                    {
                        KillTimer(hWnd, IDT_TIMER_DOWN);
                        sprite.inBounce = FALSE;
                    }
                    else
                    {
                        sprite.y -= sprite.BOUNCE_SPEED;
                        InvalidateRect(hWnd, NULL, TRUE);
                    }
                    return 0;

                case IDT_TIMER_RIGHT:
                    if (sprite.x == rcClientRect.right - sprite.width - sprite.BOUNCE_LENGTH)
                    {
                        KillTimer(hWnd, IDT_TIMER_RIGHT);
                        sprite.inBounce = FALSE;
                    }
                    else
                    {
                        sprite.x -= sprite.BOUNCE_SPEED;
                        InvalidateRect(hWnd, NULL, TRUE);
                    }
                    return 0;

                case IDT_TIMER_LEFT:
                    if (sprite.x == rcClientRect.left + sprite.BOUNCE_LENGTH)
                    {
                        KillTimer(hWnd, IDT_TIMER_LEFT);
                        sprite.inBounce = FALSE;
                    }
                    else
                    {
                        sprite.x += sprite.BOUNCE_SPEED;
                        InvalidateRect(hWnd, NULL, TRUE);
                    }
                    return 0;
            }
        }
        break;
    case WM_MOUSEWHEEL:
        {

       
        if (sprite.inBounce == false)
        {

            int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);

            RECT rcClientRect;
            GetClientRect(hWnd, &rcClientRect);

            if (LOWORD(wParam) == MK_SHIFT)
            {

                if (wheelDelta > 0)
                {
                    sprite.moveLeft(rcClientRect.left, hWnd);
                }
                else
                {
                    sprite.moveRight(rcClientRect.right, hWnd);
                }
            }
            else
            {


                if (wheelDelta > 0)
                {
                    sprite.moveUp(rcClientRect.top, hWnd);
                }
                else
                {
                    sprite.moveDown(rcClientRect.bottom, hWnd);
                }
            }

            InvalidateRect(hWnd, NULL, TRUE);
        }

        }
        break;
    case WM_PAINT:
        {
        
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            HDC bmpDC = CreateCompatibleDC(hdc);
            SelectObject(bmpDC, hBmp);
            BLENDFUNCTION blendf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };  
            AlphaBlend(hdc, sprite.x, sprite.y, sprite.width, sprite.height, bmpDC, 0, 0, 100, 137, blendf);
            DeleteDC(bmpDC);
            //DeleteObject(hBmp);

            EndPaint(hWnd, &ps);

           
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
