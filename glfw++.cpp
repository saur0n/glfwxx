#include <vector>
#include "glfw++.hpp"

using namespace glfw;
using std::vector;

void glfw::getVersion(int &major, int &minor, int &rev) {
    glfwGetVersion(&major, &minor, &rev);
}

const char * glfw::getVersionString() {
    return glfwGetVersionString();
}

void glfw::defaultWindowHints() {
    glfwDefaultWindowHints();
}

void glfw::windowHint(int hint, int value) {
    glfwWindowHint(hint, value);
}

void glfw::windowHint(int hint, const char * value) {
    glfwWindowHintString(hint, value);
}

void glfw::pollEvents() {
    glfwPollEvents();
}

void glfw::waitEvents() {
    glfwWaitEvents();
}

void glfw::waitEvents(double timeout) {
    glfwWaitEventsTimeout(timeout);
}

void glfw::postEmptyEvent() {
    glfwPostEmptyEvent();
}

bool glfw::rawMouseMotionSupported() {
    return glfwRawMouseMotionSupported();
}

const char * glfw::getKeyName(int key, int scancode) {
    return glfwGetKeyName(key, scancode);
}

int glfw::getKeyScancode(int key) {
    return glfwGetKeyScancode(key);
}

bool glfw::joystickPresent(int jid) {
    return glfwJoystickPresent(jid);
}

const float * glfw::getJoystickAxes(int jid, int &count) {
    return glfwGetJoystickAxes(jid, &count);
}

const unsigned char * glfw::getJoystickButtons(int jid, int &count) {
    return glfwGetJoystickButtons(jid, &count);
}

const unsigned char * glfw::getJoystickHats(int jid, int &count) {
    return glfwGetJoystickHats(jid, &count);
}

const char * glfw::getJoystickName(int jid) {
    return glfwGetJoystickName(jid);
}

const char * glfw::getJoystickGUID(int jid) {
    return glfwGetJoystickGUID(jid);
}

void glfw::setJoystickUserPointer(int jid, void * pointer) {
    glfwSetJoystickUserPointer(jid, pointer);
}

void * glfw::getJoystickUserPointer(int jid) {
    return glfwGetJoystickUserPointer(jid);
}

int glfw::joystickIsGamepad(int jid) {
    return glfwJoystickIsGamepad(jid);
}

GLFWjoystickfun glfw::setJoystickCallback(GLFWjoystickfun callback) {
    return glfwSetJoystickCallback(callback);
}

int glfw::updateGamepadMappings(const char * string) {
    return glfwUpdateGamepadMappings(string);
}

const char * glfw::getGamepadName(int jid) {
    return glfwGetGamepadName(jid);
}

int glfw::getGamepadState(int jid, GLFWgamepadstate &state) {
    return glfwGetGamepadState(jid, &state);
}

double glfw::getTime() {
    return glfwGetTime();
}

void glfw::setTime(double time) {
    glfwSetTime(time);
}

uint64_t glfw::getTimerValue() {
    return glfwGetTimerValue();
}

uint64_t glfw::getTimerFrequency() {
    return glfwGetTimerFrequency();
}

GLFWwindow * glfw::glfwGetCurrentContext() {
    return glfwGetCurrentContext();
}

void glfw::swapInterval(int interval) {
    return glfwSwapInterval(interval);
}

bool glfw::extensionSupported(const char * extension) {
    return glfwExtensionSupported(extension);
}

GLFWglproc glfw::glfwGetProcAddress(const char * procname) {
    return glfwGetProcAddress(procname);
}

bool glfw::vulkanSupported() {
    return glfwVulkanSupported();
}

const char ** glfw::getRequiredInstanceExtensions(uint32_t &count) {
    return glfwGetRequiredInstanceExtensions(&count);
}

#if defined(VK_VERSION_1_0)
GLFWvkproc glfw::getInstanceProcAddress(VkInstance instance, const char * procname) {
    return glfwGetInstanceProcAddress(instance, procname);
}
#endif

/******************************************************************************/

Cursor::Cursor(const GLFWimage* image, int xhot, int yhot) :
        cursor(glfwCreateCursor(image, xhot, yhot)) {}

Cursor::Cursor(int shape) : cursor(glfwCreateStandardCursor(shape)) {}

Cursor::~Cursor() {
    glfwDestroyCursor(cursor);
}

/******************************************************************************/

Monitor::Monitor(GLFWmonitor * monitor) : monitor(monitor) {}

void Monitor::getPhysicalSize(int &widthMM, int &heightMM) {
    glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
}

void Monitor::getContentScale(float &xscale, float &yscale) {
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
}

const char * Monitor::getName() {
    return glfwGetMonitorName(monitor);
}

void Monitor::setUserPointer(void * pointer) {
    glfwSetMonitorUserPointer(monitor, pointer);
}

void * Monitor::getUserPointer() {
    return glfwGetMonitorUserPointer(monitor);
}

const GLFWvidmode * Monitor::getVideoModes(int &count) {
    return glfwGetVideoModes(monitor, &count);
}

const GLFWvidmode * Monitor::getVideoMode() {
    return glfwGetVideoMode(monitor);
}

void Monitor::setGamma(float gamma) {
    glfwSetGamma(monitor, gamma);
}

const GLFWgammaramp * Monitor::getGammaRamp() {
    return glfwGetGammaRamp(monitor);
}

void Monitor::setGammaRamp(const GLFWgammaramp * ramp) {
    glfwSetGammaRamp(monitor, ramp);
}

/******************************************************************************/

namespace glfw {
class Internal {
public:
    static void windowPosCallback(GLFWwindow * window, int xpos, int ypos) {
        if (Window * w=find(window))
            w->onPosition(xpos, ypos);
    }

    static void windowSizeCallback(GLFWwindow * window, int width, int height) {
        if (Window * w=find(window))
            w->onSize(width, height);
    }

    static void windowCloseCallback(GLFWwindow * window) {
        if (Window * w=find(window))
            w->onClose();
    }

    static void windowRefreshCallback(GLFWwindow * window) {
        if (Window * w=find(window))
            w->onRefresh();
    }

    static void windowFocusCallback(GLFWwindow * window, int focused) {
        if (Window * w=find(window))
            w->onFocus(focused);
    }

    static void windowIconifyCallback(GLFWwindow * window, int iconified) {
        if (Window * w=find(window))
            w->onIconify(iconified);
    }

    static void windowMaximizeCallback(GLFWwindow * window, int maximized) {
        if (Window * w=find(window))
            w->onMaximize(maximized);
    }

    static void windowFramebufferSizeCallback(GLFWwindow * window, int width, int height) {
        if (Window * w=find(window))
            w->onFramebufferSize(width, height);
    }

    static void windowContentScaleCallback(GLFWwindow * window, float xscale, float yscale) {
        if (Window * w=find(window))
            w->onContentScale(xscale, yscale);
    }

    static void windowKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
        if (Window * w=find(window))
            w->onKey(key, scancode, action, mods);
    }

    static void windowCharCallback(GLFWwindow * window, unsigned int codepoint) {
        if (Window * w=find(window))
            w->onChar(codepoint);
    }

    static void windowCharModsCallback(GLFWwindow * window, unsigned int codepoint, int mods) {
        if (Window * w=find(window))
            w->onCharMods(codepoint, mods);
    }

    static void windowMouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
        if (Window * w=find(window))
            w->onMouseButton(button, action, mods);
    }

    static void windowCursorPosCallback(GLFWwindow * window, double xpos, double ypos) {
        if (Window * w=find(window))
            w->onCursorPos(xpos, ypos);
    }

    static void windowCursorEnterCallback(GLFWwindow * window, int entered) {
        if (Window * w=find(window))
            w->onCursorEnter(entered);
    }

    static void windowScrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
        if (Window * w=find(window))
            w->onScroll(xoffset, yoffset);
    }

    static void windowDropCallback(GLFWwindow * window, int pathCount, const char * paths[]) {
        if (Window * w=find(window))
            w->onDrop(pathCount, paths);
    }
    
    static void add(Window * window) {
        if (window) {
            Window * ptr=window;
            for (auto i=windows.begin(); i!=windows.end(); ++i) {
                if ((*i)->window>ptr->window) {
                    Window * prev=*i;
                    *i=ptr;
                    ptr=prev;
                }
            }
            windows.emplace_back(ptr);
        }
    }
    
    static void remove(Window * window) {
        if (window) {
            bool deleting=false;
            for (auto i=windows.begin(); i!=windows.end(); ++i) {
                if (deleting)
                    *(i-1)=*i;
                else if (*i==window)
                    deleting=true;
            }
            if (deleting)
                windows.resize(windows.size()-1);
        }
    }
    
    static Window * find(GLFWwindow * window) {
        size_t low=0;
        size_t high=windows.size()-1;
        
        while (low<=high) {
            size_t mid=(low+high)>>1;
            Window * midVal=windows[mid];
            
            if (midVal->window<window)
                low=mid+1;
            else if (midVal->window>window)
                high=mid-1;
            else
                return midVal; // window found
        }
        
        return nullptr;
    }
    
private:
    static vector<Window *> windows;
};

vector<Window *> Internal::windows;

}

Window::Window(int width, int height, const char * title) :
        window(glfwCreateWindow(width, height, title, nullptr, nullptr)) {
    init();
}

Window::Window(int width, int height, const char * title, const Monitor &monitor) :
        window(glfwCreateWindow(width, height, title, monitor.monitor, nullptr)) {
    init();
}

Window::Window(int width, int height, const char * title, const Window &share) :
        window(glfwCreateWindow(width, height, title, nullptr, share.window)) {
    init();
}

Window::Window(int width, int height, const char * title, const Monitor &monitor,
        const Window &share) :
        window(glfwCreateWindow(width, height, title, monitor.monitor, share.window)) {
    init();
}

Window::~Window() {
    // Unregister the window
    Internal::remove(this);
    
    glfwDestroyWindow(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool value) {
    glfwSetWindowShouldClose(window, value);
}

void Window::setTitle(const char * title) {
    glfwSetWindowTitle(window, title);
}

void Window::setIcon(int count, const GLFWimage* images) {
    glfwSetWindowIcon(window, count, images);
}

void Window::getPosition(int &xpos, int &ypos) {
    glfwGetWindowPos(window, &xpos, &ypos);
}

void Window::setPosition(int xpos, int ypos) {
    glfwSetWindowPos(window, xpos, ypos);
}

void Window::getSize(int &width, int &height) {
    glfwGetWindowSize(window, &width, &height);
}

void Window::setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) {
    glfwSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);
}

void Window::setAspectRatio(int numer, int denom) {
    glfwSetWindowAspectRatio(window, numer, denom);
}

void Window::setSize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

void Window::getFramebufferSize(int &width, int &height) {
    glfwGetFramebufferSize(window, &width, &height);
}

void Window::getFrameSize(int &left, int &top, int &right, int &bottom) {
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
}

void Window::getContentScale(float &xscale, float &yscale) {
    glfwGetWindowContentScale(window, &xscale, &yscale);
}

float Window::getOpacity() {
    return glfwGetWindowOpacity(window);
}

void Window::setOpacity(float opacity) {
    glfwSetWindowOpacity(window, opacity);
}

void Window::iconify() {
    glfwIconifyWindow(window);
}

void Window::restore() {
    glfwRestoreWindow(window);
}

void Window::maximize() {
    glfwMaximizeWindow(window);
}

void Window::show() {
    glfwShowWindow(window);
}

void Window::hide() {
    glfwHideWindow(window);
}

void Window::focus() {
    glfwFocusWindow(window);
}

void Window::requestAttention() {
    glfwRequestWindowAttention(window);
}

Monitor Window::getMonitor() {
    return Monitor(glfwGetWindowMonitor(window));
}

void Window::setMonitor(Monitor monitor, int xpos, int ypos, int width, int height, int refreshRate) {
    glfwSetWindowMonitor(window, monitor.monitor, xpos, ypos, width, height, refreshRate);
}

int Window::getAttribute(int attrib) {
    return glfwGetWindowAttrib(window, attrib);
}

void Window::setAttribute(int attrib, int value) {
    glfwSetWindowAttrib(window, attrib, value);
}

void Window::setUserPointer(void * pointer) {
    glfwSetWindowUserPointer(window, pointer);
}

void * Window::getUserPointer() {
    return glfwGetWindowUserPointer(window);
}

int Window::getInputMode(int mode) {
    return glfwGetInputMode(window, mode);
}

void Window::setInputMode(int mode, int value) {
    glfwSetInputMode(window, mode, value);
}

int Window::getKey(int key) {
    return glfwGetKey(window, key);
}

int Window::getMouseButton(int button) {
    return glfwGetMouseButton(window, button);
}

void Window::getCursorPos(double &xpos, double &ypos) {
    glfwGetCursorPos(window, &xpos, &ypos);
}

void Window::setCursorPos(double xpos, double ypos) {
    glfwSetCursorPos(window, xpos, ypos);
}

void Window::setCursor(Cursor &cursor) {
    glfwSetCursor(window, cursor.cursor);
}

void Window::setClipboardString(const char * string) {
    glfwSetClipboardString(window, string);
}

const char * Window::getClipboardString() {
    return glfwGetClipboardString(window);
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(window);
}

Window * Window::getCurrentContext() {
    return Internal::find(glfwGetCurrentContext());
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

#if defined(VK_VERSION_1_0)
VkResult Window::createSurface(VkInstance instance, const VkAllocationCallbacks * allocator, VkSurfaceKHR * surface) {
    return glfwCreateWindowSurface(instance, window, allocator, surface);
}
#endif

void Window::onPosition(int xpos, int ypos) {
    (void)xpos;
    (void)ypos;
}

void Window::onSize(int width, int height) {
    (void)width;
    (void)height;
}

void Window::onClose() {}

void Window::onRefresh() {}

void Window::onFocus(int focused) {
    (void)focused;
}

void Window::onIconify(int iconified) {
    (void)iconified;
}

void Window::onMaximize(int maximized) {
    (void)maximized;
}

void Window::onFramebufferSize(int width, int height) {
    (void)width;
    (void)height;
}

void Window::onContentScale(float xscale, float yscale) {
    (void)xscale;
    (void)yscale;
}

void Window::onKey(int key, int scancode, int action, int mods) {
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void Window::onChar(unsigned int codepoint) {
    (void)codepoint;
}

void Window::onCharMods(unsigned int codepoint, int mods) {
    (void)codepoint;
    (void)mods;
}

void Window::onMouseButton(int button, int action, int mods) {
    (void)button;
    (void)action;
    (void)mods;
}

void Window::onCursorPos(double xpos, double ypos) {
    (void)xpos;
    (void)ypos;
}

void Window::onCursorEnter(int entered) {
    (void)entered;
}

void Window::onScroll(double xoffset, double yoffset) {
    (void)xoffset;
    (void)yoffset;
}

void Window::onDrop(int pathCount, const char * paths[]) {
    (void)pathCount;
    (void)paths;
}

void Window::init() {
    glfwSetWindowPosCallback(window, Internal::windowPosCallback);
    glfwSetWindowSizeCallback(window, Internal::windowSizeCallback);
    glfwSetWindowCloseCallback(window, Internal::windowCloseCallback);
    glfwSetWindowRefreshCallback(window, Internal::windowRefreshCallback);
    glfwSetWindowFocusCallback(window, Internal::windowFocusCallback);
    glfwSetWindowIconifyCallback(window, Internal::windowIconifyCallback);
    glfwSetWindowMaximizeCallback(window, Internal::windowMaximizeCallback);
    glfwSetFramebufferSizeCallback(window, Internal::windowFramebufferSizeCallback);
    glfwSetWindowContentScaleCallback(window, Internal::windowContentScaleCallback);
    glfwSetKeyCallback(window, Internal::windowKeyCallback);
    glfwSetCharCallback(window, Internal::windowCharCallback);
    glfwSetCharModsCallback(window, Internal::windowCharModsCallback);
    glfwSetMouseButtonCallback(window, Internal::windowMouseButtonCallback);
    glfwSetCursorPosCallback(window, Internal::windowCursorPosCallback);
    glfwSetCursorEnterCallback(window, Internal::windowCursorEnterCallback);
    glfwSetScrollCallback(window, Internal::windowScrollCallback);
    glfwSetDropCallback(window, Internal::windowDropCallback);
    
    // Register the window
    Internal::add(this);
}

__attribute__((constructor))
static void init() {
    glfwInit();
}

__attribute__((destructor))
static void destroy() {
    glfwTerminate();
}
