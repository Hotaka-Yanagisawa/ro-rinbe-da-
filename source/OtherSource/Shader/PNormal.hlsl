//--- 定数バッファ
struct Material
{
	float4 diffuse;
	float4 ambient;
	float4 specular;
	float4 emissive;
};
cbuffer ConstantBuffer : register(b0)
{
	Material objMat;
};
cbuffer ConstantBuffer : register(b1)
{
	float3 lightDir;
	Material lightMat;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);

//--- 入力データ
struct PS_IN {

	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

//--- メイン
float4 main(PS_IN PIN) : SV_Target
{
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;

	float4 diffuse = objMat.diffuse * lightMat.diffuse * max(dot(normalize(PIN.normal), -lightDir), 0);
	float4 ambient = objMat.ambient * lightMat.ambient;
	color.rgb *= diffuse + ambient;

	return color;
}
