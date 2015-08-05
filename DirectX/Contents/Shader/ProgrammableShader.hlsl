Texture2D texture2d;

SamplerState samplerState;

float4 diffuseLight;

float4 diffuseMaterial;

float3 lightPosition;

matrix modelView;

matrix modelViewProjection;

matrix normal;

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

	float4 color : COLOR;
};

PSInput VS(VSInput input)
{
	PSInput output = (PSInput)0;

	// temp variable
	float3 N = normalize(mul(input.normal, (float3x3)normal));

	float3 pos = mul(input.position, modelView).xyz;

	float3 L = normalize(lightPosition - pos);

	float3 V = normalize(-pos);

	float3 H = normalize(L + V);

	// calc
	float diffuse = max(dot(N, L), 0.0f);

	float4 diffuseColor = diffuseLight * diffuseMaterial * diffuse;

	float4 color = diffuseColor;

	// output
	output.position = mul(input.position, modelViewProjection);

	output.texcoord = input.texcoord;

	color = 1.0f;

	output.color = saturate(color);

	return output;
}

float4 PS(PSInput input) : SV_Target
{
	return texture2d.Sample(samplerState, input.texcoord) * input.color;
}

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
	RenderTargetWriteMask[0] = 0x0F;
};

technique11 Diffuse
{
	pass P0
	{
		SetBlendState(NoBlend, float4(1.0f, 1.0f, 1.0f, 1.0f), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
