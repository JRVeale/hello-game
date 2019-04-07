//Entity Component System
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
	//generate a new ComponentID
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

//as using a bitset (rather than vector or dynamic array) size must be known at compile
constexpr std::size_t maxComponents = 32; //max components an initity can hold
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;	//a reference to its owner

	//NB. virtual methods can be overwritten by derived classes' methods
	virtual void init() {}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};

class Entity {
private:
	Manager& manager;

	bool active = true;	//remove from game if false

	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager){}
	void update() {
		//loop through all its components and update them
		for (auto& c : components) c->update();
	}
	void draw() {
		//loop through all its components and draw them
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup) {
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup) {
		groupBitSet[mGroup] = false;
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	// this helps me to understand: http://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/
	template <typename T, typename... TArgs>	//Variadic template
	T& addComponent(TArgs&&... mArgs)			//function...
	{
		//to understand TArgs&& and std::forward https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/
		T* c(new T(std::forward<TArgs>(mArgs)...));	//A Component, or member of class derived from Component
		c->entity = this;	//Set the component's owner to this entity
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		//give the component[s] to the entity
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();	//initialise the components
		return *c;
	}

	template <typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	
};

class Manager {
	//Keeps a list of all our entities...
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	void refresh() {	//remove inactive entities from groupedEntities
		for (auto i(0u); i < maxGroups; i++) {
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity) {
				return !mEntity->isActive() || !mEntity->hasGroup(i);
				}),
				std::end(v));
		}
						//and entities
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity) {
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		return groupedEntities[mGroup];	//the vector of entities in that group
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};