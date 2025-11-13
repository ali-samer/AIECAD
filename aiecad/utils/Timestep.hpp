#pragma once
#include <chrono>

namespace aiecad {
class Timestep {
public:
	using clock = std::chrono::steady_clock;

	Timestep() = default;
	auto  step() const { return clock::now(); }
	void  start() { m_last = step(); }
	float getDelta() { return (step() - m_last).count(); }
	void  update() { start(); }

private:
	double            m_dt {};
	clock::time_point m_last{};
};
} // namespace aiecad
