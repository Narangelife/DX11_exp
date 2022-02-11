#include "MainSystem.h"
#include "../Direct3D.h"
#include "../framework.h"

void MainSystem::Initialize() {

}

void MainSystem::Execute() {
	float color[4] = { 0.25f, 1.0f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);

	{
		struct VertexType {
			DirectX::XMFLOAT3 POS;
		};

		VertexType v[6] = {
			{{0, 1.0f, 0}},
			{{0.87f, 0.5f, 0}},
			{{-0.87f, 0.5f, 0}},
			{{0.87f, -0.5f, 0}},
			{{-0.87f, -0.5f, 0}},
			{{0, -1.0f, 0}}
		};

		// ���_�o�b�t�@�̍쐬 ==========================

		//���_�o�b�t�@�̐ݒ�
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //�f�o�C�X�Ƀo�C���h����Ƃ��̎��
		vbDesc.ByteWidth = sizeof(v); //�쐬����o�b�t�@�̃T�C�Y
		vbDesc.MiscFlags = 0; // ���̑��̃t���O
		vbDesc.StructureByteStride = 0; // �\�����o�b�t�@�̍\���̂̃T�C�Y
		vbDesc.Usage = D3D11_USAGE_DEFAULT; //�o�b�t�@�̎g�p�@
		vbDesc.CPUAccessFlags = 0;

		//���_�o�b�t�@�̍쐬
		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 }; //�������ރf�[�^
		D3D.m_divice->CreateBuffer(&vbDesc, &initData, &vb); // �쐬�I

		// �`��X�^�[�g ================================

		//���_�o�b�t�@�̐ݒ�
		UINT stride = sizeof(VertexType);
		UINT offset = 0;
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�v���~�e�B�u�g�|���W�[�̃Z�b�g

		//�V�F�[�_�[���Z�b�g
		D3D.m_deviceContext->VSSetShader(D3D.m_VS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_PS.Get(), 0, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_InputLayout.Get());


		D3D.m_deviceContext->Draw(6, 0);
	}

	// �o�b�N�o�b�t�@�̒��g����ʂɕ`��
	D3D.m_swapChain->Present(1, 0);
}