#pragma once

#include "glm/glm.hpp"

namespace Ff
{
    /**
     * Class, that represents camera and its controls.
     */
    class Camera
    {
    public:
        /** Sets position. */
        Camera();

        /**
         * Generate projection matrix.
         * @return projection matrix.
         * @param viewport viewport extent used to generate matrix. 
         */
        glm::mat4 generateProjMatrix(const struct Viewport2D& viewport) const;

        /**
         * Generate view matrix.
         * @return view matrix.
         * @param x camera x position. 
         * @param y camera y position. 
         */
        glm::mat4 generateViewMatrix(float x, float y) const;

        /** Moves, drags and zooms camera based on user input. */
        void controlCamera(float delta);

    private:
        void dragCamera(float delta);
        void moveCamera(float delta);
        void zoomCamera(double wheelOffset, float delta) { width -= wheelOffset * zoomSpeed * delta; }

    public:
        glm::vec3 position;
        float width = 4.0f;
        float speed = 15.0f;
        float zoomSpeed = 30.0f;
        float speedConst = 0.09f;
    };
} // namespace Ff