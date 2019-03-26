#include "Window.h"
#include <stdexcept>

namespace t3d {
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
	{
		switch (msg) {
			case WM_MOUSEHOVER: 
			case WM_INPUT:
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MOUSEWHEEL:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
				break;

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				// アプリ終了 
				if (wParam == VK_ESCAPE)
					::DestroyWindow(hWnd);

				break;

			//! ウィンドウの拡縮の際に呼ばれる
			case WM_SIZE:
			{
				auto width = LOWORD(lParam);
				auto height = HIWORD(lParam);
				//			DXGI::Swapchain::GetInstance()->ResizeBackBuffer(width, height);
			}
			break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				break;
			default:
				return ::DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0L;
	}
	Window::Window(const tstring& AppName, HINSTANCE hInstance, UINT width, UINT height)
		: m_hInstance{ hInstance }, m_width{ width }, m_height{ height }
	{
		// ウィンドウモード 
		DWORD windowStyle = WS_BORDER | WS_CAPTION | WS_SYSMENU;
		
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = sizeof(DWORD);
		wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = nullptr;
		wc.hIconSm = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = _T("MainWindow");
		wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH));
		wc.hInstance = hInstance;
		// ウィンドウを登録
		::RegisterClassEx(&wc);

		RECT rc;
		::SetRect(&rc, 0, 0, width, height);
		// ウィンドウモードのときタイトルバーを考慮して表示領域を設定するために必要なサイズを取得する 
		::AdjustWindowRect(&rc, windowStyle, FALSE);

		// ウィンドウを作成 
		auto hWnd = ::CreateWindow(
			wc.lpszClassName,
			AppName.c_str(),
			windowStyle,
			0,
			0,
			rc.right - rc.left,
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			hInstance, 
			nullptr
			);

		if (!hWnd)
			throw std::exception("CreateWindowでエラーが発生しました。ウィンドウが作成できません。");
		
		m_hWnd = hWnd;

		::UpdateWindow(hWnd);
		::ShowWindow(hWnd, SW_SHOW);
	}

	Window::~Window()
	{
		::UnregisterClass(_T("MainWindow"), m_hInstance);
	}

	void Window::setIcon(const tstring& fileName)
	{
		HICON hIcon = (HICON)::LoadImage(m_hInstance, fileName.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		SendMessage(m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}

	bool Window::setTitle(const tstring& title)
	{
		return ::SetWindowText(m_hWnd, title.c_str());
	}

	float Window::width()
	{
		return static_cast<float>(m_width);
	}

	float Window::height()
	{
		return static_cast<float>(m_height);
	}

	void Window::enableCursor(bool enable)
	{
		::ShowCursor(enable);
	}
}