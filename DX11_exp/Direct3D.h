#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

/// <summary>
/// Direct3D 用クラス
/// </summary>
class Direct3D {

public:

	/// <summary>
	///  Direct3D デバイス:
	/// グラフィック関係の素材を創造(画像やポリゴン等)
	/// </summary>
	ComPtr<ID3D11Device> m_divice;

	/// <summary>
	/// Direct3D デバイスコンテキスト:
	/// 素材を使用してBackBufferに描画(メイン)
	/// </summary>
	ComPtr<ID3D11DeviceContext> m_deviceContext;

	/// <summary>
	/// スワップチェーン:
	/// 直接ウィンドウに描画せず、裏画面(BackBuffer)とウィンドウを切り替える
	/// </summary>
	ComPtr<IDXGISwapChain> m_swapChain;

	/// <summary>
	/// バックバッファーのRTビュー:
	/// BackBufferにアクセスするためのハンドル(操作用)
	/// </summary>
	ComPtr<ID3D11RenderTargetView> m_backBufferView;

	/// <summary>
	/// Direct3D の初期化
	/// </summary>
	/// <param name="hWnd">ウィンドウハンドル</param>
	/// <param name="width">画面幅</param>
	/// <param name="height">画面高さ</param>
	/// <returns></returns>
	bool Initialize(HWND hWnd, int width, int height);

private:

	// シングルトン

	static inline Direct3D* s_instance;
	Direct3D() {}

public:

	/// <summary>
	/// インスタンスの作成
	/// </summary>
	static void CreateInstance() {
		DeleteInstance();
		s_instance = new Direct3D();
	}

	/// <summary>
	/// インスタンスの削除
	/// </summary>
	static void DeleteInstance() {
		if (s_instance != nullptr) {
			delete s_instance;
			s_instance = nullptr;
		}
	}

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns></returns>
	static Direct3D& GetInstance() {
		return *s_instance;
	}


};

// インスタンス取得用マクロ
#define D3D Direct3D::GetInstance()