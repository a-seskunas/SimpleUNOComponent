# SimpleUNOComponent
A simple UNO component with two services that uses CMake to build a LibreOffice extension and links to the KDReports C++ library

This repo is an update to part of the [tutorial series on LibreOffice extension development in C++ in Linux](https://niocs.github.io/LOBook/extensions/index.html)

The aim of this project is to update the repo from [LOBook Part 4](https://niocs.github.io/LOBook/extensions/part4.html) to use CMake for building
and add access to the KDReports library.

## Instructions to build
1. In order to get LimeReports to build on my system Ubuntu 22.04.5 I had to install the following dependencies
   ```sudo apt install libqt5svg5-dev qtdeclarative5-dev```
   You may need to install others, I haven't tested on other systems so I can't be sure what is needed.

2. Clone SimpleUNOComponent. If you already have the SimpleUNOComponent repo from one of the other branches, it can be reused, you just need to remove the build directory, and skip this step.
   ```mkdir ~/Extensions; cd ~/Extensions
      git clone https://github.com/a-seskunas/SimpleUNOComponent.git
      git checkout LimeReport```

3. Clone LimeReport in the SimpleUNOComponent directory.
   ```cd ~/Extensions/SimpleUNOComponent
      git clone https://github.com/fralx/LimeReport.git ```

4. In order for LimeReport to find a missing header, I had to manually change cmake/modules/GenerateVersionHeader.cmake\
   Line 25 reads \
   ```${CMAKE_SOURCE_DIR}/limereport/version.h.in change it to -> ${CMAKE_SOURCE_DIR}/LimeReport/limereport/version.h.in```\
   Line 26 reads \
   ```${CMAKE_BINARY_DIR}/limereport/version.h change it to -> ${CMAKE_BINARY_DIR}/LimeReport/limereport/version.h```

6. Now you can use CMake to build the extension and LimeReport should be included in the build
   ```mkdir build; cd build;
      cmake ..
      cmake --build .
   ```

7. If the build is successful, you will get ~/Extensions/SimpleUNOComponent/SimpleUNOComponent.oxt which is the newly built extension.

8. More information on installing and using the extension can be found in [https://niocs.github.io/LOBook/extensions/part4.html](https://niocs.github.io/LOBook/extensions/part4.html)
   The quick version is
   1. Tools->Extensions->Add - Navigate to the location of SimpleUNOComponent.oxt
   2. Tools->Options->Macro Security - Select Medium
   3. Restart LO when asked
   4. Open the SimpleComponent.ods file located in root directory of the repository
   5. When asked, agree to open the file with macros enabled
   6. Click the big grey button and a window should appear with the appropriate text
