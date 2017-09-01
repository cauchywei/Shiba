cmake_minimum_required(VERSION 3.7)
project(Shiba)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")


File(GLOB SOURCE_FILES
        source/*.cpp
        source/*.h
        source/framework/*.cpp
        source/common/*.cpp
        source/gui/graphics/*.cpp
        source/gui/graphics/gl/*.cpp
        source/platform/*.cpp
        source/platform/*.h
        source/platform/sfml/*.cpp
        source/platform/sfml/service/*.cpp
        source/utils/*.cpp
        source/utils/*.h
        source/gui/window/*.cpp
        source/gui/window/*.h
        source/common/*.h
        source/framework/*.h
        source/framework/*.cpp
        source/framework/math/*.h
        source/framework/graphic/shader/*.cpp
        source/framework/model/*.cpp
        source/framework/model/loader/*.cpp
        source/framework/model/loader/*.h
        source/framework/model/*.cpp
        source/thirdpart/*.h
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
#        window/WindowEvent.h platform/sfml/SFMLApplication.cpp platform/sfml/SFMLApplication.h SFMLMain.cpp SFMLMain.h platform/sfml/SFMLController.cpp platform/sfml/SFMLController.h graphics/gl/GLGraphicsRenderer.cpp graphics/gl/GLGraphicsRenderer.h launcher.cpp launcher.h platform/ShibaNative.h common/ShibaTypes.h utils/List.h utils/Interface.h platform/sfml/service/SfmlEventService.cpp platform/sfml/service/SfmlEventService.h framework/GLWindow.cpp framework/GLWindow.h)

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


add_executable(Shiba ${SOURCE_FILES} source/utils/FileUtil.cpp source/framework/ShibaOpenGL.cpp)