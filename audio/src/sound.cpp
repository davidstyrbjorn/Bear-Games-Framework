#include"../include/sound/sound.h"

#include<iostream>
#include<al.h>
#include<alc.h>

#include"../include/sound/decoders/wav_decoder.h"

test::test()
{
	int error;

	//device = alcOpenDevice(NULL);
	//if (!device)
	//	std::cout << "Failed to create device\n";
	//
	//context = alcCreateContext(device, NULL);
	//if (!alcMakeContextCurrent(context))
	//	std::cout << "Failed to create context\n";
	//if ((error = alGetError()) != AL_NO_ERROR)
	//	std::cout << "OpenAL error at LINE 19\n";

	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	alGenBuffers(1, &buffer);
	int size, freq, format, chan, samplerate, bps;
	void* data = bear::sound::load_wav("D:\\temp\\sound.wav", chan, samplerate, bps, size, format);
	alBufferData(buffer, format, data, size, samplerate);

	alSourcei(source, AL_BUFFER, buffer);
}

void test::play()
{
	alSourcePlay(source);
}
