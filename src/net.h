// Copyright 2012 Lauri Niskanen
// Copyright 2012 Antti Aalto
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

#ifndef NET_H
#define NET_H

#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <enet/enet.h>

#include "vector2.h"
#include "object.h"
#include "client.h"
#include "serverClient.h"

class Object;

namespace net {
	// Define basic connection parameters
	const unsigned int CHANNELS      = 2;
	const unsigned char MAX_CLIENTS  = 32;
	const float MAX_FLOAT            = 10000.0f;
	const double STREAM_INTERVAL     = 5000.0f;
	const unsigned int PING_INTERVAL = 1000;

	// Master server options
	const unsigned int MASTER_SERVER_PING_INTERVAL = 60000;

	// >>> DEPRECATED: Use Packet instead
	// Client control packets
	const unsigned char PACKET_HANDSHAKE  = 0x01; // Initialize connection
	const unsigned char PACKET_NICK_TAKEN = 0x02; // Inform about a reserved nick name
	const unsigned char PACKET_JOIN       = 0x03; // Inform about a joining client
	const unsigned char PACKET_LEAVE      = 0x04; // Inform about a leaving client

	// Object command packets
	const unsigned char PACKET_CREATE  = 0x20; // Create new objects
	const unsigned char PACKET_SELECT  = 0x21; // Select objects and prevent others from moving them
	const unsigned char PACKET_REMOVE  = 0x22; // Remove objects
	const unsigned char PACKET_MOVE    = 0x23; // Move objects
	const unsigned char PACKET_FLIP    = 0x24; // Flip objects
	const unsigned char PACKET_OWN     = 0x25; // Make objects private
	const unsigned char PACKET_SHUFFLE = 0x26; // Shuffle objects
	const unsigned char PACKET_ROTATE  = 0x27; // Rotate objects

	// Other command packets
	const unsigned char PACKET_CHAT = 0x40; // Send a chat message
	const unsigned char PACKET_ROLL = 0x42; // Roll a die on the server

	// Master server communication
	const unsigned char PACKET_MS_QUERY    = 0xC0; // Request the server list
	const unsigned char PACKET_MS_REGISTER = 0xC1; // Register to the server list
	const unsigned char PACKET_MS_UPDATE   = 0xC2; // Update registered information

	// Stream packets
	const unsigned char PACKET_PINGS = 0xE0; // Broadcast ping information
	// <<< DEPRECATED

	bool isNickTaken(std::map<unsigned char, ServerClient*> clients, std::string nick);

	// >>> DEPRECATED: Use Packet instead
	void sendCommand(ENetHost *connection, const char *data, size_t length, bool isReliable=true);
	void sendCommand(ENetPeer *peer, const char *data, size_t length);

	void intToBytes(unsigned char *bytes, unsigned int value);
	unsigned int bytesToInt(unsigned char *bytes);

	void shortToBytes(unsigned char *bytes, unsigned short value);
	unsigned int bytesToShort(unsigned char *bytes);

	void floatToBytes(unsigned char *bytes, float value);
	float bytesToFloat(unsigned char *bytes);
	Vector2 bytesToVector2(unsigned char *bytes);

	void dataAppendInt(std::string &data, unsigned int value);
	void dataAppendShort(std::string &data, unsigned short value);
	void dataAppendVector2(std::string &data, Vector2 value);
	// <<< DEPRECATED

	std::string IPIntegerToString(unsigned int ip);
	std::string AddressToString(ENetAddress address);

	std::string getPrettyFileSize(unsigned int size);

	void removeObject(std::vector<Object*> &objectOrder, Object* object);
}

#endif
