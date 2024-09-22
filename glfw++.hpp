#ifndef __GLFW_GLFWXX_HPP
#define __GLFW_GLFWXX_HPP

#include <GLFW/glfw3.h>

namespace glfw {

class Internal;

/** Retrieves the version of the GLFW library **/
void getVersion(int &major, int &minor, int &rev);
/** Returns a string describing the compile-time configuration **/
const char * getVersionString();
/** Resets all window hints to their default values **/
void defaultWindowHints();
/** Sets the specified window hint to the desired value **/
void windowHint(int hint, int value);
/** Sets the specified window hint to the desired value **/
void windowHint(int hint, const char * value);
/** Processes all pending events **/
void pollEvents();
/** Waits until events are queued and processes them **/
void waitEvents();
/** Waits with timeout until events are queued and processes them **/
void waitEvents(double timeout);
/** Posts an empty event to the event queue **/
void postEmptyEvent();
/** Returns whether raw mouse motion is supported **/
bool rawMouseMotionSupported();
/** Returns the layout-specific name of the specified printable key **/
const char * getKeyName(int key, int scancode);
/** Returns the platform-specific scancode of the specified key **/
int getKeyScancode(int key);
/** Returns whether the specified joystick is present **/
bool joystickPresent(int jid);
/** Returns the values of all axes of the specified joystick **/
const float * getJoystickAxes(int jid, int &count);
/** Returns the state of all buttons of the specified joystick **/
const unsigned char * getJoystickButtons(int jid, int &count);
/** Returns the state of all hats of the specified joystick **/
const unsigned char * getJoystickHats(int jid, int &count);
/** Returns the name of the specified joystick **/
const char * getJoystickName(int jid);
/** Returns the SDL compatible GUID of the specified joystick **/
const char * getJoystickGUID(int jid);
/** Sets the user pointer of the specified joystick **/
void setJoystickUserPointer(int jid, void * pointer);
/** Returns the user pointer of the specified joystick **/
void * getJoystickUserPointer(int jid);
/** Returns whether the specified joystick has a gamepad mapping **/
int joystickIsGamepad(int jid);
/** Sets the joystick configuration callback **/
GLFWjoystickfun setJoystickCallback(GLFWjoystickfun callback);
/** Adds the specified SDL_GameControllerDB gamepad mappings **/
int updateGamepadMappings(const char * string);
/** Returns the human-readable gamepad name for the specified joystick **/
const char * getGamepadName(int jid);
/** Retrieves the state of the specified joystick remapped as a gamepad **/
int getGamepadState(int jid, GLFWgamepadstate &state);
/** Returns the GLFW time **/
double getTime();
/** Sets the GLFW time **/
void setTime(double time);
/** Returns the current value of the raw timer **/
uint64_t getTimerValue();
/** Returns the frequency, in Hz, of the raw timer **/
uint64_t getTimerFrequency();
/** Returns the window whose context is current on the calling thread **/
GLFWwindow * glfwGetCurrentContext();
/** Sets the swap interval for the current context **/
void swapInterval(int interval);
/** Returns whether the specified extension is available **/
bool extensionSupported(const char * extension);
/** Returns the address of the specified function for the current context **/
GLFWglproc glfwGetProcAddress(const char * procname);
/** Returns whether the Vulkan loader and an ICD have been found **/
bool vulkanSupported();
/** Returns the Vulkan instance extensions required by GLFW **/
const char ** getRequiredInstanceExtensions(uint32_t &count);
#if defined(VK_VERSION_1_0)
/** Returns the address of the specified Vulkan instance function **/
GLFWvkproc getInstanceProcAddress(VkInstance instance, const char * procname);
#endif

/** Encapsulates a pointer to a GLFW cursor **/
class Cursor {
    friend class Window;
public:
    /** Creates a custom cursor **/
    Cursor(const GLFWimage* image, int xhot, int yhot);
    /** Creates a cursor with a standard shape **/
    explicit Cursor(int shape);
    /** Destroys a cursor **/
    ~Cursor();
    
private:
    explicit Cursor(const Cursor &other)=delete;
    Cursor &operator =(const Cursor &other)=delete;
    
    GLFWcursor * cursor;
};

/** Encapsulates a pointer to a GLFW monitor **/
class Monitor {
    friend class Window;
public:
    /** Encapsulate a GLFW monitor **/
    explicit Monitor(GLFWmonitor * monitor);
    /** Returns the physical size of the monitor **/
    void getPhysicalSize(int &widthMM, int &heightMM);
    /** Retrieves the content scale for the specified monitor **/
    void getContentScale(float &xscale, float &yscale);
    /** Returns the name of the specified monitor **/
    const char * getName();
    /** Sets the user pointer of the specified monitor **/
    void setUserPointer(void * pointer);
    /** Returns the user pointer of the specified monitor **/
    void * getUserPointer();
    /** Sets the monitor configuration callback **/
    
    /** Returns the available video modes for the specified monitor **/
    const GLFWvidmode * getVideoModes(int &count);
    /** Returns the current mode of the specified monitor **/
    const GLFWvidmode * getVideoMode();
    /** Generates a gamma ramp and sets it for the specified monitor **/
    void setGamma(float gamma);
    /** Returns the current gamma ramp for the specified monitor **/
    const GLFWgammaramp * getGammaRamp();
    /** Sets the current gamma ramp for the specified monitor **/
    void setGammaRamp(const GLFWgammaramp * ramp);
    
private:
    explicit Monitor(const Monitor &monitor)=delete;
    Monitor &operator =(const Monitor &monitor)=delete;
    
    GLFWmonitor * monitor;
};

/**/
class Window {
    friend class Cursor;
    friend class Monitor;
    friend class Internal;
public:
    /** Creates a window and its associated context **/
    Window(int width, int height, const char * title);
    /** Creates a window and its associated context **/
    Window(int width, int height, const char * title, const Monitor &monitor);
    /** Creates a window and its associated context **/
    Window(int width, int height, const char * title, const Window &share);
    /** Creates a window and its associated context **/
    Window(int width, int height, const char * title, const Monitor &monitor,
        const Window &share);
    /** Destroys the specified window and its context **/
    virtual ~Window();
    /** Checks the close flag of the specified window **/
    bool shouldClose();
    /** Sets the close flag of the specified window **/
    void setShouldClose(bool value);
    /** Sets the title of the specified window **/
    void setTitle(const char * title);
    /** Sets the icon for the specified window **/
    void setIcon(int count, const GLFWimage* images);
    /** Retrieves the position of the content area of the specified window **/
    void getPosition(int &xpos, int &ypos);
    /** Sets the position of the content area of the specified window **/
    void setPosition(int xpos, int ypos);
    /** Retrieves the size of the content area of the specified window **/
    void getSize(int &width, int &height);
    /** Sets the size limits of the specified window **/
    void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
    /** Sets the aspect ratio of the specified window **/
    void setAspectRatio(int numer, int denom);
    /** Sets the size of the content area of the specified window **/
    void setSize(int width, int height);
    /** Retrieves the size of the framebuffer of the specified window **/
    void getFramebufferSize(int &width, int &height);
    /** Retrieves the size of the frame of the window **/
    void getFrameSize(int &left, int &top, int &right, int &bottom);
    /** Retrieves the content scale for the specified window **/
    void getContentScale(float &xscale, float &yscale);
    /** Returns the opacity of the whole window **/
    float getOpacity();
    /** Sets the opacity of the whole window **/
    void setOpacity(float opacity);
    /** Iconifies the specified window **/
    void iconify();
    /** Restores the specified window **/
    void restore();
    /** Maximizes the specified window **/
    void maximize();
    /** Makes the specified window visible **/
    void show();
    /** Hides the specified window **/
    void hide();
    /** Brings the specified window to front and sets input focus **/
    void focus();
    /** Requests user attention to the specified window **/
    void requestAttention();
    /** Returns the monitor that the window uses for full screen mode **/
    Monitor getMonitor();
    /** Sets the mode, monitor, video mode and placement of a window **/
    void setMonitor(Monitor monitor, int xpos, int ypos, int width, int height, int refreshRate);
    /** Returns an attribute of the specified window **/
    int getAttribute(int attrib);
    /** Sets an attribute of the specified window **/
    void setAttribute(int attrib, int value);
    /** Sets the user pointer of the specified window **/
    void setUserPointer(void * pointer);
    /** Returns the user pointer of the specified window **/
    void * getUserPointer();
    /** Returns the value of an input option for the specified window **/
    int getInputMode(int mode);
    /** Sets an input option for the specified window **/
    void setInputMode(int mode, int value);
    /** Returns the last reported state of a keyboard key for the specified window **/
    int getKey(int key);
    /** Returns the last reported state of a mouse button for the specified window **/
    int getMouseButton(int button);
    /** Retrieves the position of the cursor relative to the content area of the window **/
    void getCursorPos(double &xpos, double &ypos);
    /** Sets the position of the cursor, relative to the content area of the window **/
    void setCursorPos(double xpos, double ypos);
    /** Sets the cursor for the window **/
    void setCursor(Cursor &cursor);
    /** Sets the clipboard to the specified string **/
    void setClipboardString(const char * string);
    /** Returns the contents of the clipboard as a string **/
    const char * getClipboardString();
    /** Makes the context of the specified window current for the calling thread **/
    void makeContextCurrent();
    /** Returns the window whose context is current on the calling thread **/
    static Window * getCurrentContext();
    /** Swaps the front and back buffers of the specified window **/
    void swapBuffers();
#if defined(VK_VERSION_1_0)
    /** Creates a Vulkan surface for the specified window **/
    VkResult createSurface(VkInstance instance, const VkAllocationCallbacks * allocator, VkSurfaceKHR * surface);
#endif
    
protected:
    /** Window position callback **/
    virtual void onPosition(int xpos, int ypos);
    /** Window size callback **/
    virtual void onSize(int width, int height);
    /** Window close callback **/
    virtual void onClose();
    /** Window content refresh callback **/
    virtual void onRefresh();
    /** Window focus callback **/
    virtual void onFocus(int focused);
    /** Window iconify callback **/
    virtual void onIconify(int iconified);
    /** Window maximize callback **/
    virtual void onMaximize(int maximized);
    /** Framebuffer size callback **/
    virtual void onFramebufferSize(int width, int height);
    /** Window content scale callback **/
    virtual void onContentScale(float xscale, float yscale);
    /** Keyboard key callback **/
    virtual void onKey(int key, int scancode, int action, int mods);
    /** Unicode character callback **/
    virtual void onChar(unsigned int codepoint);
    /** Unicode character with modifiers callback **/
    virtual void onCharMods(unsigned int codepoint, int mods);
    /** Mouse button callback **/
    virtual void onMouseButton(int button, int action, int mods);
    /** Cursor position callback **/
    virtual void onCursorPos(double xpos, double ypos);
    /** Cursor enter/leave callback **/
    virtual void onCursorEnter(int entered);
    /** Scroll callback **/
    virtual void onScroll(double xoffset, double yoffset);
    /** Path drop callback **/
    virtual void onDrop(int path_count, const char * paths[]);
    
private:
    explicit Window(const Window &other)=delete;
    Window &operator =(const Window &other)=delete;
    void init();
    
    GLFWwindow * window;
};

}

#endif
