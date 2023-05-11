#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline glm::mat4 Otho(float left, float right, float top, float bottom, float nearPlane, float farPlane, float offset, bool IsNDCDepthHomogeneous);

#ifndef HEADER_MATH_H
#define HEADER_MATH_H


inline glm::mat4 Otho(float left, float right, float top, float bottom, float nearPlane, float farPlane, float offset, bool IsNDCDepthHomogeneous)
{
    glm::mat4 ortho = glm::ortho(left, right, top, bottom, nearPlane, farPlane);
    ortho = glm::scale(ortho, glm::vec3(2.0f / (right - left), 2.0f / (top - bottom), IsNDCDepthHomogeneous ? -2.0f / (farPlane - nearPlane) : -1.0f / (farPlane - nearPlane)));
    ortho = glm::translate(ortho, glm::vec3(-1.0f * (right + left) / (right - left), -1.0f * (top + bottom) / (top - bottom), -1.0f * (farPlane + nearPlane + offset) / (farPlane - nearPlane)));
    return ortho;
}

#endif  // HEADER_MATH_H