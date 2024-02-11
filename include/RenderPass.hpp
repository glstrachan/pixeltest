#pragma once

class RenderPass {
public:
    virtual ~RenderPass() = default;

    virtual void setup() = 0;    // Prepare the render pass
    virtual void draw() = 0;     // Execute the render pass
    virtual void cleanup() = 0;  // Clean up after the render pass
};

class TexturePass : public RenderPass {

};

class ScreenPass : public RenderPass {

};