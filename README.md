# CreateWindow

## MFC  
MFC란? -> Microsoft Foundation Class  
(쉽게 말해, win32 API를 쉽게 사용하도록 클라스들이 모여있는 도서관이다.)

##Chapter 1 - Windows Programming Model  
win32 API는 기본적으로 메세지 기반 방식이다.  

![chaper_1_shot](https://user-images.githubusercontent.com/80387186/148035857-a3ddca70-9ec6-4e1c-9745-093165427ec2.PNG)  

win32 API 구조를 보면  
```
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
    LoadStringW(hInstance, IDC_WIN32PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT));

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
```
while 문 안에서 계속해서 메세지 루프가 돌면서 돌아가게 된다.  

##Chapter 2 - MFC CWnd Class
CObject -> CCmdTarget -> CWnd 순으로 상속받게된다.  
Cwnd 아래에 다양한 함수들이 존재한다. 

##Chapter 3 - MFC UI framework basic  
SDI Framework (Single Document Interface)
![chapter_3_shot](https://user-images.githubusercontent.com/80387186/148041688-229db4b6-9518-4591-919b-0c8f480eb34a.PNG)  
![chapter_3_shot2](https://user-images.githubusercontent.com/80387186/148041917-0cde775b-7cf6-47ff-bd06-f821ea5dc688.PNG)  
기본적으로 MFC 구조는 
App, Doc, View, Frame으로 구성되어있다.  
1 App은 전체적인 것.  
2 Doc은 문서와 관련 된 것.  
3 View와 Frame은 보이는 것.  

---
**[중요!!] 여기서 메세지는 뷰와 프레임만 받을 수 있다.**  
**[중요!!] view만 부모를 바꿀 찬스를 준다.**  
**[중요!!] 재정의 시, 해당 내용이 cpp와 header 그리고 Message_MAp(cpp파일 내)에 추가 된다.**  
**[중요!!] 전역 선언 시 Afx를 붙인다. MessageBox() -> X AfxMessageBox() -> O**  
```
// 이런식으로 메세지맵 안에도 재정의 내용이 추가 됨.
BEGIN_MESSAGE_MAP(CCreateWindowView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()
```
**[중요!!] 상호 간에 접근 할 시에는 특정 함수를 호출하면 되는데 Frame과 App은 Afx로 불러올 수 있다.  
AfxGetMainWnd() AfxGetApp() 나머지는 위의 shot2 사진 참고**  

---

- SDI의 구성 순서 (상속)  
CObject -> CCmdTarget -> CWinThread -> CWinApp  

- CFrameWnd의 구성 순서 (상속)  
CObject -> CCmdTarget -> CWnd -> CFrameWnd

## Chapter 4 - MFC SDI application flow  
App 생성자-> InitInstance -> Doc 생성자 -> Frame 생성자-> 기타등등 ->  Run  
CMainFrame::Onclose -> 기타등등 -> OnDestroy -> 소멸자 -> ExitInstance() 로 마무리 된다.  
PostMessage()와 SendMessage()로 CMainFrame::WindowProc()에 전달하여 명령 실행한다.  

## Chapter 5 - Keyboard & Message  
WM_KEYDOWN & OnKeyDown()  
WM_KEYUP & OnKeyUP()  
WM_CHAR & OnChar)  
WM_SYSKEYDOWN & OnSysKeyDown()  
WM_SYSKEYUP & OnSysKeyUP()  
WM_SYSCHAR & OnSysChar)  
**좌표를 찍을 때, 스크린 좌표와 클라이언트 좌표가 있다. 주로 클라이언트 좌표를 이용해야한다.**  
```
// 스크린 좌표
m_wndChild.GetWindowRect(&rectChild);
// 클라이언트 좌표 
ScreenToClient(&rectChild);
```
## Chapter 7 - Mouse & Message  
다른 repo에 있는 https://github.com/ohjiwoo123/MouseDemo/blob/master/MouseDemo/MouseDemoView.cpp  
CMouseDemoView.cpp 코드 참고 @@ 

---
## Special Chapter - 전역변수,지역변수,정적변수(Static),맴버변수  
변수 종류|지역성(Locality)|생명주기(LifeTime)
:---------: | :---------: | :---------:
전역변수 | Wide | Long
지역변수 | Narrow | Short
정적변수 | Narrow | Long
맴버변수 | Middle | Middle  

1 전역변수 (Global Variable)  
- 모든 곳에서 다 불러서 사용할 수 있는 변수  
- (장점) - 편하게 사용 가능하다.  
- (단점) - 메모리 용량을 불필요하게 많이 사용한다.  

2 지역변수 (Local Variable)  
- 지역(함수) 내에서만 사용할 수 있는 변수  
- (장점) - 지역 내에서 깔끔하게 사용 가능
- (단점) - 지역(범위) 밖에서는 사용을 못함.  

3 정적변수 (Static Variable)  
- 함수가 끝나면 죽지만 내용은 살아있음.  
- (장점) - static으로 변수를 선언하여 계속 값을 이어서 받을 수 있다. 
- (단점) - 지역변수와 마찬가지로 특정 점위 밖에서는 사용하지 못한다.  
```
// Static 변수 예시
#include <stdio.h>

void increaseNumber()
{
    static int num1 = 0;     // 정적 변수 선언 및 값 초기화

    printf("%d\n", num1);    // 정적 변수 num1의 값을 출력

    num1++;    // 정적 변수 num1의 값을 1 증가시킴
}

int main()
{
    increaseNumber();    // 0
    increaseNumber();    // 1
    increaseNumber();    // 2
    increaseNumber();    // 3: 정적 변수가 사라지지 않고 유지되므로 값이 계속 증가함

    return 0;
}
```
4 맴버변수 (Member Variable)  
- 특정 클래스나 맴버내에서만 사용할 수 있는 변수  
- (장점) 전역변수의 단점을 잘 커버해준다. 프로그래밍을 잘하는 사람은 맴버 변수를 잘 활용한다고 함.  
- (단점) 딱히 없는 거 같다.  
```
class CMouseDemoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMouseDemoView() noexcept;
	DECLARE_DYNCREATE(CMouseDemoView)

// 특성입니다.
public:
	CMouseDemoDoc* GetDocument() const;

// 작업입니다.
public:
	int m_x;
	int m_y;
	BOOL m_DRAGFLAG;
}
```
MFC에서는 위와 같이 헤더파일에서 class 내에서 private, public 등 활용하여 맴버변수를 선언한다.  
**[중요!!] C11 부터는 선언과 동시에 초기화가 가능하다고는 하나,  
원래 정석은 선언은 클래스 헤더파일에서 하고  
초기화는 아래와 같이 cpp 생성자에서 한다.**
```
CMouseDemoView::CMouseDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// 생성자에서 가장 빠르게 부를 수 있다. 
	m_x = 100;
	m_y = 200;
	m_DRAGFLAG = FALSE;
}
```
