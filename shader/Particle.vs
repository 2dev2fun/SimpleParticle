#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 vs_Color;

uniform float uPointSize;

void main() {
	vs_Color = aColor;
	gl_Position = vec4(aPosition, 0.0f, 1.0f);
	gl_PointSize = uPointSize;
}
