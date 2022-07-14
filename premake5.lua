workspace "akira"
  architecture "x86"
  startproject "akira"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

  outputdir = "%{cfg.buildcfg}"

  IncludeDir = {}
  IncludeDir["minhook"] = "dependencies/minhook"
  
  CppVersion = "C++20"
  MsvcToolset = "v143"
  WindowsSdkVersion = "10.0"
  
  function DeclareMSVCOptions()
    filter "system:windows"
    staticruntime "Off"
    systemversion (WindowsSdkVersion)
    toolset (MsvcToolset)
    cppdialect (CppVersion)

    defines
    {
      "_CRT_SECURE_NO_WARNINGS",
      "NOMINMAX",
      "WIN32_LEAN_AND_MEAN",
      "_WIN32_WINNT=0x601" -- Support Windows 7
    }
    
    disablewarnings
    {
      "4100", -- C4100: unreferenced formal parameter
      "4201", -- C4201: nameless struct/union
      "4307", -- C4307: integral constant overflow
	    "4311", -- C4311: 'variable' : pointer truncation from 'type' to 'type'
      "4302", -- C4302: 'conversion' : truncation from 'type 1' to 'type 2'
	    "4267", -- C4267: 'var' : conversion from 'size_t' to 'type', possible loss of data
	    "4244"  -- C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
    }
  end
   
  function DeclareDebugOptions()
    filter "configurations:Debug"
      defines { "_DEBUG" }
      symbols "On"
    filter "not configurations:Debug"
      defines { "NDEBUG" }
  end
	
  project "minhook"
    location "dependencies/%{prj.minhook}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/lib/" .. outputdir)
    objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")
	
    files
    {
	    "dependencies/%{prj.name}/include/**.h",
      "dependencies/%{prj.name}/src/**.c",
    }
	
    includedirs
    {
      "dependencies/%{prj.name}/",
	    "dependencies/%{prj.name}/include/",
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()
	
  project "akira"
    location "akira"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir)
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
	
    files
    {
      "src/**.h",
      "src/**.cpp",
    }

    includedirs
    {
	    "%{IncludeDir.minhook}",
      "src"
    }

    libdirs
    {
      "bin/lib"
    }

    links
    {
	    "minhook",
    }

    DeclareMSVCOptions()
    DeclareDebugOptions()

    flags { "NoImportLib", "Maps", "MultiProcessorCompile" }

    filter "configurations:Debug"
      defines { "akira_DEBUG" }

    filter "configurations:Release"
      defines { "akira_RELEASE" }
      optimize "speed"
	  
    filter "configurations:Dist"
      flags { "LinkTimeOptimization", "FatalCompileWarnings" }
      defines { "akira_DIST" }
      optimize "speed"