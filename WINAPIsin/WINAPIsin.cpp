#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {

	MSG msg = { 0 }; //	Структура для хранения сообщения
	HWND hwnd; // Дескриптор главного окна программы
	WNDCLASSW wc = { 0 }; // Класс окна

	wc.style = CS_HREDRAW | CS_VREDRAW;//стиль класса окна(внутренняя область окна д.б. перерисована при изменении размеров окна)
	wc.cbClsExtra = 0;//число дополнительных байт, которые размещаются вслед за структурой класса
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Window"; //имя класса окна
	wc.hInstance = hInst;//установка экземпляра программы
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE - 4);//кисть фона, цвет для рисования клиентской области
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WindowProcedure; //функция окна
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//установка курсора
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//иконка для приложения

	RegisterClassW(&wc);//функция регистрации класса окна в системе
	hwnd = CreateWindowW(wc.lpszClassName, L"Графика",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		30, 100, 1800, 400, NULL, NULL, hInst, NULL);//параметры окна

	ShowWindow(hwnd, nCmdShow);//показ окна
	UpdateWindow(hwnd);//если область обновления непуста, то функция посылает сообщение прямо оконной функции данного окна

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg); //функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); //посылает сообщение функции WndProc()
	}
	return (int)msg.wParam;//код завершения возвращается в систему
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {//оконная процедура
	HDC hDC;//дескриптор ориентации текста на экране
	PAINTSTRUCT ps;//структура, в которой содержится информация о клиенской области(размеры, цвет и т.д.)
	static int sX, sY;
	int a, b, x_scr, y_scr;//экранные координаты
	double x, h = M_PI / 10;//частота прорисовки
	int ampl = 150;// мплитуда колебания
	static HPEN hPen1, hPen2;
	static HBRUSH hBrush;

	switch (msg) {

	case WM_SIZE:
		sX = LOWORD(lParam);//ширина окна
		sY = HIWORD(lParam);//высота окна
		break;

	case WM_CTLCOLORSTATIC:
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)GetStockObject(NULL_BRUSH);
		break;

	case WM_CREATE:
		CreateWindowW(L"Static", L"0", WS_VISIBLE | WS_CHILD | SS_CENTER, 270, 190, 1025, 15, hwnd, NULL, NULL, NULL);
		CreateWindowW(L"Static", L"x", WS_VISIBLE | WS_CHILD | SS_CENTER, 560, 190, 1500, 15, hwnd, NULL, NULL, NULL);
		CreateWindowW(L"Static", L"y", WS_VISIBLE | WS_CHILD | SS_CENTER, 270, 10, 1025, 15, hwnd, NULL, NULL, NULL);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);//инициалирует контекст устройсва
		hPen1 = CreatePen(PS_SOLID, 3, RGB(111, 45, 135));
		hPen2 = CreatePen(PS_SOLID, 2, RGB(252, 3, 3));
		hBrush = CreateHatchBrush(HS_CROSS, RGB(156, 202, 255));

		SelectObject(hDC, hBrush);
		Rectangle(hDC, 0, 0, sX, sY);

		a = sX / 2;//координаты центра окна
		b = sY / 2;

		SelectObject(hDC, hPen1);
		MoveToEx(hDC, 0, b, NULL);
		LineTo(hDC, sX, b);
		MoveToEx(hDC, a, 0, NULL);
		LineTo(hDC, a, sY);

		MoveToEx(hDC, a, b, NULL);
		SelectObject(hDC, hPen2);
		h = 3 * M_PI / a;//шаг по оси х
		for (x = -M_PI, x_scr = 0; x < 500; x += h)
		{
			if (sin(x) == -1) ampl -= 10;//уменьшение амплинуды каждый раз как синусоида достигает своего минимального значения
			x_scr = x * 5 * M_PI;//частота колебания
			y_scr = (ampl * sin(x) + 180);//+180 = это смещение сигнала вниз по ОY
			LineTo(hDC, x_scr, y_scr);
		}

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hPen1);
		DeleteObject(hPen2);
		DeleteObject(hBrush);
		PostQuitMessage(0);//завершение программы
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
