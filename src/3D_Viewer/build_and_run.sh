#!/bin/bash
rm *.o Makefile moc_*
qmake 3D_Viewer.pro
make
rm *.o Makefile moc_*
./3D_Viewer

