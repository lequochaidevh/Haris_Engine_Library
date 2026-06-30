#include "OrthographicCamera.h"
#include "Texture.h"

#include "Entry/Alias.h"
#include <utility>  //  std::move

namespace Haris {

enum class RAINBOW { None, Static, Dynamic };

// 1. define struct
struct DrawStateInfo {
    glm::vec4 _tintColor;
    RAINBOW   _rainbow_state;
    float     _tilingFactor;

    DrawStateInfo(glm::vec4&& tintColor, RAINBOW rb_state, float tilingFactor)
        : _tintColor(std::move(tintColor)),
          _rainbow_state(rb_state),
          _tilingFactor(tilingFactor) {}
    DrawStateInfo(glm::vec4& tintColor, RAINBOW rb_state, float tilingFactor)
        : _tintColor(tintColor),
          _rainbow_state(rb_state),
          _tilingFactor(tilingFactor) {}

    void reset() {
        _tintColor     = glm::vec4(1.0f);
        _rainbow_state = RAINBOW::None;
        _tilingFactor  = 1.0f;
    }
};

class Renderer2D {
 public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();

    static void Flush();

    // Primitives
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
                         const Ref<Texture2D>& texture);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size,
                         const Ref<Texture2D>& texture);

    static void DrawRotatedQuad(const glm::vec2& position,
                                const glm::vec2& size, float rotation);
    static void DrawRotatedQuad(const glm::vec3& position,
                                const glm::vec2& size, float rotation);
    static void DrawRotatedQuad(const glm::vec2& position,
                                const glm::vec2& size, float rotation,
                                const Ref<Texture2D>& texture);
    static void DrawRotatedQuad(const glm::vec3& position,
                                const glm::vec2& size, float rotation,
                                const Ref<Texture2D>& texture);

 private:
    // 2. Declare static instance
    // mordern c++17 inline static
    // inline static Ref<DrawStateInfo> _s_state_instance = nullptr;
    static Ref<DrawStateInfo> _s_state_instance;

    struct RandomColor_t {
        // 1. Changed to value types.
        glm::vec4 subcolor;
        glm::vec4 pluscolor;
        glm::vec4 mulcolor;
        glm::vec4 sub2color;

        void build_rainbow();
    };

    // inline static mordern c++17
    inline static RandomColor_t ExtraColor;

 public:
    static void SetDrawStateInfo(glm::vec4&& tintColor, RAINBOW rb_state,
                                 float tilingFactor);

    static void SetDrawStateInfo(glm::vec4& tintColor, RAINBOW rb_state,
                                 float tilingFactor);

    static void SetDrawStateInfo(Ref<DrawStateInfo>& draw_state);

    static void ResetDrawStateInfo();
};

}  // namespace Haris
