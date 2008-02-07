!include "MUI.nsh" # Modern look, plxz

Name "LOVE"
OutFile "install.exe"
Icon "love.ico" # this doesn't seem to work

InstallDir $PROGRAMFILES\LOVE
InstallDirRegKey HKCU "Software\LOVE" ""

# Graphics
!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "top.bmp" # optional
!define MUI_WELCOMEFINISHPAGE_BITMAP "left.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "left.bmp"

# Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Languages
!insertmacro MUI_LANGUAGE "English"

# Main Program
Section "LOVE" MainProg

	SectionIn RO
	SetOutPath $INSTDIR

	# Program
	File love.exe
	# DLLs
	File DevIL.dll
	File freetype6.dll
	File ILU.dll
	File ILUT.dll
	File libogg-0.dll
	File libvorbis-0.dll
	File libvorbisfile-3.dll
	File lua5.1.dll
	File physfs.dll
	File SDL.dll
	File SDL_mixer.dll
	File smpeg.dll
	File zlib1.dll
	# Icons
	File love.ico
	File game.ico
	# Text
	File changes.txt
	File license.txt
	File readme.txt

	# Uninstaller
	WriteUninstaller $INSTDIR\Uninstall.exe

	# Start Menu
	CreateDirectory "$SMPROGRAMS\LOVE"
	CreateShortCut "$SMPROGRAMS\LOVE\LOVE.lnk" "$INSTDIR\love.exe"
	CreateShortCut "$SMPROGRAMS\LOVE\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
	WriteINIStr "$SMPROGRAMS\LOVE\Documentation.url" "InternetShortcut" "URL" "http://love.sourceforge.net/docs/"

	# Desktop
	CreateShortCut "$DESKTOP\LOVE.lnk" "$INSTDIR\love.exe" ""

	# Registry
	WriteRegStr HKCU "Software\LOVE" "" $INSTDIR
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LOVE" "DisplayName" "LOVE (remove only)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LOVE" "UninstallString" "$INSTDIR\Uninstall.exe"
	
	# love file association
	WriteRegStr HKCR ".love" "" "LOVE"
	WriteRegStr HKCR "LOVE" "" "LOVE Game File"
	WriteRegStr HKCR "LOVE\DefaultIcon" "" "$INSTDIR\game.ico"
	WriteRegStr HKCR "LOVE\shell" "" "open"
	WriteRegStr HKCR "LOVE\shell\open" "" "Open in LOVE"
	WriteRegStr HKCR "LOVE\shell\open\command" "" "$INSTDIR\love.exe $\"%1$\""
	# Refresh shell icons
	System::Call 'shell32.dll::SHChangeNotify(i, i, i, i) v  (0x08000000, 0, 0, 0)'

SectionEnd

# Demos
Section "Demos" Demos

	SetOutPath $INSTDIR\demos

	# Files
	File demos\animation.love
	File demos\chinchilla.love
	File demos\colorblend.love
	File demos\hello-love.love
	File demos\image-mouse.love
	File demos\movement.love
	File demos\passingclouds.love
	File demos\sound.love
	File demos\text-imagefont.love
	
	# Start menu
	CreateDirectory "$SMPROGRAMS\LOVE\Demos"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Animation Demo.lnk" "$INSTDIR\demos\animation.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Chinchilla.lnk" "$INSTDIR\demos\chinchilla.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Color Blend Demo.lnk" "$INSTDIR\demos\colorblend.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Hello LOVE.lnk" "$INSTDIR\demos\hello-love.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Mouse and Image Basics.lnk" "$INSTDIR\demos\image-mouse.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Movement.lnk" "$INSTDIR\demos\movement.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Passing Clouds.lnk" "$INSTDIR\demos\passingclouds.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Sound.lnk" "$INSTDIR\demos\sound.love"
	CreateShortCut "$SMPROGRAMS\LOVE\Demos\Text Demo.lnk" "$INSTDIR\demos\text-imagefont.love"

SectionEnd

# Descriptions
LangString DESC_MainProg ${LANG_ENGLISH} "Version 0.2.0"
LangString DESC_Demos ${LANG_ENGLISH} "A series of demos to show what LOVE can do."

# Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${MainProg} $(DESC_MainProg)
	!insertmacro MUI_DESCRIPTION_TEXT ${Demos} $(DESC_Demos)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

# Uninstall
Section "Uninstall"

	# Delete Demos
	Delete $INSTDIR\demos\animation.love
	Delete $INSTDIR\demos\chinchilla.love
	Delete $INSTDIR\demos\colorblend.love
	Delete $INSTDIR\demos\hello-love.love
	Delete $INSTDIR\demos\image-mouse.love
	Delete $INSTDIR\demos\movement.love
	Delete $INSTDIR\demos\passingclouds.love
	Delete $INSTDIR\demos\sound.love
	Delete $INSTDIR\demos\text-imagefont.love
	RMDir $INSTDIR\demos
	# Program
	Delete $INSTDIR\love.exe
	# DLLs
	Delete $INSTDIR\DevIL.dll
	Delete $INSTDIR\freetype6.dll
	Delete $INSTDIR\ILU.dll
	Delete $INSTDIR\ILUT.dll
	Delete $INSTDIR\libogg-0.dll
	Delete $INSTDIR\libvorbis-0.dll
	Delete $INSTDIR\libvorbisfile-3.dll
	Delete $INSTDIR\lua5.1.dll
	Delete $INSTDIR\physfs.dll
	Delete $INSTDIR\SDL.dll
	Delete $INSTDIR\SDL_mixer.dll
	Delete $INSTDIR\smpeg.dll
	Delete $INSTDIR\zlib1.dll
	# Icons
	Delete $INSTDIR\love.ico
	Delete $INSTDIR\game.ico
	# Text
	Delete $INSTDIR\changes.txt
	Delete $INSTDIR\license.txt
	Delete $INSTDIR\readme.txt
	RMDir $INSTDIR

	# Start menu
	Delete "$SMPROGRAMS\LOVE\Demos\Animation Demo.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Chinchilla.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Color Blend Demo.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Hello LOVE.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Mouse and Image Basics.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Movement.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Passing Clouds.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Sound.lnk"
	Delete "$SMPROGRAMS\LOVE\Demos\Text Demo.lnk"
	RMDir "$SMPROGRAMS\LOVE\Demos"
	Delete "$SMPROGRAMS\LOVE\LOVE.lnk"
	Delete "$SMPROGRAMS\LOVE\Uninstall.lnk"
	Delete "$SMPROGRAMS\LOVE\Documentation.url"
	RMDir "$SMPROGRAMS\LOVE"
	
	# Desktop
	Delete "$DESKTOP\LOVE.lnk"

	# Uninstall keys
	DeleteRegKey /ifempty HKCU "Software\LOVE"
	DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\LOVE"
	
	# love file association
	DeleteRegKey HKCR "LOVE"
	DeleteRegKey HKCR ".love"
	# Refresh shell icons
	System::Call 'shell32.dll::SHChangeNotify(i, i, i, i) v  (0x08000000, 0, 0, 0)'

SectionEnd