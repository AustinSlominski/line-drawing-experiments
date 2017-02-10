#version 120

uniform sampler2D tex0;
varying vec2 texCoordVarying;

uniform float time;
uniform float speed;
uniform float band_width;



vec2 center = vec2(0.5,0.5);

void main() {
    vec2 uv = texCoordVarying;
    //normalized makes a fan
    
    float floor = 0.1;
    float ceiling = 1.0;
    
    vec3 col = vec4(uv,0.5+0.5*sin(time),1.0).xyz;
    
    float x = (center.x-uv.x);
    float y = (center.y-uv.y);
    
    float r = -sqrt(x*x + y*y); //uncoment this line to symmetric ripples
//    float r = -(x*x + y*y);
//    float z = sin((r+time*speed)/0.053);
//    float z = sin((r+time*speed)/band_width);
    float z = clamp(sin((r+time*speed)/band_width),floor,ceiling);
    
    gl_FragColor = vec4(z,z,z,1.0);
}

/*
 
 vec2 center = vec2(0.5,0.5);
 float speed = 0.035;
 float invAr = iResolution.y / iResolution.x;
 
 void mainImage( out vec4 fragColor, in vec2 fragCoord )
 {
	vec2 uv = fragCoord.xy / iResolution.xy;
 
	vec3 col = vec4(uv,0.5+0.5*sin(iGlobalTime),1.0).xyz;
 
 vec3 texcol;
 
	float x = (center.x-uv.x);
	float y = (center.y-uv.y) *invAr;
 
	//float r = -sqrt(x*x + y*y); //uncoment this line to symmetric ripples
	float r = -(x*x + y*y);
	float z = 1.0 + 0.5*sin((r+iGlobalTime*speed)/0.013);
	
	texcol.x = z;
	texcol.y = z;
	texcol.z = z;
	
	fragColor = vec4(col*texcol,1.0);
 }
*/
