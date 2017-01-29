#include "BouncebackPacket.h"

void BouncebackPacket::createPacket(bool flag, std::string message)
{
    this->ipv6Flag = flag;
    this->packet = message;
    this->payload = &this->packet[0];
    this->returnPacket = true;
}
