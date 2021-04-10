project(w3l)

add_executable(w3l resource.rc)

target_sources(w3l PRIVATE 
    nodefaultlib.cpp
    nodefaultlib.h 
    peb.h 
    resource.h 
    w3l.cpp)

if(MSVC)    
    target_compile_definitions(w3l PRIVATE 
        -DUNICODE 
        -D_UNICODE 
        -DWIN32 
        -D_WINDOWS)

    set_target_properties(w3l PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
    
    target_link_options(w3l PRIVATE 
        "/INCREMENTAL:NO" 
        "/SUBSYSTEM:WINDOWS" 
        "/OPT:REF" 
        "/OPT:ICF"
        "/NODEFAULTLIB"
        "/DYNAMICBASE:NO" 
        "/NXCOMPAT:NO" 
        "/MACHINE:X86" 
        "/SAFESEH:NO"
        "/BASE:0x7E540000")
    
    target_link_libraries(w3l PRIVATE 
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

    set(W3L_DEBUG_OPTIONS /ZI /Od /W3 /Oy /Os /GS- /Gy)
    set(W3L_RELEASE_OPTIONS /Zi /O1 /W3 /Oy /Os /GS- /Gy)    
    target_compile_options(w3l PRIVATE "$<$<CONFIG:DEBUG>:${W3L_DEBUG_OPTIONS}>")
    target_compile_options(w3l PRIVATE "$<$<CONFIG:RELEASE>:${W3L_RELEASE_OPTIONS}>")

    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()