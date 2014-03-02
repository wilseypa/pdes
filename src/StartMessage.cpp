
#include "DeserializerManager.h"        // for DeserializerManager
#include "SerializedInstance.h"         // for SerializedInstance
#include "StartMessage.h"

void
StartMessage::serialize(SerializedInstance* addTo) const {
    return KernelMessage::serialize(addTo);
}

Serializable*
StartMessage::deserialize(SerializedInstance* data) {
    unsigned int source = data->getUnsigned();
    unsigned int dest = data->getUnsigned();
    unsigned int incNum = data->getUnsigned();
    StartMessage* retval = new StartMessage(source, dest);
    retval->setIncarnationNumber(incNum);
    return retval;
}

const string&
StartMessage::getStartMessageType() {
    static const string startMessageType = "StartMessage";
    return startMessageType;
}


void
StartMessage::registerDeserializer() {
    DeserializerManager::instance()->registerDeserializer(getStartMessageType(),
                                                          &deserialize);
}
