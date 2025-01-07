# SimpleUNOComponent
A simple UNO component with two services that uses CMake to build and links to the KDReports C++ library

This repo uses part of the [tutorial series on LibreOffice extension development in C++ in Linux](https://niocs.github.io/LOBook/extensions/index.html)

The aim of this project is to update the repo from [LOBook Part 4](https://niocs.github.io/LOBook/extensions/part4.html) to use CMake for building
and add access to the KDReports library.

## Instructions to build
**Only tested on Ubuntu 22.04.5**

This example uses KDReports, which relies on the Qt library, it also assumes you have a LibreOffice build.

1. Check to see if Qt is installed
   
   ```qmake --version```

3. Get the KDReports library
   
   ```git clone https://github.com/KDAB/KDReports.git```

5. Follow the directions here [https://github.com/KDAB/KDReports/blob/kdreports-1.9/INSTALL-cmake.txt](https://github.com/KDAB/KDReports/blob/kdreports-1.9/INSTALL-cmake.txt)
   to build. Make sure install KDReports using the instructions in Step 7 in the installation guide linked above.

6. Once KDReports has been installed in /usr/local set the CMAKE_PREFIX variable.
   You may want to add this to your .bashrc or other appropriate file for persistence
   
   ```export CMAKE_PREFIX_PATH=/usr/local/KDAB/KDReports-2.3.95```

8. All of the prerequests should be fulfilled, we will now build the SimpleUNOComponent extension. Note, CMake needs to know the location of your LibreOffice build, which for me is $HOME/libreoffice. If the location of your LibreOffice build is different then $HOME/libreoffice, you need to go into the CMakeLists.txt file and change lines 8 and 9 to point to the correct location. Then:
   
   ```
   mkdir extensions; cd exetensions
   git clone https://github.com/a-seskunas/SimpleUNOComponent.git
   git checkout KDReports
   cd SimpleUNOCompnent
   mkdir build; cd build;
   cmake ..
   cmake --build .
   ```

6. If all goes well, green and blue writing, no red 😃, there will be a SimpleUNOComponent.oxt file in the build dir
   
   ```
   CMakeCache.txt  CMakeFiles  cmake_install.cmake  inc  Makefile  misc  SimpleUNOComponent.oxt
   ```

7. More information on installing and using the extension can be found in [https://niocs.github.io/LOBook/extensions/part4.html](https://niocs.github.io/LOBook/extensions/part4.html)
   The quick version is

   1. Tools->Extensions->Add - Navigate to the location of SimpleUNOComponent.oxt
   2. Tools->Options->Macro Security - Select Medium
   3. Restart LO when asked
   4. Open the SimpleComponent.ods file located in root directory of the repository
   5. When asked, agree to open the file with macros enabled
   6. Click the big grey button and a window should appear with the appropriate text

## Testing
After building using the steps above, the TestSimpleComponent file will be available in the build directory. This test can be used instead of manually testing the extension as described above using SimpleComponent.ods. To run TestSimpleComponent, make sure you are located in the build directory and type

```make TestSimpleComponent.run```

You may see some warnings that you can ignore, and then it should print

```connected to a running office...```

and then some more text showing that some functions have been called which indicate the test was a success.

If the following message appears

```caught BootstrapException: no soffice installation found!```

You may have incorrectly set environmental variables. Look in CMakeLists.txt and make sure that the UNO_PATH variable is set to the correct path

```/path_to_your_libreoffice/instdir/program```

If the test successfully connects to the soffice instance but fails with an UNO Exception

```caught UNO exception: component context fails to supply service inco.niocs.test.MyService1 of type inco.niocs.test.XSomething```

Check to make sure you have installed the compiled extension, steps for this are listed above in the build instructions. It can be useful when running into problems to manually test the extension using SimpleComponent.ods.

When developing, keep in mind that when changes are made to the extension, it must be re-installed in order for the changes to be shown in the extension and in turn in TestSimpleComponent or in a manual test.
