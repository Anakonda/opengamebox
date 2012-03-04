// Copyright 2012 Lauri Niskanen
//
// This file is part of OpenGamebox.
//
// OpenGamebox is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenGamebox is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenGamebox.  If not, see <http://www.gnu.org/licenses/>.

#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <vector>
#include <list>
#include <set>

#include "net.h"
#include "irenderer.h"
#include "vector2.h"
#include "objectClass.h"

namespace net {
	struct Client;
}

class Object {
public:
	Object(ObjectClass *objectClass, std::string objectId, unsigned int id, Vector2 location);

	void initForClient(IRenderer *renderer);
	ObjectClass* getObjectClass(void) const;
	std::string getObjectId(void) const;
	std::string getFullId(void) const;
	std::string getName(void) const;
	unsigned short getId(void) const;
	Vector2 getLocation(void) const;
	Vector2 getTargetLocation(void) const;
	Vector2 getSize(void) const;
	Vector2 getGridSize(void) const;
	bool testLocation(Vector2 location) const;
	bool testCollision(const Object *object, bool second = false) const;

	bool isUnder(void) const;
	Vector2 getStackDelta(void) const;
	std::list<Object*> getObjectsAbove(std::set<Object*> &visited);
	bool checkIfUnder(std::vector<Object*> objectOrder);
	bool isSelectedBy(net::Client *client) const;
	net::Client* getSelected(void);
	bool isOwnedBy(net::Client *client) const;
	net::Client* getOwner(void);
	bool isFlipped(void) const;

	void setLocation(Vector2 location);
	void select(net::Client *client);
	void own(net::Client *client);
	void flip(void);
	void setFlipped(bool flipped);
	void setAnimation(Vector2 target, float time);

	void animate(double deltaTime);
	void draw(IRenderer *renderer, net::Client *localClient) const;

private:
	ObjectClass *objectClass;
	std::string objectId;
	unsigned short id;
	Vector2 location;
	Vector2 size;
	bool flipped;
	std::string image;
	std::string backside;
	Vector2 stackDelta;

	net::Client *selected;
	net::Client *owner;
	std::list<Object*> objectsAbove;

	Vector2 animationTarget;
	float animationTime;
};

#endif
