
rd gamedata
md gamedata

robocopy "G:\Program Files (x86)\Steam\steamapps\common\Quake 3 Arena\baseq3" .\gamedata\baseq3 *.*
robocopy "G:\Program Files (x86)\Steam\steamapps\common\Quake 3 Arena\missionpack" .\gamedata\missionpack *.*

copy "G:\Program Files (x86)\Steam\steamapps\common\Quake 3 Arena\Team Arena.bat" .\gamedata\
