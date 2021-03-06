

#include "example.h"
#define IMPO_IMPLEMENTATION
#include "imponder.h"
#include <random>
#include <math.h>

namespace eg {

static constexpr float kPi = 3.14159265358979323846f;
static constexpr float kPi2 = kPi * 2.f;
using byte = unsigned char;

struct Vec2
{
    float x, y;

    Vec2(float x_ = 0.f, float y_ = 0.f) : x(x_), y(y_) {}

    Vec2 operator + (const Vec2& o) const { return { x + o.x, y + o.y }; }
    Vec2 operator - (const Vec2& o) const { return { x - o.x, y - o.y }; }
    Vec2 operator * (float s) const { return { x * s, y * s }; }
    operator ImVec2() const { return ImVec2(x, y); }
};

struct Random 
{
    std::mt19937 rand; // 32-bit Mersienne Twister random number generator.

    unsigned uint() { return rand(); }
    
    template <typename U>
    U range(unsigned lo, unsigned hi) {
        return static_cast<U>(lo + uint() % (hi - lo));
    }

    float onef() { return static_cast<float>(uint()) / rand.max(); }

    float rangef(float lo, float hi) { return lo + onef() * (hi - lo); }

    Vec2 vec2() { return { onef(), onef() }; }
    
    Vec2 polar() {
        const float rad = onef() * kPi2;
        return { cosf(rad), sinf(rad) };
    }
};

static Random g_rand;

struct Scene;

struct Actor
{
    Vec2 pos, vel;
    float param[4];
    ImColor colour;
};

struct Behaviour
{
    PONDER_POLYMORPHIC();
public:

    enum class Type { Random };

    virtual ~Behaviour() {}
    virtual void enter(Scene& s) {}
    virtual void update(const Update& up, Scene& s) = 0;
};

struct Scene
{
    std::vector<std::unique_ptr<Behaviour>> behaves;
    std::vector<Actor> actors;
    size_t behaveIndex{};
    Vec2 screenSize{};
    Vec2 screenMin{}, screenMax{};

    void init(const Init&);
    void update(const Update&);
    void draw();
    Behaviour& currBehaviour() { return *behaves[behaveIndex]; }
};

static Scene g_scene;

struct RandomBehaviour final : Behaviour
{
    float velscale{ 100.f };

    void randomise(Actor& a)
    {
        a.vel = g_rand.vec2() * velscale - Vec2(velscale) * 0.5f;
        a.param[0] = g_rand.rangef(2.f, 5.f);
    }

    void enter(Scene& s) final
    {
        for (Actor& a : s.actors) {
            randomise(a);
            a.pos = s.screenSize * 0.5f + g_rand.vec2() * 200.f - Vec2(100.f, 100.f);
            a.colour = ImColor(g_rand.range<int>(50, 255), 0, 0);
        }
    }

    void update(const Update& up, Scene& s) final
    {
        for (Actor& a : s.actors) {
            if ((a.param[0] -= up.dt) < 0.f)
                randomise(a);
            a.pos = a.pos + a.vel * up.dt;
            if (a.pos.x < s.screenMin.x || a.pos.x > s.screenMax.x)
                a.vel.x = -a.vel.x;
            if (a.pos.y < s.screenMin.y || a.pos.y > s.screenMax.y)
                a.vel.y = -a.vel.y;
        }
    }
};


void Scene::init(Init const& in)
{
    screenSize = { (float)in.screenW, (float)in.screenH };
    screenMin = { 10.f, 10.f };
    screenMax = screenSize - screenMin;
    behaves.emplace_back(std::make_unique<RandomBehaviour>());
    actors.resize(50);
    currBehaviour().enter(*this);
}

void Scene::update(Update const& up)
{
    currBehaviour().update(up, *this);
}

static bool show_canvas = true;

void Scene::draw()
{
    ImGui::Begin("Canvas", &show_canvas,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos("Canvas", ImVec2(0, 0));
    ImGui::SetWindowSize(screenSize);
    ImDrawList* dl = ImGui::GetWindowDrawList();

    for (Actor& a : actors)
    {
        const float sz{ 10.f };
        dl->AddQuadFilled(
            a.pos + Vec2(-sz, 0),
            a.pos + Vec2(0, -sz),
            a.pos + Vec2(sz, 0),
            a.pos + Vec2(0, sz),
            a.colour
        );
    }

    ImGui::End();
}

}

// Need to declare these in the top/global namespace.
PONDER_TYPE(eg::Vec2);
PONDER_TYPE(eg::Actor);
PONDER_TYPE(eg::Behaviour);
PONDER_TYPE(eg::RandomBehaviour);

namespace eg {

static bool show_demo_window = true;

void init(Init const& in)
{
    using namespace ponder;

    Class::declare<Vec2>()
        .property("x", &Vec2::x)
        .property("y", &Vec2::y)
        ;

    Class::declare<Actor>()
        .property("pos", &Actor::pos)
        .property("vel", &Actor::vel)
        ;

    Class::declare<Behaviour>();

    Class::declare<RandomBehaviour>()
        .base<Behaviour>()
        .property("velocityScale", &RandomBehaviour::velscale)
        ;

    g_scene.init(in);
}

bool update(const Update& up)
{
    g_scene.update(up);
    g_scene.draw();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    if (up.frameNum == 0)
        ImGui::SetWindowCollapsed("Dear ImGui Demo", true);

    impo::showMetadata();

    {
        impo::Editor ed;
        ed.edit(dynamic_cast<RandomBehaviour&>(g_scene.currBehaviour())); // Hmmm
    }

    return true;
}

} // namespace eg

