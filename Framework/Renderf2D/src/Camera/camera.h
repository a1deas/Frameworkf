#pragma once

#include "glm/glm.hpp"

namespace Ff
{
    class Camera
    {
    public:
        Camera();
        glm::mat4 generateProjMatrix(const struct Viewport2D& viewport) const;
        glm::mat4 generateViewMatrix(float x, float y) const;

        void onEvent();
        bool moveCamera(float delta);

        void zoomCamera(double offset, float delta) { width -= offset * zoomSpeed * delta; }
        
    public:
        float width = 4.0f;
        glm::vec3 position;
        float speed = 15.0f;
        float zoomSpeed = 30.0f;
    };

} // namespace Ff