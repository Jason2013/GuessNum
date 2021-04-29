cmake_minimum_required(VERSION 3.15)
project(GuessNum)

set(PRE_HEADER_FILES
    StdAfx.cpp
)

set(HEADER_FILES
    GuessNum.h
    StdAfx.h
    number.h
    resource.h
)

set(SOURCE_FILES
    GuessNum.cpp
    number.cpp
)

set(RESOURCE_FILES
    GuessNum.ico
    small.ico
)

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/$(IntDir)/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

add_msvc_precompiled_header(StdAfx.h StdAfx.cpp SOURCE_FILES)

source_group("Resource Files" FILES ${RESOURCE_FILES})

add_executable(GuessNum
    ${HEADER_FILES}
    ${PRE_HEADER_FILES}
    ${RESOURCE_FILES}
    ${SOURCE_FILES}
    GuessNum.rc
)

target_compile_definitions(GuessNum PRIVATE
    UNICODE
    _UNICODE
)

target_link_options(GuessNum PRIVATE
    "/SUBSYSTEM:WINDOWS"
)

target_link_libraries(GuessNum Winmm.lib)
