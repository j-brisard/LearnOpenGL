#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 color = vec3(0.0);
    float offset = 1.0/600.0; //Define how far from the center pixel in the kernel we sample in the screenTexture
    vec3 col1, col2, col3;
    col1 = vec3(0);
    col2 = vec3(0,1,0);
    col3 = vec3(0);


    /*
    //Blur
    col1 = vec3(1.0/9.0,1.0/9.0,1.0/9.0);
    col2 = vec3(1.0/9.0,1.0/9.0,1.0/9.0);
    col3 = vec3(1.0/9.0,1.0/9.0,1.0/9.0);
    */

    /*
    //Emboss
    col1 = vec3(-2,-1,0);
    col2 = vec3(-1,1,1);
    col3 = vec3(0,1,2);
    */

    /*
    //Sharpen
    col1 = vec3(-1,-1,-1);
    col2 = vec3(-1,9,-1);
    col3 = vec3(-1,-1,-1);
    */

    /*
    //Outline
    col1 = vec3(-1,-1,-1);
    col2 = vec3(-1,8,-1);
    col3 = vec3(-1,-1,-1);
    */

    mat3 kernel = mat3(col1,col2,col3);

    for (int i=-1; i<2;i++){
        for (int j=-1; j<2;j++){
            color += kernel[j+1][i+1]*vec3(texture(screenTexture, vec2(TexCoords.x+i*offset, TexCoords.y+j*offset)));
        }
    }
    FragColor = vec4(color, 1.0);

    /*
    //Grayscale PostProcessing
    FragColor = texture(screenTexture,TexCoords);
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