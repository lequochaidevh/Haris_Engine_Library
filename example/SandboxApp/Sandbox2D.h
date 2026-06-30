#pragma once
#include "BaseHeaderConfig.h"
#include "Haris.h"

class Sandbox2D : public Haris::Layer {
 public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void         OnUpdate(Haris::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void         OnEvent(Haris::Event& e) override;

 private:
    Haris::OrthographicCameraController m_CameraController;

    // Temp
    Haris::Ref<Haris::VertexArray> m_SquareVA;
    Haris::Ref<Haris::Shader>      m_FlatColorShader;

    Haris::Ref<Haris::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor       = {0.2f, 0.3f, 0.8f, 1.0f};
    glm::vec4 m_CheckerboardColor = {0.5f, 0.5f, 0.5f, 1.0f};
};