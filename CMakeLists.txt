cmake_minimum_required(VERSION 3.7)
project(Shiba)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


File(GLOB SOURCE_FILES
        source/*.cpp
        source/*.h
        source/framework/*.cpp
        source/common/*.cpp
        source/graphics/*.cpp
        source/graphics/gl/*.cpp
        source/native/*.cpp
        source/native/*.h
        source/native/sfml/*.cpp
        source/native/sfml/service/*.cpp
        source/utils/*.cpp
        source/utils/*.h
        source/window/*.cpp
        source/window/*.h
        source/common/*.h
        )

#set(SOURCE_FILES
#        main.cpp
#        window/INativeWindow.h
#        Application.cpp
#        Application.h
#        utils/Singleton.h
#        Color.h
#        window/GuiWindow.cpp
#        window/GuiWindow.h
#        window/WindowEvent.h native/sfml/SFMLApplication.cpp native/sfml/SFMLApplication.h SFMLMain.cpp SFMLMain.h native/sfml/SFMLController.cpp native/sfml/SFMLController.h graphics/gl/GLGraphicsRenderer.cpp graphics/gl/GLGraphicsRenderer.h launcher.cpp launcher.h native/ShibaNative.h common/ShibaTypes.h utils/List.h utils/Interface.h native/sfml/service/SfmlEventService.cpp native/sfml/service/SfmlEventService.h framework/GLWindow.cpp framework/GLWindow.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif ()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif ()

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_libraries(${SFML_LIBRARIES})
endif ()

find_package(Threads REQUIRED)
if (THREADS_FOUND)
    link_libraries(Threads::Threads)
endif ()


add_executable(Shiba ${SOURCE_FILES} source/utils/List.h)