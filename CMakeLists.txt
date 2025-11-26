cmake_minimum_required(VERSION 3.10.0)
project(app VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_language(RC)
set(APP_ICON_RESOURCE_WINDOWS resources.rc)

include_directories("src")

add_executable(app WIN32
  main.cpp 

  src/Application.cpp 
  src/Widget.cpp 
  src/internal/Environment.cpp

  app.manifest 
  ${APP_ICON_RESOURCE_WINDOWS}
)


target_link_libraries(app PRIVATE d2d1 dwrite windowscodecs)