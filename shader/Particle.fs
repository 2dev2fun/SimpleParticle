#version 330 core

in vec4 vs_Color;
out vec4 fs_Color;

void main() {
	vec2 circleCoord = 2.0f * gl_PointCoord - 1.0f;
	if (dot(circleCoord, circleCoord) > 1.0f) {
		discard;
	}

	fs_Color = vs_Color;
}
