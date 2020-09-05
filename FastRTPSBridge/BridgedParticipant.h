/////
////  BridgedParticipant.h
///   Copyright © 2019 Dmitriy Borovikov. All rights reserved.
//

#pragma once

#include <fastrtps/rtps/reader/RTPSReader.h>
#include <fastrtps/rtps/writer/RTPSWriter.h>
#include <fastrtps/rtps/history/ReaderHistory.h>
#include <fastrtps/rtps/history/WriterHistory.h>
#include "BridgedReaderListener.h"
#include "BridgedWriterListener.h"

class BridgedParticipantListener;
class BridgedParticipant
{
    struct ReaderInfo {
        eprosima::fastrtps::rtps::RTPSReader* reader;
        eprosima::fastrtps::rtps::ReaderHistory* history;
        BridgedReaderListener* listener;
        ~ReaderInfo() {
            delete history;
            delete listener;
        }
    };

    struct WriterInfo {
        eprosima::fastrtps::rtps::RTPSWriter* writer;
        eprosima::fastrtps::rtps::WriterHistory* history;
        BridgedWriterListener* listener;
        ~WriterInfo() {
            delete history;
            delete listener;
        }
    };

    eprosima::fastrtps::rtps::RTPSParticipant* mp_participant;
    BridgedParticipantListener* mp_listener;
    std::string partitionName;
    
    BridgeContainer container;
    
    std::map<std::string, ReaderInfo*> readerList;
    std::map<std::string, WriterInfo*> writerList;
public:
    BridgedParticipant();
    virtual ~BridgedParticipant();
    void setContainer(BridgeContainer container);

    bool createParticipant(const char* name,
                           const uint32_t domain,
                           const char *interfaceIPv4,
                           const char* networkAddress);
    void setPartition(const char* name) { partitionName = std::string(name); }
    bool addReader(const char* name,
                   const char* dataType,
                   const bool keyed,
                   const bool transientLocal,
                   const bool reliable,
                   const void * payloadDecoder);
    
    bool removeReader(const char* name);
    
    bool addWriter(const char* name,
                   const char* dataType,
                   const bool keyed,
                   const bool transientLocal);
    bool removeWriter(const char* name);
    bool send(const char* name, const uint8_t* data, uint32_t length, const void* key, uint32_t keyLength);
    void resignAll();
};
