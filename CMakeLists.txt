cmake_minimum_required( VERSION 2.8 )

project( PianoTrainer )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)


set( SOURCE_FILES
	Staff.h
	Staff.cpp
	StaffPresenter.h
	StaffPresenter.cpp
	main.cpp)

source_group("" FILES ${SOURCE_FILES} )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

#qt5_use_modules(ThermoProto Widgets)

# Use the Widgets module from Qt 5.
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets)

