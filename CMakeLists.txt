# ALL THE NEEDED LIBRARIES ARE STATICALLY LINKED,
# MEANING YOU DON'T HAVE TO DOWNLOAD THEM BY YOURSELF

# set minimum CMake version
cmake_minimum_required(VERSION 3.10)
# set project name
set(PROJECT_NAME G3CE)
project(${PROJECT_NAME})

# set output folder for the generated executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# add include folder (contains all header files)
include_directories(include)
# add include folders for glad and stbi
include_directories(libs/glad libs/stbi)

# look for OpenGL in the current system
find_package(OpenGL REQUIRED)

# create static libraries for all the downloaded .h files and their respective .c implementations
add_library(glad STATIC libs/glad/glad.c)
add_library(stbi STATIC libs/stbi/stb_image.c)

# link math to stb_image library otherwise it'll be missing the pow function
target_link_libraries(stbi PRIVATE -lm)

# add GLFW from the original git repository (downloaded and put into libs/glfw)
add_subdirectory(libs/glfw)

# create executable
add_executable(${PROJECT_NAME}
    src/main.c
    src/engine/app.c
    src/engine/core/input.c
    src/engine/core/window.c
    src/engine/gfx/mesh.c
    src/engine/gfx/renderer.c
    src/engine/gfx/shader.c
    src/engine/gfx/texture.c
    src/engine/utils/console.c
    src/engine/utils/file.c
)

# link the libraries to the project
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL # linked from the previously found library
    OpenGL::GLU # linked from the previously found library
    glad # linked from the previously created static library
    stbi # linked from the previously created static library
    glfw # linked from the loaded subdirectory
)

# include directories to make include paths fancier
target_include_directories(${PROJECT_NAME} PRIVATE
    libs
)