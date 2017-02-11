#version 120

varying vec4 position;
varying vec2 texCoordinates;
varying vec3 positionNormalized;

void main()
{
    positionNormalized = normalize(position.xyz);
    texCoordinates = gl_MultiTexCoord0.xy;
    gl_Position = ftransform();
}
