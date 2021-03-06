<img src="SlicerAstroAppIcon.png" width="256">


Introduction
------------
SlicerAstroApp is an Astronomy (HI) customization of 3DSlicer with the SlicerAstro [extension](https://github.com/Punzo/SlicerAstro).

Prerequisites
-------------
### Linux
install build prerequisities (tested on Ubuntu 20.04, gcc 9.3.0):
1. ```sudo apt install chrpath git-core make gcc g++ libxt-dev libgl1-mesa-dev libglu1-mesa-dev libfontconfig-dev libxrender-dev libncurses5-dev libosmesa6-dev bison build-essential gperf libasound2-dev libatkmm-1.6-dev libbz2-dev libcap-dev libcups2-dev libdrm-dev libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev libgcrypt20-dev libglib2.0-0 libglib2.0-dev libglu1-mesa-dev libgstreamer1.0-dev libice6 libicu-dev libnss3-dev libpci-dev libpulse-dev libsm6 libxcb-sync0-dev libssl-dev libudev-dev libx11-dev libx11-xcb-dev libxcb-composite0 libxcb-composite0-dev libxcb-cursor-dev libxcb-cursor0 libxcb-damage0 libxcb-damage0-dev libxcb-dpms0 libxcb-dpms0-dev libxcb-dri2-0 libxcb-dri2-0-dev libxcb-dri3-0 libxcb-dri3-dev libxcb-ewmh-dev libxcb-ewmh2 libxcb-glx0 libxcb-glx0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-image0 libxcb-image0-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-present-dev libxcb-present0 libxcb-randr0 libxcb-randr0-dev libxcb-record0 libxcb-record0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-render0 libxcb-render0-dev libxcb-res0 libxcb-res0-dev libxcb-screensaver0 libxcb-screensaver0-dev libxcb-shape0 libxcb-shape0-dev libxcb-shm0 libxcb-shm0-dev libxcb-sync-dev libxcb-sync-dev libxcb-sync1 libxcb-util-dev libxcb-util0-dev libxcb-util1 libxcb-xf86dri0 libxcb-xf86dri0-dev libxcb-xfixes0 libxcb-xfixes0-dev libxcb-xinerama0 libxcb-xinerama0-dev libxcb-xkb-dev libxcb-xkb1 libxcb-xtest0 libxcb-xtest0-dev libxcb-xv0 libxcb-xv0-dev libxcb-xvmc0 libxcb-xvmc0-dev libxcb1 libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxrandr-dev libxslt1-dev libxss-dev libxtst-dev libpthread-stubs0-dev libpthread-workqueue0 libpthread-workqueue-dev perl python ruby gyp ninja-build libwebp-dev libjsoncpp-dev libopus-dev libminizip-dev libavutil-dev libavformat-dev libavcodec-dev libevent-dev libwayland-dev libwayland-egl1-mesa libwayland-server0 libgles2-mesa-dev libxkbcommon-dev libsrtp2-dev``` NOTE: the majority of these prerequisities were needed to compile Qt from source, however now we can download it with the online installer. Anyway installing them, would not bring any issue.  
1. cmake minimum version has to be 3.17.3. If your system one is older, please download it from https://cmake.org/download/ and check [update-cmake](https://github.com/plampite/ibpark/blob/master/DeveloperGuide.md#update-cmake).
1. download the qt (version 5.15.1) online [installer](https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run) and install the following: Desktop gcc 64-bit, Sources, Qt WebEngine, Qt Script, Qt Debug Information Files and Qt Creator (this last it is installed in default).

### MacOS (tested on MacOS 10.13)
1. cmake minimum version has to be 3.17.3. If your system one is older, please download it from https://cmake.org/download/ and check [update-cmake](https://github.com/plampite/ibpark/blob/master/DeveloperGuide.md#update-cmake).
1. install qt (version 5.15.1) using the special package [qt-easy-build](https://github.com/jcfr/qt-easy-build/tree/5.15.1). 
1. Install Xcode: ```xcode-select --install ```

### Windows
Currently SlicerAstro extension does not compile/work under Windows (because of specific libraries deps, e.g. wcslib).

### Additional Info 
[Slicer Prerequisites]

Checkout
--------
* Create a Github account
* Create SSH keys associated to your account: [SSH Key Generation Instructions].
* Add the SSH key to your Github account: [Steps to add SSH Key to Github].
* Clone the repository and follow platform specific instructions below:

        $ git clone https://github.com/Punzo/SlicerAstroApp.git 

Build
-----

Make sure that you can compile Slicer OR have the Prerequisites for Slicer: [Slicer Build Instructions].

### Unix-like

1. Configure CMake

```bat
mkdir SlicerAstroApp-build
cd SlicerAstroApp-build
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DQt5_DIR=path-to-Qt/lib/cmake/Qt5 ../SlicerAstroApp
```
for setting the VTK version add: ```-DSlicer_VTK_VERSION_MAJOR=9``` (Note: at the moment vtk9 is not officially supported by 3DSlicer yet, default is vtk8)

N.B. * ___MacOSX:___*  
add ```-DCMAKE_OSX_DEPLOYMENT_TARGET=10.xx``` (e.g.: 10.14 for Mojave) to the cmake command

after cmake (temporary fix to avoid errors from inability to package astropy): 

```bat
cd slicersources-build/python-slicerastro-requirements-prefix/src/python-slicerastro-requirements-stamp 
cp python-slicerastro-requirements-install-Release.cmake python-slicerastro-requirements-install
```

2. Build

```bat
make -j 8
```

3. SlicerAstroApp executable lives in `path/to/SlicerAstroApp-build/Slicer-build/`

Make the Package 
----------------

### Unix-like

```bat
cd SlicerAstroApp-build/Slicer-build
make package
```


Resources
---------
* [3D Slicer Developer Wiki](http://wiki.slicer.org/slicerWiki/index.php/Documentation/Nightly/Developers)


[Slicer Prerequisites]: https://www.slicer.org/wiki/Documentation/Nightly/Developers/Build_Instructions#PREREQUISITES
[Slicer Build Instructions]: https://www.slicer.org/slicerWiki/index.php/Documentation/Nightly/Developers/Build_Instructions
[SSH Key Generation Instructions]: https://gitlab.kitware.com/help/ssh/README
[Steps to add SSH Key to Github]: https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/
[Slicer Windows Dev Environment]: https://www.slicer.org/wiki/Documentation/Nightly/Developers/Build_Instructions#Windows

