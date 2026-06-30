#pragma once

extern Haris::Application* Haris::CreateApplication();

int main(int argc, char** argv) {
    HARIS_PROFILE_BEGIN_SESSION("Startup", "HarisProfile-Startup.json");
    auto app = Haris::CreateApplication();
    HARIS_PROFILE_END_SESSION();

    HARIS_PROFILE_BEGIN_SESSION("Runtime", "HarisProfile-Runtime.json");
    app->Run();
    HARIS_PROFILE_END_SESSION();

    HARIS_PROFILE_BEGIN_SESSION("Startup", "HarisProfile-Shutdown.json");
    delete app;
    HARIS_PROFILE_END_SESSION();
}
