#include"../include/sound/openal_buffer.h"
#include"../include/sound/openal_source.h"

#include"../include/sound/decoders/wav_decoder.h"

#include<al.h>
#include<alc.h>

using namespace bear::sound;

SoundSource::SoundSource()
{
	m_SoundBuffer = new SoundBuffer();

	alGenSources(1, &m_SourceID);
}

bear::sound::SoundSource::SoundSource(std::string a_FilePath)
{
	m_SoundBuffer = new SoundBuffer();

	alGenSources(1, &m_SourceID);
	this->loadSound(a_FilePath);
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &m_SourceID);
}

void bear::sound::SoundSource::loadSound(std::string a_FilePath)
{
	alSourcef(m_SourceID, AL_PITCH, 1);
	alSourcef(m_SourceID, AL_GAIN, 1);
	alSource3f(m_SourceID, AL_POSITION, 0, 0, 0);
	alSource3f(m_SourceID, AL_VELOCITY, 0, 0, 0);
	alSourcei(m_SourceID, AL_LOOPING, AL_FALSE);

	// Fill buffer with the new data 
	m_SoundBuffer->setBufferSource(a_FilePath);

	// Attatch the sound buffer to this source
	alSourcei(m_SourceID, AL_BUFFER, m_SoundBuffer->getID());
}

int bear::sound::SoundSource::getState()
{
	int state;
	alGetSourcei(m_SourceID, AL_SOURCE_STATE, &state);
	return state;
}

void bear::sound::SoundSource::play_instantaneous()
{
	if(getState() != AL_PAUSED)
		alSourcePlay(m_SourceID);
}

void bear::sound::SoundSource::play()
{
	int s = getState();
	if (s == AL_PLAYING || s == AL_PAUSED)
		return;
	alSourcePlay(m_SourceID);
}

void bear::sound::SoundSource::stop()
{
	alSourceStop(m_SourceID);
}

void bear::sound::SoundSource::reset()
{
	alSourceRewind(m_SourceID);
}

void bear::sound::SoundSource::reset_and_play()
{
	alSourceRewind(m_SourceID);
	if(getState() != AL_PAUSED)
		alSourcePlay(m_SourceID);
}

void bear::sound::SoundSource::set_loooping(bool a_Looping)
{
	alSourcei(m_SourceID, AL_LOOPING, a_Looping);
}

void bear::sound::SoundSource::setVolume(float a_Volume)
{
	alSourcef(m_SourceID, AL_GAIN, a_Volume);
}

void bear::sound::SoundSource::pause()
{
	alSourcePause(m_SourceID);
}

void bear::sound::SoundSource::resume()
{
	alSourcePlay(m_SourceID);
}

// OPENAL BUFFER //

SoundBuffer::SoundBuffer()
{
	alGenBuffers(1, &m_BufferID);
}

bear::sound::SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers(1, &m_BufferID);
}

void bear::sound::SoundBuffer::setBufferSource(std::string a_FilePath)
{
	int size, freq, format, chan, samplerate, bps;
	void* data = bear::sound::load_wav(a_FilePath.c_str(), chan, samplerate, bps, size, format);
	alBufferData(m_BufferID, format, data, size, samplerate);

	int error = alGetError();
	if (error != AL_NO_ERROR) {
		std::cout << "ERROR: Buffer Data";
	}
}