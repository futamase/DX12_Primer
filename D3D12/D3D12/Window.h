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
		UINT m_width, m_height;  //! �s�v�ɂȂ邩��
	public:
		/**@brief �R���X�g���N�^
		*@param[in] AppName �^�C�g���o�[�ɕ\�����閼�O
		*@param[in] hInstance �C���X�^���X�n���h��
		*@param[in] width �E�B���h�E�̕�
		*@param[in] height �E�B���h�E�̍���
		*/
		Window(const tstring& AppName, HINSTANCE hInstance, UINT width, UINT height);

		/**@brief �f�X�g���N�^*/
		~Window();

		/**@brief �E�B���h�E�n���h����Ԃ�
		*@return �E�B���h�E�n���h��
		*/
		HWND getHWnd() const { return m_hWnd; }

		/**@brief �E�B���h�E�̕���Ԃ�
		*@return �E�B���h�E�̕�
		*/
		float width();

		/**@brief �E�B���h�E�̍�����Ԃ�
		*@return �E�B���h�E�̍���
		*/
		float height();

		void enableCursor(bool enable);

		/**@brief �A�C�R����ݒ肷��(������)
		*@param fileName �摜�t�@�C���ւ̃p�X
		*/
		void setIcon(const tstring& fileName);

		bool setTitle(const tstring& title);
	};
}