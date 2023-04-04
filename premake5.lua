workspace "2DRenderer"
	configurations { "Debug", "Release" }
	platforms { "x64" }

project "Boulder"
	location "Boulder"
	language "C++"
	kind "ConsoleApp"

	targetdir ("target")
	objdir ("obj")

	files 
	{ 
		"Boulder/res/**.h", 
		"Boulder/res/**.hpp",
		"Boulder/res/**.cpp",
		"Boulder/src/**.h", 
		"Boulder/src/**.hpp",
		"Boulder/src/**.cpp",
		"Boulder/Boulder.cpp"
	}
	
	libdirs
	{
		"Boulder/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2015/",
		"Boulder/Dependencies/GLEW/lib/Release/x64/"
	}

	links
	{
		"glfw3",
		"glew32s",
		"opengl32.lib"
	}

	defines
	{
		"GLEW_STATIC",
		"_MBCS"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"
	
	filter "platforms:Shared64"
		kind "SharedLib"
		architecture "x64"