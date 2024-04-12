#pragma once 
#include <string> 
#include "myLib.h"

namespace NS_Ticket {
    void parseJSONTicker(std::string &idCard, std::string &ticketCode, std::string JSON) {
        idCard = "";
        ticketCode = "";
        int i = 0;
        int length = (int)JSON.length();
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                idCard = idCard + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            ticketCode = ticketCode + JSON[i];
        }
    }
    
    string stringtifyTicket(string idCard, string ticketCode) {
        return idCard + '#' + ticketCode;
    }

    struct ticket {
        string idCard;
        string ticketCode {};
        ticket() {}
        ticket (int idCard, std::string ticket) {
            this->idCard = idCard;
            this->ticketCode = ticketCode;
        }
        ~ticket() {}
    };

    string handleLineCode(int code, int lineLength) {
        string lineCode = NS_myLib::Number_to_String(code);
        for (int i = 1; i <= lineLength - lineCode.length(); ++i)
            lineCode = "0" + lineCode;
        return lineCode;
    }
}