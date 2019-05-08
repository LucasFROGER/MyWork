struct VS_INPUT
{
	float4 pos: POSITION;
	float4 texCoord: TEXCOORD;
	float4 color: COLOR;
};

struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float2 texCoord: TEXCOORD;
	float4 color: COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 worldMat;
	float4x4 vpMat;
};

VS_OUTPUT main(VS_INPUT input, uint vertexID : SV_VertexID)
{
	VS_OUTPUT output;

	// vert id 0 = 0000, uv = (0, 0)
	// vert id 1 = 0001, uv = (1, 0)
	// vert id 2 = 0010, uv = (0, 1)
	// vert id 3 = 0011, uv = (1, 1)
	float2 uv = float2(vertexID & 1, (vertexID >> 1) & 1);

	// set the position for the vertex based on which vertex it is (uv)
	float4 newPos = float4(input.pos.x + (input.pos.z * uv.x), input.pos.y - (input.pos.w * uv.y), 0, 1);
	float4x4 mvp = mul(worldMat, vpMat);
	newPos = mul(newPos, mvp);
	output.pos = newPos;
	output.color = input.color;
	// set the texture coordinate based on which vertex it is (uv)
	output.texCoord = float2(input.texCoord.x + (input.texCoord.z * uv.x), input.texCoord.y + (input.texCoord.w * uv.y));

	return output;
}