#include "gui_impl.h"
#include "log.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_dx12.h"
#include "font.h"
#include "../plugin/Menu.h"
#include "../plugin/Settings.h"
#include "notifications.h"
#include "../helper/eKeyboardMan.h"
#include "dx12hook.h"
#include "../helper/eGamepadManager.h"

bool  GUIImplementation::ms_bInit;
bool  GUIImplementation::ms_bFailed;
bool  GUIImplementation::ms_bShouldReloadFonts;;
bool  GUIImplementation::ms_bShouldRefreshRenderTarget;
HWND  GUIImplementation::ms_hWindow;
ID3D11RenderTargetView* GUIImplementation::ms_pRenderTarget;
WNDPROC GUIImplementation::ms_pWndProc;
GUIImplementationMode		GUIImplementation::ms_mode;
ID3D12DescriptorHeap* GUIImplementation::g_pd3dRtvDescHeap = nullptr;
ID3D12DescriptorHeap* GUIImplementation::g_pd3dSrvDescHeap = nullptr;
ID3D12CommandQueue* GUIImplementation::g_pd3dCommandQueue = nullptr;
ID3D12GraphicsCommandList* GUIImplementation::g_pd3dCommandList = nullptr;
std::vector<GUIImplementation::GFrameContext> GUIImplementation::frameContextData;
ID3D11DeviceContext* GUIImplementation::ms_cachedContext;
int GUIImplementation::numBuffers;

void GUIImplementation::Init(GUIImplementationMode mode)
{
	eLog::Message(__FUNCTION__, "INFO: Init");
	ms_bInit = false;
	ms_bFailed = false;
	ms_hWindow = 0;
	ms_pRenderTarget = nullptr;
	ms_bShouldReloadFonts = false;
	ms_bShouldRefreshRenderTarget = false;
	ms_pWndProc = 0;
	ms_cachedContext = nullptr;
	ms_mode = mode;
	numBuffers = 0;
	frameContextData.clear();
}


bool GUIImplementation::ImGui_InitDX12(IDXGISwapChain* pSwapChain, HWND hWindow)
{
	if (!ImGui::CreateContext())
	{
		eLog::Message(__FUNCTION__, "Failed to create ImGui context!");
		return false;
	}

	ImGui::GetIO().ConfigFlags  = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	if (!ImGui_ImplWin32_Init(ms_hWindow))
	{
		eLog::Message(__FUNCTION__, "Failed to init Win32 Backend!");
		return false;
	}


	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device! Error code: 0x%X", hResult);
		return false;
	}

	{
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		pSwapChain->GetDesc(&desc);
		numBuffers = desc.BufferCount;
		frameContextData.clear();
		frameContextData.resize(numBuffers);
	}


	{
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		ZeroMemory(&desc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.NumDescriptors = numBuffers;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		HRESULT hResult = pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dSrvDescHeap));

		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to create g_pd3dSrvDescHeap! Error code: 0x%X", hResult);
			return false;
		}
	}

	{
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		ZeroMemory(&desc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.NumDescriptors = numBuffers;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NodeMask = 1;


		HRESULT hResult = pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dRtvDescHeap));

		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to create g_pd3dRtvDescHeap! Error code: 0x%X", hResult);
			return false;
		}
	}

	ID3D12CommandAllocator* allocator = nullptr;

	hResult = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));

	for (UINT i = 0; i < numBuffers; i++)
		frameContextData[i].g_commandAllocator = allocator;

	if (pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, nullptr, IID_PPV_ARGS(&g_pd3dCommandList)) != S_OK ||
		g_pd3dCommandList->Close() != S_OK)
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to create command list! Error code: 0x%X", hResult);
		return false;
	}

	{
		SIZE_T rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

		for (UINT i = 0; i < numBuffers; i++)
		{
			ID3D12Resource* pBuffer = nullptr;
			pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBuffer));
			pDevice->CreateRenderTargetView(pBuffer, nullptr, rtvHandle);
			frameContextData[i].g_mainRenderTargetResource = pBuffer;
			frameContextData[i].g_mainRenderTargetDescriptor = rtvHandle;
			rtvHandle.ptr += rtvDescriptorSize;
		}
	}


	if (!ImGui_ImplDX12_Init(pDevice, numBuffers,
		DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap, g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
		g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart()))
	{
		eLog::Message(__FUNCTION__, "Failed to init DX12 Backend!");
		return false;
	}

	ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	if (!ms_pWndProc)
	{
		eLog::Message(__FUNCTION__, "Failed to set Window Procedure! Error code: %d", GetLastError());
		return false;
	}

	ImGui_SetStyle();
	eLog::Message(__FUNCTION__, "INFO: Init OK");
	return true;
}

void GUIImplementation::ImGui_SetupRenderTargetsDX12(IDXGISwapChain* pSwapChain)
{
	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
		return;

	for (UINT i = 0; i < numBuffers; ++i)
	{
		ID3D12Resource* pBackBuffer = NULL;
		pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer)
		{
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
			pSwapChain->GetDesc(&sd);

			D3D12_RENDER_TARGET_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(D3D12_RENDER_TARGET_VIEW_DESC));
			desc.Format = sd.BufferDesc.Format;
			desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

			pDevice->CreateRenderTargetView(pBackBuffer, &desc, frameContextData[i].g_mainRenderTargetDescriptor);
			frameContextData[i].g_mainRenderTargetResource = pBackBuffer;
		}
	}
}

void GUIImplementation::ImGui_DeleteRenderTargetsDX12(IDXGISwapChain* pSwapChain)
{
	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
		return;

	for (UINT i = 0; i < numBuffers; ++i)
	{
		if (frameContextData[i].g_mainRenderTargetResource)
		{
			frameContextData[i].g_mainRenderTargetResource->Release();
			frameContextData[i].g_mainRenderTargetResource = nullptr;
		}
	}
}

void GUIImplementation::ImGui_Reload(IDXGISwapChain* pSwapChain)
{
	ImGui_DeleteRenderTargetsDX12(pSwapChain);
	ms_bShouldRefreshRenderTarget = true;
}

void GUIImplementation::ImGui_SetStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);
	ImVec4* colors = style->Colors;

	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		ImVec4 col = style->Colors[i];
		if (i == ImGuiCol_Text || i == ImGuiCol_TextDisabled ||
			i == ImGuiCol_WindowBg || i == ImGuiCol_MenuBarBg) continue;
		style->Colors[i] = { col.z * 0.85f, col.y, col.x * 1.25f, col.w };
	}

	ImGui_ReloadFont();
}

void GUIImplementation::ImGui_ReloadFont()
{
	float fontSize = 16.0f;
	float fMenuScale = SettingsMgr->fMenuScale;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * fMenuScale);
	io.Fonts->Build();

	ImGui_ImplDX12_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}

void GUIImplementation::OnPresent(IDXGISwapChain3* pSwapChain)
{
	if (ms_bFailed)
		return;

	if (!ms_bInit)
		OnPresent_GUIStart(pSwapChain);

	ImGui_ProcessDX12(pSwapChain);
}

void GUIImplementation::OnPresent_GUIStart(IDXGISwapChain* pSwapChain)
{
	if (ms_bInit)
		return;

	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device! Error code: 0x%X", hResult);
		return;
	}

	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	pSwapChain->GetDesc(&swapChainDescription);

	ms_hWindow = swapChainDescription.OutputWindow;

	if (!ms_hWindow)
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device window!");
		return;
	}

	if (ImGui_InitDX12(pSwapChain, ms_hWindow))
	{
		ms_bInit = true;
		ms_bFailed = false;
		eLog::Message(__FUNCTION__, "INFO: Init OK");
	}
	ms_bShouldRefreshRenderTarget = true;

	if (SettingsMgr->bEnableGamepadSupport && ms_bInit)
		CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GamepadThread), 0, NULL, 0);

	// load plugins only after gui was ok
	PluginInterface::LoadPlugins();

}

void GUIImplementation::ImGui_Process(ID3D11DeviceContext* pContext)
{

}

void GUIImplementation::ImGui_ProcessDX12(IDXGISwapChain3* pSwapChain)
{
	if (!ms_bInit)
		return;

	g_pd3dCommandQueue = DX12Hook::Get()->GetCommandQueue();

	if (!g_pd3dCommandQueue)
		return;

	if (ms_bShouldReloadFonts)
		ImGui_ReloadFont();

	if (ms_bShouldRefreshRenderTarget)
	{
		ImGui_SetupRenderTargetsDX12(pSwapChain);
		ms_bShouldRefreshRenderTarget = false;
	}

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	GUI_Process();
	
	ImGui::EndFrame();

	UINT backBufferIdx = pSwapChain->GetCurrentBackBufferIndex();
	GFrameContext& frameContext = frameContextData[backBufferIdx];


	ID3D12CommandAllocator* commandAllocator = nullptr;
	commandAllocator = frameContextData[backBufferIdx].g_commandAllocator;
	commandAllocator->Reset();


	D3D12_RESOURCE_BARRIER barrier = { };
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = frameContext.g_mainRenderTargetResource;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	g_pd3dCommandList->Reset(commandAllocator, nullptr);
	g_pd3dCommandList->ResourceBarrier(1, &barrier);
	g_pd3dCommandList->OMSetRenderTargets(1, &frameContext.g_mainRenderTargetDescriptor, FALSE, nullptr);
	g_pd3dCommandList->SetDescriptorHeaps(1, &g_pd3dSrvDescHeap);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pd3dCommandList);
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	g_pd3dCommandList->ResourceBarrier(1, &barrier);
	g_pd3dCommandList->Close();

	g_pd3dCommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&g_pd3dCommandList));

}

void GUIImplementation::OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	ImGui_Reload(pSwapChain);
}

void GUIImplementation::OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{

}


void GUIImplementation::Shutdown()
{
	if (!ms_bInit)
		return;

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX12_Shutdown();
}

float GUIImplementation::GetDeltaTime()
{
	float delta = 1.0f / 60.0f;
	if (ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}

void GUIImplementation::RequestFontReload()
{
	ms_bShouldReloadFonts = true;
}


LRESULT WINAPI GUIImplementation::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->m_bIsFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->m_bIsFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->OnActivate();
		if (wParam == SettingsMgr->iToggleSlowMoKey)
			TheMenu->OnToggleSlowMotion();
		if (wParam == SettingsMgr->iToggleFreeCameraKey)
			TheMenu->OnToggleFreeCamera();
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

void GUIImplementation::GUI_Process()
{
	ImGui::GetIO().MouseDrawCursor = false;

	static bool ms_bFirstDraw = true;

	if (ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(4500);
		Notifications->PushNotification("MK1Hook %s is running! Press %s to open the menu. Build date: %s\n", MK12HOOK_VERSION, eKeyboardMan::KeyToString(SettingsMgr->iHookMenuOpenKey), __DATE__);
		ms_bFirstDraw = false;
	}

	Notifications->Draw();
	TheMenu->Draw();

}
