<img src="SlicerAstroAppIcon.png" width="256">


Introduction
------------
SlicerAstro is an Astronomy (HI) customization of 3DSlicer with the SlicerAstro [extension](https://github.com/Punzo/SlicerAstro).

Prerequisites
-------------
* [Slicer Prerequisites]

Checkout
--------
* Create a Github account
* Create SSH keys associated to your account: [SSH Key Generation Instructions].
* Add the SSH key to your Github account: [Steps to add SSH Key to Github].
* Clone the repository and follow platform specific instructions below:

        $ git clone git@github.com:Punzo/SlicerAstroApp

Build
-----

Make sure that you can compile Slicer OR have the Prerequisites for Slicer: [Slicer Build Instructions].

### Unix-like

Tested Development environment: ubuntu 20.04, cmake 3.17.3, Qt 5.15.0, c++ 9.3.0.

1. Configure CMake

```bat
mkdir SlicerAstroApp-build
cd SlicerAstroApp-build
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DQt5_DIR=path/qt/lib/cmake/Qt5 ../SlicerAstroApp
```
* ___MacOSX:___ Set variable CMAKE_OSX_DEPLOYMENT_TARGET
    
2. Build

```bat
make -j 8
```

3. SlicerAstroApp executable lives in `path/to/SlicerAstroApp-build/Slicer-build/`

Package
-------

### Unix-like

```bat
cd SlicerAstroApp-build
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

