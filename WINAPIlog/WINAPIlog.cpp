#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2);

int i = -150, xView, yView, j = 5, k = 500, l = -5, m = -200, n = 0, o = 500;
double y;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = L"Window";
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	if (!RegisterClass(&w))
		return 0;

	hWnd = CreateWindow(w.lpszClassName, L"Графика",
		WS_OVERLAPPEDWINDOW, 100, 100, 500, 400, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, (HINSTANCE)NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0)) {//Получаем сообщение из очереди
		TranslateMessage(&lpMsg);//Преобразует сообщения клавиш в символы
		DispatchMessage(&lpMsg);//Передаёт сообщение соответствующей функции окна
	}
	return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	HPEN hPen; //создаём перо
	static HPEN hPen1, hPen2, hPen3;
	int a = 1, b = 0, x_scr, y_scr;
	double x, h;//Цикл обработки сообщений
	switch (messg)
	{
	case WM_SIZE:
		xView = LOWORD(lParam);
		yView = HIWORD(lParam);

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ISOTROPIC); //логические единицы отображаем, как физические
		SetWindowExtEx(hdc, 500, 500, NULL); //Длина осей
		SetViewportExtEx(hdc, xView, -yView, NULL); //Определяем облась вывода
		SetViewportOrgEx(hdc, xView / 6, yView / 2, NULL); //Начало координат

		hPen3 = CreatePen(PS_SOLID, 1, RGB(156, 202, 255));
		SelectObject(hdc, hPen3);
		while (m < 600) {
			Line(hdc, m, 500, m, -300);
			m = m + 10;
		}

		while (o > -300) {
			Line(hdc, -150, o, 600, o);
			o = o - 10;
		}

		hPen1 = CreatePen(PS_DASHDOT, 3, RGB(0, 0, 0));
		SelectObject(hdc, hPen1);
		Line(hdc, 0, -300, 0, 500);
		Line(hdc, -150, 0, 600, 0);
		hPen2 = CreatePen(PS_DASH, 3, RGB(111, 45, 135));
		SelectObject(hdc, hPen2);
		while (i < 600) {
			Line(hdc, i, j, i, j - 10);
			i = i + 10;
		}

		TextOut(hdc, 520, -15, L"x", 1);
		while (k > -300) {
			Line(hdc, l, k, l + 10, k);
			k = k - 10;
		}
		TextOut(hdc, 10, 230, L"y", 1);

		for (i = -300; i < 600; i++) {
			y = 50.0 * (log(i * 0.01));
			LineTo(hdc, i, (int)y);
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hPen1);
		DeleteObject(hPen2);
		DeleteObject(hPen3);
		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
	return LineTo(hdc, x2, y2); //нарисовать линию
}