#pragma once

#include<memory>
#include<vector>

namespace bear { namespace ecs { 

	class Entity;

	enum world_events {
		ENTITY_CREATED, // Called when entity gets added to the world using create()
					    // not neccesarily when that entity is constructed
		ENTITY_REMOVED  // called when entity is removed using remove()
	};

	class World 
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_EntityList;

	public:
		/*
		* Creates a new empty world
		*/
		World();

		/*
		* Calls update on all entities living in the world
		*/
		void update();

		/*
		* Adds entity into world
		*/
		void create(std::string a_ID);

		/*
		* Removes entity from world
		*/
		void remove(std::string a_ID);
		
		/*
		* Clears the world of entites
		*/
		void clear();

		/*
		* Returns refernce to entity with a_ID currently living inside this world
		*/
		std::shared_ptr<Entity> getEntity(std::string a_ID);
	};

} } 