//--- 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
	float4 val;
};

//--- 入力データ
struct GS_IN
{
	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 wPos : TEXCOORD3;
};

//--- 出力データ
struct GS_OUT
{
	float4 pos : SV_POSITION;
	float4 color : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 wPos : TEXCOORD3;
};

[maxvertexcount(3)]
void main(triangle GS_IN In[3], 
	inout TriangleStream<GS_OUT> TriStream)
{
	GS_OUT Out;

	float4 vec = (In[0].pos + In[1].pos + In[2].pos) / 3.0;

	for (int i = 0; i < 3; ++i)
	{
		Out = In[i];

		if (val.x > 0)
		{
			Out.pos.x = In[i].pos.x + vec.x * val.x * sin(val.y);
			Out.pos.y = In[i].pos.y + vec.y * val.x * sin(val.y);
		}

		TriStream.Append(Out);
	}
	TriStream.RestartStrip();
}
