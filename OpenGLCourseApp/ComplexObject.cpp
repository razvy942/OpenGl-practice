//#define _USE_MATH_DEFINES
//#include <cmath>
//
//#include "ComplexObject.h"
//
//ComplexObject::ComplexObject() {
//    meshList = std::vector<Mesh*>();
//    uniformObjectModelLocation = 0;
//  
//    objectModelMatrix = new glm::mat4(1.0f);
//
//    objectList = std::vector<ComplexObject*>();
//
//    hasModelMatrix = false;
//}
//
//ComplexObject::~ComplexObject() {
//    // Clears the objectlist
//    for (int i = 0; i < objectList.size(); i++) {
//        objectList[i]->ClearObject();
//    }
//
//    // Clean up the meshlist.
//    for (int i = 0; i < meshList.size(); i++) {
//        meshList[i]->~Mesh();
//        delete meshList[i];
//    }
//
//    if (hasModelMatrix) {
//        // If we have set the model matrix, clean it up.
//        ResetModelMatrix();
//    }
//    else {
//        // If not, just clean the pointer.
//        delete objectModelMatrix;
//        objectModelMatrix = NULL;
//    }
//
//    // Destroy the object list.
//    for (int i = 0; i < objectList.size(); i++) {
//        objectList[i]->~ComplexObject();
//        delete objectList[i];
//    }
//}
//
//void ComplexObject::RenderObject() {
//    // If we have a custom transformation...
//    if (hasModelMatrix) {
//        // ... we apply it to our children, rendering them with it.
//        for (int i = 0; i < meshList.size(); i++) {
//            meshList[i]->RenderMesh(*objectModelMatrix, 4);
//        }
//
//        for (int i = 0; i < objectList.size(); i++) {
//            objectList[i]->RenderObject(*objectModelMatrix, 4);
//        }
//    }
//    else {
//        // No transformation means we just render our children as is.
//        for (int i = 0; i < meshList.size(); i++) {
//            meshList[i]->RenderMesh();
//        }
//
//        for (int i = 0; i < objectList.size(); i++) {
//            objectList[i]->RenderObject();
//        }
//    }
//}
//
//void ComplexObject::RenderObject(glm::mat4& modelMatrix, GLuint uniformModel) {
//    glm::mat4 model(1.0f);
//
//    if (hasModelMatrix) {
//        // If we have a custom transformation, we combine it with the provided transformation.
//        model = modelMatrix * *objectModelMatrix;
//    }
//    else {
//        // If we dont have a current transformation, just pass the provided transformation.
//        model = modelMatrix;
//    }
//
//    // Rendering our children
//    for (int i = 0; i < meshList.size(); i++) {
//        meshList[i]->RenderMesh(model, 4);
//    }
//
//    for (int i = 0; i < objectList.size(); i++) {
//        objectList[i]->RenderObject(model, 4);
//    }
//
//}
//
//void ComplexObject::RenderLetters(Texture* cardboard, Texture* silver)
//{
//    
//    // If we have a custom transformation...
//    if (hasModelMatrix)
//    {
//        // ... we apply it to our children, rendering them with it.
//        for (int i = 0; i < meshList.size(); i++)
//        {
//            meshList[i]->RenderMesh(*objectModelMatrix, 4);
//        }
//
//        cardboard->UseTexture();
//
//        objectList[0]->RenderObject(*objectModelMatrix, 4);
//        // objectList[1]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//
//        //glBindTexture(GL_TEXTURE_2D, 0);
//
//        /*silver->UseTexture();
//
//        objectList[2]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//        objectList[3]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//
//        glBindTexture(GL_TEXTURE_2D, 0);*/
//
//    }
//    else
//    {
//        // No transformation means we just render our children as is.
//        for (int i = 0; i < meshList.size(); i++)
//        {
//            meshList[i]->RenderMesh();
//        }
//
//        cardboard->UseTexture();
//
//        objectList[0]->RenderObject(*objectModelMatrix, 4);
//        // objectList[1]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//
//       // glBindTexture(GL_TEXTURE_2D, 0);
//
//        //silver->UseTexture();
//
//        //objectList[2]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//        //objectList[3]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
//
//        //glBindTexture(GL_TEXTURE_2D, 0);
//
//
//    }
//
//}
//
//
//void ComplexObject::ClearObject() {
//    // Clears the meshlist
//    for (int i = 0; i < meshList.size(); i++) {
//        meshList[i]->ClearMesh();
//    }
//
//    // Clears the objectlist
//    for (int i = 0; i < objectList.size(); i++) {
//        objectList[i]->ClearObject();
//    }
//}
//
//void ComplexObject::SetModelMatrix(glm::mat4& matrix, GLuint uniformModelLocation) {
//    if (hasModelMatrix) {
//        // Removing the model matrix from gpu
//        glUniform1f((*this).uniformObjectModelLocation, 0.0f);
//    }
//
//    *objectModelMatrix = matrix;
//    uniformObjectModelLocation = uniformModelLocation;
//
//    hasModelMatrix = true;
//}
//
//void ComplexObject::ResetModelMatrix() {
//    hasModelMatrix = false;
//
//    // Removing the model matrix from gpu
//    glUniform1f((*this).uniformObjectModelLocation, 0.0f);
//
//    uniformObjectModelLocation = 0;
//
//    delete objectModelMatrix;
//    objectModelMatrix = NULL;
//}
//
//glm::mat4& ComplexObject::GetModelMatrix() {
//    if (hasModelMatrix)
//        return *objectModelMatrix;
//    else {
//        // If no matrix has been set for this object, we return a generic identity matrix.
//        // Could throw an exception too, because if someone tries to modify that generic matrix, it wont change this object's matrix.
//        glm::mat4 model = glm::mat4(1.0f);
//        return model;
//    }
//}
//
//void ComplexObject::TranslateModel(GLfloat x, GLfloat y, GLfloat z) {
//    glm::mat4 model = GetModelMatrix();
//    model = glm::translate(model, glm::vec3(x, y, z));
//    glUniformMatrix4fv(uniformObjectModelLocation, 1, GL_FALSE, glm::value_ptr(model));
//}
//
//void ComplexObject::RotateModel(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
//    glm::mat4 model = GetModelMatrix();
//    model = glm::rotate(model, angle, glm::vec3(x, y, z));
//    glUniformMatrix4fv(uniformObjectModelLocation, 1, GL_FALSE, glm::value_ptr(model));
//}
//
//void ComplexObject::ScaleModel(GLfloat xScale, GLfloat yScale, GLfloat zScale) {
//    glm::mat4 model = GetModelMatrix();
//    model = glm::scale(model, glm::vec3(xScale, yScale, zScale));
//    glUniformMatrix4fv(uniformObjectModelLocation, 1, GL_FALSE, glm::value_ptr(model));
//}
//
//void ComplexObject::ShearModel(GLfloat angle) {
//    glm::mat4 model = GetModelMatrix();
//    model = glm::shearY3D(model, angle, 0.0f);
//    glUniformMatrix4fv(uniformObjectModelLocation, 1, GL_FALSE, glm::value_ptr(model));
//}
//
//
//void ComplexObject::Transform(bool* keys) {
//    // Move up when capital W is pressed
//    if (keys[GLFW_KEY_W] && keys[GLFW_KEY_LEFT_SHIFT]) {
//        TranslateModel(0.0f, 0.05f, 0.0f);
//    }
//    // Move left when capital A is pressed
//    if (keys[GLFW_KEY_A] && keys[GLFW_KEY_LEFT_SHIFT]) {
//        TranslateModel(-0.05f, 0.0f, 0.0f);
//    }
//    // Move down when capital S is pressed
//    if (keys[GLFW_KEY_S] && keys[GLFW_KEY_LEFT_SHIFT]) {
//        TranslateModel(0.0f, -0.05f, 0.0f);
//    }
//    // Move right when capital D is pressed
//    if (keys[GLFW_KEY_D] && keys[GLFW_KEY_LEFT_SHIFT]) {
//        TranslateModel(0.05f, 0.0f, 0.0f);
//    }
//    // Rotate Model 5deg right
//    if (keys[GLFW_KEY_D] && !keys[GLFW_KEY_LEFT_SHIFT]) {
//        RotateModel(0.0f, 1.0f, 0.0f, (5.0f * M_PI) / 180.0f);
//    }
//    // Rotate Model 5deg left
//    if (keys[GLFW_KEY_A] && !keys[GLFW_KEY_LEFT_SHIFT]) {
//        RotateModel(0.0f, 1.0f, 0.0f, -(5.0f * M_PI) / 180.0f);
//    }
//    // Scale up with U is pressed
//    if (keys[GLFW_KEY_U]) {
//        ScaleModel(1.01f, 1.01f, 1.01f);
//    }
//    // Scale down with J is pressed
//    if (keys[GLFW_KEY_J] && !keys[GLFW_KEY_LEFT_SHIFT]) {
//        ScaleModel(0.99f, 0.99f, 0.99f);
//    }
//    // Shear clockwise 5deg with M is pressed
//    if (keys[GLFW_KEY_M] && !keys[GLFW_KEY_LEFT_SHIFT]) {
//        ShearModel((5.0f * M_PI) / 180.0f);
//    }
//    // Shear counterclockwise 5deg with N is pressed
//    if (keys[GLFW_KEY_N] && !keys[GLFW_KEY_LEFT_SHIFT]) {
//        ShearModel(-(5.0f * M_PI) / 180.0f);
//    }
//    // Random location when space is pressed
//    while (keys[GLFW_KEY_SPACE]) {
//        glm::mat4 model = glm::mat4(1.0f);
//        glUniformMatrix4fv(uniformObjectModelLocation, 1, GL_FALSE, glm::value_ptr(model));
//        TranslateModel(rand() % 17 - 9, 0, rand() % 17 - 9);
//    }
//}
//


#define _USE_MATH_DEFINES
#include <cmath>

#include "ComplexObject.h"

ComplexObject::ComplexObject() {
    meshList = std::vector<IndependentMesh*>();
    uniformObjectModelLocation = 0;
    objectModelMatrix = new glm::mat4(1.0f);

    objectList = std::vector<ComplexObject*>();

    hasModelMatrix = false;
}

ComplexObject::~ComplexObject() {
    // Clears the objectlist
    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->ClearObject();
    }

    // Clean up the meshlist.
    for (int i = 0; i < meshList.size(); i++) {
        meshList[i]->~IndependentMesh();
        delete meshList[i];
    }

    if (hasModelMatrix) {
        // If we have set the model matrix, clean it up.
        ResetModelMatrix();
    }
    else {
        // If not, just clean the pointer.
        delete objectModelMatrix;
        objectModelMatrix = NULL;
    }

    // Destroy the object list.
    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->~ComplexObject();
        delete objectList[i];
    }
}

void ComplexObject::RenderObject() {
    // If we have a custom transformation...
    if (hasModelMatrix) {
        // ... we apply it to our children, rendering them with it.
        for (int i = 0; i < meshList.size(); i++) {
            meshList[i]->RenderMesh(*objectModelMatrix, uniformObjectModelLocation);
        }

        for (int i = 0; i < objectList.size(); i++) {
            objectList[i]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
        }
    }
    else {
        // No transformation means we just render our children as is.
        for (int i = 0; i < meshList.size(); i++) {
            meshList[i]->RenderMesh();
        }

        for (int i = 0; i < objectList.size(); i++) {
            objectList[i]->RenderObject();
        }
    }
}

void ComplexObject::RenderObject(glm::mat4& modelMatrix, GLuint uniformModel) {
    glm::mat4 model(1.0f);

    if (hasModelMatrix) {
        // If we have a custom transformation, we combine it with the provided transformation.
        model = modelMatrix * *objectModelMatrix;
    }
    else {
        // If we dont have a current transformation, just pass the provided transformation.
        model = modelMatrix;
    }

    // Rendering our children
    for (int i = 0; i < meshList.size(); i++) {
        meshList[i]->RenderMesh(model, uniformModel);
    }

    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->RenderObject(model, uniformModel);
    }

}

void ComplexObject::RenderLetters(Texture* cardboard, Texture* silver, bool toggleTexture)
{

    // If we have a custom transformation...
    if (hasModelMatrix)
    {
        // ... we apply it to our children, rendering them with it.
        for (int i = 0; i < meshList.size(); i++)
        {
            meshList[i]->RenderMesh(*objectModelMatrix, uniformObjectModelLocation);
        }

        if (toggleTexture) cardboard->UseTexture();

        objectList[0]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
        objectList[1]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);

        if (toggleTexture) glBindTexture(GL_TEXTURE_2D, 0);

        if (toggleTexture) silver->UseTexture();

        objectList[2]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
        objectList[3]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);

        if (toggleTexture) glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        // No transformation means we just render our children as is.
        for (int i = 0; i < meshList.size(); i++)
        {
            meshList[i]->RenderMesh();
        }

        if (toggleTexture) cardboard->UseTexture();

        objectList[0]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
        objectList[1]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);

        if (toggleTexture) glBindTexture(GL_TEXTURE_2D, 0);

        if (toggleTexture) silver->UseTexture();

        objectList[2]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);
        objectList[3]->RenderObject(*objectModelMatrix, uniformObjectModelLocation);

        if (toggleTexture) glBindTexture(GL_TEXTURE_2D, 0);


    }

}


void ComplexObject::ClearObject() {
    // Clears the meshlist
    for (int i = 0; i < meshList.size(); i++) {
        meshList[i]->ClearMesh();
    }

    // Clears the objectlist
    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->ClearObject();
    }
}

void ComplexObject::SetModelMatrix(glm::mat4& matrix, GLuint uniformModelLocation) {
    if (hasModelMatrix) {
        // Removing the model matrix from gpu
        glUniform1f((*this).uniformObjectModelLocation, 0.0f);
    }

    *objectModelMatrix = matrix;
    uniformObjectModelLocation = uniformModelLocation;

    hasModelMatrix = true;
}

void ComplexObject::ResetModelMatrix() {
    hasModelMatrix = false;

    // Removing the model matrix from gpu
    glUniform1f((*this).uniformObjectModelLocation, 0.0f);

    uniformObjectModelLocation = 0;

    delete objectModelMatrix;
    objectModelMatrix = NULL;
}

glm::mat4& ComplexObject::GetModelMatrix() {
    if (hasModelMatrix)
        return *objectModelMatrix;
    else {
        // If no matrix has been set for this object, we return a generic identity matrix.
        // Could throw an exception too, because if someone tries to modify that generic matrix, it wont change this object's matrix.
        glm::mat4 model = glm::mat4(1.0f);
        return model;
    }
}

void ComplexObject::TranslateModel(GLfloat x, GLfloat y, GLfloat z) {
    glm::mat4 model = GetModelMatrix();
    model = glm::translate(model, glm::vec3(x, y, z));
    SetModelMatrix(model, uniformObjectModelLocation);
}

void ComplexObject::RotateModel(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
    glm::mat4 model = GetModelMatrix();
    model = glm::rotate(model, angle, glm::vec3(x, y, z));
    SetModelMatrix(model, uniformObjectModelLocation);
}

void ComplexObject::ScaleModel(GLfloat xScale, GLfloat yScale, GLfloat zScale) {
    glm::mat4 model = GetModelMatrix();
    model = glm::scale(model, glm::vec3(xScale, yScale, zScale));
    SetModelMatrix(model, uniformObjectModelLocation);
}

void ComplexObject::ShearModel(GLfloat angle) {
    glm::mat4 model = GetModelMatrix();
    model = glm::shearY3D(model, angle, 0.0f);
    SetModelMatrix(model, uniformObjectModelLocation);
}


void ComplexObject::Transform(bool* keys) {
    // Move up when capital W is pressed
    if (keys[GLFW_KEY_W] && keys[GLFW_KEY_LEFT_SHIFT]) {
        TranslateModel(0.0f, 0.05f, 0.0f);
    }
    // Move left when capital A is pressed
    if (keys[GLFW_KEY_A] && keys[GLFW_KEY_LEFT_SHIFT]) {
        TranslateModel(-0.05f, 0.0f, 0.0f);
    }
    // Move down when capital S is pressed
    if (keys[GLFW_KEY_S] && keys[GLFW_KEY_LEFT_SHIFT]) {
        TranslateModel(0.0f, -0.05f, 0.0f);
    }
    // Move right when capital D is pressed
    if (keys[GLFW_KEY_D] && keys[GLFW_KEY_LEFT_SHIFT]) {
        TranslateModel(0.05f, 0.0f, 0.0f);
    }
    // Rotate Model 5deg right
    if (keys[GLFW_KEY_D] && !keys[GLFW_KEY_LEFT_SHIFT]) {
        RotateModel(0.0f, 1.0f, 0.0f, (5.0f * M_PI) / 180.0f);
    }
    // Rotate Model 5deg left
    if (keys[GLFW_KEY_A] && !keys[GLFW_KEY_LEFT_SHIFT]) {
        RotateModel(0.0f, 1.0f, 0.0f, -(5.0f * M_PI) / 180.0f);
    }
    // Scale up with U is pressed
    if (keys[GLFW_KEY_U]) {
        ScaleModel(1.01f, 1.01f, 1.01f);
    }
    // Scale down with J is pressed
    if (keys[GLFW_KEY_J] && !keys[GLFW_KEY_LEFT_SHIFT]) {
        ScaleModel(0.99f, 0.99f, 0.99f);
    }
    // Shear clockwise 5deg with M is pressed
    if (keys[GLFW_KEY_M] && !keys[GLFW_KEY_LEFT_SHIFT]) {
        ShearModel((5.0f * M_PI) / 180.0f);
    }
    // Shear counterclockwise 5deg with N is pressed
    if (keys[GLFW_KEY_N] && !keys[GLFW_KEY_LEFT_SHIFT]) {
        ShearModel(-(5.0f * M_PI) / 180.0f);
    }
    // Random location when space is pressed
    while (keys[GLFW_KEY_SPACE]) {
        glm::mat4 model = glm::mat4(1.0f);
        SetModelMatrix(model, uniformObjectModelLocation);
        TranslateModel(rand() % 17 - 9, 0, rand() % 17 - 9);
    }
}
