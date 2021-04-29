// GuessNum.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "number.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	MainDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int InsStr(TCHAR *, int, int, TCHAR *);
int CheckJudge(TCHAR *);
int CheckJudgeChar(TCHAR * Str);

int CheckNum(TCHAR * Str, int num[4]);

void EnableHuman(HWND hDlg);
void EnableCom(HWND hDlg);
void DisableAll(HWND);
void ClearControls(HWND);

///////////////////////////////////////////////////////////
int Answer[4];  // ��
int TmpAns[4];  // ��ѡ��



struct TmpSol History[8]; // ��ʷ��¼
int Count; // �²����
int GameOver = 0; // ��Ϸ������־
///////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	hInst = hInstance;
	srand((unsigned)time(NULL));
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)MainDlgProc);
	return 0;
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUESSNUM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESSNUM));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESSNUM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUESSNUM);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_NEW:
				   DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, (DLGPROC)MainDlgProc);
				   break;
				case IDM_ABOUT:
				   DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, _tcslen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

// Message handler for Main box.
LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int Mode = 1; // 0 - �˲£� 1 - ���Բ�
	static HWND hCtl = NULL, hList = NULL;
//	static HPEN hPenNum = NULL;
	int nCmd;
	switch (message)
	{
		case WM_INITDIALOG:
			{
				HWND hCtl=GetDlgItem(hDlg, IDC_NUMBOX);
//				hPenNum = CreatePen(PS_SOLID, 0, (COLORREF)RGB(255,0,0));
				SendMessage(hCtl, EM_LIMITTEXT, (WPARAM)4, (LPARAM)0);
				hCtl=GetDlgItem(hDlg, IDC_JUDGEBOX);
				SendMessage(hCtl, EM_LIMITTEXT, (WPARAM)4, (LPARAM)0);
				hList = GetDlgItem(hDlg, IDC_LIST1);
				DisableAll(hDlg);
			}
			return TRUE;

		case WM_COMMAND:
			if (HIWORD(wParam) == EN_UPDATE) //|| wParam == EN_UPDATE)
			{
				if (GetDlgCtrlID((HWND)lParam) == IDC_JUDGEBOX)
				{
					static TCHAR szOld[5] = {TCHAR('\0')};
					TCHAR szBuf[6];
					//Get
					SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)5, (LPARAM)szBuf);
					if (CheckJudgeChar(szBuf) == 0)
					{
						// ������ֵ
						lstrcpy(szOld, szBuf);
					}
					else
					{
						// �ָ�ԭֵ
						SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)0, (LPARAM)szOld);
						PlaySound(TEXT("ding.wav"), 0, SND_ASYNC);
					}
				}
				return TRUE;
			}

			nCmd=LOWORD(wParam);
			if (nCmd == IDOK || nCmd == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (nCmd >= IDC_NUM0 && nCmd <= IDC_B)
			{
				// �޸������ı�������
				int Beg, End;

				TCHAR szNum[13]=TEXT("0123456789AB");
				int index = nCmd - IDC_NUM0;
				TCHAR c[2];

				c[0] = szNum[index];
				c[1] = TCHAR('\0');

				TCHAR szNumBuf[5];

				HWND hCtl; //=GetDlgItem(hDlg, IDC_NUMBOX);
				if (Mode == 0)
					hCtl=GetDlgItem(hDlg, IDC_NUMBOX);
				else // Mode == 0
					hCtl=GetDlgItem(hDlg, IDC_JUDGEBOX);

				SendMessage(hCtl, WM_GETTEXT, (WPARAM)5, (LPARAM)szNumBuf);
				SendMessage(hCtl, EM_GETSEL, (WPARAM)&Beg, (LPARAM)&End);

				if (lstrlen(szNumBuf)==4 && End == Beg)
				{
					PlaySound(TEXT("ding.wav"), 0, SND_ASYNC); 
					SetFocus(hCtl);
					return TRUE;
				}

				SendMessage(hCtl, EM_GETSEL, (WPARAM)&Beg, (LPARAM)&End);

				InsStr(szNumBuf, Beg, End, c);

				SendMessage(hCtl, WM_SETTEXT, (WPARAM)0, (LPARAM)szNumBuf);
				SendMessage(hCtl, EM_SETSEL, (WPARAM)(Beg+1), (LPARAM)(Beg+1));

				SetFocus(hCtl);

				return TRUE;
			}
			

			
			switch (LOWORD(wParam))
			{
			case IDC_JUDGE:
				{
					TCHAR szBuf[32];
//					int num[4];
					SendMessage(hCtl, WM_GETTEXT, (WPARAM)5, (LPARAM)szBuf);
//					CheckJudge(szBuf);//, num);
					if (! CheckJudge(szBuf))
					{
						MessageBox(hDlg, TEXT("�жϵ���ʽΪXAXB������XΪ0��4�����֡�"), TEXT("��ʾ"), MB_ICONSTOP);
//						SetFocus(hCtl);

					}
					else
					{
						int a=szBuf[0]-TCHAR('0');
						int b=szBuf[2]-TCHAR('0');

						History[Count].a= a;//szBuf[0]-TCHAR('0');
						History[Count].b= b;//szBuf[2]-TCHAR('0');
//						Count++;// 
						AddTemp(History, Count, TmpAns);

						wsprintf(szBuf, TEXT("%d. %d%d%d%d %dA%dB"), ++Count, 
							TmpAns[0],TmpAns[1],TmpAns[2],TmpAns[3],
							a,b);//1, 1, 1, 1, 2, 2);
						SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)szBuf);
						
						// ���Լ���������
						if (!GenTemp(TmpAns, History, Count)) // �Ҳ������õ���������
						{
							MessageBox(hDlg, TEXT("���Բ²��������4�����֣���������Ĵ𰸡�"), TEXT("��ʾ"), MB_ICONINFORMATION);
							Mode=3; // �û���������
							EnableHuman(hDlg);
							hCtl = GetDlgItem(hDlg, IDC_NUMBOX);
							SendMessage(hCtl, EM_SETSEL, 0, 4);
							SetFocus(hCtl);
							return TRUE;
						}
						else
						{
							wsprintf(szBuf, TEXT("%d%d%d%d"), TmpAns[0], TmpAns[1], TmpAns[2], TmpAns[3]);
							SendMessage(GetDlgItem(hDlg, IDC_NUMBOX), WM_SETTEXT, 0, (LPARAM)szBuf);

						}
////						GetTe// 
//						int Tempero
//	int i,a,b;
//	for (i=0;i<Count;i++)
//	{
//		compare(Num,History[i].num,&a,&b);
//		if (a!=solutions[i].a||b!=solutions[i].b)
//			return 1;
//	}
//	return 0;
//}
					}
					SetFocus(hCtl);

				}
				return TRUE;
				break;
			case IDC_ENTERNUM:
				{
					// Mode = 0
					TCHAR szBuf[32];
					int num[4];
					SendMessage(hCtl, WM_GETTEXT, (WPARAM)5, (LPARAM)szBuf);
//					CheckNum(szBuf, num);
					if (CheckNum(szBuf, num) || ! Correct4Number(num))
					{
						MessageBox(hDlg, TEXT("������4��������ͬ�����֡�"), TEXT("��ʾ"), MB_ICONSTOP);
						SetFocus(hCtl);
					}
					else if (Mode ==3)
					{
						TCHAR szBuf[1024]={TCHAR('\0')};
						TCHAR szTmp[64];
						
						int i, a, b;
						for (i=0; i<Count; i++)
						{
							compare(num, History[i].num, &a, &b);
							if (a != History[i].a || b != History[i].b)
							{
								wsprintf(szTmp, TEXT("%d. %d%d%d%d��%d%d%d%d��ȣ��õ����Ϊ%dA%dB��\n"),
									i, History[i].num[0], History[i].num[1], History[i].num[2], History[i].num[3],
									num[0], num[1], num[2], num[3], History[i].a, History[i].b);
								lstrcat(szBuf, szTmp);
								//lstrcat(szBuf, szTmp);
							}
//							if (compare(num, History[i].num, &a, &b))
						}
						MessageBox(hDlg, szBuf, TEXT(""), MB_ICONSTOP);
					}
					else
					{
						// "1. 1234 0A0B"
						TCHAR szBuf[] = TEXT("1. 1234 0A0B");
						HWND hWnd = GetDlgItem(hDlg, IDC_LIST1);
						int a, b;
						compare(Answer, num, &a, &b);

						wsprintf(szBuf, TEXT("%d. %d%d%d%d %dA%dB"), ++Count, 
							num[0],num[1],num[2],num[3],
							a,b);//1, 1, 1, 1, 2, 2);
						SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)szBuf);

						if (a==4 && b==0)
						{
							//int r=MessageBox(hDlg, TEXT("�¶��ˣ����������\n\n�Ƿ�����һ�֣�"), TEXT("��ϲ"), MB_ICONINFORMATION | MB_YESNO);
							int r=MessageBox(hDlg, TEXT("�¶��ˣ����������"), TEXT("��ϲ"), MB_ICONINFORMATION);
							GameOver ++;
							//DisableAll(hDlg);

							/*if (r == IDYES)
							{
								PostMessage(hDlg, IDM_NEW_HUMAN, 0, 0);
							}*/
						}
						else if (Count == 8)
						{
							// 8��û���С�
							TCHAR szBuf[64];
							wsprintf(szBuf, TEXT("8��û�в��У����ֽ�����ף�´κ��ˣ�\n\n��ȷ�𰸣�%d%d%d%d"),
								Answer[0], Answer[1], Answer[2], Answer[3]);
							MessageBox(hDlg, szBuf, TEXT("����"), MB_ICONINFORMATION);
							GameOver ++;
						}

						if (GameOver)
						{
							DisableAll(hDlg);
							TCHAR szBuf[]=TEXT("��ȷ�𰸣�0000");
							wsprintf(szBuf, TEXT("��ȷ�𰸣�%d%d%d%d"),
								Answer[0],Answer[1],Answer[2],Answer[3]);
							SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)szBuf);
						}
					}

					


				}
				
				SendMessage(hCtl, EM_SETSEL, 0, 4);
				SetFocus(hCtl);
				return TRUE;
				break;
//			case IDC_JUDGE:
//				break;
			case IDC_CLEAR:
				{
					TCHAR szNum[1]={TCHAR('\0')};
					//HWND hCtl=GetDlgItem(hDlg, IDC_NUMBOX);
					SendMessage(hCtl, WM_SETTEXT, (WPARAM)0, (LPARAM)szNum);
				}
				SetFocus(hCtl);
				break;
			case IDM_NEW_HUMAN:
				Mode = 0;
				hCtl=GetDlgItem(hDlg, IDC_NUMBOX);
				EnableHuman(hDlg);
				urand(Answer);
				Count=0; // �²������0
				GameOver=0;
//				SendMessage(hList,LB_RESETCONTENT, 0, 0);
				ClearControls(hDlg);
				SetFocus(hCtl);
				break;

			case IDM_NEW_COM:
				Mode = 1;
				Count=0;
				hCtl=GetDlgItem(hDlg, IDC_JUDGEBOX);
				ClearControls(hDlg);

//				SendMessage(hList,LB_RESETCONTENT, 0, 0);
				EnableCom(hDlg);
				{
//					int num[4];
					urand(TmpAns);
					TCHAR szBuf[5];
					wsprintf(szBuf, TEXT("%d%d%d%d"),TmpAns[0],TmpAns[1],TmpAns[2],TmpAns[3]);
					SendMessage(GetDlgItem(hDlg, IDC_NUMBOX), WM_SETTEXT, 0, (LPARAM)szBuf);
					Count=0;
					AddTemp(History, 0, TmpAns);
//					History[0].num[0]=num[0];
//					History[0].num[1]=num[1];
//					History[0].num[2]=num[2];
//					History[0].num[3]=num[3];
				}
				
				SetFocus(hCtl);
				break;
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, (DLGPROC)About);
				return TRUE;
			case IDM_EXIT:
				PostMessage(hDlg, WM_COMMAND, IDOK, 0);
				return TRUE;
				break;
			}
			
//			case WM_CTLCOLORSTATIC:
//				{
//					if (GetDlgCtrlID((HWND)lParam) == IDC_NUMBOX)//C_NUMBOX)
//					{
//						HDC hdc = (HDC)wParam;
////						SelectObject(hdc, (HGDIOBJ)GetStockObject(BLACK_BRUSH));
////						int x=1;
//						return (BOOL)hPenNum;//GetStockObject(BLACK_BRUSH);
//					}
//				}
//				break;
//			case WM_DESTROY:
//				if (hPenNum != NULL)
//				{
//					DeleteObject(hPenNum);
//				}
//				break;

			break;
	}
    return FALSE;
}


// ��Str�ַ����д�Beg��ʼ��End�������ַ������滻��SubStr
// Str��SubStr���ȶ�������5�ַ�

int InsStr(TCHAR * Str, int Beg, int End, TCHAR * SubStr)
{
	TCHAR szBuf[5]={TCHAR('\0')};
	if (Beg >0)
	{
		lstrcpyn(szBuf, Str, Beg+1);
	}
	lstrcat(szBuf, SubStr);
	lstrcat(szBuf, Str+End);
	lstrcpy(Str, szBuf);
	return 0;
}

int CheckNum(TCHAR * Str, int num[4])
{
	if (lstrlen(Str) != 4)
		return 1;
	num[0] = *Str - TCHAR('0');
	num[1] = *(Str+1) - TCHAR('0');
	num[2] = *(Str+2) - TCHAR('0');
	num[3] = *(Str+3) - TCHAR('0');
	return 0;
}

int CheckJudgeChar(TCHAR * Str)
{
	int len = lstrlen(Str);
	static TCHAR szChars[]=TEXT("01234aAbB");
	int c, i, ln, Bad;
	if (len < 1)
		return 0;

	if (len >4)
		return 1;

	ln = lstrlen(szChars);

	for (c=0; c<len; c++)
	{
		Bad = 1;

		for (i=0; i< ln; i++)
		{
			if ( *(Str+c) == szChars[i] )
			{
				Bad = 0;
				break;
			}
		}
		if (Bad) 
			return 1; // �ַ�������ȷ
	}
	return 0;
}

int CheckJudge(TCHAR * Str)
{
	int i;
	TCHAR c;

	// ��ʽΪ #A#B��#Ϊ0-4����
	if (lstrlen(Str) != 4)
	{
		return 1; // ���Ȳ���ȷ
	}
	if (*(Str+1) != TCHAR('a') || *(Str+1) != TCHAR('A') || *(Str+3) != TCHAR('b') || *(Str+3) != TCHAR('B'))
	{
		return 2; // ��ʽ����ȷ
	}

	for (i=0; i<=1; i++)
	{
		if (i==0)
			c = *Str;
		else
			c = *(Str+2);
		if (c != TCHAR('0') || c != TCHAR('1') || c != TCHAR('2') || c != TCHAR('3') || c != TCHAR('4'))
			return 3; // ���ֲ���ȷ
	}

	if ((*Str - TCHAR('0') + *(Str+2) - TCHAR('0')) >4)
		return 3; // ���ֲ���ȷ
	return 0; // �ַ�����ȷ
}

void ClearControls(HWND hDlg)
{
	TCHAR szBuf[] = TEXT("");
	
	HWND hCtl = GetDlgItem(hDlg, IDC_NUMBOX);
	SendMessage(hCtl, WM_SETTEXT, 0, (LPARAM)szBuf);

	hCtl = GetDlgItem(hDlg, IDC_JUDGEBOX);
	SendMessage(hCtl, WM_SETTEXT, 0, (LPARAM)szBuf);
	
	hCtl = GetDlgItem(hDlg, IDC_LIST1);
	SendMessage(hCtl, LB_RESETCONTENT, 0, 0);

}

void EnableHuman(HWND hDlg)
{
	int i;
	HWND hCtl;
	for (i=IDC_NUM0; i<=IDC_NUM9; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, TRUE);
		//SendMessage(hCtl, WM_ENABLE, TRUE, 0);
	}

	for (i=IDC_A; i<=IDC_B; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, FALSE);
		//SendMessage(hCtl, WM_ENABLE, FALSE, 0);
	}
	
	hCtl = GetDlgItem(hDlg, IDC_NUMBOX);
	EnableWindow(hCtl, TRUE);

	hCtl = GetDlgItem(hDlg, IDC_ENTERNUM);
	EnableWindow(hCtl, TRUE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGEBOX);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGE);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_CLEAR);
	EnableWindow(hCtl, TRUE);

	
}

void EnableCom(HWND hDlg)
{
	int i;
	HWND hCtl;
	for (i=IDC_NUM0; i<=IDC_NUM4; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, TRUE);
		//SendMessage(hCtl, WM_ENABLE, TRUE, 0);
	}

	for (i=IDC_NUM5; i<=IDC_NUM9; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, FALSE);
		//SendMessage(hCtl, WM_ENABLE, FALSE, 0);
	}

	for (i=IDC_A; i<=IDC_B; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, TRUE);
		//SendMessage(hCtl, WM_ENABLE, TRUE, 0);
	}

		hCtl = GetDlgItem(hDlg, IDC_NUMBOX);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_ENTERNUM);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGEBOX);
	EnableWindow(hCtl, TRUE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGE);
	EnableWindow(hCtl, TRUE);

	hCtl = GetDlgItem(hDlg, IDC_CLEAR);
	EnableWindow(hCtl, TRUE);
}

void DisableAll(HWND hDlg)
{
	int i;
	HWND hCtl;
	for (i=IDC_NUM0; i<=IDC_B; i++)
	{
		hCtl = GetDlgItem(hDlg, i);
		EnableWindow(hCtl, FALSE);
	}

	hCtl = GetDlgItem(hDlg, IDC_NUMBOX);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_ENTERNUM);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGEBOX);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_JUDGE);
	EnableWindow(hCtl, FALSE);

	hCtl = GetDlgItem(hDlg, IDC_CLEAR);
	EnableWindow(hCtl, FALSE);
}
