cmake_minimum_required(VERSION 3.5)

project(SimpleUNOComponent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################
# SET LOCATION OF LIBREOFFICE HERE
set(LO $ENV{HOME}/libreoffice)
##########################################

set(LOROOT ${LO}/instdir)
set(UNO_PATH ${LOROOT}/program)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Generate C++ header files for all of sdk's uno types from the LO's rdb files -- only needs to be run once during setup
execute_process(COMMAND ${LOROOT}/sdk/bin/cppumaker -Gc -O./inc 
	                ${LOROOT}/program/types.rdb 
			${LOROOT}/program/types/offapi.rdb
)

# Use unoidl-write to create the SimpleComponent.rdb file
add_custom_target(SimpleComponentRDB ALL DEPENDS ${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.rdb)
add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.rdb
	COMMAND ${LOROOT}/sdk/bin/unoidl-write 
	        ${LO}/udkapi 
		${PROJECT_SOURCE_DIR}/some.idl 
		${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.rdb
	DEPENDS ${PROJECT_SOURCE_DIR}/some.idl
)

# Generate C++ header files (hpp and hdl) for new types and their dependencies from rdb files
# If a new Service is added to some.idl, it must be added to the command below
# AUTOMATE ME
add_custom_target(GenerateHeaders ALL DEPENDS ${PROJECT_BINARY_DIR}/inc/SimpleComponent/inco/niocs/test/*)
add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/inc/SimpleComponent/inco/niocs/test/*
	COMMAND ${LOROOT}/sdk/bin/cppumaker -Gc -O${PROJECT_BINARY_DIR}/inc/SimpleComponent
                        -Tinco.niocs.test.XSomething 
			-Tinco.niocs.test.MyService1 
			-Tinco.niocs.test.MyService2
	                 ${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.rdb
			-X${LOROOT}/program/types.rdb 
			-X${LOROOT}/program/types/offapi.rdb
	DEPENDS ${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.rdb
)

add_executable(TestSimpleComponent TestSimpleComponent.cxx)
add_library(service1_impl OBJECT service1_impl.cxx)
add_library(service2_impl OBJECT service2_impl.cxx)

add_library(SimpleComponent.uno SHARED service1_impl service2_impl)
set_target_properties(SimpleComponent.uno 
	              PROPERTIES PREFIX "" 
		                 LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/misc/SimpleComponent/Linux_x86_64
)

add_definitions(-DUNX 
	        -DGCC 
		-DLINUX 
		-DCPPU_ENV=gcc3
)
find_package(KDReports CONFIG REQUIRED)
target_link_libraries(service1_impl KDReports::kdreports)

include_directories(
    	${PROJECT_SOURCE_DIR}
	${PROJECT_BINARY_DIR}/inc
	${PROJECT_BINARY_DIR}/inc/SimpleComponent
    	${LOROOT}/sdk/include
)

target_link_directories(SimpleComponent.uno PRIVATE
	${LOROOT}/program
	${LOROOT}/sdk/lib
	${PROJECT_BINARY_DIR}/lib
)

target_link_libraries(SimpleComponent.uno
	uno_sal
	uno_cppu
	uno_cppuhelpergcc3
	KDReports::kdreports	
)

target_link_directories(TestSimpleComponent PRIVATE
	${LOROOT}/program
	${LOROOT}/sdk/lib
	${PROJECT_BINARY_DIR}/lib
)

target_link_libraries(TestSimpleComponent
	uno_sal
	uno_cppu
	uno_cppuhelpergcc3
)

# This xml file tells LO extension manager where to find the rdb file and a file 
# SimpleComponent.components which would point to the .so shared lib
file(WRITE ${PROJECT_BINARY_DIR}/misc/SimpleComponent/META-INF/manifest.xml
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
    <!DOCTYPE manifest:manifest PUBLIC \"-//OpenOffice.org//DTD Manifest 1.0//EN\" \"Manifest.dtd\">
    <manifest:manifest xmlns:manifest=\"http://openoffice.org/2001/manifest\">
    <manifest:file-entry manifest:media-type=\"application/vnd.sun.star.uno-typelibrary;type=RDB\"
                    manifest:full-path=\"SimpleComponent.rdb\"/>
    <manifest:file-entry manifest:media-type=\"application/vnd.sun.star.uno-components;platform=Linux_x86_64\"
                    manifest:full-path=\"SimpleComponent.components\"/>
     </manifest:manifest>"
)

# This is an xml file which tells the LO extension manager where to find the shared 
# library and what all services are implemented along with the fully qualified implementation names
# Any services must be added here
file(WRITE ${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.components
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
     <components xmlns=\"http://openoffice.org/2010/uno-components\">
     <component loader=\"com.sun.star.loader.SharedLibrary\" uri=\"Linux_x86_64/SimpleComponent.uno.so\">
        <implementation name=\"inco.niocs.test.my_sc_impl.MyService1\">
            <service name=\"inco.niocs.test.MyService1\"/>
        </implementation>
        <implementation name=\"inco.niocs.test.my_sc_impl.MyService2\">
            <service name=\"inco.niocs.test.MyService2\"/>
        </implementation>
    </component>
    </components>"
)

# Zip up the contentents of misc/SimpleComponet to produce the extension file *.oxt 
add_custom_target(SimpleComponent_extension ALL DEPENDS SimpleUNOComponent.oxt)
add_custom_command(OUTPUT SimpleUNOComponent.oxt
	COMMAND /usr/bin/zip -r ../../SimpleUNOComponent.oxt . *
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/misc/SimpleComponent
	DEPENDS ${PROJECT_SOURCE_DIR}/some.idl 
	        ${PROJECT_SOURCE_DIR}/*.cxx 
		${PROJECT_BINARY_DIR}/misc/SimpleComponent/SimpleComponent.components 
		${PROJECT_BINARY_DIR}/misc/SimpleComponent/META-INF/manifest.xml
)

# Custom command to run the test, invoke by typing:  make TestSimpleComponent.run  on the command line
# The UNO_PATH environment variable must be set in order for this to connect to a running soffice instance
add_custom_target(TestSimpleComponent.run
	COMMAND ${CMAKE_COMMAND} -E env "UNO_PATH=${UNO_PATH}" ${PROJECT_BINARY_DIR}/TestSimpleComponent
	WORKING_DIRECTORY ${LOROOT}/sdk
)
