#pragma once

#include<string>
#include<array>
#include<iostream>

#include"ecs.h"
#include"component.h"

namespace bear { namespace ecs { 

	struct entity_component_slot {
		Component m_Component;
		bool m_IsActive;
	};

	class Entity {
	private:
		std::string m_ID;
		std::array<entity_component_slot, COMPONENT_COUNT> m_ComponentList;

	public:
		Entity(std::string a_ID);
		~Entity();
		
		void update();

		/*
		Adds component of a_Type to the entity if it already exists return false else return true
		*/
		bool addComponent(component_types a_Type);
		Component* getComponent(component_types a_Type);

		std::string getID();
		void setID(std::string a_ID);
	};

} } 