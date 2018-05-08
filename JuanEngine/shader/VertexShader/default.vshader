struct VS_INPUT
{
	float2 pos : POSITION;
	float4 col : COLOR0;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
};

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output;
	output.pos = float4(input.pos,1,1);
	output.col = input.col;
	return output; 
}