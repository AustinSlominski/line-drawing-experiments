#version 120

uniform sampler2D tex0;
uniform sampler2D alpha_mask;
uniform vec2 range;
varying vec2 texCoordVarying;

void main()
{
    vec2 uv = texCoordVarying;
    vec4 layer = texture2D(tex0,uv);
    float alpha = texture2D(alpha_mask,uv).r;
    
    if (layer.a != 0) {
        if(alpha > range.x){
//            layer.a = alpha;
//            layer.a = 1.0;
        }else{
            layer.a = 0;
        }
    }
    
    gl_FragColor = layer;
}
