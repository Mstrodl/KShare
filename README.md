# Mary's kshare patches

* Building on modern ffmpeg
* Wayland support for screenshotting
* Wayland support for global hotkeys

These are all pretty low-effort changes.

This fork contains GPL-licensed components from
[flameshot](https://github.com/flameshot-org/flameshot),
mostly in and around the wayland screenshotting stuff.
You should probably use it instead, but for some reason I'm really stuborn.

# KShare
A [ShareX](https://getsharex.com/) inspired cross platform utility written with Qt.

|Linux|Windows|
|:---:|:-----:|
|[![Build Status](https://nativeci.arsenarsen.com/job/KShare%20(dev)/badge/icon)](https://nativeci.arsenarsen.com/job/KShare%20(dev))|[![Build status](https://ci.appveyor.com/api/projects/status/7wa4f0bl6u62lo6v?svg=true)](https://ci.appveyor.com/project/ArsenArsen/kshare)|
## Screenshot
Made with KShare itself, of course :)
![](http://i.imgur.com/ffWvCun.png)

## Usage
See the [wiki](https://github.com/ArsenArsen/KShare/wiki).
Please note that KShare is not compatiable with Wayland due to some permission issues. Please use X.Org instead.

## Dependencies
* Qt 5 Widgets
* Qt 5 GUI
* Qt 5 Network
* Qt 5 X11Extras | Winextras
* [QHotkey](https://github.com/Skycoder42/QHotkey)
* libavformat
* libavcodec
* libavutil
* libswscale

Additionally, on Linux, you require:
* XCB
* XCB xfixes
* XCB cursor

Despite the name implying so, this project does not depend on the KDE API at all.

## Install
|Distro|Link|
|:----:|:--:|
|Arch Linux (development)|[kshare-git](https://aur.archlinux.org/packages/kshare-git/)|
|Ubuntu/Debian (development)|[.deb](https://nativeci.arsenarsen.com/job/KShare%20\(dev\)/main=linux/lastSuccessfulBuild/artifact/packages/simpleName.deb)|
|Arch Linux |[kshare](https://aur.archlinux.org/packages/kshare/)|
|Ubuntu/Debian |[.deb](https://nativeci.arsenarsen.com/job/KShare%20\(master\)/main=linux/lastSuccessfulBuild/artifact/packages/simpleName.deb)|

For other UNIX-like platforms, and MSYS2 (for Windows):

You have to obtain the dependencies though.
```bash
git clone --recursive https://github.com/ArsenArsen/KShare.git
cd KShare
qmake # Might be qmake-qt5 on your system
make
```

On systems with FFMpeg pre-3.1 you need to apply `OlderSystemFix.patch` to `src/recording/encoders/encoder.cpp`.
On systems with Qt pre-5.7 you need to install the Qt version from their website.
You can attempt to `curl https://raw.githubusercontent.com/ArsenArsen/KShare/master/install.sh | bash`

You can find more details [here](https://blog.arsenarsen.com/posts/compiling-kshare-on-linux-mac-os-x-and-windows-final-revision)

## Support (and contact)
There's a few ways to get support, you can:
* join `#kshare` on [Freenode](https://webchat.freenode.net/?channels=kshare)
* open an issue

If someone can answer, they probably will.

###### Started on 19th of April 2017 to bring some attention and improvement to Linux screenshotting.
