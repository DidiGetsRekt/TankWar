#version 120
uniform sampler2D texture;
uniform float TimeVar;

void main() {
	
    vec2 coord = gl_TexCoord[0].xy;
    vec4 pixel_color = texture2D(texture, coord);
	pixel_color.r = mod(TimeVar, 1.0);
	pixel_color.g = mod(-TimeVar, 1.0);
	pixel_color.b = mod(-TimeVar*2, 1.0);
	gl_FragColor = pixel_color*gl_Color;
}