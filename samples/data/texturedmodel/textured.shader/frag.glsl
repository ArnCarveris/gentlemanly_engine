#version 100
precision highp float;

uniform sampler2D tex;

varying vec2 tex_coords;

void main()
{
	gl_FragColor = texture2D(tex, tex_coords);

	if(gl_FragColor.a < 0.1) discard;

}
