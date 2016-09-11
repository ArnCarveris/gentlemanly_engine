#pragma once

#include <ge/asset_manager.hpp>
#include <ge/concept/asset.hpp>

#include <Rocket/Core/FontDatabase.h>

#include <boost/filesystem.hpp>

namespace ge
{
namespace ui
{
/// An asset for loading fonts into rocket.
/// This is a void cached asset meaning that the font is stored internally
/// Inside rocket and that calling to load the same asset twice will have no affect
///
/// SPECIFICATION:
/// ```json
/// {
///   "asset_type": "rocket_font_asset",
///   "font_file": "/path/to/ttf/or/otf",
///   "rcss_name": "optional CSS name, it is extracted from the file by default",
///   "font_style": "either normal or italic; if rcss_name is specified, this is required",
///   "font_weight": "either notrmal or bold, if rcss_name is specififed, this is required"
/// }
/// ```
struct rocket_font_asset {
	/// No loaded type, it is stored internally in Rocket
	using loaded_type = void;

	/// We want caching to avoid loading the same font twice
	using cached = std::false_type;

	/// Asset loading function
	static void load_asset(asset_manager& manager, const char* asset_name, const char* filepath,
		const nlohmann::json& json_data)
	{
		std::string abs_path =
			boost::filesystem::absolute(json_data["font_file"], filepath).string();

		// get names etc
		auto rcss_name_iter = json_data.find("rcss_name");

		// if the rcss name wasn't specified, just do the basic load
		if (rcss_name_iter == json_data.end()) {
			Rocket::Core::FontDatabase::LoadFontFace(abs_path.c_str());
		} else {  // if not, load in with the parameters

			std::string rcss_name_str = *rcss_name_iter;

			std::string font_style_str = json_data["font_style"];
			std::string font_weight_str = json_data["font_weight"];

			// load those into enums

			Rocket::Core::Font::Style e_style;
			if (font_style_str == "normal") {
				e_style = Rocket::Core::Font::STYLE_NORMAL;
			} else if (font_style_str == "italic") {
				e_style = Rocket::Core::Font::STYLE_ITALIC;
			} else {
				throw std::runtime_error(
					"Unrecognized font_style \"" + font_style_str + "\" in asset: " + filepath);
			}

			Rocket::Core::Font::Weight e_weight;
			if (font_weight_str == "normal") {
				e_weight = Rocket::Core::Font::WEIGHT_NORMAL;
			} else if (font_weight_str == "bold") {
				e_weight = Rocket::Core::Font::WEIGHT_BOLD;
			} else {
				throw std::runtime_error(
					"Unrecognized font_weight \"" + font_weight_str + "\" in asset: " + filepath);
			}

			Rocket::Core::FontDatabase::LoadFontFace(
				abs_path.c_str(), rcss_name_str.c_str(), e_style, e_weight);
		}
	}

	/// Requries the asset to have "asset_type": "rocket_font_asset"
	static const char* asset_type() { return "rocket_font_asset"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<rocket_font_asset>));
}

static const char* asset_type() { return "rocket_font_asset"; }
}
