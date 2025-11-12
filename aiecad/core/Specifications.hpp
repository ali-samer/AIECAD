#pragma once

#include <string>
#include <cstdint>

namespace aiecad {

struct WindowSpecification;
struct ApplicationSpecification;

struct WindowSpecification {
	std::string title;
	int width;
	int height;
	bool resizable;
	int swap_interval;
	float dpi_scale;
	std::uint32_t spec_version;
};

struct ApplicationSpecification {
	std::string name;
	WindowSpecification window_spec;

	// TODO <ApplicationSpecification : struct> : method body was made on fly. Must change to something meaningful
	explicit operator bool() const {
		return window_spec.title.empty();
	}
};

} // namespace aiecad