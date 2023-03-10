#include <windows.h>
#include <stdio.h>
#include<string>

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static char textSaved[20];
	static char textSaved_2[20];
	

	static HWND label1, Textbox1, Textbox2;
	
	switch(Message) {
		case WM_CREATE:

		label1 = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE|WS_CHILD|WS_BORDER,20,20,200,20,hwnd,NULL,NULL,NULL);

		Textbox1 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,45,45,150,20,hwnd,NULL,NULL,NULL);
		Textbox2 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,45,70,150,20,hwnd,NULL,NULL,NULL);

		CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,50,110,30,30,hwnd,(HMENU) 1,NULL,NULL);

		CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,80,110,30,30,hwnd,(HMENU) 2,NULL,NULL);

		CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,110,110,30,30,hwnd,(HMENU) 3,NULL,NULL);

		CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,140,110,30,30,hwnd,(HMENU) 4,NULL,NULL);



		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case 1:
		{
			GetWindowText(Textbox1, &textSaved[0],21);
			GetWindowText(Textbox2, &textSaved_2[0],21);
			float x,y;
			sscanf(textSaved, "%f", &x);
			sscanf(textSaved_2, "%f", &y);
			float sum = x + y;
			char shoW[100];
			sprintf(shoW, "%f", sum);
			::MessageBox(hwnd, shoW, "Result", MB_OK);
			break;
		}
		case 2:
		{
			GetWindowText(Textbox1, &textSaved[0],21);
			GetWindowText(Textbox2, &textSaved_2[0],21);
			float x,y;
			sscanf(textSaved, "%f", &x);
			sscanf(textSaved_2, "%f", &y);
			float minus = x - y;
			char shoW[100];
			sprintf(shoW, "%f", minus);
			::MessageBox(hwnd, shoW, "Result", MB_OK);
			break;
		}
		case 3:
		{
			GetWindowText(Textbox1, &textSaved[0],21);
			GetWindowText(Textbox2, &textSaved_2[0],21);
			float x,y;
			sscanf(textSaved, "%f", &x);
			sscanf(textSaved_2, "%f", &y);
			float times = x * y;
			char shoW[100];
			sprintf(shoW, "%f", times);
			::MessageBox(hwnd, shoW, "Result", MB_OK);
			break;
		}
		case 4:
		{
			GetWindowText(Textbox1, &textSaved[0],21);
			GetWindowText(Textbox2, &textSaved_2[0],21);
			float x,y;
			sscanf(textSaved, "%f", &x);
			sscanf(textSaved_2, "%f", &y);
			float divide = x / y;
			char shoW[100];
			sprintf(shoW, "%f", divide);
			::MessageBox(hwnd, shoW, "Result", MB_OK);
			break;
		}
		

		
			
				
		}
		break;



		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	HBRUSH brush = CreateSolidBrush(RGB(200, 0, 0));
	wc.hbrBackground = brush;
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
