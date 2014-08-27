angadi
======

Angadi is a general purpose billing software suitable for Micro and Small enterprises operating in Tamilnadu, India.

Steps for setting up your development environment:
1. Download and install Qt (5.3.1) open source from http://qt-project.org/. Qt is a cross-platform application and UI framework for developers using C++. 
2. Qt comes bundled with its own IDE, Qt Creator (3.1.2).
3. On Windows you should also install the optional component, MinGW 4.8 (32 bit) bundled with Qt.
4. Download and install open source Evolus Pencil (2.0.5) from http://pencil.evolus.vn/. This is for viewing and editing the wire-frame source files (with the .ep extension).
5. For viewing and editing the data files in the SQLite database (with the .sqlite extension), you can try the open source SQLite Database Browser (3.2) http://sqlitebrowser.org/.
6. On GitHub fork this repository (which will make a copy of the source code in your GitHub account).
7. Clone that to your local desktop (which will make a copy of the source code in your local desktop) and open the project file (angadi.pro) in QT Creator.
8. Build the project "angadi". If all is well, the build should be successful. On Windows it should create the "angadicpp.exe" file.  
9. Run the above executable file. On Windows you have to add the "mingw48_32\bin" folder, from wherever you installed Qt, to the path environment variable so that it can find the DLL files needed to run.
10. Now you are all set to work on the bugs and enhancements in the angadi project (https://github.com/thamizha/angadi/issues). Once you are fully satisfied that your changes work well, test them thoroughly and send in a pull request (with a detailed description of the change you made) to the angadi team!


