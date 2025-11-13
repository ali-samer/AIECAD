#pragma once

#include <filesystem>
namespace fs = std::filesystem;

namespace aiecad {
class SandboxService {
public:
	explicit SandboxService(const fs::path& root);
	~SandboxService() = default;

	// ensure the root exists
	bool ensure();

	const fs::path& root() const {return m_root; }

	// creates a temp subdir
	fs::path makeTemp(const std::string &hint) const;

	// utility to check a path belongs to the sandbox
	bool isInSandbox(const fs::path& path) const;
private:
	fs::path m_root;
};
} // namespace aiecad