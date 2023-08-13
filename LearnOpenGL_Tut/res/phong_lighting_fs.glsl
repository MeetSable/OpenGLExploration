#version 460 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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

uniform vec3 viewPos;

in vec2 TexCoord;
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
	vec3 ambient = 
    	light.ambient
    	* vec3(texture(material.diffuse, TexCoord));
    
    if(vec3(texture(material.specular, TexCoord)) == vec3(0.0, 0.0, 0.0))
        ambient = vec3(texture(material.emission, TexCoord));
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, light.position), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	return ambient + diffuse + specular;
}