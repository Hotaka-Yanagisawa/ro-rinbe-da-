//--- 入力データ
struct PS_IN {

	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

//--- メイン
float main(PS_IN PIN) : SV_Target
{
	float ZVal = PIN.pos.z / PIN.pos.w;
	return ZVal;
}
