#pragma once

#include<string>
#include<array>
#include<iostream>

#include"ecs.h"
#include"component.h"

namespace bear { namespace ecs { 

	class Entity {
	private:
		std::string m_ID;
		std::array<Component, COMPONENT_COUNT> m_ComponentList;

	public:
		Entity(std::string a_ID);
		
		void update() {
			std::cout << this->m_ID << std::endl;
		}

		std::string getID();
		void setID(std::string a_ID);
	};

} } 