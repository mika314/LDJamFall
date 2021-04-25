all: FORCE Source/Fall/level1e_mid.h Source/Fall/level1n_mid.h Source/Fall/level1h_mid.h
	../sync/linwin.sh
	ssh win "TEMP=C:/Users/teant/AppData/Local/Temp E:/UE_4.26/Engine/Build/BatchFiles/Build.bat FallEditor Win64 Development -Project=E:/prj/Fall/Fall.uproject -WaitMutex -FromMsBuild 2>&1" | ../fixpath/fixpath
	../sync/winlin.sh
	play /usr/share/sounds/sound-icons/percussion-12.wav 2> /dev/null

Source/Fall/level1e_mid.h: Assets/midi/level1e.mid
	xxd -i Assets/midi/level1e.mid > Source/Fall/level1e_mid.h
Source/Fall/level1n_mid.h: Assets/midi/level1n.mid
	xxd -i Assets/midi/level1n.mid > Source/Fall/level1n_mid.h
Source/Fall/level1h_mid.h: Assets/midi/level1h.mid
	xxd -i Assets/midi/level1h.mid > Source/Fall/level1h_mid.h

winlin: FORCE
	../sync/winlin.sh
FORCE:
