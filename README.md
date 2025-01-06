# SimpleUNOComponent
A simple UNO component with two services that uses CMake to build a LibreOffice Extension.

This repo is an update to part of the [tutorial series on LibreOffice extension development in C++ in Linux](https://niocs.github.io/LOBook/extensions/index.html)

There are two additional branches that build off the main branch to include KDReports and LimeReport in each respective branch.
For instructions on building these branches and additional information see the links below.

[SimpleUNOComponent with KDReports](https://github.com/a-seskunas/SimpleUNOComponent/tree/KDReports)\
[SimpleUNOComponent with LimeReport](https://github.com/a-seskunas/SimpleUNOComponent/tree/LimeReport)

To build this project

1. Clone the git repo. It can be located anywhere.\
```mkdir ~/Extensions; cd ~/Extensions; git clone https://github.com/a-seskunas/SimpleUNOComponent.git```  
2. ```cd SimpleUNOComponent; mkdir build; cd build```
3. ```cmake ..```
4. ```cmake --build .```
5. If the build is successful, you will get ~/Extensions/SimpleUNOComponent/SimpleUNOComponent.oxt which is the newly built extension.
6. More information on installing and using the extension can be found in https://niocs.github.io/LOBook/extensions/part4.html The quick version is
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
