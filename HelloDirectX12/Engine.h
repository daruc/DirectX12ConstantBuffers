#pragma once
#include <d3d12.h>
#include "d3dx12.h"
#include <wrl.h>
#include <dxgi1_4.h>	// ?
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using Microsoft::WRL::ComPtr;
using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;

struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;

	Vertex(float x, float y, float z, float r, float g, float b, float a)
		: pos(x, y, z), color(r, g, b, a)
	{
	}
};

class Engine
{
private:
	UINT m_resolutionWidth;
	UINT m_resolutionHeight;
	HWND m_hwnd;

	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12Resource> m_renderTarget[2];
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Fence> m_fence;
	ComPtr<ID3D12Device> m_device;

	// drawing triangles
	ComPtr<ID3D12RootSignature> m_rootSignature;

	ComPtr<ID3D12Resource> m_vertexBuffer;
	ComPtr<ID3D12Resource> m_vBufferUploadHeap;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	ComPtr<ID3D12Resource> m_indexBuffer;
	ComPtr<ID3D12Resource> m_iBufferUploadHeap;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	ComPtr<ID3DBlob> m_vertexShader;
	ComPtr<ID3DBlob> m_pixelShader;
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;

	// depth/stencil buffer
	ComPtr<ID3D12DescriptorHeap> m_dsDescriptorHeap;
	ComPtr<ID3D12Resource> m_dsBuffer;

	int m_frameIndex;	// render target index
	UINT m_rtvDescriptorSize;	// Render Target View descriptor heap size
	UINT64 m_fenceValue;
	HANDLE m_fenceEvent;

	void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter);
	void WaitForPreviousFrame();

	void CreateRootSignature();
	void LoadShaders();
	void CreatePipelineStateObject();
	void CreateVertexBuffer();
	void FillOutViewportAndScissorRect();
public:
	Engine(UINT resolutionWidth, UINT resolutionHeight);
	~Engine();

	void Init(HWND hwnd);
	void Render();
	void Destroy();
};