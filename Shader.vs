#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;

void main(){
    const float offset = 2.01;
	
	vec3 pos = vertexPosition_modelspace;
	pos.x += float(gl_InstanceID) * offset;
	
	gl_Position = MVP * vec4(pos, 1.0);
	UV = vertexUV;
}