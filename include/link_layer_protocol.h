//
// Created by yank0vy3rdna on 14.01.2022.
//

#ifndef NETWORK_STAND_LINK_LAYER_PROTOCOL_H
#define NETWORK_STAND_LINK_LAYER_PROTOCOL_H

class LinkLayerProtocol {
    virtual int write(void *, int16_t count, unsigned char address) = 0;

    virtual int read(void *) = 0;

    virtual void tick() = 0;

    virtual int available() = 0;
};

#endif //NETWORK_STAND_LINK_LAYER_PROTOCOL_H
