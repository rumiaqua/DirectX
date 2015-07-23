Texture2D txDiffuse;

SamplerState samLinear;

matrix World;

matrix View;

matrix Projection;

float4 vMeshColor;

struct VSInput
{
	float4 position : POSITION;

	float2 texcoord : TEXCOORD0;

	float3 normal : NORMAL;
};

struct PSInput
{
	float4 position : SV_POSITION;

	float2 texcoord : TEXCOORD0;

	float3 normal : NORMAL;
};

PSInput VS(VSInput input)
{
	PSInput output = (PSInput)0;

	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);

	output.texcoord = input.texcoord;

	output.normal = input.normal;

	return output;
}

float4 PS(PSInput input) : SV_Target
{
	return txDiffuse.Sample(samLinear, input.texcoord) * vMeshColor;
}

technique11 Default
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
