#include <ge/animation_actor.hpp>
#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/input_subsystem.hpp>
#include <ge/texture_asset.hpp>

using namespace ge;

int main() {

    runtime r;
    r.m_asset_manager.add_asset_path("data/");
    r.add_subsystem<input_subsystem>({});
    auto& sdl = r.add_subsystem<sdl_subsystem>({
        "Example",
        {},
        {1280, 720}
    });

    auto root_actor = actor::root_factory(&r);
    r.set_root_actor(root_actor.get());

    mesh_settings msettings = r.m_asset_manager.get_asset<mesh_settings_asset>("texturedmodel/textured.meshsettings");
    msettings.m_material.m_property_values["Texture"] = r.m_asset_manager.get_asset<texture_asset>("animationtest.texture");
    auto animation_act = actor::factory<animation_actor>(root_actor.get(), msettings, 10.f);

    auto camera = actor::factory<camera_actor>(root_actor.get(), 4);
    sdl.set_camera(camera.get());

    while(r.tick());
}
