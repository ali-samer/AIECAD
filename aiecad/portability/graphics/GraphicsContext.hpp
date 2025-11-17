#pragma once

#include <cstdint>
#include <aiecad/macros/Macros.hpp>

namespace aiecad {

class GraphicsContext {
public:
	virtual ~GraphicsContext() = default;
	AIECAD_DELETE_COPY_AND_MOVE(GraphicsContext);

	virtual void init() = 0;
	virtual void swapBuffers() = 0;
protected:
	GraphicsContext() = default;
};
} // namespace aiecad