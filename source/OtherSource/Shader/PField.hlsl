//--- 定数バッファ
Texture2D tex : register(t0);
SamplerState samp : register(s0);

//--- 入力データ
struct PS_IN {

	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 wPos : TEXCOORD3;
};

//--- メイン
float4 main(PS_IN PIN) : SV_Target
{
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;

	float coord = PIN.wPos.x * PIN.wPos.x + PIN.wPos.z * PIN.wPos.z;
	if ((coord > (250 * 250)) && (coord < (255 * 255)))
		color.rgb *= 1.5f;

	return color;
}
