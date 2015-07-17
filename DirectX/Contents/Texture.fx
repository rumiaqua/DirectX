matrix Projection;

Texture2D txDiffuse;

SamplerState samLinear;

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Nor : NORMAL;
};

struct PS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, Projection);
	output.Tex = input.Tex;
	
	return output;
}

float4 PS( PS_INPUT input) : SV_Target
{
	return txDiffuse.Sample(samLinear, input.Tex);
}

technique11 Default
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
		SetComputeShader(NULL);
	}
}
