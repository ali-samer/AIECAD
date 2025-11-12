#pragma once

namespace aiecad {
class GraphicsContext {
public:
	virtual ~GraphicsContext() = default;

	virtual void init() = 0;
	virtual void swapBuffers() = 0;
};
} // namespace aiecad