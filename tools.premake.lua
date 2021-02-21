
workspace "Q3Tools"
    configurations { "debug", "release" }
    platforms { "x86", "x86_64" }
    location "tools"

project "q3map"
    kind "ConsoleApp"
    language "C++"
    files { "q3map\\**.h", "q3map\\**.cpp", "q3map\\**.c" }

    filter { "configurations:debug" }
        defines { "DEBUG", "_DEBUG", "WIN32" }
        symbols "On"

    filter { "configurations:release" }
        defines { "NDEBUG" }
        optimize "On"


project "q3radiant"
    kind "ConsoleApp"
    language "C++"
    files { "q3radiant\\**.h", "q3radiant\\**.cpp" }

    filter { "configurations:debug" }
        defines { "DEBUG", "_DEBUG", "WIN32" }
        symbols "On"

    filter { "configurations:release" }
        defines { "NDEBUG" }
        optimize "On"
