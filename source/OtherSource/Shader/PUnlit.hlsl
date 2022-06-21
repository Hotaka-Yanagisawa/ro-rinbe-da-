//--- �萔�o�b�t�@
Texture2D tex : register(t0);
SamplerState samp : register(s0);

//--- ���̓f�[�^
struct PS_IN {

	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

//--- ���C��
float4 main(PS_IN PIN) : SV_Target
{
	float4 color = tex.Sample(samp, PIN.uv) * PIN.color;
	if (color.a <= 0.2f) discard;

	return color;
}
