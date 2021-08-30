/*! \file ClientResponse.h
    \brief ClientResponse class declaration. 
*/
#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include <iostream>
#include <chrono>
#include <thread>
#include "../Message/Message.h"
#include "../BaseResponse/BaseResponse.h"

class ClientResponse : public BaseResponse {
    void Command(Message* from_client);
    void Response(Message* from_client);
public:
    ClientResponse(int serial_number, int total_tasks, int first_task = 0);
    //! \brief Class destructor.
    virtual ~ClientResponse() = default;
    void Processing(Message* from_client);
};

#endif // CLIENTRESPONSE_H
