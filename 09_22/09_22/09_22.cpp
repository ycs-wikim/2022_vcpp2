// 09_22.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "09_22.h"

#include <stdlib.h>     // 랜덤 함수 사용
#include <time.h>       // 랜덤 시드 값을 변경

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY0922, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0922));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0922));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0922);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 내 캐릭터
RECT g_me;
// 상대 캐릭터
RECT g_you;
// 그라운드
RECT g_ground;
// 아이템
RECT g_item;
// 게임 시간
int g_gametime;
// 게임 시간 표시 사각형
RECT g_game;

// 치트키
bool g_c = false;
// 게임 진행 상태
bool g_status = true;

//타이머 설정값
int g_timer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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

    case WM_LBUTTONDOWN:
    {
        int x, y;
        RECT is, tmp;
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        tmp.left = x;
        tmp.top = y;
        tmp.right = x + 1;
        tmp.bottom = y + 1;

        if (true == IntersectRect(&is, &tmp, &g_me))
        {
            //MessageBox(hWnd, L"눌렀다!", L"ok", MB_OK);
        }

    }
        break;

    case WM_LBUTTONUP:
    {
        int x, y;
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        g_me.left = x;
        g_me.top = y;
        g_me.right = x + 100;
        g_me.bottom = y + 100;

        InvalidateRect(hWnd, NULL, TRUE);
    }
        break;

    /// 키를 입력하면 전달되는 메시지
/*    case WM_KEYDOWN:
    {
        MessageBox(hWnd, L"키가 눌렸어요", L"54rtg", MB_OK);
    }

    break;
*/
    case WM_KEYDOWN:
    {
        if (false == g_status)
            break;

        switch (wParam)
        {
        case VK_SPACE:
            g_c = true;
            break;
        case VK_LEFT:
            g_me.left -= 10;
            g_me.right -= 10;
            break;
        case VK_RIGHT:
            g_me.left += 10;
            g_me.right += 10;
            break;
        case VK_UP:
            g_me.top -= 10;
            g_me.bottom -= 10;
            break;
        case VK_DOWN:
            g_me.top += 10;
            g_me.bottom += 10;
            break;
        }

        // 계산된 좌표가 그라운드를 벗어나는지 확인
        if (10 > g_me.left)
        {
            g_me.left = 10;
            g_me.right = 110;
        }
        if (10 > g_me.top)
        {
            g_me.top = 10;
            g_me.bottom = 110;
        }
        if (500 < g_me.right)
        {
            g_me.right = 500;
            g_me.left = 400;
        }
        if (500 < g_me.bottom)
        {
            g_me.bottom = 500;
            g_me.top = 400;
        }

        // 아이템 획득 확인
        RECT is;

        if (true == IntersectRect(&is, &g_me, &g_item))
        {
            //MessageBox(hWnd, L"먹었다.", L"아이템", MB_OK);
            g_gametime += 3;
            g_item.left = 10 + (rand() % 390);
            g_item.top = 10 + (rand() % 390);
            g_item.right = g_item.left + 100;
            g_item.bottom = g_item.top + 100;
        }

        InvalidateRect(hWnd, NULL, true);
    }
    break;

    case WM_TIMER:
    {
        if (1 == wParam)
        {
            RECT is;

            if (g_timer >= 200)
                g_timer -= 100;
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 1, g_timer, NULL);

            if (g_me.left < g_you.left)
            {
                g_you.left -= 10;
                g_you.right -= 10;
            }
            else
            {
                g_you.left += 10;
                g_you.right += 10;
            }
            if (g_me.top < g_you.top)
            {
                g_you.top -= 10;
                g_you.bottom -= 10;
            }
            else
            {
                g_you.top += 10;
                g_you.bottom += 10;
            }
            if (false == g_c)
            {
                if (true == IntersectRect(&is, &g_me, &g_you))
                {
                    KillTimer(hWnd, 1);
                    MessageBox(hWnd, L"잡혔습니다.", L"KIM윤재", MB_OK);
                }
            }

            
        }
        else if (2 == wParam)
        {
            g_gametime--;   // 게임 시간 감소
            if (0 >= g_gametime)
            {
                g_status = false;
                g_gametime = 0;
                KillTimer(hWnd, 1);
                KillTimer(hWnd, 2);
            }
            g_game.right = 10 + (g_gametime * 10);
        }
        InvalidateRect(hWnd, NULL, true);
    }
    break;
    case WM_CREATE:
    {
        // 랜덤 시드 값 초기화
        srand(time(NULL));

        // 게임 시간 초기화
        g_gametime = 10;

        g_timer = 1000;
        SetTimer(hWnd, 1, g_timer, NULL);
        SetTimer(hWnd, 2, 1000, NULL);

        g_me.left = 10;
        g_me.top = 10;
        g_me.right = 110;
        g_me.bottom = 110;

        g_you.left = 300;
        g_you.top = 300;
        g_you.right = 400;
        g_you.bottom = 400;

        g_ground.left = 10;
        g_ground.top = 10;
        g_ground.right = 500;
        g_ground.bottom = 500;

        g_item.left = 10 + (rand() % 390);
        g_item.top = 10 + (rand() % 390);
        g_item.right = g_item.left + 100;
        g_item.bottom = g_item.top + 100;

        g_game.left = 10;
        g_game.top = 520;
        g_game.right = g_gametime * 10;
        g_game.bottom = 560;
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 그라운드
            Rectangle(hdc, g_ground.left, g_ground.top, g_ground.right, g_ground.bottom);

            // 아이템
            Ellipse(hdc, g_item.left, g_item.top, g_item.right, g_item.bottom);

            // 내 캐릭터
            Rectangle(hdc, g_me.left, g_me.top, g_me.right, g_me.bottom);
            
            // 상대 캐릭터
            Rectangle(hdc, g_you.left, g_you.top, g_you.right, g_you.bottom);

            // 게임 시간 표시
            Rectangle(hdc, g_game.left, g_game.top, g_game.right, g_game.bottom);
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

// 정보 대화 상자의 메시지 처리기입니다.
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
