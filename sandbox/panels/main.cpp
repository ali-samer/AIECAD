// main.cpp
#include <cstdio>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include <imgui_internal.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static GLFWwindow* make_window(int w, int h, const char* title) {
    if (!glfwInit()) throw std::runtime_error("glfwInit failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!win) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1); // vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("gladLoadGLLoader failed");

    return win;
}

static void imgui_init(GLFWwindow* win) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;      // keyboard controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;          // docking ON
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;        // multi-viewport (optional, nice)

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 6.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // backend bindings
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

static void imgui_shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void BuildDockspaceLayout(ImGuiID dockspace_id) {
    ImGui::DockBuilderRemoveNode(dockspace_id);                    // clear any previous layout
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

    ImGuiID dock_id_nav, dock_id_center;
    dock_id_center = dockspace_id;
    dock_id_nav = ImGui::DockBuilderSplitNode(dock_id_center, ImGuiDir_Up, 0.10f, nullptr, &dock_id_center);

    ImGui::DockBuilderDockWindow("Nav Bar",  dock_id_nav);

    ImGui::DockBuilderFinish(dockspace_id);
}

static void DrawMainMenuBar(bool& show_demo) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("ImGui Demo Window", nullptr, &show_demo);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About AIECAD…")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

static void DrawNavBar() {
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoMove     |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 6));
    if (ImGui::Begin("Nav Bar", nullptr, flags)) {
        ImGui::TextUnformatted("Project: <none>");
        ImGui::SameLine();
        if (ImGui::Button("New")) { /* later: action */ }
        ImGui::SameLine();
        if (ImGui::Button("Open")) { /* later: file dialog */ }
        ImGui::SameLine();
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
        ImGui::SameLine();
        if (ImGui::Button("Run ▶")) { /* later: run pipeline */ }
        ImGui::SameLine();
        ImGui::TextDisabled("|");
        ImGui::SameLine();
        ImGui::TextUnformatted("Tip: This is a docked toolbar.");
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

static void BeginDockspaceHost(bool& layout_initialized, bool& show_demo) { // <-- MODIFIED
    ImGuiWindowFlags host_flags =
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_MenuBar;

    const ImGuiViewport* vp = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(vp->Pos);
    ImGui::SetNextWindowSize(vp->Size);
    ImGui::SetNextWindowViewport(vp->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("DockSpaceHost", nullptr, host_flags); // no title bar, covers viewport

    ImGui::PopStyleVar(3);

    DrawMainMenuBar(show_demo);

    ImGuiID dockspace_id = ImGui::GetID("AIECAD/DockSpace");
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_PassthruCentralNode; // allows background to show
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), dock_flags);

    if (!layout_initialized) {
        BuildDockspaceLayout(dockspace_id);
        layout_initialized = true;
    }
}

static void EndDockspaceHost() {
    ImGui::End(); // DockSpaceHost
}

static void DrawExampleCentral() {
    if (ImGui::Begin("Welcome")) {
        ImGui::TextWrapped("This is the central dock area. "
                           "Open/drag windows, split panes, and experiment.");
    }
    ImGui::End();
}

int main() try {
    GLFWwindow* window = make_window(1400, 900, "AIECAD - Tutorial Frame");
    imgui_init(window);

    bool layout_initialized = false;
    bool show_demo = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        BeginDockspaceHost(layout_initialized, show_demo);
        EndDockspaceHost();

        if (show_demo) {
            ImGui::ShowDemoWindow(&show_demo);
        }

        DrawNavBar();
        DrawExampleCentral();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.10f, 0.10f, 0.11f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(window);
    }

    imgui_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
catch (const std::exception& e) {
    std::fprintf(stderr, "FATAL: %s\n", e.what());
    return 1;
}