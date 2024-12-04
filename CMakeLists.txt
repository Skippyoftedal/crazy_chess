cmake_minimum_required(VERSION 3.25)
project(crazy_chess)

set(CMAKE_CXX_STANDARD 20)


add_executable(crazy_chess src/main.cpp
        src/model/Board.cpp
        src/model/piece.cpp
        src/model/Queen.cpp
        src/model/King.cpp
        src/model/Rook.cpp
        src/model/Bishop.cpp
        src/model/Pawn.cpp
        src/model/Knight.cpp
        src/model/Tile.cpp
        src/model/FontLoader.h
        src/model/FontLoader.cpp
        src/model/headers/PieceColor.h
        src/model/headers/PromotionChoice.h
        src/model/headers/PromotionModal.h
)



file(COPY ${CMAKE_SOURCE_DIR}/src/resources/images DESTINATION ${CMAKE_BINARY_DIR}/images/)



include_directories(include /usr/include c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(myFirstGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
#target_compile_options(myFirstGame PRIVATE -Wall -Wextra -Wpedantic)

#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
