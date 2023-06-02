workspace "rainbow-lines"  
    configurations { "Debug", "Release" }

project "app"  
    kind "ConsoleApp"   
    language "C++"   

targetdir "bin/%{cfg.buildcfg}" 
files { "include/**.h", "include/**.hpp", "src/**.cpp", "src/**.c" }
includedirs {"include"}
links { "glfw" }

filter "system:Windows"
    defines {"ROC_WINDOWS"}

filter "system:Linux"
    defines {"ROC_NIX"}

filter "configurations:Debug"
    defines { "ROC_DEBUG" }  
    symbols "On" 

filter "configurations:Release" 
    optimize "On" 