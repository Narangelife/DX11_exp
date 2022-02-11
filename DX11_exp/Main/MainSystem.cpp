#include "MainSystem.h"
#include "../Direct3D.h"

void MainSystem::Initialize() {

}

void MainSystem::Execute() {
	float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);

	// バックバッファの中身を画面に描画
	D3D.m_swapChain->Present(1, 0);
}