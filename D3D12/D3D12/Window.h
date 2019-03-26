#pragma once

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <memory>

namespace t3d {

	using tstring = std::basic_string<TCHAR>;

	class Window
	{
	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		UINT m_width, m_height;  //! 不要になるかも
	public:
		/**@brief コンストラクタ
		*@param[in] AppName タイトルバーに表示する名前
		*@param[in] hInstance インスタンスハンドル
		*@param[in] width ウィンドウの幅
		*@param[in] height ウィンドウの高さ
		*/
		Window(const tstring& AppName, HINSTANCE hInstance, UINT width, UINT height);

		/**@brief デストラクタ*/
		~Window();

		/**@brief ウィンドウハンドルを返す
		*@return ウィンドウハンドル
		*/
		HWND getHWnd() const { return m_hWnd; }

		/**@brief ウィンドウの幅を返す
		*@return ウィンドウの幅
		*/
		float width();

		/**@brief ウィンドウの高さを返す
		*@return ウィンドウの高さ
		*/
		float height();

		void enableCursor(bool enable);

		/**@brief アイコンを設定する(未実装)
		*@param fileName 画像ファイルへのパス
		*/
		void setIcon(const tstring& fileName);

		bool setTitle(const tstring& title);
	};
}