//--- 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
	float4x4 World;
};
cbuffer ConstantBuffer : register(b1)
{
	float4x4 View;
	float4x4 Proj;
};

//--- 入力データ
struct VS_IN
{
	float3 pos : POSITION0;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

//--- 出力データ
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 wPos : TEXCOORD3;
};

//--- メイン
VS_OUT main(VS_IN VIN)
{
	VS_OUT VOUT;

	VOUT.pos = float4(VIN.pos, 1);
	VOUT.pos = mul(VOUT.pos, World);
	VOUT.wPos = VOUT.pos;
	VOUT.pos = mul(VOUT.pos, View);
	VOUT.pos = mul(VOUT.pos, Proj);

	VOUT.uv = VIN.uv;
	VOUT.color = VIN.color;
	VOUT.normal = mul(VIN.normal, (float3x3)World);

	return VOUT;
}
