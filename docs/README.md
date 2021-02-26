
# Goals

+ [x] Convert To latest Visual Studio
+ [ ] Get Compiling and working.
+ [ ] Migrate to build system (premake).
+ [ ] Get build happening on circleci.
+ [ ] Document how code works.
+ [ ] Integrate v8 engine.
+ [ ] first experiment with porting bots to JS modules.
+ [ ] Make mod system for javascript mods.
+ [ ] (Maybe) Get to compile on other platforms.

# Links

+ [explorer++ post](https://explorerplusplus.com/blog/2019/03/07/embedding-v8-c++-application)
+ [Google's V8 Instructions](https://v8.dev/docs/build)

# Notes

+ The Visual Studio build requires the env var **V8CODE_ROOT** be set to point at the root directory of the of the V8 content.  e.g. it will look for directories like **%V8CODE_ROOT%\v8\include**

+ Start Quake3 Debug build using the command line parameters **+set sv_pure 0** so it skips the bytecode content.  Reading this causes a crash.  Currently the Quake3 Release build will still crash as if it ignores the request.
+ I copied my game data into **code\baseq3**
+ The **Startup Project** should be the **quake3** one.  If not, right-click on it and choose **Set as Startup Project**
+ If everything is working, the **qpew** function in **code\vs\weapon_Bullet_Fire_qpew.js** will run every time you fire the starting weapon.  It is loading, compiling and running with each bullet, so that's why it's noticeably slow.  That can be fixed later.  All you can change is health right now.  It was an experiment.

# V8 build

+ Start by installing google's **depot_tools** from the instructions [on the Chromium site](https://chromium.googlesource.com/chromium/src/+/master/docs/windows_build_instructions.md#install)
+ Pull down a copy of the source by following the instructions at the [v8.dev site](https://v8.dev/docs/source-code#instructions) rather than using git directly.  Note that you can use git on the source once it is downloaded.
+ Make sure you are in the **v8** subdirectory
+ We want version **8.8** so do `git checkout -b 8.8 -t branch-heads/8.8` to setup a branch
+ To do a Win32 debug build
 + Carve out boilerplate for the target by using `python tools/dev/v8gen.py ia32.debug`
 + We want to edit the build instructions so do `gn args out.gn/ia32.debug` This will pop up a notepad with the **out.gn\ia32.debug\args.gn** file in it.  Fix it to look like:
 ```
is_debug = true
target_cpu = "x86"
v8_enable_backtrace = true
v8_enable_slow_dchecks = true
v8_optimized_debug = false
is_component_build = false
v8_static_library = true
is_clang = false
use_custom_libcxx = false
v8_monolithic = true
v8_use_external_startup_data = false
treat_warnings_as_errors = false
 ```
 + Run the build `ninja -k 10 -C out.gn/ia32.debug` The **-k** switch is to skip up to 10 build errors.
 + Wait an hour or so
 + The important artifact is:
```
v8\out.gn\ia32.debug\obj\v8_monotlith.lib
```

+ To do a Win32 release build it is pretty much the same ...
 + `python tools/dev/v8gen.py ia32.release`
 + `gn args out.gn/ia32.release`
```
is_debug = false
target_cpu = "x86"
v8_enable_backtrace = true
v8_enable_slow_dchecks = true
v8_optimized_debug = false
is_component_build = false
v8_static_library = true
is_clang = false
use_custom_libcxx = false
v8_monolithic = true
v8_use_external_startup_data = false
treat_warnings_as_errors = false
```
 +`ninja -k 10 -C out.gn/ia32.release`
 + The important artifact is:
```
v8\out.gn\ia32.release\obj\v8_monotlith.lib
```
