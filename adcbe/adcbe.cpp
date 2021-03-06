// adcbe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <chrono>
#include <iostream>
#include <thread>

#include "Bancho/BanchoServer.h"
#include "Web/WebServer.h"

#include "Response.h"
#include "Bancho/Packets/Packet.h"

int main(void)
{
    std::thread checkThread([] {
        while (1) {
            std::this_thread::sleep_for(std::chrono::seconds(30));
            Global::CheckPlayerTimeout();
        }
    });
    BanchoServer bServer;
    WebServer wServer;
    std::thread bThread([&] { bServer.start_server(5001); });
    std::thread wThread([&] { wServer.start_server(5002); });
    bThread.join();
    wThread.join();
    checkThread.join();
}
// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
