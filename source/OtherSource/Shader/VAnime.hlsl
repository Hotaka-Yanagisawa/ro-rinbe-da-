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
cbuffer ConstantBuffer : register(b2)
{
	float4x4 Bone[150];
};

//--- 入力データ
struct VS_IN
{
	float3 pos : POSITION0;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 weight : BLENDWEIGHT0;
	uint4 index : BLENDINDICES0;
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
	float4x4 mat = 0;
	mat += Bone[VIN.index.x] * VIN.weight.x;
	mat += Bone[VIN.index.y] * VIN.weight.y;
	mat += Bone[VIN.index.z] * VIN.weight.z;
	mat += Bone[VIN.index.w] * VIN.weight.w;

	VS_OUT VOUT;
	VOUT.pos = float4(VIN.pos, 1);
	VOUT.pos = mul(VOUT.pos, mat);
	VOUT.pos = mul(VOUT.pos, World);
	VOUT.pos = mul(VOUT.pos, View);
	VOUT.pos = mul(VOUT.pos, Proj);

	VOUT.uv = VIN.uv;
	VOUT.color = VIN.color;

	VOUT.normal = VIN.normal;
	VOUT.normal = mul(VOUT.normal, (float3x3)mat);
	VOUT.normal = mul(VOUT.normal, (float3x3)World);

	return VOUT;
}
