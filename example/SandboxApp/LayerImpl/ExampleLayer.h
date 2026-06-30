#pragma once

#include "BaseHeaderConfig.h"

class ExampleLayer : public Haris::Layer {
 public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    void         OnUpdate(Haris::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void         OnEvent(Haris::Event& e) override;

 private:
    Haris::ShaderLibrary           m_ShaderLibrary;
    Haris::Ref<Haris::Shader>      m_Shader;
    Haris::Ref<Haris::VertexArray> m_VertexArray;

    Haris::Ref<Haris::Shader>      m_FlatColorShader;
    Haris::Ref<Haris::VertexArray> m_SquareVA;

    Haris::Ref<Haris::Texture2D> m_Texture, m_HarisLogoTexture;

    Haris::OrthographicCameraController m_CameraController;
    float                               m_SquareMoveSpeed = 2.0f;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
    glm::vec3 m_SquarePosition;
};