#ifndef ZFOO_EMPTYOBJECT_H
#define ZFOO_EMPTYOBJECT_H

#include "zfoocpp/ByteBuffer.h"

namespace zfoo {

    
    class EmptyObject : public IProtocol {
    public:
        

        ~EmptyObject() override = default;

        static EmptyObject valueOf() {
            auto packet = EmptyObject();
            
            return packet;
        }

        int16_t protocolId() override {
            return 0;
        }

        bool operator<(const EmptyObject &_) const {
            
            return false;
        }
    };


    class EmptyObjectRegistration : public IProtocolRegistration {
    public:
        int16_t protocolId() override {
            return 0;
        }

        void write(ByteBuffer &buffer, IProtocol *packet) override {
            if (packet == nullptr) {
                buffer.writeInt(0);
                return;
            }
            auto *message = (EmptyObject *) packet;
            buffer.writeInt(-1);
        }

        IProtocol *read(ByteBuffer &buffer) override {
            auto *packet = new EmptyObject();
            auto length = buffer.readInt();
            if (length == 0) {
                return packet;
            }
            auto beforeReadIndex = buffer.readerIndex();
            
            if (length > 0) {
                buffer.readerIndex(beforeReadIndex + length);
            }
            return packet;
        }
    };
}

#endif
