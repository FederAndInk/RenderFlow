#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL3/DebugUtils.hpp>
#include <GL3/GLTypes.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <unordered_map>

namespace GL3
{
//!
//! \brief      FPS view Camera class
//!
//! This class provides view matrix and projection matrix getter for
//! retrieving vertices which is transformed into camera space.
//! Also provide UBO(UniformBufferObject) for binding camera to multiple shader.
//!
class Camera
{
 public:
    //! Default constructor
    Camera();
    //! Default destructor
    virtual ~Camera();
    //! Initialize the camera
    bool SetupUniformBuffer();
    //! Setup camera position, direction and up vector.
    void SetupCamera(const glm::vec3& pos, const glm::vec3& dir,
                     const glm::vec3& up);
    //! Returns view matrix
    glm::mat4 GetViewMatrix();
    //! Returns projection matrix
    glm::mat4 GetProjectionMatrix();
    //! Bind the uniform buffer to the current context.
    void BindCamera(GLuint bindingPoint) const;
    //! Unbind camera
    //! declared as static because nothing related with member variables or
    //! method
    static void UnbindCamera();
    //! Returns the uniform buffer ID
    GLuint GetUniformBuffer() const;
    //! Update the matrix with specific methods, such as perspective or
    //! orthogonal.
    void UpdateMatrix();
    //! Process the continuous key input
    void ProcessInput(unsigned int key);
    //! Process the continuous mouse cursor position input
    void ProcessCursorPos(double xpos, double ypos);
    //! Cleanup the resources
    void CleanUp();

 protected:
    virtual void OnUpdateMatrix(){};
    glm::mat4 _projection, _view;
    glm::vec3 _position, _direction, _up;

 private:
    //! Returns the uniform variable location matched with given name.
    GLint GetUniformLocation(const std::string& name);

    std::unordered_map<std::string, GLint> _uniformCache;
    DebugUtils _debug;
    float _speed;
    GLuint _uniformBuffer;
};

};  // namespace GL3

#endif  //! end of Camera.hpp