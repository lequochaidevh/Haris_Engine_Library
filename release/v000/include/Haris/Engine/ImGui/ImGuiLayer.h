#pragma once
#include "Entry/Alias.h"
#include "Layer/Layer.h"

namespace Haris {

class HARIS_API ImGuiLayerImpl {
 public:
    ImGuiLayerImpl(){};
    ~ImGuiLayerImpl(){};

    virtual void OnAttach()      = 0;
    virtual void OnDetach()      = 0;
    virtual void OnImGuiRender() = 0;

    virtual void Begin() = 0;
    virtual void End()   = 0;

 private:
    float m_Time = 0.0f;
};

class HARIS_API ImGuiLayer : public Layer {
 protected:
    Scope<ImGuiLayerImpl> m_Impl;

 public:
    ImGuiLayer();
    ~ImGuiLayer() = default;

    virtual void OnAttach() override { m_Impl->OnAttach(); };
    virtual void OnDetach() override { m_Impl->OnDetach(); };
    virtual void OnImGuiRender() override { m_Impl->OnImGuiRender(); };

    virtual void Begin() { m_Impl->Begin(); };
    virtual void End() { m_Impl->End(); };

 private:
    float m_Time = 0.0f;
};

}  // namespace Haris