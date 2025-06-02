#include "WEBSERVER.h"

char *response = "HTTP/1.1 204 No Content\r\n\r\n";
const char Login_Page[] =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
        "<title>Login</title>"
        "<style>"
        "body { font-family: Arial, sans-serif; background: linear-gradient(135deg, #667eea, #764ba2); margin: 0; padding: 0; }"
        ".login-container { width: 320px; padding: 40px; background: white; border-radius: 10px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.3); position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); }"
        ".login-container h2 { text-align: center; margin-bottom: 20px; color: #333; }"
        ".login-container input[type='text'], .login-container input[type='password'] { width: 100%; padding: 12px 20px; margin: 8px 0; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }"
        ".login-container input[type='submit'] { width: 100%; background-color: #4CAF50; color: white; padding: 14px 20px; margin-top: 12px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; }"
        ".login-container input[type='submit']:hover { background-color: #45a049; }"
				".btn:active { background-color: #3e8e41; }"
        "</style></head><body>"
        "<div class='login-container'>"
        "<h2>Login</h2>"
        "<form action='/login' method='GET'>"
        "User: <input name='user' type='text' placeholder='Enter Username' required><br>"
        "Pass: <input name='pass' type='password' placeholder='Enter Password' required><br>"
        "<input type='submit' value='Login'>"
        "</form>"
        "</div></body></html>";
const char main_page[] ="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
        "<title>Home Page</title>"
        "<style>"
        "body { font-family: Arial, sans-serif; background: linear-gradient(135deg, #667eea, #764ba2); margin: 0; padding: 0; height: 100vh; display: flex; justify-content: center; align-items: center; }"
        ".container { width: 100%; max-width: 800px; padding: 40px; text-align: center; background-color: white; border-radius: 10px; box-shadow: 0 0 15px rgba(0, 0, 0, 0.1); }"
        ".welcome-message { font-size: 36px; margin-bottom: 30px; color: #333; }"
        ".button-container { display: flex; justify-content: center; gap: 20px; margin-top: 30px; }"
        ".btn { padding: 15px 30px; font-size: 18px; color: white; background-color: #4CAF50; border: none; border-radius: 5px; cursor: pointer; transition: background-color 0.3s ease; }"
        ".btn:hover { background-color: #45a049; }"
        ".btn:active { background-color: #3e8e41; }"
        "</style></head><body>"
        "<div class='container'>"
        "<div class='welcome-message'>Welcome to your IoT Server</div>"
        "<p>Choose an option below to either view the data or configure your server.</p>"
        "<div class='button-container'>"
        "<a href='/dataCenter'><button class='btn'>Data Center</button></a>"
        "</div>"
        "</div>"
        "</body></html>";

char Data_Center_page[]=
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
" <meta charset=\"UTF-8\">\n"
" <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
" <title>Data Center</title>\n"
" <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n"
" <style>\n"
" body {\n"
" background-color: #f4f7f9;\n"
" font-family: Arial, sans-serif;\n"
" margin: 0;\n"
" padding: 0;\n"
" }\n"
" .container {\n"
" display: flex;\n"
" justify-content: center;\n"
" align-items: flex-start;\n"
" margin: 50px;\n"
" }\n"
" .card {\n"
" background-color: white;\n"
" border-radius: 10px;\n"
" box-shadow: 0 4px 8px rgba(0,0,0,0.1);\n"
" padding: 30px;\n"
" width: 300px;\n"
" margin: 10px;\n"
" }\n"
" h2 {\n"
" color: #333;\n"
" margin-bottom: 20px;\n"
" text-align: center;\n"
" }\n"
" .data-item {\n"
" font-size: 18px;\n"
" margin: 10px 0;\n"
" color: #555;\n"
" }\n"
" @media (max-width: 600px) {\n"
" .container {\n"
" flex-direction: column;\n"
" align-items: center;\n"
" }\n"
" }\n"
" </style>\n"
"</head>\n"
"<body>\n"
" <div class=\"container\">\n"
" <div class=\"card\">\n"
" <h2>ESP Data</h2>\n"
" <div class=\"data-item\">Temperature: <span id=\"esp_temp\">0</span> °C</div>\n"
" <div class=\"data-item\">CH1: <span id=\"esp_ch1\">0</span></div>\n"
" <div class=\"data-item\">CH2: <span id=\"esp_ch2\">0</span></div>\n"
" <div class=\"data-item\">CH3: <span id=\"esp_ch3\">0</span></div>\n"
" <div class=\"data-item\">CH4: <span id=\"esp_ch4\">0</span></div>\n"
" </div>\n"
" </div>\n"
"\n"
" <script>\n"
" function updateESP() {\n"
" fetch('/esp_all')\n"
" .then(response => response.text())\n"
" .then(data => {\n"
" const values = data.split('\\n');\n"
" document.getElementById('esp_temp').innerText = values[0].split(':')[1].trim();\n"
" document.getElementById('esp_ch1').innerText = values[1].split(':')[1].trim();\n"
" document.getElementById('esp_ch2').innerText = values[2].split(':')[1].trim();\n"
" document.getElementById('esp_ch3').innerText = values[3].split(':')[1].trim();\n"
" document.getElementById('esp_ch4').innerText = values[4].split(':')[1].trim();\n"
" })\n"
" .catch(error => console.error('Error updating ESP data:', error));\n"
" }\n"
"\n"
" setInterval(updateESP, 10000);\n"
" window.onload = updateESP;\n"
" </script>\n"
"</body>\n"
"</html>\n"
"";


void sendHTML(const char* htmlContent) {
    linkID = extractLinkID(CpyBuffer);
    if (linkID < 0 || linkID > 4) return;

    int totalLen = strlen(htmlContent);
    int sent = 0;

    while (sent < totalLen) {
        int chunkLen = (totalLen - sent > MAX_SEND_SIZE) ? MAX_SEND_SIZE : (totalLen - sent);
        
        snprintf(cmdBuffer, sizeof(cmdBuffer), "AT+CIPSEND=%d,%d\r\n", linkID, chunkLen);
        SendTxt_usart2(cmdBuffer);
        delay_ms(100);
        
        for (int i = 0; i < chunkLen; i++) {
            SendChar_usart2(htmlContent[sent + i]);
        }
        sent += chunkLen;
				delay_ms(100);
    }
    /*sprintf(cmdBuffer,"AT+CIPCLOSE=%d\r\n", linkID);
    SendTxt_usart2(cmdBuffer);
    delay_ms(100);
		ClearBuffer(cmdBuffer, sizeof(cmdBuffer));*/
}



int extractLinkID(const char* buffer) {
    const char* start = strstr(buffer, "+IPD,");
    if (start) {
        return atoi(start + 5); // "+IPD," = 5 caractères
    }
    return -1; // Erreur, pas trouvé
}



void esp_all_res() {
    char content[100];
    sprintf(content, "Temp: %.2f\nCh1: %hu\nCh2: %hu\nCh3: %hu\nCh4: %hu",
            Esp_temperature,
            Esp_ADC_Value[0],
            Esp_ADC_Value[1],
            Esp_ADC_Value[2],
						Esp_ADC_Value[3]);

    char resp[300];
    int content_length = strlen(content);

    sprintf(resp,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: keep-alive\r\n"
        "\r\n"
        "%s",
        content_length,
        content
    );
    sendHTML(resp);
}



void processRequest(char* request) {
    if ((strstr(request,"GET / HTTP"))) {
        sendHTML(Login_Page);
    }
		else  if (strstr(request, "GET /login?user=admin&pass=admin") != NULL) {
        sendHTML(main_page);
    }
		else if (strstr(request, "GET /dataCenter") != NULL) {
        sendHTML(Data_Center_page);
    }
		else if (strstr(request, "GET /esp_all")) {
				esp_all_res();	
    }
		else if (strstr(request,"favicon.ico")){
				sendHTML(response);	
		}
}


