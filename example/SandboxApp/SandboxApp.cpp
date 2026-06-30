// #define HARIS_BUILD_DEBUG 1

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Haris.h>
#include <Common/Logger/Logger.h>

// ------------Entry Point------------
#include "Entry/EntryPoint.h"
#include "Sandbox2D.h"

#include "LayerImpl/ExampleLayer.h"

class Sandbox : public Haris::Application {
 public:
    Sandbox() {
        LOG_INFO("Sanbox created");
        DebugMacroBuilt::CheckAllConfigs();
        HARIS_ASSERT(false, "Failed to create Sanbox");

        // PushOverlay(new ExampleLayer());
        PushOverlay(new Sandbox2D());
    }

    ~Sandbox() {}
};

Haris::Application* Haris::CreateApplication() { return new Sandbox(); }