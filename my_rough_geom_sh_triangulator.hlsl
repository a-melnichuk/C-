cbuffer cbPerFrame
{
	float4x4 gViewProj; 
	float4x4 gWorld; 
};
 

struct VS_IN
{
	float3 posL : POSITION;
	float4 diffuse : DIFFUSE;
	float4 spec : SPECULAR;
};

struct VS_OUT
{
	float3 posL : POSITION;
	float4 posH : SV_POSITION;
	float4 diffuse : DIFFUSE;
	float4 spec : SPECULAR;
};

struct GS_OUT
{
	float4 posH    : SV_POSITION;
   	float3 posW    : POSITION;
   	float3 normalW : NORMAL;
  	float4 diffuse : DIFFUSE;
	float4 spec : SPECULAR;
};

 
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	float4x4 gWVP = mul(gWorld,gViewProj);
	vOut.posH = mul(float4(vIn.posL, 1.0f), gWVP);
	//pass data into geometry shader stage.
	vOut.posL  = vIn.posL;
	vOut.diffuse = vIn.diffuse;
	vOut.spec = vIn.spec;

	return vOut;
}

[maxvertexcount(28)]
void GS(triangle VS_OUT gIn[3],
    inout TriangleStream<GS_OUT> triStream)
{
    	GS_OUT gOut;
	float4x4 gWVP = mul(gWorld,gViewProj);
	gOut.spec    = gIn[0].spec;
	gOut.diffuse = gIn[0].diffuse;
	float3 e0 = gIn[1].posL - gIn[0].posL;
    	float3 e1 = gIn[2].posL - gIn[0].posL;
    	float3 n  = normalize( cross(e0, e1) );
	gOut.normalW = mul(float4(n, 0.0f), gWorld);

   	int level = 2;
	float depth = 3 + 2*(level-1); 

	float3 u = gIn[2].posL-gIn[1].posL;
	float3 v = gIn[0].posL-gIn[1].posL;
	

	for(float i=1;i<depth;i+=1.0f)
	{
		
		float s =i/(depth-1);
		float s_prev = (i-1)/(depth-1);

		for(float j=0;j<i+1;j+=1.0f)
		{
			//set lambda to be maximum of delta s
			float lambda = s;
					
			float t = j/i;
			//normalization maps point to point on unit sphere
			//when t = s, v = 0; when t = 0, u = 0;
			float3 pt = normalize( gIn[1].posL +(s-t*lambda)*v + t*lambda*u );

			gOut.posW    = mul(float4(pt, 1.0f), gWorld);
			gOut.posH    = mul(float4(pt, 1.0f), gWVP);	
			triStream.Append(gOut);

			lambda = s_prev;
			float3 pt_prev = normalize( gIn[1].posL +(s_prev - t*lambda)*v + t*lambda*u );
			gOut.posW    = mul(float4(pt_prev, 1.0f), gWorld);
			gOut.posH    = mul(float4(pt_prev, 1.0f), gWVP);
			
			triStream.Append(gOut);
		}
		triStream.RestartStrip();
	}
	
}
