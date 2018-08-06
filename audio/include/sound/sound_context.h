#pragma once

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

namespace bear { namespace sound { 

	class SoundContext {
	private:
		ALCdevice* m_Device;
		ALCcontext* m_Context;

	public:
		// Private constructor since no instance of this class is suppoed to be created 
		// Just used to call the static methods to interact and start OpenAL
		SoundContext() { }

	public:
		// Inits OpenAL for use
		void init();

		// OpenAL deconstruction
		void exit();
	};

} } 