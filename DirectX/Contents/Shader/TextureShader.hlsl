Texture2D texture2d;

SamplerState samplerState;

matrix world;

matrix projection;

float4 color;

float4 uv;

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
};

PSInput VS(VSInput input)
{
	PSInput output = (PSInput)0;

	// output.position = mul(input.position, projection);
	// output.position = mul(output.position, world);
	output.position = mul(input.position, world);
	output.position = mul(output.position, projection);

	output.texcoord = input.texcoord * float2(uv.z, uv.w) + float2(uv.x, uv.y);

	return output;
}

float4 PS(PSInput input) : SV_Target
{
	return texture2d.Sample(samplerState, input.texcoord) * color;
}

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
	RenderTargetWriteMask[0] = 0x0F;
};

technique11 Default
{
	pass P0
	{
		SetBlendState(NoBlend, float4(1.0f, 1.0f, 1.0f, 1.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
