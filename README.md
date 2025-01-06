# SimpleUNOComponent
A simple UNO component with two services that uses CMake to build a LibreOffice extension and links to the LimeReport C++ library

This repo is an update to part of the [tutorial series on LibreOffice extension development in C++ in Linux](https://niocs.github.io/LOBook/extensions/index.html)

The aim of this project is to update the repo from [LOBook Part 4](https://niocs.github.io/LOBook/extensions/part4.html) to use CMake for building
and add access to the LimeReport library.

## Instructions to build
1. In order to get LimeReports to build on my system Ubuntu 22.04.5 I had to install the following dependencies

   ```
       sudo apt install libqt5svg5-dev qtdeclarative5-dev
   ```

   You may need to install others, I haven't tested on other systems so I can't be sure what is needed.

2. Clone SimpleUNOComponent. If you already have the SimpleUNOComponent repo from one of the other branches, it can be reused, you just need to remove the build directory, and skip this step.

```
       mkdir ~/Extensions; cd ~/Extensions
       git clone https://github.com/a-seskunas/SimpleUNOComponent.git
       git checkout LimeReport
```

3. Clone LimeReport in the SimpleUNOComponent directory.

   ```
      cd ~/Extensions/SimpleUNOComponent
      git clone https://github.com/fralx/LimeReport.git 
      ```

4. In order for LimeReport to find a missing header, I had to manually change cmake/modules/GenerateVersionHeader.cmake\
   Line 25 reads
   ```
   ${CMAKE_SOURCE_DIR}/limereport/version.h.in change it to -> 
   ${CMAKE_SOURCE_DIR}/LimeReport/limereport/version.h.in
   ```
   Line 26 reads
   ```
   ${CMAKE_BINARY_DIR}/limereport/version.h change it to -> 
   ${CMAKE_BINARY_DIR}/LimeReport/limereport/version.h
   ```

6. Now you can use CMake to build the extension and LimeReport should be included in the build
   ```mkdir build; cd build;
      cmake ..
      cmake --build .
   ```

7. If the build is successful, you will get ~/Extensions/SimpleUNOComponent/SimpleUNOComponent.oxt which is the newly built extension.

8. More information on installing and using the extension can be found in [https://niocs.github.io/LOBook/extensions/part4.html](https://niocs.github.io/LOBook/extensions/part4.html)
   The quick version is
1. Clone the git repo. It can be located anywhere.\
```mkdir ~/Extensions; cd ~/Extensions; git clone https://github.com/a-seskunas/SimpleUNOComponent.git```  
2. If your LibreOffice installation is in a non-standard place i.e. not in $HOME/libreoffice, you need to go into CMakeLists.txt and change the LO variable to the correct location.
3. ```cd SimpleUNOComponent; mkdir build; cd build```
4. ```cmake ..```
5.`cmake --build .```
6. If the build is successful, you will get ~/Extensions/SimpleUNOComponent/SimpleUNOComponent.oxt which is the newly built extension.
7. More information on installing and using the extension can be found in https://niocs.github.io/LOBook/extensions/part4.html The quick version is

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
