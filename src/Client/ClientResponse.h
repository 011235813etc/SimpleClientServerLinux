#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

// #include <memory>
// #include <unistd.h>
#include <iostream>
#include "../Message/Message.h"
#include "../BaseResponse/BaseResponse.h"

class ClientResponse : public BaseResponse {

    void Command(Message* rcvd);
    void Response(Message* rcvd);

public:
    ClientResponse(int serial_number, int total_tasks, int first_task = 0);
    virtual ~ClientResponse();
    void Processing(Message* rcvd);
};

#endif // CLIENTRESPONSE_H
