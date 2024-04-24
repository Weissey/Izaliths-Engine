#pragma once
#include "glfw3.h"
#include <glew.h>

class FenceObject {

private:
    GLsync* fence;
    bool signaled;

public:

    FenceObject() : fence(nullptr), signaled(false) {}

    /*void OnRender() {
        fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }

    bool CheckSignal() {
        GLenum result = glClientWaitSync(fence, GL_SYNC_FLUSH_COMMANDS_BIT, 1);

        if (result == GL_TIMEOUT_EXPIRED || result == GL_WAIT_FAILED)
            signaled = false;
        else
            signaled = true;

        glDeleteSync(fence);
        return signaled;
    }*/

    bool IsSignaled() const {
        return signaled;
    }
};