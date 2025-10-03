

set(CMAKE_THREAD_PREFER_PTHREAD ON) # tells cmake to prefer posix threads over other options
set(THREADS_PREFER_PTHREAD_FLAG ON) # tells cmake to prefer posix threads compiler and linker flags over other options
find_package(Threads REQUIRED)
set(SWAG_HAVE_PTHREAD "${CMAKE_USE_PTHREADS_INIT}")
list(APPEND CMAKE_REQUIRED_LIBRARY Threads::Threads)
list(APPEND SWAG_LINK_LIBRARIES Threads::Threads)


