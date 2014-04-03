#version 130

//Same fragment shader as lab1

in vec4 pass_color;

out vec4 out_color;

void main()
{
	out_color = pass_color;
}
