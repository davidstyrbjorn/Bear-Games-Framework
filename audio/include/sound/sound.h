#pragma once

#include"sound_context.h"
#include"openal_buffer.h"
#include"openal_source.h"

class test {
public:
	unsigned int buffer, source;
	ALCdevice* device;
	ALCcontext* context;

	test();
	void play();
};