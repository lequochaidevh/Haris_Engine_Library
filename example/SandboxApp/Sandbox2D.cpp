#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) {}

void Sandbox2D::OnAttach() {
    HARIS_PROFILE_FUNCTION();
    m_CheckerboardTexture = Haris::Texture2D::Create(CHECKER_BOARD_PATH);
}

void Sandbox2D::OnDetach() { HARIS_PROFILE_FUNCTION(); }

void Sandbox2D::OnUpdate(Haris::Timestep ts) {
    HARIS_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(ts);

    // Render
    {
        HARIS_PROFILE_SCOPE("Renderer Pre-process");
        Haris::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Haris::RenderCommand::Clear();
    }

    {
        HARIS_PROFILE_SCOPE("Renderer Draw");
        Haris::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Haris::Renderer2D::SetDrawStateInfo(m_SquareColor,
                                            Haris::RAINBOW::Dynamic, 1.0f);
        Haris::Renderer2D::DrawQuad({-10.0f, 0.0f}, {0.8f, 0.8f});

        Haris::Renderer2D::SetDrawStateInfo(m_SquareColor, Haris::RAINBOW::None,
                                            1.0f);
        Haris::Renderer2D::DrawRotatedQuad({-10.0f, -4.0f}, {0.8f, 0.8f},
                                           -45.0f);
        Haris::Renderer2D::ResetDrawStateInfo();

        Haris::Renderer2D::SetDrawStateInfo(
            glm::vec4({1.1f, 1.1f, 1.1f, 2.0f}) - m_SquareColor,
            Haris::RAINBOW::Static, 1.0f);
        Haris::Renderer2D::DrawQuad({-12.f, -5.f}, {1.5f, 0.75f});

        Haris::Ref<Haris::DrawStateInfo> RefDrawState =
            Haris::CreateRef<Haris::DrawStateInfo>(
                m_CheckerboardColor, Haris::RAINBOW::Dynamic, 10.0f);
        Haris::Renderer2D::SetDrawStateInfo(RefDrawState);
        Haris::Renderer2D::DrawQuad({1.0f, 1.0f, 1.0f}, {5.0f, 5.0f},
                                    m_CheckerboardTexture);

        Haris::Renderer2D::SetDrawStateInfo(m_SquareColor,
                                            Haris::RAINBOW::Dynamic, 1.0f);
        Haris::Renderer2D::DrawQuad({-6.0f, -6.0f, 1.0f}, {5.0f, 5.0f},
                                    m_CheckerboardTexture);

        Haris::Renderer2D::SetDrawStateInfo(m_SquareColor,
                                            Haris::RAINBOW::Static, 1.0f);
        Haris::Renderer2D::DrawQuad({-7.0f, -7.0f, 1.0f}, {1.0f, 5.0f},
                                    m_CheckerboardTexture);

        static float rotation = 0.0f;
        rotation += ts * 50.0f;
        Haris::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {3.0f, 3.0f},
                                           rotation, m_CheckerboardTexture);

        Haris::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender() {
    HARIS_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::ColorEdit4("Checkerboard Color",
                      glm::value_ptr(m_CheckerboardColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(Haris::Event& e) {
    HARIS_PROFILE_FUNCTION();
    m_CameraController.OnEvent(e);
}