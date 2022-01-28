//
// Created by yank0vy3rdna on 14.01.2022.
//

#ifndef NETWORK_STAND_UART_H
#define NETWORK_STAND_UART_H

#include "link_layer_protocol.h"
#include <SoftwareSerial.h>

#pragma pack(push, 1)
struct packet {
    int16_t heading_bytes = 2000;
    int16_t packet_size{};
    void *data{};
};
#pragma pack(pop)

class UART : public LinkLayerProtocol {
// todo buffer incoming packets every tick
public:
    UART(int8_t rx, int8_t tx) {
        this->serial = new SoftwareSerial(rx, tx);
        this->serial->begin(9600);
    }

    int available() override {
        return this->serial->available();
    }

    void tick() override {

    }

    int write(void *pVoid, int16_t count, unsigned char address) override {
        struct packet outbound_packet{};
        outbound_packet.packet_size = count;
        outbound_packet.data = pVoid;

        this->serial->write((uint8_t *) &outbound_packet, sizeof(outbound_packet) - sizeof(void *));
        this->serial->write((uint8_t *) outbound_packet.data, outbound_packet.packet_size);
    }

    int read(void *pVoid) override {
        struct packet incoming_packet{};
        const int header_size = sizeof(struct packet) - sizeof(void *);
        if (this->serial->available() < header_size)
            return 0;
        this->serial->readBytes((char *) &incoming_packet, header_size);
        if (this->serial->available() < incoming_packet.packet_size)
            return 0;
        byte *body_buffer = static_cast<byte *>(malloc(incoming_packet.packet_size));
        incoming_packet.data = body_buffer;
        this->serial->readBytes(body_buffer, incoming_packet.packet_size);
        memcpy(&incoming_packet, pVoid, sizeof(incoming_packet));
        return 1;
    }

private:
    SoftwareSerial *serial;
};

#endif //NETWORK_STAND_UART_H
