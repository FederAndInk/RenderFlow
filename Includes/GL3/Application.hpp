#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <cxxopts/cxxopts.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace GL3
{
class Camera;
class Shader;
class Window;

//!
//! \brief      Main update part of the program.
//!
//! This class represents main application of the program.
//! The program can generate multiple of Application instance, sharing opengl
//! resources like framebuffer, shader, etc..
class Application
{
 public:
    //! Default constructor
    Application();
    //! Default desctrutor
    virtual ~Application();
    //! Initialize the Application
    bool Initialize(std::shared_ptr<GL3::Window> window,
                    const cxxopts::ParseResult& configure);
    //! Add camera instance with Perspective or Orthogonal
    void AddCamera(std::shared_ptr<GL3::Camera>&& camera);
    //! Update the application with delta time.
    void Update(double dt);
    //! Draw the one frame of the application.
    void Draw();
    //! Clean up the all resources.
    void CleanUp();
    //! Returns the application title
    virtual const char* GetAppTitle() const = 0;
    //! Process the input key
    void ProcessInput(unsigned int key);
    //! Process the mouse cursor positions
    void ProcessCursorPos(double xpos, double ypos);
    //! Process framebuffer resizing
    void ProcessResize(int width, int height);

 protected:
    virtual bool OnInitialize(std::shared_ptr<GL3::Window> window,
                              const cxxopts::ParseResult& configure) = 0;
    virtual void OnCleanUp() = 0;
    virtual void OnUpdate(double dt) = 0;
    virtual void OnDraw() = 0;
    virtual void OnProcessInput(unsigned int key) = 0;
    virtual void OnProcessResize(int width, int height) = 0;

    std::vector<std::shared_ptr<GL3::Camera> > _cameras;
    std::unordered_map<std::string, std::shared_ptr<GL3::Shader> > _shaders;
};
};  // namespace GL3

#endif  //! end of Application.hpp