
-- the goal...q3 with v8 ....maybe 64 bit as well.
workspace "Q3Withv8"
    configurations { "debug", "release" }
    platforms { "x86", "x86_64" }
    location "build"

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

project "lcc"
  kind "ConsoleApp"
  language "C++"
  files { "lcc\\**.h", "lcc\\**.cpp", "lcc\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "botlib"
  kind "StaticLib"
  language "C++"
  files { "code\\botlib\\**.h", "code\\botlib\\**.cpp", "code\\botlib\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "splines"
  kind "StaticLib"
  language "C++"
  files { "code\\splines\\**.h", "code\\splines\\**.cpp" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "jpeg-6"
  kind "StaticLib"
  language "C++"
  files { "code\\jpeg-6\\**.h", "code\\jpeg-6\\**.cpp", "code\\jpeg-6\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "q3_ui"
  kind "StaticLib"
  language "C++"
  files { "code\\q3_ui\\**.h", "code\\q3_ui\\**.cpp", "code\\q3_ui\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "bspc"
  kind "StaticLib"
  language "C++"
  files { "code\\bspc\\**.h", "code\\bspc\\**.cpp", "code\\bspc\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"

project "cgame"
  kind "StaticLib"
  language "C++"
  files { "code\\cgame\\**.h", "code\\cgame\\**.cpp", "code\\cgame\\**.c" }


  filter { "configurations:debug" }
      defines { "DEBUG" }
      symbols "On"

  filter { "configurations:release" }
      defines { "NDEBUG" }
      optimize "On"
