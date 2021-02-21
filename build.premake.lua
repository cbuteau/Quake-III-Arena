
-- the goal...q3 with v8 ....maybe 64 bit as well.
workspace "Q3Withv8"
    configurations { "debug", "release" }

project "q3asm"
    kind "ConsoleApp"
    language "C++"
    files { "q3asm\\**.h", "q3asm\\**.cpp" }

    filter { "configurations:debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:release" }
        defines { "NDEBUG" }
        optimize "On"
