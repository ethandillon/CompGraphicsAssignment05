//
// Created by Ben on 6/11/2024.
//

#ifndef ERROR_CHECK_H
#define ERROR_CHECK_H

namespace cs4722 {
    /**
     *  This function sets up GLFW debugging messages.
     *  It should be called just before initializing GLFW.
     *  That is the function call glfwInit.
     */
    void enableGlfwDebugging();

    /**
     *  This function sets up OpenGL debugging messages.
     *  The function must be called after GLAD is loaded.
     *  That would be after the function call to gladLoadGL.
     */
    void enableOpenglDebugging();
}

#endif //ERROR_CHECK_H
