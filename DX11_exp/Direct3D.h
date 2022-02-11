#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

/// <summary>
/// Direct3D �p�N���X
/// </summary>
class Direct3D {

public:

	/// <summary>
	///  Direct3D �f�o�C�X:
	/// �O���t�B�b�N�֌W�̑f�ނ�n��(�摜��|���S����)
	/// </summary>
	ComPtr<ID3D11Device> m_divice;

	/// <summary>
	/// Direct3D �f�o�C�X�R���e�L�X�g:
	/// �f�ނ��g�p����BackBuffer�ɕ`��(���C��)
	/// </summary>
	ComPtr<ID3D11DeviceContext> m_deviceContext;

	/// <summary>
	/// �X���b�v�`�F�[��:
	/// ���ڃE�B���h�E�ɕ`�悹���A�����(BackBuffer)�ƃE�B���h�E��؂�ւ���
	/// </summary>
	ComPtr<IDXGISwapChain> m_swapChain;

	/// <summary>
	/// �o�b�N�o�b�t�@�[��RT�r���[:
	/// BackBuffer�ɃA�N�Z�X���邽�߂̃n���h��(����p)
	/// </summary>
	ComPtr<ID3D11RenderTargetView> m_backBufferView;

	/// <summary>
	/// Direct3D �̏�����
	/// </summary>
	/// <param name="hWnd">�E�B���h�E�n���h��</param>
	/// <param name="width">��ʕ�</param>
	/// <param name="height">��ʍ���</param>
	/// <returns></returns>
	bool Initialize(HWND hWnd, int width, int height);

private:

	// �V���O���g��

	static inline Direct3D* s_instance;
	Direct3D() {}

public:

	/// <summary>
	/// �C���X�^���X�̍쐬
	/// </summary>
	static void CreateInstance() {
		DeleteInstance();
		s_instance = new Direct3D();
	}

	/// <summary>
	/// �C���X�^���X�̍폜
	/// </summary>
	static void DeleteInstance() {
		if (s_instance != nullptr) {
			delete s_instance;
			s_instance = nullptr;
		}
	}

	/// <summary>
	/// �C���X�^���X�̎擾
	/// </summary>
	/// <returns></returns>
	static Direct3D& GetInstance() {
		return *s_instance;
	}


};

// �C���X�^���X�擾�p�}�N��
#define D3D Direct3D::GetInstance()