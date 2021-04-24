all: FORCE Source/Fall/test_mid.h
	../sync/linwin.sh
	ssh win "TEMP=C:/Users/teant/AppData/Local/Temp E:/UE_4.26/Engine/Build/BatchFiles/Build.bat FallEditor Win64 Development -Project=E:/prj/Fall/Fall.uproject -WaitMutex -FromMsBuild 2>&1" | ../fixpath/fixpath
	../sync/winlin.sh
	play /usr/share/sounds/sound-icons/percussion-12.wav 2> /dev/null

Source/Fall/test_mid.h: Assets/midi/Test.mid
	xxd -i Assets/midi/Test.mid > Source/Fall/test_mid.h

winlin: FORCE
	../sync/winlin.sh
FORCE:
