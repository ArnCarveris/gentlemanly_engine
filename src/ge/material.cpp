#include "ge/material.hpp"
#include "ge/shader.hpp"

namespace ge
{
material::material(const std::shared_ptr<shader>& arg_shader) : shader_for_material{arg_shader}
{
	if (!arg_shader) throw std::runtime_error("Cannot initalize a material with an empty shader");
}

material::~material() {}
}
