// 頂点シェーダーから出力する形式
struct VertexOutput {
	float4 pos : SV_Position;
};

// 頂点シェーダー
VertexOutput VT(float4 pos : POSITION) {
	VertexOutput Out;
	Out.pos = pos;
	return Out;
}

// ピクセルシェーダー
float4 PixcelShader(VertexOutput In) : SV_Target0{
	return float4(0.92f, 0.64f, 1.0f, 1);
}