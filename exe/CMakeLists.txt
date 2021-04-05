project(w3l)

add_executable(w3l)

target_sources(w3l PRIVATE 
    nodefaultlib.cpp
    nodefaultlib.h 
    peb.h 
    resource.h 
    w3l.cpp)

if(MSVC)
    set_target_properties(w3l PROPERTIES VS_GLOBAL_ApplicationIcon "${CMAKE_CURRENT_SOURCE_DIR}/Red1_.ico")
    
    target_compile_definitions(w3l PRIVATE 
        -DUNICODE 
        -D_UNICODE 
        -DWIN32 
        -D_WINDOWS
        -DUNICODE
        -D_UNICODE)
    
    target_compile_options(w3l PRIVATE /Zi /W3 /O1 /Oy /Os /GS- /Gy)
    
    target_link_options(w3l PRIVATE 
        "/INCREMENTAL:NO" 
        #"/NODEFAULTLIB"
        "/MANIFESTUAC:\"/level='requireAdministrator' /uiAccess='false'\"" 
        "/SUBSYSTEM:WINDOWS" 
        "/OPT:REF" 
        "/OPT:ICF" 
        "/DYNAMICBASE:NO" 
        "/NXCOMPAT:NO" 
        "/MACHINE:X86" 
        "/SAFESEH:NO")
        #"/BASE:\"0x7E540000\"")
    
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
endif()