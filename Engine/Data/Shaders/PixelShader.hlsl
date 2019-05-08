Texture2D t1 : register(t0);
SamplerState s1 : register(s0);

struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float3 normal: NORMAL;
	float2 uv: UV;
	float3 tan: TANGENT;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
	// return interpolated color
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	return t1.Sample(s1, 1.0 - input.uv);

}