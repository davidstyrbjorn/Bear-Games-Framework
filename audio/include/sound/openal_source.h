#pragma once

#include"openal_buffer.h"

namespace bear { namespace sound { 

	class SoundSource {
	protected:
		SoundBuffer *m_SoundBuffer;
		unsigned int m_SourceID;

	public:
		// Default constructor 
		SoundSource();
		// 
		SoundSource(std::string a_FilePath);

		// Deconstructor
		virtual ~SoundSource();

		// Loads buffer data into source
		void loadSound(std::string a_FilePath);

		// Virtual methods 
		virtual void play();
		virtual void stop();
		virtual void reset();
		virtual void pause();
	};

} } 