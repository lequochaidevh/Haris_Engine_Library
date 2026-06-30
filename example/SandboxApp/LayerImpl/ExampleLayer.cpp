#include "ExampleLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
    : Layer("Example"),
      m_CameraController(1280.0f / 720.0f, true),
      m_SquarePosition(1.0f) {
    m_VertexArray = Haris::VertexArray::Create();

    float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                             0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                             0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

    Haris::Ref<Haris::VertexBuffer> vertexBuffer =
        Haris::VertexBuffer::Create(vertices, sizeof(vertices));

    Haris::BufferLayout layout = {{Haris::ShaderDataType::Float3, "a_Position"},
                                  {Haris::ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t                       indices[3] = {0, 1, 2};
    Haris::Ref<Haris::IndexBuffer> indexBuffer =
        Haris::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA = Haris::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  //
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  //
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  //
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   //
    };

    Haris::Ref<Haris::VertexBuffer> squareVB =
        Haris::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    squareVB->SetLayout({{Haris::ShaderDataType::Float3, "a_Position"},
                         {Haris::ShaderDataType::Float2, "a_TexCoord"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t                       squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Haris::Ref<Haris::IndexBuffer> squareIB = Haris::IndexBuffer::Create(
        squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

    m_Shader = Haris::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

    std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

            void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

    m_FlatColorShader = Haris::Shader::Create(
        "FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

    std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    auto textureShader = m_ShaderLibrary.Load(BASIC_TEXTURE_SHADER_PATH);

    m_Texture          = Haris::Texture2D::Create(CHECKER_BOARD_PATH);
    m_HarisLogoTexture = Haris::Texture2D::Create(HARIS_LOGO_PATH);

    textureShader->Bind();
    textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Haris::Timestep ts) {
    m_CameraController.OnUpdate(ts);

    if (Haris::Input::IsKeyPressed(INP_KEY_J))
        m_SquarePosition.x -= m_SquareMoveSpeed * ts;
    else if (Haris::Input::IsKeyPressed(INP_KEY_L))
        m_SquarePosition.x += m_SquareMoveSpeed * ts;

    if (Haris::Input::IsKeyPressed(INP_KEY_I))
        m_SquarePosition.y += m_SquareMoveSpeed * ts;
    else if (Haris::Input::IsKeyPressed(INP_KEY_K))
        m_SquarePosition.y -= m_SquareMoveSpeed * ts;

    if (Haris::Input::IsKeyPressed(INP_KEY_UP)) {
        float zoom_level = m_CameraController.GetZoomLevel();
        zoom_level -= m_SquareMoveSpeed * ts;
        m_CameraController.SetZoomLevel(zoom_level);
    } else if (Haris::Input::IsKeyPressed(INP_KEY_DOWN)) {
        float zoom_level = m_CameraController.GetZoomLevel();
        zoom_level += m_SquareMoveSpeed * ts;
        m_CameraController.SetZoomLevel(zoom_level);
    }

    Haris::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Haris::RenderCommand::Clear();

    // Render
    Haris::Renderer::BeginScene(m_CameraController.GetCamera());

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Haris::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
        }
    }
    auto textureShader = m_ShaderLibrary.Get("BasicTexture");

    glm::mat4 square_transform =
        glm::translate(glm::mat4(1.0f), m_SquarePosition);

    // CHECK BOARD
    {
        glm::mat4 scaler_ = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
        glm::vec3 pos_(1.6f, -1.6f, 1.0f);
        glm::mat4 transform_ = glm::translate(glm::mat4(1.0f), pos_) * scaler_;

        m_Texture->Bind();
        Haris::Renderer::Submit(textureShader, m_SquareVA, transform_);
    }

    // BLUE QUAD OVERLAY AFTER LOGO
    Haris::Renderer::Submit(m_FlatColorShader, m_SquareVA, square_transform);

    glm::vec3 scale_texture(1.8f, 2.8f, 1.0f);
    m_HarisLogoTexture->Bind();
    Haris::Renderer::Submit(textureShader, m_SquareVA,
                            glm::scale(square_transform, scale_texture));

    // Big Blue Quad
    {
        glm::mat4 scaler_ = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
        glm::vec3 pos_(-1.6f, -1.6f, 1.0f);
        glm::mat4 transform_ = glm::translate(glm::mat4(1.0f), pos_) * scaler_;

        m_FlatColorShader->Bind();
        Haris::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform_);
    }

    // Triangle
    Haris::Renderer::Submit(m_Shader, m_VertexArray);

    Haris::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void ExampleLayer::OnEvent(Haris::Event& event) {
    m_CameraController.OnEvent(event);
}
