#include <iostream>
#include <math.h>
 
//OPENGL INCLUDES.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <loadShader.cpp>

//GLM INCLUDES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#pragma warning(disable : 4996) // stops fopen error being deprecated

GLuint loadBMP_custom(const char* imagepath) {
    unsigned char header[54];
    unsigned int dataPos, width, height, imageSize;
    unsigned char* data;
    FILE* file = fopen(imagepath, "rb");
    if (!file) { printf("Image could not be opened\n"); return 0; }
    if (fread(header, 1, 54, file) != 54) {
        printf("Not a correct BMP file\n");
        return false;
    }
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }
    dataPos = *(int*)&(header[0x0a]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;
    data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLFWwindow* window;


int main(){
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
    }
    //GLFWwindow* window;
    int width = 1024; int height = 700;
    window = glfwCreateWindow(width, height, "Paradise", NULL, NULL);
    if (!window) {
        std::cout << "Failed to initialize window!" << std::endl;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "failed to initialize GLEW!" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    /*static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f - 0.000004f,
    0.000103f, 1.0f - 0.336048f,
    0.335973f, 1.0f - 0.335903f,
    1.000023f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.336024f, 1.0f - 0.671877f,
    0.667969f, 1.0f - 0.671889f,
    1.000023f, 1.0f - 0.000013f,
    0.668104f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.000059f, 1.0f - 0.000004f,
    0.335973f, 1.0f - 0.335903f,
    0.336098f, 1.0f - 0.000071f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.336024f, 1.0f - 0.671877f,
    1.000004f, 1.0f - 0.671847f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.668104f, 1.0f - 0.000013f,
    0.335973f, 1.0f - 0.335903f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.668104f, 1.0f - 0.000013f,
    0.336098f, 1.0f - 0.000071f,
    0.000103f, 1.0f - 0.336048f,
    0.000004f, 1.0f - 0.671870f,
    0.336024f, 1.0f - 0.671877f,
    0.000103f, 1.0f - 0.336048f,
    0.336024f, 1.0f - 0.671877f,
    0.335973f, 1.0f - 0.335903f,
    0.667969f, 1.0f - 0.671889f,
    1.000004f, 1.0f - 0.671847f,
    0.667979f, 1.0f - 0.335851f
    };*/

    static const GLfloat g_uv_buffer_data[] = {
        //1
        0.374f, 3.0f,
        0.622f, 1.0f,
        0.622f, 0.749f,
        0.374f, 1.0f,
        0.374f, 0.749f,
        0.622f, 1.0f,
        //4 <--- (Face 2 & 3 are top and bottom faces of cube)
        0.374f, 0.749f,
        0.622f, 0.749f,
        0.123f, 0.501f,
        0.374f, 0.749f,
        0.374f, 0.501f,
        0.622f, 0.501f,
        //5
        0.374f, 0.501f,
        0.123f, 0.501f,
        0.622f, 0.252f,
        0.374f, 0.501f,
        0.374f, 0.252f,
        0.622f, 0.252,
        //6
        0.374f, 0.252f,
        0.622f, 0.252f,
        0.622f, 0.0f,
        0.373f, 0.25f,
        0.373f, 0.0f,
        0.622f, 0.0f,
        //2 <---- (top face)
        0.622f, 0.749f,
        0.874f, 0.749f,
        0.874f, 0.501f,
        0.622f, 0.749f,
        0.622f, 0.501f,
        0.874f, 0.501f,
        //3 <---- (bottom face)
        0.127f, 0.749f,
        0.374f, 0.749f,
        0.374f, 0.501f,
        0.127f, 0.749f,
        0.123f, 0.501f,
        0.374f, 0.501f

    };


    //GLuint Texture = loadBMP_custom("uvtemplate.bmp");

    //stb image code for loading
    int w, h, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("GrassUV1.png", &w, &h, &channels, STBI_rgb);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    const int cubeAmount = 4.0f;
    glm::vec2 cubes[cubeAmount];
    unsigned int index;

    for (int y = 0; y < cubeAmount; y++) {
        glm::vec2 translation;
        translation.y = (float)y / 10.0f;
        /*for (int x = 0; x < cubeAmount; x += 1) {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f;
            std::cout << y << std::endl;
            cubes[index++] = translation;
            
        }
        cubes[index++] = translation;*/
        
    }




    GLuint programID = LoadShaders("Shader.vs", "Shader.fs");

    //store instanced data in an array buffer
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* cubeAmount, &cubes[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint texturebuffer;
    glGenBuffers(1, &texturebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glVertexAttribDivisor(2, 1);
    

    glEnable(GL_CULL_FACE);

    float offset = 2.5f;
    float radius = 50.0f;
    glm::mat4* ModelMatrices;
    ModelMatrices = new glm::mat4(cubeAmount);
    /*for (unsigned int i = 0; i < cubeAmount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        float angle = (float)i / (float)cubeAmount * 360.0f;
        float displacement = (rand() % (int)(2.0f * offset * 100.0f)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2.0f * offset * 100.0f)) / 100.0f - offset;
        float y = displacement * 0.4f;
        displacement = (rand() % (int)(2.0f * offset * 100.0f)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;

        model = glm::translate(model, glm::vec3(x, y, z));

        ModelMatrices[i] = model;
    }*/



    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f / 255.0f, 170.0f / 255.0f, 204.0f / 255.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3, GL_FLOAT, GL_FALSE,
            0,
            (void*)0
        );

        computeMatricesFromInputs();

        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);

        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1.0f, 0.0f, 1.0f));

        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; // must be compiled after all matrix changes

        GLuint MatrixID = glGetUniformLocation(programID, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        //glDrawArrays(GL_TRIANGLES, 0, 12*3);
        
        glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, cubeAmount);
        
       
        glDisableVertexAttribArray(0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}