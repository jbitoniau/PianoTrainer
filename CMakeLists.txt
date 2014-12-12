cmake_minimum_required( VERSION 2.8 )

project( PianoTrainer )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

include_directories( Dependencies/rtmidi-2.1.0 )

set( SOURCE_FILES
	INoteGenerator.h
	BasicNoteGenerator.h
	BasicNoteGenerator.cpp
	LeitnerNoteGenerator.h
	LeitnerNoteGenerator.cpp
	Note.h
	Note.cpp
	Clef.h
	Clef.cpp
	StaffClef.h
	StaffClef.cpp
	Staff.h
	Staff.cpp
	GrandStaff.h
	GrandStaff.cpp
	StaffPresenter.h
	StaffPresenter.cpp
	GrandStaffPresenter.h
	GrandStaffPresenter.cpp
	NoteProvider.h
	NoteProvider.cpp
	NoteProviderMidi.h
	NoteProviderMidi.cpp
	NoteProviderKeyboard.h
	NoteProviderKeyboard.cpp
	QNoteProviderUpdater.h
	QNoteProviderUpdater.cpp
	QExercise.h
	QExercise.cpp
	Main.cpp)

source_group("" FILES ${SOURCE_FILES} )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

#qt5_use_modules(ThermoProto Widgets)

# Use the Widgets module from Qt 5.
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets)


if( WIN32 )
	target_link_libraries( ${PROJECT_NAME} winmm )
	target_link_libraries( ${PROJECT_NAME} 
							debug ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/rtmidi-2.1.0/lib/rtmidid.lib 	
							optimized ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/rtmidi-2.1.0/lib/rtmidi.lib )
else()
	#target_link_libraries( ${PROJECT_NAME} asound )
	#target_link_libraries( ${PROJECT_NAME} pthread )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/rtmidi-2.1.0/librtmidi.so )
endif()
