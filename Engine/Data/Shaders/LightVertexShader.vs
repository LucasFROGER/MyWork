struct VS_INPUT
{
	float3 pos: POSITION;
	float3 normal: NORMAL;
	float2 uv: UV;
	float3 tangent: TANGENT;
};

struct VS_OUTPUT
{
	float4 wvpPos : SV_POSITION; // camera pos;
	float3 normal : NORMAL;
	float2 texCoord: UV;
	float3 tangent : TANGENT;
	float4 wPos : POSITION; // lighting pos;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 wMat;
	float4x4 vpMat;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	
	float4 newPosition = float4(input.pos, 1.0f);
	float4 newNormal = float4(input.normal, 1.0f);
	
	newPosition = mul(newPosition, wMat);
	output.wPos = newPosition;
	newPosition = mul(newPosition, vpMat);

	newNormal = normalize(mul(newNormal, transpose(-(wMat))));
	
	output.wvpPos = newPosition;
	output.texCoord = input.uv;
	output.normal = newNormal;
	output.tangent = input.tangent;

	return output;
}