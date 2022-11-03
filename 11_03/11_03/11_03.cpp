// 11_03.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "11_03.h"

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

    // 프로그램을 실행할 때 : Ctrl + F5
    // 디버깅 모드로 실행할 때 : F5 or 로컬 Windows 디버거

    // 브레이크 포인트(중단점) 설정/해제 : F9
    // 지금 실행하려는(실행된 상태X) 라인의 위치
    // 한 줄 단위로 실행시키고자 할때 : F10
    // 디버깅 모드 즉시 중단 : SHIFT + F5

    int x = 0;
    x = x + 23476;
    x = x++;


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1103, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1103));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1103));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1103);
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

// 스레드 함수 원형 : DWORD WINAPI 함수명(LPVOID 변수명)
//  함수 반환값이 DWORD이기 때문에 반드시 return 0; 반환해야 함
//  return 0;의 0의 의미 : 프로세스/스레드 return 0 ==> 정상 종료
//                        다른 값인 경우, 이유가 있다. -9 ==> 강제 종료

// 마우스의 좌표
LPARAM g_lParam;

// HWND를 param으로 전달 받는 것으로 설정
DWORD WINAPI drawLines(LPVOID param)
{
    HWND hWnd = (HWND)param;
    HDC hdc;
    int x, y, i;
    int hp = 35;

    //MessageBox(hWnd, L"불렸음", L"훗", MB_OK);
    x = LOWORD(g_lParam);
    y = HIWORD(g_lParam);

    hdc = GetDC(hWnd);

    for (i = 0; i < y; i++)
    {
        //hp--;
        if (0 == hp)
        {
            // 0. 좋지 않은 경우 : ExitThread() 실행하지 않고 종료 (강제 종료)
            //return 0;
            // 1. 스레드의 동작 종료
            //break;
            // 2. 스레드 스스로 종료
            ExitThread(0);
        }
        MoveToEx(hdc, x, 0, NULL);
        LineTo(hdc, x, i);
        Sleep(30);
    }

    ReleaseDC(hWnd, hdc);

    // 스레드가 정상 종료되기 전에 자원정리까지 요청하는 형태
    ExitThread(0);
    return 0;
}



HANDLE g_handle[1000] = { NULL, };  // 스레드의 핸들

int g_index;

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

    case WM_RBUTTONDOWN:
    {
        //SuspendThread(g_handle);

        // Base Thread 일시 중단
        SuspendThread(GetCurrentThread());
        /*
        for(int i = 0; i < 1000; i++)
            SuspendThread(g_handle[i]);
            */
    }
        break;

    case WM_KEYDOWN:
    {
        for (int i = 0; i < 1000; i++)
            ResumeThread(g_handle[i]);

        // 스레드 내부에서 자신을 종료할 때 사용
        // 현재 위치에서 ExitThread() 호출하면, 대상은 Base Thread가 됨
        // 즉, Base Thread가 종료되면, 프로그램 자체가 종료
        //ExitThread(0);
    }
        break;

    case WM_LBUTTONDOWN:
    {
        DWORD tid;      // 스레드 생성 후, 스레드의 ID를 반환 받는 변수

        g_lParam = lParam;

        g_handle[g_index++] = CreateThread(NULL, 0, drawLines, hWnd, 0, &tid);
        // 에러 처리
        if (NULL == g_handle)
        {
            MessageBox(hWnd, L"스레드 생성 실패", L"저런", MB_OK);
            break;
        }

        /*
        // 스레드의 일시 정지
        SuspendThread(handle);

        // delay : 3초 정도 대기
        Sleep(3000);

        // 스레드의 동작 재개
        ResumeThread(handle);
        */
    }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
