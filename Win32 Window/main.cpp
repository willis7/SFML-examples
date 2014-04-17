#include <windows.h>
#include "stdafx.h"

#define WIN_NAME "Win32 window"

HWND mainHWND = 0;						// Save the handle to the window.

LRESULT CALLBACK WindowProc(HWND hWnd,		//The window
							UINT message,		//The message itself
							WPARAM wParam,	//More information about the message
							LPARAM lParam)  //More information about the message
{
	// This is the main message handler of the system
	PAINTSTRUCT paintStruct;			// Used in WM_PAINT
	HDC hdc;							// Handle to a device context

	// What is the message
	switch(message)
	{
		case WM_CREATE:
		{
			//TODO: initialization stuff here
			return(0);
		} break;

		case WM_PAINT:
		{
			// Simply validate the window
			hdc = BeginPaint(hWnd,&paintStruct);			// Get a handle to the GDC (Graphics Device Context)
			EndPaint(hWnd,&paintStruct);
			return(0);
		} break;

		case WM_DESTROY:
		{
			// Kill the application
			PostQuitMessage(0);
			return(0);
		} break;

		default:break; //Default condition

	} // End switch statement

	// Process any messages that we didn't take care of
	return (DefWindowProc(hWnd, message, wParam, lParam));

}
//End of function WindowProc



int WINAPI WinMain(HINSTANCE hInsatance,		// Think of this as an ID card, Windows will occasionally ask for your ID and you will have to give windows this value. Windows uses this to tell your program apart from other programs.
			HINSTANCE hPrevInstance,			// Used in old 16bit Windows.
			LPSTR lpCmdLine,					// String that contains everything the user specifies on the command line, except your program name.
			int nShowCmd)						// Tells the program how to display itself on screen.
{

	WNDCLASS windowClass;					// Create a WNDCLASS.
	HWND hWnd;								// Declare a handle to window.

	// Configure the WNDCLASS.
	windowClass.style =	CS_DBLCLKS |								// Recieve messages about double clicks.
						CS_OWNDC |									// Give the window its own 'device context' to speed up painting to the window.
						CS_HREDRAW |								// Send messages in response to any window re-sizing.
						CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;								// Assign the address of the event handler
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInsatance;									// Handle to instance
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// Handle to icon
	windowClass.hCursor = LoadCursor(NULL, IDC_CROSS);					// Handle to cursor
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// Set a colour for the background
	windowClass.lpszMenuName = NULL;									// A pointer to the menu resource
	windowClass.lpszClassName = (LPCWSTR) WIN_NAME;					// The window title

	// Register the window class.
	RegisterClass(&windowClass);
	
	// Create the window.
	hWnd = CreateWindow((LPCWSTR) WIN_NAME,							// Class
							TEXT("Window Brap!"),					// Title
							WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							0,0,									// x,y
							320,200,								// width, height
							NULL,									// Handle to parent
							NULL,									// Handle to menu
							hInsatance,								// Instance
							NULL);									// Creation stuff

	
	mainHWND = hWnd;					// Save the window handle in a global 
	MSG message;

	while(message.message == WM_QUIT) //Start main loop and test if quit
	{
		if (PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{			
			TranslateMessage(&message);		// Translate any accelerator keys			
			DispatchMessage(&message);		// send the message to the window proc
		}								// end if

		// Main (game) processing goes here

	} // End while loop
	return(message.wParam); //Way of returning to windows

	return 0;
}