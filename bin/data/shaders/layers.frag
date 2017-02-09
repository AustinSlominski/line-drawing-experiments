#version 120

uniform sampler2D layer_1;
uniform sampler2D layer_2;
uniform sampler2D layer_3;
uniform sampler2D layer_4;
uniform sampler2D layer_5;
uniform sampler2D layer_6;
uniform sampler2D layer_7;
uniform sampler2D alpha_mask;
varying vec2 texCoordVarying;

void main()
{
    vec2 uv = texCoordVarying;
    

    
    if (layer.a != 0) {
        layer.a = texture2D(alpha_mask,uv).r;
    }
    
    gl_FragColor = layer;
}
