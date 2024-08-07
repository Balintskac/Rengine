#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

out vec3 FragPos;
out vec3 Normal;
out vec2 Texture;
out vec4 fragPosLightSpace;

uniform mat4 model;
uniform mat4 inverse_model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

uniform bool reverse_normals;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Texture = aTexture;
    /*
    if(reverse_normals) // a slight hack to make sure the outer large cube displays lighting from the 'inside' instead of the default 'outside'.
        Normal = transpose(inverse(mat3(model))) * (-1.0 * aNormal);
    else
        Normal = transpose(inverse(mat3(model))) * aNormal;
        */
     Normal = mat3(transpose(inverse_model)) * aNormal;  
    fragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0);
}