// 09_08.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

// 프로젝트 생성 시 자동으로 만들어지는 헤더
#include "framework.h"
#include "09_08.h"

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

// APIENTRY : 프로그램의 시작점을 나타내는 예약어
// wWinMain : 윈도우 GUI 프로그램의 시작 함수(main()과 동일)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // OS가 만들어준 나의 정보체
                     _In_opt_ HINSTANCE hPrevInstance,  // 나와 동일한 프로그램의 정보체
                     _In_ LPWSTR    lpCmdLine,          // argc, argv와 같음
                     _In_ int       nCmdShow)           // 화면 출력 여부
{
    // 사용되지 않는 인수를 제거하는 매크로
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY0908, szWindowClass, MAX_LOADSTRING);

    // OS에 프로그램의 설정을 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0908));

    // OS가 만들어서 응용 프로그램이 실행할 정보를 담는 구조체
    MSG msg;

    // 기본 메시지 루프입니다: 무한 루프
    // OS가 전달한 메시지를 획득
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 번역
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            // 번역 ==> 응용 프로그램용
            TranslateMessage(&msg);
            // 메시지 전송
            DispatchMessage(&msg);
        }
    }

    // 프로그램 종료
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // Window Class Extention Wchar
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0908));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0908);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 설정된 상태로 동작할 것을 OS에 알림
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

   // 우리가 볼 수 있는 프로그램 화면을 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // 메인 윈도우 생성 확인
   if (!hWnd)
   {
      return FALSE;
   }

   // 기본적으로 모든 윈도우 창은 최초 설정이 보이지 않음
   // 화면에 출력해달라~ 라고 요청
   ShowWindow(hWnd, nCmdShow);
   // 변경 사항이 있다면 표시해줘~
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
                // Default Window Proc : OS에서 메시지를 처리하도록 전달
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_LBUTTONDOWN:
    {
        int x, y;   // 마우스의 좌표 값 획득을 위해

        // x 좌표 획득
        x = LOWORD(lParam);
        // y 좌표 획득
        y = HIWORD(lParam);

        HDC hdc = GetDC(hWnd);

        // 시작점 설정 API
        MoveToEx(hdc, 0, 0, NULL);
        // 끝점 설정과 동시에 그리기 API
        LineTo(hdc, x, y);

        ReleaseDC(hWnd, hdc);
    }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // HDC : Handle Device(모니터) Context
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 화면에 글자 출력 API
            TextOut(hdc, 50, 20, L"202207001 김원일", 13);

            // 시작점 설정 API
            MoveToEx(hdc, 0, 0, NULL);
            // 끝점 설정과 동시에 그리기 API
            LineTo(hdc, 300, 300);

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
