#pragma once
#include <chrono>

namespace aiecad {
class Timestep {
public:
	using clock = std::chrono::steady_clock;

	Timestep() = default;
	auto  step() const { return clock::now(); }
	void  start() { m_last = step(); }
	float getDelta() {
		const auto delta = std::chrono::duration<float>(step() - m_last);
		m_dt = delta.count(); // seconds
		return m_dt;
	}
	void  update() { start(); }

private:
	float             m_dt {};
	clock::time_point m_last{};
};
} // namespace aiecad
