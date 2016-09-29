#include "ge/rocket_subsystem.hpp"

#include <Rocket/Core.h>

using namespace ge;

bool rocket_subsystem::initialize(rocket_subsystem::config)
{
	auto sdl_sub = m_runtime->get_subsystem<sdl_subsystem>();
	if (!sdl_sub) {
		return false;
	}

	auto m_render_interface = new ui::render_interface(m_runtime->m_asset_manager, sdl_sub->get_size());
	auto m_system_interface = new ui::system_interface(*m_runtime);

	Rocket::Core::SetSystemInterface(m_system_interface);
	Rocket::Core::SetRenderInterface(m_render_interface);

	Rocket::Core::Initialise();

	m_context = Rocket::Core::CreateContext(
		"default", {int(sdl_sub->get_size().x), int(sdl_sub->get_size().y)});

	return true;
}

bool rocket_subsystem::update(std::chrono::duration<float> delta)
{
	m_context->Render();

	return true;
}

bool rocket_subsystem::shutdown()
{
	m_context->RemoveReference();

	Rocket::Core::Shutdown();

	return true;
}
