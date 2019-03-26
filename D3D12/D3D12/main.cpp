#include <d3d12.h>
#include "Window.h"
#include "dx12.h"

int APIENTRY _tWinMain(HINSTANCE instance, HINSTANCE, LPTSTR, INT)
{
#ifdef _DEFINE
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	t3d::Window window{ _T("app"), ::GetModuleHandle(nullptr), 800, 600 };
	t3d::DX12 app{ 800,600,L"app", window.getHWnd() };
	app.OnInit();
			app.OnRender();
			app.OnUpdate();

	MSG msg{};
	// �Q�[�����[�v
	while (true) {
		// ���b�Z�[�W�����邩�ǂ���
		if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			// ���b�Z�[�W���擾���AWM_QUIT���ǂ���
			if (!::GetMessage(&msg, NULL, 0, 0))
				break;
			::TranslateMessage(&msg);  //�L�[�{�[�h���p���\�ɂ���
			::DispatchMessage(&msg);  //�����Windows�ɖ߂�
		}
		else {
			// �Q�[�����C������
			//UpdateFrame();
			::Sleep(1);
		}
	}

	app.OnDestroy();
	return 0;
}
