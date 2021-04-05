project(wl27)

add_library(wl27 SHARED)

target_sources(wl27 PUBLIC
    dep.cpp
    dep.h
    functions.cpp
    functions.h
    nodefaultlib.cpp
    nodefaultlib.h
    patches.h
    pstdint.h
    resource.h
    w3lh.cpp
    w3lh.h)

if(MSVC)

    target_compile_definitions(wl27 PRIVATE 
        -DWIN32
        -D_WINDOWS
        -D_USRDLL
        -DDLL_EXPORTS
        -DUNICODE
        -D_UNICODE)

        target_link_options(w3lh PRIVATE
        "/MANIFEST"
        "/LTCG:incremental"
        "/NXCOMPAT:NO"
        "/DYNAMICBASE:NO" 
        "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\""
        "/SUBSYSTEM:WINDOWS" 
        "/MACHINE:X86" 
        "/SAFESEH"
        "/ERRORREPORT:PROMPT"
        "/NOLOGO"
        "/INCREMENTAL:NO"
        #"/NODEFAULTLIB"
        "/TLBID:1"
        "/OPT:ICF"
        "/DLL")
        #"/BASE:\"0x76290000\"")

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
        odbccp32.lib)

endif()    