# Use Google Chrome to render your Website as an application
I was again on the trip of researching for cross-platform desktop WebViews to render my project, ViStriker, as a desktop application, on a standalone process that I could distribute and users could run.

I noticed Google Chrome has three interesting parameters:
```
--app=URL               # Renders your website as an application.
--force-app-mode        # Disables address bar.
--hide-scrollbars       # Disables additional UI bars.
```

So I made this repository that contains necessary code to run Chrome in app mode for any website, reliably, in both Windows and Linux systems that is lightweight, standalone and can be built in exe/out executables.

## Why Chrome? It might be not installed in all machines.
When you need a WebView, you have some solutions: Electron, Python WebViews, JavaFX WebView component, etc...

In first example, Electron produces a huge exe program, not standalone, that weights over 100 MB even for a 'Hello World' (But it renders perfectly as it bundles Chromium).

Python WebViews are a lightweight solution but some applications made with complex frameworks, like Angular 4 w/TypeScript with Material Design Lite (Angular Material) are not supported enough (There is need to fix CSS and other problems).

JavaFX WebView component is another lightweight solution, but it relies on JVM; not every user has a JVM installed.

It's more likely that those users have Google Chrome installed. This projects relies exactly on it; if you don't have Google Chrome installed, it doesn't run because it can't find chrome process.

I'm eventually considering to extend this project to run alternative browsers in case Chrome is not present. In case, contributes with a PR are highly appreciated.

## Why not bundle then Chromium with your application?
Chromium weights 60MB+. This is an alternative. I made an executable by compiling this project and it weights 104 KB. It's 590 times smaller.

If people have Chrome installed, that's very easy and fast to distribute a web application as a desktop app like this.

## Run examples
The entire application aim is to dynamically create a `.bat` or `.sh` shell file, depending on your platform, run it (So it launches Chrome in app mode) and destroy shell files generated in runtime.

In `app.c` there is the whole shell code logic.

In repository there are two shell scripts:
- `chrome_windows.bat` is a BAT example, with comments, about how Chrome is launched in Windows. To identify where Chrome is installed reliably, BAT reads its associated path key from the registry and uses it to launch Chrome;
- `chrome_linux.sh` is a SH example about how Chrome is launched in Linux (It's deadly simple).

Those are ONLY examples. All code logic is ONLY in `app.c`, therefore you have to change `app.c` if you want to change generated scripts behaviors.

Launch from cmd/powershell, on Windows:
```
chrome_windows.bat
```

Launch from bash shell, on Linux:
```
./chrome_linux.sh
```
or
```
bash ./chrome_linux.sh
```

## Configure the app
In `app.c`, simply change the URLs to the one you wish to link your application to.

## Linux: compile and launch app for Linux systems
gcc should be automatically installed on most Linux distributions.
```
gcc -o launcher.out launcher.c.
./launcher.out
```

## Linux: compile for Windows systems
You need to install MinGW to properly compile for x32 and x64 architectures.
```
sudo apt-get install mingw-w64
```

Compile for x32 windows:
```
i686-w64-mingw32-gcc -o launcher_32bit.exe app.c
```

Compile for x64 windows:
```
x86_64-w64-mingw32-gcc -o launcher_64bit.exe app.c
```

Compilation generates a .exe file that you can launch on any Windows system.