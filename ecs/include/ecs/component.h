#pragma once

#include"ecs.h"

namespace bear { namespace ecs { 

	/*
	This can be inhertied from when the user wants to create his own components
	*/
	class IComponent {
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void terminate() = 0;
		virtual bool reset() = 0;
	};

	class Component : public IComponent {
	public:
		virtual void init() override { }
		virtual void update() override { }
		virtual void terminate() override { }
		virtual bool reset() override { return false; }
		
		virtual int getType() { return -1; }
	};

} } 