#include "Server.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <WinSock2.h>
#include <sstream>
#include <string>
#include "Request.h"
#include "Response.h"

#define PAYLOAD_SIZE 2048

int Server::start_server(const unsigned short& port)
{
    std::mutex tMutex;

    WSADATA wsa;
    int wserr = WSAStartup(2, &wsa);
    if (wserr != 0) {
        printf("Failed to start WSocket\nError Code: %d\n", wserr);
        return 1;
    }

    sockaddr_in serv;
    memset(&serv, 0, sizeof(SOCKADDR_IN));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(sock, (SOCKADDR*)&serv, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        std::cerr << "Couldn't bind to :" << port << std::endl;
        return 1;
    }

    if (listen(sock, 10) == SOCKET_ERROR) {
        std::cerr << "Failed to listen" << std::endl;
        return 1;
    }

    std::cout << "Started Server on :" << port << "!\n";

    std::thread threads[4];
    for (auto& i : threads) {
        i = std::thread{
        [&] {
            while (1) {
                SOCKET csock = accept(sock, NULL, NULL);
                if (csock == INVALID_SOCKET) {
                    std::cerr << "Invalid Socket Error Code: " << WSAGetLastError() << std::endl;
                    continue;
                }

                char* buffer = (char*)malloc(PAYLOAD_SIZE);
                if (buffer == NULL) continue;
                int rcvd = recv(csock, buffer, PAYLOAD_SIZE, 0);

                if (!rcvd) {
                    std::cerr << "Socket Read Error" << std::endl;
                    continue;
                }

                char* payload_start = strstr(buffer, "\r\n\r\n"); // Aka Header End
                auto request = Request();
                std::string httpHeader(buffer, payload_start ? (size_t)(payload_start - buffer) : rcvd);
                unsigned int hstart = httpHeader.find(' ');
                if (hstart == -1) {
                    send(csock, "HTTP/1.1 400 Bad Request", 25, 0);
                    closesocket(csock);
                    continue;
                }

                request.Method = httpHeader.substr(0, hstart++);
                request.URI = httpHeader.substr(hstart, httpHeader.find(' ', hstart) - hstart);

                hstart = httpHeader.find("\r\n") + 2;
                // Parse Headers
                for (auto& i : request.Headers) {
                    unsigned int split = httpHeader.find(": ", hstart);
                    if (split == -1) break; // Invalid Header Line
                    i.Key = httpHeader.substr(hstart, split - hstart);
                    i.Value = httpHeader.substr(split + 2, (hstart = httpHeader.find("\r\n", hstart) + 2) - split - 4);
                    if (hstart == 1) break;
                }

                if (request.Method != "GET") {
                    try {
                        request.ContentLength = std::stoll(request.GetHeader("Content-Length"));
                    }
                    catch (const std::invalid_argument) {
                        request.ContentLength = 0;
                    }

                    if (request.ContentLength) {
                        payload_start += 4;
                        request.Body.resize(request.ContentLength);
                        memcpy(&request.Body[0], payload_start, request.ContentLength);
                    }

                }

                free(buffer);

                auto response = Response(csock);
                processRequest(request, response);
                if (!response.w) response.EndResponse(200);
                closesocket(csock);
            }
        }
        };
    }

    for (auto& i : threads) {
        i.join();
    }
}
