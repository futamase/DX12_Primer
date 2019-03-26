#pragma once

#include <windows.h>

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "dx12_helper.h"

#include <string>

namespace t3d {
	using Microsoft::WRL::ComPtr;
	using namespace DirectX;

	class DX12 {
	public:
		DX12(UINT width, UINT height, std::wstring name, HWND hWnd);

		virtual void OnInit();
		virtual void OnUpdate();
		virtual void OnRender();
		virtual void OnDestroy();

		static const UINT FrameCount = 2;

		// Pipeline objects.
		ComPtr<IDXGISwapChain3> m_swapChain;
		ComPtr<ID3D12Device> m_device;
		ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
		ComPtr<ID3D12CommandAllocator> m_commandAllocator;
		ComPtr<ID3D12CommandQueue> m_commandQueue;
		ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
		ComPtr<ID3D12PipelineState> m_pipelineState;
		ComPtr<ID3D12GraphicsCommandList> m_commandList;
		CD3DX12_VIEWPORT m_viewport;
		CD3DX12_RECT m_scissorRect;
		ComPtr<ID3D12RootSignature> m_rootSignature;
		UINT m_rtvDescriptorSize;

		HWND m_hWnd;

		// Synchronization objects.
		UINT m_frameIndex;
		HANDLE m_fenceEvent;
		ComPtr<ID3D12Fence> m_fence;
		UINT64 m_fenceValue;

		UINT m_width, m_height;

		struct Vertex
		{
			XMFLOAT3 position;
			XMFLOAT4 color;
		};

		// App resources.
		ComPtr<ID3D12Resource> m_vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

		void LoadPipeline();
		void LoadAssets();
		void PopulateCommandList();
		void WaitForPreviousFrame();
	};
}