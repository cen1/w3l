project(wl27)

add_library(wl27 SHARED)

target_sources(wl27 PUBLIC
    dep.c
    dep.h
    functions.c
    functions.h
    nodefaultlib.c
    nodefaultlib.h
    patches.h
    pstdint.h
    resource.h
    w3lh.c
    w3lh.h
)

set_source_files_properties(dep.c PROPERTIES COMPILE_OPTIONS "/TP")

if(MSVC)

    target_compile_definitions(wl27 PRIVATE 
        -DWIN32
        -D_WINDOWS;
        -D_USRDLL
        -DDLL_EXPORTS
        -D_UNICODE
        -DUNICODE
        -D_WINDLL
        -D_USING_V110_SDK71_
        "$<$<CONFIG:DEBUG>:DEBUG>"
    )

    set_target_properties(wl27 PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\" /SUBSYSTEM:WINDOWS\",5.01\"")

    target_link_options(wl27 PRIVATE
        "/MANIFEST"
        "/LTCG:incremental"
        "/NXCOMPAT:NO"
        "/NODEFAULTLIB"
        "/DYNAMICBASE:NO" 
        "/MACHINE:X86" 
        "/SAFESEH"
        "/ERRORREPORT:PROMPT"
        "/NOLOGO"
        "/INCREMENTAL:NO"
        "/TLBID:1"
        "/DLL"
        "/OPT:ICF"
        "/OPT:REF"
        "/BASE:0x76290000"
    )

    target_link_libraries(wl27 PRIVATE 
        Shlwapi.lib
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
        odbccp32.lib
    )

    set(WL27_DEBUG_OPTIONS /GS- /TC /GL /analyze- /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise 
                           /errorReport:prompt /WX- /Zc:forScope /Gd /Oy- /Oi /MT /nologo)
    set(WL27_RELEASE_OPTIONS /Zi /O2 /W3 /Oy /Os /GS- /Gy)
    target_compile_options(wl27 PRIVATE "$<$<CONFIG:DEBUG>:${WL27_DEBUG_OPTIONS}>")
    target_compile_options(wl27 PRIVATE "$<$<CONFIG:RELEASE>:${WL27_RELEASE_OPTIONS}>")

    set(WL27_RELEASE_L_OPTIONS 
        "/INCREMENTAL:NO"
        "/DYNAMICBASE:NO"
        "/OPT:REF"
        "/OPT:ICF"
    )
    target_link_options(wl27 PRIVATE "$<$<CONFIG:RELEASE>:${WL27_RELEASE_L_OPTIONS}>")

    set(WL27_RELEASE_LIB ucrt.lib)
    target_link_libraries(wl27 PRIVATE "$<$<CONFIG:RELEASE>:${WL27_RELEASE_LIB}>")    

    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif()    