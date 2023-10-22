#include "camera.h"
#include "glm/geometric.hpp"
#include "Platform/input.h"
#include "graphicsContext.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Ff
{
    Camera::Camera()
    {
        position = { 0.0f, 0.0f, 3.0f };
    }

    glm::mat4 Camera::generateProjMatrix(const Viewport2D& viewport) const
    {
        float aspectRatio = viewport.width / viewport.height;
        float displayHeight = width / aspectRatio;

        const float halfDisplayWidth = width * 0.5f;
        const float halfDisplayHeight = displayHeight * 0.5f;

        glm::mat4 proj = glm::ortho(-halfDisplayWidth, halfDisplayWidth, -halfDisplayHeight, halfDisplayHeight, -1.0f, 1.0f);
        return proj;
    }

    glm::mat4 Camera::generateViewMatrix(float x, float y) const
    {
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
        return view;
    }

    void Camera::controlCamera(float delta)
    {
        moveCamera(delta);
        dragCamera(delta);
        zoomCamera(Input::getScrollOffset(), delta);
    }

    void Camera::dragCamera(float delta)
    {
        if (Input::isButtonPressed(MouseButton::LEFT) && Input::isKeyPressed(Key::KEY_SPACE))
        {
            glm::vec2 offset = Input::getMouseOffset();
            position.x += offset.x * delta * width * speedConst;
            position.y -= offset.y * delta * width * speedConst;
        }
    }

    void Camera::moveCamera(float delta)
    {
        if (Input::isKeyPressed(Key::KEY_LEFT) || Input::isKeyPressed(Key::KEY_A))
        {
            position.x -= speed * delta;
        }

        if (Input::isKeyPressed(Key::KEY_RIGHT) || Input::isKeyPressed(Key::KEY_D))
        {
            position.x += speed * delta;
        }

        if (Input::isKeyPressed(Key::KEY_UP) || Input::isKeyPressed(Key::KEY_W))
        {
            position.y += speed * delta;
        }

        if (Input::isKeyPressed(Key::KEY_DOWN) || Input::isKeyPressed(Key::KEY_S))
        {
            position.y -= speed * delta;
        }
    }

} // namespace Ff