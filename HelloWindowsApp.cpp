#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include "BaseWindow.h"
#include <shobjidl.h> 




class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR ClassName() const { return L"Sample Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
	}
	return 0;
	case WM_CLOSE:
		if (MessageBox(m_hwnd, L"Really quit?", L"My application", MB_OKCANCEL) ==
			IDOK)
		{
			DestroyWindow(m_hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int
	nCmdShow)
{
	MainWindow win;
	if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}
	ShowWindow(win.Window(), nCmdShow);
	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int
	nCmdShow)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);
			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH,
						&pszFilePath);
					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return 0;
}
*/