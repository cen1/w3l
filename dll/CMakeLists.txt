project(w3lh)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules")
message(${CMAKE_BINARY_DIR})

add_library(w3lh SHARED)

target_sources(w3lh PUBLIC
    debug.cpp
    debug.h
    dep.cpp
    dep.h
    functions.cpp
    functions.h
    http.h
    http.cpp
    nodefaultlib.cpp
    nodefaultlib.h 
    patches.h 
    pstdint.h 
    resource.h
    safe-queue.hpp
    w3lh.cpp
    w3lh.h
    
    game/globals.h
    game/hooks.cpp
    game/offsets.h
    game/player-slot-helpers.cpp
    game/hook-handlers.cpp
    game/hooks.h
    game/player-slot-helpers.h
    game/hook-handlers.h
    game/LobbyInfo.h
    game/PlayerInfoUpdater.h
    game/structures.h

    game/PlayerInfo/DefaultPlayerInfo.h
    game/PlayerInfo/LagabuseDotaPlayerInfo.h
    game/PlayerInfo/PlayerInfo.h
    )


find_package(httplib REQUIRED)
find_package(nlohmann_json REQUIRED)

target_include_directories(w3lh PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

target_link_libraries(w3lh PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

if(MSVC)

    target_compile_definitions(w3lh PRIVATE 
        -DWIN32
        -D_WINDOWS
        -D_USRDLL
        -DW3LH_EXPORTS
        -DUNICODE
        -D_UNICODE)

    set_target_properties(w3lh PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\"")

    target_link_options(w3lh PRIVATE
        "/MANIFEST"
        "/NXCOMPAT:NO"
        "/SUBSYSTEM:WINDOWS" 
        "/MACHINE:X86" 
        "/SAFESEH:NO"
        "/ERRORREPORT:PROMPT"
        "/NOLOGO"
        "/TLBID:1" 
        "/DLL"
        "/BASE:0x76290000")

    target_link_libraries(w3lh PRIVATE 
        kernel32.lib
        user32.lib
        gdi32.lib
        winspool.lib
        comdlg32.lib
        advapi32.lib
        shell32.lib
        ole32.lib
        oleaut32.lib
        uuid.lib
        odbc32.lib
        odbccp32.lib)

    set(W3LH_DEBUG_OPTIONS /ZI /Od /W3 /Oy /Os /GS- /Gy /Gm /RTC1)
    set(W3LH_RELEASE_OPTIONS /Zi /O2 /W3 /Oy /Os /GS- /Gy)
    target_compile_options(w3lh PRIVATE "$<$<CONFIG:DEBUG>:${W3LH_DEBUG_OPTIONS}>")
    target_compile_options(w3lh PRIVATE "$<$<CONFIG:RELEASE>:${W3LH_RELEASE_OPTIONS}>")

    set(W3LH_RELEASE_L_OPTIONS 
        "/INCREMENTAL:NO"
        "/DYNAMICBASE:NO"
        "/OPT:REF"
        "/OPT:ICF")
    target_link_options(w3lh PRIVATE "$<$<CONFIG:DEBUG>:${W3LH_DEBUG_L_OPTIONS}>")
    target_link_options(w3lh PRIVATE "$<$<CONFIG:RELEASE>:${W3LH_RELEASE_L_OPTIONS}>")

    set(W3LH_RELEASE_LIB ucrt.lib)
    target_link_libraries(w3lh PRIVATE "$<$<CONFIG:RELEASE>:${W3LH_RELEASE_LIB}>")

endif()