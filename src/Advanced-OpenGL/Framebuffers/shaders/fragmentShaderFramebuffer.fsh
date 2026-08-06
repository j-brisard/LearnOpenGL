#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    FragColor = vec4(0.0);

    vec3 col1 = vec3(3,3,3);
    vec3 col2 = vec3(3,-24,3);
    vec3 col1 = vec3(3,3,3);

    mat3 kernel = mat3(col1,col2,col3);

    for (int i=-1; i<2;i++){
        for (int j=0; j<3;j++){
            FragColor += kernel[j][i]*texture(screenTexture, vec2(TexCoords.x+i, TexCoords.y+j));
        }
}


    /*
    //Grayscale PostProcessing
    //FragColor = texture(screenTexture,TexCoords);
    float average = (0.2126*FragColor.x + 0.7152*FragColor.y + 0.0722*FragColor.z); //Rec 709 Factors for more accurate results
    FragColor = vec4(average,average,average,1.0);
    */

    /*
    //Complete Inversion PostProcessing
    FragColor = vec4(1-vec3(texture(screenTexture, TexCoords)),1.0);
    /*

    /*
    //Color Component Only Inversion PostProcessing
    vec3 texColor = vec3(texture(screenTexture, TexCoords));
    FragColor = vec4(1-texColor.x, texColor.y, texColor.z ,1.0);
    */

    /*
    //Regular Texture
    FragColor = texture(screenTexture, TexCoords);
    */
}