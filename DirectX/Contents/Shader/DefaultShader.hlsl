Texture2D texture2d;

SamplerState samplerState;

matrix world;

matrix view;

matrix projection;

float4 color;

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

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.texcoord = input.texcoord;

	output.normal = input.normal;

	return output;
}

float4 PS(PSInput input) : SV_Target
{
	return texture2d.Sample(samplerState, input.texcoord) * color;
}

BlendState SrcAlphaBlendingAdd
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_COLOR;
	DestBlend = INV_SRC_COLOR;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};

BlendState NoBlend
{
	BlendEnable[0] = false;
};

BlendState AlphaBlend
{
	//AlphaToCoverageEnable = TRUE; //acts as an Alpha Test, clipping pixels with alpha<0.5
	//IndependentBlendEnable = TRUE; //no worky
	BlendEnable[0] = true;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
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

technique11 Blend
{
	pass P0
	{
		SetBlendState(SrcAlphaBlendingAdd, float4(1.0f, 1.0f, 1.0f, 1.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
