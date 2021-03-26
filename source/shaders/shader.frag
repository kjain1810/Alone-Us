#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragLocation;

// output data
out vec3 color;

uniform int status;
uniform vec3 location;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    color = fragColor;
    if(status == 0)
    {
        float distance = distance(location.xy, fragLocation.xy);
        if(distance > 0.5)
            color = vec3(52.0/256.0, 73.0/256.0, 94.0/256.0);
    }
}
