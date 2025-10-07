set(CMAKE_THREAD_PREFER_PTHREAD ON) # tells cmake to prefer posix threads over other options
set(THREADS_PREFER_PTHREAD_FLAG ON) # tells cmake to prefer posix threads compiler and linker flags over other options
find_package(Threads REQUIRED)
set(SWAG_HAVE_PTHREAD "${CMAKE_USE_PTHREADS_INIT}")
list(APPEND CMAKE_REQUIRED_LIBRARY Threads::Threads)
list(APPEND SWAG_LINK_LIBS Threads::Threads)

find_package(XRT REQUIRED)
list(APPEND SWAG_INCLUDE_DIRS "${XRT_INCLUDE_DIR}")
list(APPEND SWAG_LINK_LIBS XRT::coreutil)