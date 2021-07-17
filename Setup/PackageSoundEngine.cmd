set /p Version=<Version.txt
if not exist ..\FamiStudio%Version%-SoundEngine mkdir ..\FamiStudio%Version%-SoundEngine
robocopy ..\SoundEngine\ ..\FamiStudio%Version%-SoundEngine *.h *.asm *.nes *.s *.txt
robocopy ..\SoundEngine\DemoSource\ ..\FamiStudio%Version%-SoundEngine\DemoSource *.c *.asm *.s *.cfg *.chr *.dmc *.pal *.rle build*.bat export_from_famistudio.bat
del ..\FamiStudio%Version%-SoundEngine\DemoSource\*_cc65.s
tar -a -c -f FamiStudio%Version%-SoundEngine.zip -C ..\FamiStudio%Version%-SoundEngine\ *
rmdir /S /Q ..\FamiStudio%Version%-SoundEngine
