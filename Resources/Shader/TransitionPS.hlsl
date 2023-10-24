Texture2D g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

namespace s3d
{
    struct PSInput
    {
        float4 position : SV_POSITION;
        float4 color : COLOR0;
        float2 uv : TEXCOORD0;
    };
}

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_sdfOutlineColor;
    float4 g_sdfShadowColor;
    float4 g_internal;
}

cbuffer CBuffer : register(b1)
{
    float g_ratio;
}

float4 main(s3d::PSInput input) : SV_TARGET
{
    float4 output = float4(0.f, 0.f, 0.f, 1.f);
    float4 texColor = g_texture0.Sample(g_sampler0, input.uv);
            
    output.a = step(texColor.r, g_ratio);
    
    return output;
}
