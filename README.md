# SimpleUNOComponent
A simple UNO component with two services that uses CMake to build and links to the KDReports C++ library

This repo uses part of the [tutorial series on LibreOffice extension development in C++ in Linux](https://niocs.github.io/LOBook/extensions/index.html)

The aim of this project is to update the repo from [LOBook Part 4](https://niocs.github.io/LOBook/extensions/part4.html) to use CMake for building
and add access to the KDReports library.

## Instructions to build
**Only tested on Ubuntu 22.04.5** milage may very

This example uses KDReports, which relies on the Qt library, it also assumes you have a LibreOffice build.

Step 1. Check to see if Qt is installed\
  ```$qmake --version```

Step 2. Get the KDReports library\
  ```$git clone https://github.com/KDAB/KDReports.git```

Step 3. Follow the directions here [https://github.com/KDAB/KDReports/blob/kdreports-1.9/INSTALL-cmake.txt](https://github.com/KDAB/KDReports/blob/kdreports-1.9/INSTALL-cmake.txt)
   to build. Make sure install KDReports using the instructions in Step 7 in the installation guide linked above.

Step 4. Once KDReports has been installed in /usr/local set the CMAKE_PREFIX variable.
   You may want to add this to your .bashrc or other appropriate file for persistence\
   ```$export CMAKE_PREFIX_PATH=/usr/local/KDAB/KDReports-2.3.95```

Step 5. All of the prerequests should be fulfilled, we will now build the SimpleUNOComponent extension. Note, CMake needs to know the location of your LibreOffice build, which for me is $HOME/libreoffice. If the location of your LibreOffice build is different then $HOME/libreoffice, you need to go into the CMakeLists.txt file and change lines 8 and 9 to point to the correct location. Then:
```
   $mkdir extensions; cd exetensions
   $git clone https://github.com/a-seskunas/SimpleUNOComponent.git
   $cd SimpleUNOCompnent
   $mkdir build; cd build;
   $cmake ..
   $cmake --build .
```
Step 6. If all goes well(green and blue writing, no red 😃), there will be a SimpleUNOComponent.oxt file in the build dir
```
CMakeCache.txt  CMakeFiles  cmake_install.cmake  inc  Makefile  misc  SimpleUNOComponent.oxt
```

Step 7. More information on installing and using the extension can be found in [https://niocs.github.io/LOBook/extensions/part4.html](https://niocs.github.io/LOBook/extensions/part4.html)
   The quick version is
   1. Tools->Extensions->Add - Navigate to the location of SimpleUNOComponent.oxt
   2. Tools->Options->Macro Security - Select Medium
   3. Restart LO when asked
   4. Open the SimpleComponent.ods file located in root directory of the repository
   5. When asked, agree to open the file with macros enabled
   6. Click the big grey button and a window should appear with the appropriate text
