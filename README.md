# 3D Viewer

<div align="center"><img src="assets/screencast.gif"></div>

## Table of contents
* [General info](https://github.com/finchren/s21_3DViewer/tree/develop#general-info)
* [Goal & requirements](https://github.com/finchren/s21_3DViewer/tree/develop#goal--requirements)
* [Bonus features](https://github.com/finchren/s21_3DViewer/tree/develop#goal--bonus-features)
* [Key learnings](https://github.com/finchren/s21_3DViewer/tree/develop#key-learnings)
* [Build](https://github.com/finchren/s21_3DViewer/tree/build)

## General info 

This project is a 3D wireframe model visualization program, developed using C11 standard with the gcc compiler and Qt libraries. The program allows users to load 3D models from obj files, apply affine transformations, and visualize the results in a user-friendly graphical interface.

## Goal & requirements

- Developed in C11 standard using gcc compiler and any additional Qt libraries and modules.
- Code located in the src folder.
- Built with a Makefile containing standard set of targets for GNU-programs (all, install, uninstall, clean, dvi, dist, tests, gcov).
- Developed according to the principles of structured programming, following the Google style.
- Full coverage of modules related to model loading and affine transformations with unit-tests.
- GUI implementation based on any GUI library with API for C89/C99/C11 (e.g., GTK+, Nuklear, raygui, microui, libagar, libui, IUP, LCUI, CEF, Qt, etc.).
- Program functionality includes model translation, rotation, scaling, and loading.
- Graphical user interface contains necessary buttons, input fields, and information about the uploaded model.
- Program processes and allows viewing models with details up to 1,000,000 vertices without freezing.

## Bonus features
- Customizable projection types (parallel and central).
- Edge and vertex display customization, including type, color, thickness, and size.
- Background color customization.
- Settings saved between program restarts.
- Saving captured screenshot.
- Recording screencasts as a gif animations (640x480, 10fps, 5s).
For screencast imagemagick tool should be installed on the target machine:
```
$ sudo apt install imagemagick
```

## Key learnings
- Mastery of the C11 standard and gcc compiler.
- Working with Qt libraries and modules.
- Implementing a GUI using a compatible library.
- Efficient handling of large 3D models.
- Implementing affine transformations in a 3D space.
- Integration of unit-tests and coverage modules.
- Customization of program settings.
- Saving and recording visual output in various formats.
- Composing documentaiton for the project.

## Build
General make target:
```
$ make
```
Clean the data from all of the targets:
```
$ make clean
```
Install the appllication to the target directory (*project_root_dir/install_directory/*)
```
$ make install
```
Uninstall the application:
```
$ make uninstall
```
Create a distribution file for the application:
```
$ make dist
```
Gcov report:
```
$ make gcov
```
Google style check:
```
$ make style
```
Execute tests:
```
$ make tests
```
Compose the documentation and open it:
```
$ make dvi
```
## Shortcuts:
- **Q** - Quit
- **Load model** - Ctrl + O
- **P** - Printscreen
- **R** - Record screencast
- **NUM 4** - Move model to the left
- **NUM 6** - Move model to the right
- **NUM 8** - Move model up
- **NUM 2** - Move model down
- **-** - Scale model down
- **+** - Scale model up
- **Ctrl + NUM 4** - Rotate model to the left
- **Ctrl + NUM 6** - Rotate model to the right
- **Ctrl + NUM 8** - Rotate model up
- **Ctrl + NUM 2** - Rotate model down
- **Ctrl + NUM 1** - Rotate model clockwise
- **Ctrl + NUM 9** - Rotate model counter-clockwise
