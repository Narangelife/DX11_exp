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

		// 頂点バッファの作成 ==========================

		//頂点バッファの設定
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //デバイスにバインドするときの種類
		vbDesc.ByteWidth = sizeof(v); //作成するバッファのサイズ
		vbDesc.MiscFlags = 0; // その他のフラグ
		vbDesc.StructureByteStride = 0; // 構造化バッファの構造体のサイズ
		vbDesc.Usage = D3D11_USAGE_DEFAULT; //バッファの使用法
		vbDesc.CPUAccessFlags = 0;

		//頂点バッファの作成
		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 }; //書き込むデータ
		D3D.m_divice->CreateBuffer(&vbDesc, &initData, &vb); // 作成！

		// 描画スタート ================================

		//頂点バッファの設定
		UINT stride = sizeof(VertexType);
		UINT offset = 0;
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //プリミティブトポロジーのセット

		//シェーダーをセット
		D3D.m_deviceContext->VSSetShader(D3D.m_VS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_PS.Get(), 0, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_InputLayout.Get());


		D3D.m_deviceContext->Draw(6, 0);
	}

	// バックバッファの中身を画面に描画
	D3D.m_swapChain->Present(1, 0);
}