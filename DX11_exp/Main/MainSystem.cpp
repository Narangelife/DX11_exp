#include "MainSystem.h"
#include "../Direct3D.h"

void MainSystem::Initialize() {

}

void MainSystem::Execute() {
	float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);

	// �o�b�N�o�b�t�@�̒��g����ʂɕ`��
	D3D.m_swapChain->Present(1, 0);
}