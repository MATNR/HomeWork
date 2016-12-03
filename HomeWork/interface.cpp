//---------------------------------------------------------------------------
// File: interface.cpp
// By:   HeliSRaiN
//                                                ���� ������������ ���������
//---------------------------------------------------------------------------
#include "interface.h"
#include "packcage.h"

HWND hwnd = FindWindow("ConsoleWindowClass", NULL); //�������� �������
HDC dc = GetDC(hwnd);
int point = 0;

enum color { //� - ����� ������� �������, B - ����� �����
	BLACK = 0,
    BLUE_B,
    GREEN_B,
    Cyan,
    Red_B,
    Magenta,
    Brown,
    GRAY_A,
    GRAY_B,
    BLUE_A,
    GREEN_A,
    LightCyan,
    RED_A,
    LightMagenta,
    YELLOW,
    WHITE  
};

void SetColor(int text, int background) {
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void drawBitmap(HDC hdcA, int x, int y, HBITMAP hbmA){
        BITMAP bm; //���������� �������� ����. ������ - BMP
        POINT ptSize, ptOrg;
        HDC hdcB = CreateCompatibleDC(hdcA); //"���������" ��� ����������� ���������. �� ������ �������� ������. ����� ��.
        HBITMAP hbmB = (HBITMAP)SelectObject(hdcB, hbmA); //��������, ������� �������� ��������� ����������� � ������
        if (hbmB){ //���� ������ ����, �� ����������
			SetMapMode(hdcB, GetMapMode(hdcA));
			GetObject(hbmA, sizeof(BITMAP), (LPSTR) &bm); // ���������� ������� ������ �����������
			ptSize.x = bm.bmWidth; //���� ������
			ptSize.y = bm.bmHeight; //���� ������
			DPtoLP(hdcA, &ptSize, 1); //������� � ����� ��������� �� ������.. ��� �� �����, ������? ����� �����
			ptOrg.x = 0; //��������
			ptOrg.y = 0; //��������
			DPtoLP(hdcB, &ptOrg, 1); //������� � ����� ��������� �� ������.. �����, �� ��������� �������� hdcB � ������
			BitBlt(hdcA, x, y, ptSize.x, ptSize.y, hdcB, ptOrg.x, ptOrg.y, SRCCOPY); //�����, ��� ������� �������!
			SelectObject(hdcB, hbmB); //���������� ��������� �������� ��������� ������
        }
        DeleteDC(hdcB); //� � ����� ��� ������� (�������� ������)
}

void drawImageToDisplay(char *logoDir, int height, int width, int x, int y){
	static HBITMAP hBitmap;
	PAINTSTRUCT ps;  
	static char MyName[260]={0};
	GetModuleFileNameA(NULL, MyName, sizeof(MyName));
	HWND hwnd = FindWindow(NULL, MyName); //�������� �������
	HDC hdc;
	hdc = GetWindowDC(hwnd);
	hBitmap = (HBITMAP)LoadImage(NULL, logoDir, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	InvalidateRect(hwnd,NULL,TRUE);
	hdc = BeginPaint(hwnd,&ps);
	drawBitmap(hdc, y, x, hBitmap);
	EndPaint(hwnd,&ps);
}

void animationLogo(){
	drawImageToDisplay("image//LogoImage.bmp", 175, 500, 30, 30); //������� ���� ������������� ����
	Sleep(500);

	for (int t = 0; t < 18; t++) cout << "\n";
	SetColor(YELLOW, BLACK);
	cout << "                     " << "�� �� ������� ����������������" << endl;
	SetColor(WHITE, BLACK);
	Sleep(250);
	SetColor(RED_A, BLACK);
	cout << "                     " << "������� 2: "; 
	SetColor(WHITE, BLACK);
	Sleep(250);
	cout << "������ ���������" << endl;
	Sleep(250);
	cout << "                                " << "���� �������" << endl;
	Sleep(250);
	cout << "                                " << "����� ���������" << endl;
	Sleep(250);
	cout << "                                " << "������ ����������" << endl;
	Sleep(250);
	cout << "                                " << "����� �������" << endl;

	Sleep(5000);
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); //�� ���������� ���������� �� "������ ��������"
}

void menuDesign(){
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//EnterComands.bmp", 50, 250, 195, 15);
	for (int t = 0; t < 21; t++) cout << "\n";
	cin >> point;
	while (point >= 5 || point == 0){
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0);
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//FailComand.bmp", 50, 250, 195, 15);
	system("CLS");
	for (int t = 0; t < 21; t++) cout << "\n";
	cin >> point;
	}
}

//��� ������������ �������� � �������� ����� ����� �������
int menuDo(){
	menuDesign();
	switch (point){
	case 1: 
		say("������� 1");
	break;
	case 2: 
		say("������� 2");
	break;
	case 3: 
		say("������� 3");
	break;
	case 4: 
		return 0;
	break;
	}
	return 0;
}

void returnToMenu(){
	system("CLS");
	menuDo();
}
 
int menuRun () {
	system("chcp 1251 > nul"); //������������
	animationLogo(); //������� ����
	system("CLS"); //������� ��� ��������� �� ���������
	menuDo(); 
	return 0;
}