// hbchat (3DS Client)
// Author: Virtualle/VirtuallyExisting
// Description: A chatting application for Wii and 3DS

#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <malloc.h>

#include <3ds/applets/swkbd.h>

int main(int argc, char **argv) {
    gfxInitDefault();
    PrintConsole topScreen, bottomScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    consoleSelect(&topScreen);
    printf("\x1b[2J");

    u32 *soc_buffer = memalign(0x1000, 0x100000);
    if (!soc_buffer) {
        printf("Failed to allocate SOC buffer\n");
    }
    if (socInit(soc_buffer, 0x100000) != 0) {
        printf("socInit failed\n");
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket create failed\n");
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(3071); // Every hbchat server should be on port 3071, if not, it will not work with any default instance, I might change this.
    server.sin_addr.s_addr = inet_addr("PUT SERVER IP HERE"); // There is currently no default server, please wait until a solution is found or host your own server.

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) != 0) {
        printf("Connect failed\n");
    }

    printf("hbchat\n");
    printf("v0.0.1\n");
    printf("Press START to exit (or just use the home menu button)\n");

    char username[32];

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000; // 10ms

    char buffer[512];
    while (aptMainLoop()) {
        gspWaitForVBlank();
        hidScanInput();

        if (hidKeysDown() & KEY_A) {
            char message[64];
            char input[64];
            SwkbdState swkbd;
            swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 1, 63);
            swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);
            swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY, 0, 0);

            SwkbdButton button = swkbdInputText(&swkbd, username, sizeof(username)); 
        }

        if (hidKeysDown() & KEY_B) {
            char message[64];
            char msg[128];

            char input[64];
            SwkbdState swkbd;
            swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 1, 63);
            swkbdSetFeatures(&swkbd, SWKBD_PREDICTIVE_INPUT);
            swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY, 0, 0);

            SwkbdButton button = swkbdInputText(&swkbd, message, sizeof(message));
            if (button == SWKBD_BUTTON_CONFIRM) {
                sprintf(msg, "<%s>: %s", username, message);
                send(sock, msg, strlen(msg), 0);
                consoleSelect(&topScreen);
                printf("Message sent!\n");
            }
        }

        fd_set readfds;
        struct timeval timeout;

        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 10000; // 10ms

        if (select(sock + 1, &readfds, NULL, NULL, &timeout) > 0) {
            ssize_t len = recv(sock, buffer, sizeof(buffer)-1, 0);
            if (len > 0) {
                buffer[len] = '\0';
                consoleSelect(&bottomScreen);
                printf("%s\n", buffer);
                consoleSelect(&topScreen);
            }
        }

        if (hidKeysDown() & KEY_START) break;
        gfxFlushBuffers();
        gfxSwapBuffers();
    }
    closesocket(sock);
    socExit();
    gfxExit();
    return 0;
}