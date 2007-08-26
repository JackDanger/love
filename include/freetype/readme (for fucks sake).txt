To install the nigger, move a copy of this folder (as well as the "ft2build.h" file in the parent folder) into
<Installation Folder>\Microsoft Visual Studio 8\VC\PlatformSDK\Include\
Then, move the ".lib" files into
<Installation Folder>\Microsoft Visual Studio 8\VC\PlatformSDK\Lib\
In Visual Studio, add "freetype2110_D.lib" (or any other lib with a "_D" in the name... experiment with which one compiles) to Debug Project Properties
Configuration Properties > Linker > Input > Additional Dependencies
And do the same to the Release Project Properties with the "freetype2110ST.lib" (or one WITHOUT the"_D") file.