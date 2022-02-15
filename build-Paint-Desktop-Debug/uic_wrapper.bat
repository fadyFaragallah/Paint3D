@echo off
SetLocal EnableDelayedExpansion
(set PATH=E:\work\Qt5_build\qtbase\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=E:\work\Qt5_build\qtbase\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=E:\work\Qt5_build\qtbase\plugins
)
E:\work\Qt5_build\qtbase\bin\uic.exe %*
EndLocal
