# Your CMakeLists.txt for spider one suit solitaire
cmake_minimum_required(VERSION 3.10)

project(
    spider
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)


include_directories("./include/")

# link_directories("/usr/lib/x86_64-linux-gnu/")

add_executable(spider ./src/Card.cpp ./src/DeckSpades.cpp ./src/AnimationWrapper.cpp ./src/AnimationWrapperST.cpp ./src/Move.cpp 
./src/DealOneRound.cpp ./src/FillFoundationPile.cpp ./src/ModelSpider.cpp ./src/ViewSpider.cpp ./src/ControllerSpider.cpp ./src/Main.cpp)

target_compile_options(spider PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(spider sfml-graphics sfml-window sfml-system)