//http://www.winprog.org/tutorial/simple_window.html

#include <windows.h>

const wchar_t g_szClassName[] = L"myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;			// handle to the device context (permission to draw)
	PAINTSTRUCT Ps;		// a variable that you need
	HPEN hRectPen;		// the handle to the red pen
	HPEN hCirPen;
	HPEN hTriPen;
	static POINT triPoint[3];
	static int triBase = 100;
	triPoint[0].x = 445;
	triPoint[0].y = 225 - (triBase / 2);
	triPoint[1].x = 470 - (triBase / 2);
	triPoint[1].y = 170 + (triBase / 2);
	triPoint[2].x = 420 + (triBase / 2);
	triPoint[2].y = 170 + (triBase / 2);

	HBRUSH rectBrush;
	HBRUSH cirBrush;
	HBRUSH triBrush;

	static int rectRed = 255;
	static int rectBlue = 0;
	static int rectGreen = 0;

	static int rectBrushRed = 128;
	static int rectBrushBlue = 128;
	static int rectBrushGreen = 128;

	static int cirRed = 155;
	static int cirBlue = 0;
	static int cirGreen = 10;

	static int cirBrushRed = 108;
	static int cirBrushBlue = 228;
	static int cirBrushGreen = 024;

	static int triRed = 0;
	static int triBlue = 50;
	static int triGreen = 10;

	static int triBrushRed = 208;
	static int triBrushBlue = 155;
	static int triBrushGreen = 124;

	static int rectX = 325;
	static int rectY = 200;
	static int cirX = 225;
	static int cirY = 200;

	POINT test[1];
	test[0].x = 123;
	static int penSize = 5;

	switch (msg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &Ps);
		hRectPen = CreatePen(PS_SOLID, penSize, RGB(rectRed, rectGreen, rectBlue));
		SelectObject(hDC, hRectPen);

		rectBrush = CreateSolidBrush(RGB(rectBrushRed, rectBrushGreen, rectBrushBlue));
		SelectObject(hDC, rectBrush);
		Rectangle(hDC, rectX + 25, rectY - 25, rectX - 25, rectY + 25);

		hCirPen = CreatePen(PS_SOLID, penSize, RGB(cirRed, cirGreen, cirBlue));
		SelectObject(hDC, hCirPen);

		cirBrush = CreateSolidBrush(RGB(cirBrushRed, cirBrushGreen, cirBrushBlue));
		SelectObject(hDC, cirBrush);
		Ellipse(hDC, cirX + 25, cirY - 25, cirX - 25, cirY + 25);

		hTriPen = CreatePen(PS_SOLID, penSize, RGB(triRed, triGreen, triBlue));
		SelectObject(hDC, hTriPen);

		triBrush = CreateSolidBrush(RGB(triBrushRed, triBrushGreen, triBrushBlue));
		SelectObject(hDC, triBrush);

		Polygon(hDC, triPoint, 3);

		DeleteObject(hRectPen);
		DeleteObject(rectBrush);
		DeleteObject(hCirPen);

		DeleteObject(cirBrush);
		DeleteObject(hTriPen);
		DeleteObject(triBrush);
		EndPaint(hwnd, &Ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			rectRed = rand() % 256;
			rectGreen = rand() % 256;
			rectBlue = rand() % 256;
			rectBrushRed = rand() % 256;
			rectBrushBlue = rand() % 256;
			rectBrushGreen = rand() % 256;

			cirRed = rand() % 256;
			cirGreen = rand() % 256;
			cirBlue = rand() % 256;
			cirBrushRed = rand() % 256;
			cirBrushBlue = rand() % 256;
			cirBrushGreen = rand() % 256;

			triRed = rand() % 256;
			triGreen = rand() % 256;
			triBlue = rand() % 256;
			triBrushRed = rand() % 256;
			triBrushBlue = rand() % 256;
			triBrushGreen = rand() % 256;
		}
		else if (wParam == VK_NEXT)
		{
			triBase -= 5;
		}
		else if (wParam == VK_PRIOR)
		{
			triBase += 5;
		}
		else if (wParam == VK_RIGHT)
		{
			rectX += 3;
		}
		else if (wParam == VK_LEFT)
		{
			rectX -= 3;
		}
		else if (wParam == VK_UP)
		{
			rectY -= 3;
		}
		else if (wParam == VK_DOWN)
		{
			rectY += 3;
		}

		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"Miles Robson",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}