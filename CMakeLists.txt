cmake_minimum_required(VERSION 3.0.0)
project(CMDGameEngine)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY CLEAN_NO_CUSTOM 1)

set (SOURCES
    CMDGETestEnv.c
    WindowHandle.c
    RenderEngine.c
    PhysicEngine.c
    SoundEngine.c
    Timers.c
    InputHandle.c
    LogHandle.c
)

set (HEADERS 
    TextGameEngine.h
)

add_executable(TestEnv ${SOURCES} ${HEADERS})

add_library(CMDGameEngine STATIC ${SOURCES} ${HEADERS})
target_include_directories(CMDGameEngine PUBLIC include)

target_link_libraries(TestEnv winmm) 