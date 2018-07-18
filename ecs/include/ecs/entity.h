#pragma once

#include<string>
#include<array>
#include<map>

#include"ecs.h"
#include"component.h"

namespace bear { namespace ecs { 

	class TransformComponent;

	struct entity_component_slot {
		Component *m_Component;
		bool m_IsPossesed;
	};

	class Entity {
	private:
		std::string m_ID;
		std::array<entity_component_slot, COMPONENT_COUNT> m_ComponentList;
		std::map<std::string, IComponent*> m_DynamicComponentList;

	public:
		Entity(std::string a_ID);
		~Entity();
		
		void update();

		/*
		1. Adds component of a_Type to the entity if it already exists return false else return true
		2. Adds user-created component to the entity
		*/
		bool addComponent(component_types a_Type);
		template<typename _T>
		void addComponent()
		{
			std::string typeName = typeid(_T).name();
			m_DynamicComponentList.insert(std::pair<std::string, IComponent*>(typeName, new _T));
		}

		/*
		Used for fetching components from the main component list
		*/
		template<typename _T>
		_T* getComponent(component_types a_Type)
		{
			if (a_Type == component_types::TRANSFORM_COMPONENT) {
				return static_cast<_T*>(m_ComponentList[component_types::RENDERABLE_COMPONENT].m_Component);
			}
			if (a_Type == component_types::RENDERABLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT] ) {
				return static_cast<_T*>(m_ComponentList[component_types::RENDERABLE_COMPONENT].m_Component);
			}

			return nullptr;
		}
		template<typename _T>
		_T* getComponent()
		{
			static std::string typeName = typeid(_T).name();
			if (m_DynamicComponentList.find(typeName) != m_DynamicComponentList.end()) {
				return static_cast<_T>(m_DynamicComponentList.at(typeName));
			}
		}
		inline TransformComponent* transform();

		std::string getID();
		void setID(std::string a_ID);
	};

} } 