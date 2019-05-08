struct VS_INPUT
{
	float3 pos: POSITION;
	float3 normal: NORMAL;
	float2 uv: UV;
	float3 tan: TANGENT;
};

struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float3 normal: NORMAL;
	float2 uv: UV;
	float3 tan: TANGENT;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 worldMat;
	float4x4 vpMat;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 newPosition = float4(input.pos, 1.0f);
	float4 newNormal = float4(input.normal, 1.0f);

	newPosition = mul(newPosition, worldMat);
	newPosition = mul(newPosition, vpMat);

	newNormal = normalize(mul(newNormal, worldMat));

	output.pos = newPosition;
	output.normal = newNormal;
	output.uv = input.uv;
	output.tan = input.tan;

	return output;
}