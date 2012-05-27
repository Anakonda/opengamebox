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

#include "packet.h"

Packet::Packet(unsigned char *data)
: readCursor(0) {
	this->data = std::string(reinterpret_cast<char*>(data));
}

void Packet::setReliable(bool isReliable) {
	this->isReliable = isReliable;
}

void Packet::writeHeader(Packet::Header value) {
	this->writeByte(static_cast<unsigned char>(value));
}

void Packet::writeByte(unsigned char value) {
	this->data.push_back(value);
}

void Packet::writeShort(unsigned short value) {
	this->writeByte(value & 0xFF);
	this->writeByte((value >> 8) & 0xFF);
}

void Packet::writeInt(unsigned int value) {
	this->writeByte(value & 0xFF);
	this->writeByte((value >> 8) & 0xFF);
	this->writeByte((value >> 16) & 0xFF);
	this->writeByte((value >> 24) & 0xFF);
}

void Packet::writeString(std::string value) {
	if (value.length() > 65535) {
		// The string is too long
		std::cerr << "Error: Can't send string with length of " << value.length()
		          << "!" << std::endl;
		return;
	}

	// Write the length as a short
	this->writeShort(value.length());

	// Write the string
	this->data.append(value);
}

void Packet::writeFloat(float value) {
	// TODO
	std::cerr << "Error: Unimplemented function 'Packet::writeFloat'!" << std::endl;
}

void Packet::writeVector2(Vector2 value) {
	this->writeFloat(value.x);
	this->writeFloat(value.y);
}

Packet::Header Packet::readHeader() {
	return static_cast<Packet::Header>(this->readByte());
}

unsigned char Packet::readByte() {
	unsigned char value = this->data.at(this->readCursor);
	++this->readCursor;
	return value;
}

unsigned short Packet::readShort(void) {
	return this->readByte()
	       + (this->readByte() << 8);
}

unsigned int Packet::readInt(void) {
	return this->readByte()
	       + (this->readByte() << 8)
	       + (this->readByte() << 16)
	       + (this->readByte() << 24);
}

std::string Packet::readString(void) {
	size_t length = this->readShort();

	std::string value = this->data.substr(this->readCursor, length);
	this->readCursor += length;
	return value;
}

float Packet::readFloat(void) {
	// TODO
	std::cerr << "Error: Unimplemented function 'Packet::readFloat'!" << std::endl;
	return 0.0f;
}

Vector2 Packet::readVector2(void) {
	return Vector2(this->readFloat(), this->readFloat());
}

void Packet::send(){
	int flags = 0;

	if (this->isReliable) {
		flags |= ENET_PACKET_FLAG_RELIABLE;
	}

	ENetPacket *packet = enet_packet_create(this->data.c_str(), this->data.size(), flags);

	if (this->connection != nullptr) {
		enet_host_broadcast(this->connection, 0, packet);
	} else if (this->peer != nullptr) {
		enet_peer_send(this->peer, 0, packet);
	}
}