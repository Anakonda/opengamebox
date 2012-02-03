#include "net.h"

net::Client::Client(ENetPeer *peer){
	this->peer = peer;
	this->joined = false;
	this->nick.clear();
}

net::Client::Client(std::string nick){
	this->joined = true;
	this->nick = nick;
}


// Check if a nick is already used
bool net::isNickTaken(std::map<unsigned char, net::Client*> clients, std::string nick){
	for (std::map<unsigned char, net::Client*>::iterator client = clients.begin(); client != clients.end(); ++client){
		if (client->second->joined && client->second->nick.compare(nick) == 0){
			return true;
		}
	}

	return false;
}

// Broadcast a command
void net::sendCommand(ENetHost *connection, const char *data, size_t length, bool isReliable){
	int flags = 0;

	if (isReliable){
		flags |= ENET_PACKET_FLAG_RELIABLE;
	}

	ENetPacket *packet = enet_packet_create(data, length, flags);
	enet_host_broadcast(connection, 0, packet);
}

// Send a command to a single peer
void net::sendCommand(ENetPeer *peer, const char *data, size_t length){
	ENetPacket *packet = enet_packet_create(data, length, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

// Convert a float in range [-MAX_FLOAT, MAX_FLOAT] to a byte array (loses precision)
void net::floatToBytes(unsigned char* bytes, float value)
{
	unsigned int out = (value + MAX_FLOAT) / (2 * MAX_FLOAT) * 16777216;

	bytes[0] = out & 0xFF;
	bytes[1] = (out >> 8) & 0xFF;
	bytes[2] = (out >> 16) & 0xFF;
}

// Convert a byte array created with floatToBytes() back to a float
float net::bytesToFloat(unsigned char* bytes)
{
	unsigned int in = (bytes[2] << 16) + (bytes[1] << 8) + bytes[0];
	return in * (2.0f * MAX_FLOAT) / 16777216.0f - MAX_FLOAT;
}

// Convert an integer format IP address to a string representation
std::string net::IPIntegerToString(unsigned int ip){
	unsigned char bytes[4];
	bytes[0] = ip & 0xFF;
	bytes[1] = (ip >> 8) & 0xFF;
	bytes[2] = (ip >> 16) & 0xFF;
	bytes[3] = (ip >> 24) & 0xFF;

	std::ostringstream string;
	string << (int) bytes[0] << "." << (int) bytes[1] << "." << (int) bytes[2] << "."<< (int) bytes[3];

	return string.str();
}

// Convert an ENetAddress to a string representation
std::string net::AddressToString(ENetAddress address){
	std::ostringstream string;
	string << net::IPIntegerToString(address.host) << ":" << address.port;

	return string.str();
}
