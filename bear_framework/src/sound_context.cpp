#include"../include/sound/sound_context.h"

#include<al.h>
#include<alc.h>

#include<iostream>

using namespace bear::sound;

ALCdevice* SoundContext::m_Device = nullptr;
ALCcontext* SoundContext::m_Context = nullptr;

void bear::sound::SoundContext::init()
{
	m_Device = alcOpenDevice(0); // default device
	if (!m_Device) {
		std::cout << "Failed to create OpenAL device\n";
	}

	m_Context = alcCreateContext(m_Device, NULL);
	if (!m_Context) {
		std::cout << "Failed to create OpenAL context\n";
	}
	if (!alcMakeContextCurrent(m_Context)) {
		std::cout << "Failed to make context current\n";
	}
}

void bear::sound::SoundContext::exit()
{
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);
}