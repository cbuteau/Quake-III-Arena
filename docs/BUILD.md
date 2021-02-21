
# Build

After cloning this repository you need to get it building.

## Install WIndows Terminal

Trust me having multiple consoles on the same directory is a plus.

Add entry so you you have acces to the visual studio tools.

https://medium.com/@calloncampbell/adding-the-visual-studio-developer-command-prompt-to-windows-terminal-ba8d966b6019

```json
{
  "acrylicOpacity": 0.75,
  "closeOnExit": true,
  "colorScheme": "Campbell",
  "commandline": "cmd.exe /k \"C://Program Files (x86)//Microsoft Visual Studio//2019//Enterprise//Common7//Tools//VsDevCmd.bat\"",
  "cursorColor": "#FFFFFF",
  "cursorShape": "bar",
  "fontFace": "Consolas",
  "fontSize": 10,
  "guid": "{26b30263-74e9-4146-b80e-11632e86d42c}",
  "historySize": 9001,
  "icon": "ms-appdata:///roaming/vs2019-32.png",
  "name": "Developer Command Prompt for VS2019",
  "padding": "0, 0, 0, 0",
  "snapOnInput": true,
  "startingDirectory": "%USERPROFILE%",
  "useAcrylic": true
},
```

this one is better still not working.
https://stackoverflow.com/questions/57925428/add-developer-command-prompt-for-visual-studio-to-windows-terminal

```json
The answer from Wallace Kelly is great, but the settings below may be a useful copy/paste for others who want Visual Studio icons, both x86 and x64 and a less DOS-like font.

As with Wallace's answer, adjust "2019" and "Professional", e.g. for 2017/Community, as needed.

enter image description here

{
  "guid": "{9a3a9308-d6f8-4b1d-896c-a27c59c28be3}",
  "name": "VS2019 x86",
  "commandline": "cmd.exe /k cd c:/dev/mc-hardware-svc/out/vs-x86-Debug && \"C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Auxiliary/Build/vcvars32.bat\"",
  "fontFace": "Consolas",
  "fontSize": 10,
  "icon" : "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/Common7/IDE/Assets/VisualStudio.70x70.contrast-black_scale-80.png",
  "hidden": false
},
{
  "guid": "{ceec68f2-0ef7-48f0-84db-4693612532cd}",
  "name": "VS2019 x64",
  "commandline": "cmd.exe /k \"C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Auxiliary/Build/vcvars64.bat\"",
  "icon" : "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/Common7/IDE/Assets/VisualStudio.70x70.contrast-black_scale-80.png",
  "hidden": false
},
```
