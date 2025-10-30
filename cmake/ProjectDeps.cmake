set(CMAKE_THREAD_PREFER_PTHREAD ON) # tells cmake to prefer posix threads over other options
set(THREADS_PREFER_PTHREAD_FLAG ON) # tells cmake to prefer posix threads compiler and linker flags over other options
find_package(Threads REQUIRED)
set(AIECAD_HAVE_PTHREAD "${CMAKE_USE_PTHREADS_INIT}")
list(APPEND AIECAD_LINK_LIBS Threads::Threads)

find_package(XRT QUIET)
if (XRT_FOUND)
    list(APPEND AIECAD_INCLUDE_DIRS "${XRT_INCLUDE_DIR}")
    list(APPEND AIECAD_LINK_LIBS XRT::coreutil)
endif ()

find_package(glfw3 REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

list(APPEND AIECAD_LINK_LIBS glfw glad::glad imgui::imgui glm::glm spdlog::spdlog_header_only)