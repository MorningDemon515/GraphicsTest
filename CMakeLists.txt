cmake_minimum_required(VERSION 3.16)

project(GraphicsTest)

function(copy_dll_to_install target dst)
	set(SRC $<TARGET_FILE_DIR:${target}>/${target}.dll)
	set(DST ${CMAKE_SOURCE_DIR}/${dst}.dll)
	add_custom_command(TARGET ${target} POST_BUILD VERBATIM
			COMMAND ${CMAKE_COMMAND} -E echo "Copying ${target} output file \"${SRC}\" to \"${DST}\""
			COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST})
endfunction()

function(copy_exe_to_install target dst)
	set(SRC $<TARGET_FILE_DIR:${target}>/${target}.exe)
	set(DST ${CMAKE_SOURCE_DIR}/${dst}.exe)
	add_custom_command(TARGET ${target} POST_BUILD VERBATIM
			COMMAND ${CMAKE_COMMAND} -E echo "Copying ${target} output file \"${SRC}\" to \"${DST}\""
			COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST})
endfunction()

add_executable(GraphicsTest 
        res.rc
        src/Main.cpp
		src/glad.c
		src/Renderer/Renderer.cpp
		src/World.cpp
)

copy_exe_to_install(GraphicsTest GraphicsTest)

include_directories(
    ${CMAKE_SOURCE_DIR}/../SDL3-3.2.26/include
	${CMAKE_SOURCE_DIR}/src/Renderer
	${CMAKE_SOURCE_DIR}/src/Math
)

target_link_libraries(GraphicsTest
                    ${CMAKE_SOURCE_DIR}/../SDL3-3.2.26/libSDL_uclibc.a
                    ${CMAKE_SOURCE_DIR}/../SDL3-3.2.26/libSDL3.dll.a
                    ${CMAKE_SOURCE_DIR}/../SDL3-3.2.26/libSDL3_test.a
                    opengl32
					d3d9)