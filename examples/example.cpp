#include <GLFW/glfw++.hpp>

class Window : public glfw::Window {
public:
    Window() : glfw::Window(800, 600, "Title") {
        makeContextCurrent();
    }
    void processInput() {
        if (getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            setShouldClose(true);
        }
    }
};

int main(int argc, char ** argv) {
    Window window;
    while (!window.shouldClose()) {
        // Обработка ввода
        window.processInput();

        // Очистка экрана (заполнение цветом)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        window.swapBuffers();
        
        glfw::pollEvents();
    }
    
    return 0;
}
