#include "NoteProviderMidi.h"

#include <map>
#include "RtMidi.h"


NoteProviderMidi::NoteProviderMidi()
	: mMidiIn(NULL)
{
	// Create an api map.
	std::map<int, std::string> apiMap;
	apiMap[RtMidi::MACOSX_CORE] = "OS-X CoreMidi";
	apiMap[RtMidi::WINDOWS_MM] = "Windows MultiMedia";
	apiMap[RtMidi::UNIX_JACK] = "Jack Client";
	apiMap[RtMidi::LINUX_ALSA] = "Linux ALSA";
	apiMap[RtMidi::RTMIDI_DUMMY] = "RtMidi Dummy";

	std::vector< RtMidi::Api > apis;
	RtMidi :: getCompiledApi( apis );

	std::cout << "\nCompiled APIs:\n";
	for ( unsigned int i=0; i<apis.size(); i++ )
		std::cout << "  " << apiMap[ apis[i] ] << std::endl;

	try 
	{
		// RtMidiIn constructor ... exception possible
		mMidiIn = new RtMidiIn();
		std::cout << "\nCurrent input API: " << apiMap[ mMidiIn->getCurrentApi() ] << std::endl;

		// Check inputs.
		unsigned int nPorts = mMidiIn->getPortCount();
		std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
		for ( unsigned i=0; i<nPorts; i++ ) 
		{
			std::string portName = mMidiIn->getPortName(i);
			std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
		}

		if ( nPorts>0 ) 
		{
			mMidiIn->openPort( 0 );
			
			// Don't ignore sysex, timing, or active sensing messages.
			mMidiIn->ignoreTypes( false, false, false );
		}
	} 
	catch ( RtMidiError &error ) 
	{
		error.printMessage();
	}
}

NoteProviderMidi::~NoteProviderMidi()
{
	delete mMidiIn;
	mMidiIn = NULL;
}


bool NoteProviderMidi::IsAvailable()
{
	return mMidiIn->getPortCount() > 0;
}

void NoteProviderMidi::update()
{
	if ( !mMidiIn->isPortOpen() )
		return;
	
	bool cont = true;
	do
	{
		std::vector<unsigned char> message;
		double stamp = mMidiIn->getMessage( &message );
		int nBytes = message.size();
		if ( nBytes!=0 )
		{
			int firstByte = message[0];
			if ( firstByte!=0xFE )		// Decimal 254
			{
				unsigned char channelIndex = firstByte & 0x0F;
				unsigned char statusCode = firstByte & 0xF0;
				//std::cout << static_cast<int>(channelIndex) << " - " << static_cast<int>(statusCode) << std::endl;
				if ( statusCode==0x90 && nBytes>=2 )			// Decimal 144
				{
					//  Note On
					unsigned char secondByte = message[1];
					Note note( secondByte );
					notifyListeners(note);
				}
/*				else if ( statusCode==0x80 && nBytes>=2 )	// Decimal 128
				{
					//  Note Off
				}*/
			}
		}
		else
		{
			cont = false;
		}
	}
	while ( cont );
	//std::cout << "========== " << std::endl;	
}