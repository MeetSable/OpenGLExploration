#version 460 core
out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

vec3 PhongShader();

void main()
{
	FragColor = vec4(PhongShader(), 1.0);
}

vec3 PhongShader()
{
    // ambient
	vec3 ambient = light.ambient * material.ambient;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightPos), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128.0);
	vec3 specular = light.specular * (spec * material.specular);

	return ambient + diffuse + specular;
}