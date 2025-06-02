#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "ESP.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEND_SIZE 1024  

extern uint16_t Esp_ADC_Value[4];
extern float Esp_temperature;
extern int linkID;

// ==== Main functions ====
void sendHTML(const char* htmlContent);     // Sends an HTML page using AT+CIPSEND
int extractLinkID(const char* buffer);      // Extracts the connection ID from incoming data
void processRequest(char* request);         // Parses HTTP requests and dispatches pages
void esp_all_res(void);




#endif // WEBSERVER_H
