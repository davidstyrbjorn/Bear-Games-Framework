#pragma once

#include<string>
#include<array>
#include<map>
#include<deque>
#include<memory>

#include"ecs.h"
#include"component.h"

namespace bear { namespace ecs { 

	class TransformComponent;

	class Entity {
	private:
		std::string m_ID;
		std::array<Component*, COMPONENT_COUNT> m_ComponentList;
		std::deque<component_types> m_ComponentsToRemove;

	public:
		Entity(std::string a_ID);
		~Entity();
		
		void update();

		/////////////////////////////
		//  Bear Component
		//    Methods
		/////////////////////////////

		// Adds component of a_Type to m_ComponentList
		bool addComponent(component_types a_Type);

		// Get component from m_ComponentList
		// use component_types::RENDERABLE_COMPONENT to get renderable component NOT component_types::RECTANGLE/TRIANGLE_SPRITE_COMPONENT
		template<typename _T>
		_T* getComponent(component_types a_Type)
		{
			return static_cast<_T*>(m_ComponentList[a_Type]);
		}

		// Remove component 
		// If you wish to remove renderable component please pass in component_types::RENDERABLE_COMPONENT
		void removeComponent(component_types a_Type);

		// Get the transform component m_ComponentList[component_types::TRANSFORM_COMPONENT]
		bear::ecs::TransformComponent* transform();

		/////////////////////////////
		//  Dynamic Component
		//      Methods
		/////////////////////////////

		std::string getID();
		void setID(std::string a_ID);
	};

} } 