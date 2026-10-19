
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <time.h>

PSP_MODULE_INFO("Runner PSP - Kaua Soares", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define SCREEN_W 480
#define SCREEN_H 272
#define GROUND_Y 220

int main(void)
{
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    int playerY = GROUND_Y;
    int obstacleX = SCREEN_W;
    int score = 0;
    int jump = 0;

    SceCtrlData pad;

    while (1) {
        sceCtrlReadBufferPositive(&pad, 1);

        if ((pad.Buttons & PSP_CTRL_CROSS) && playerY == GROUND_Y)
            jump = 1;

        if (jump) {
            playerY -= 8;
            if (playerY < 130) jump = 2;
        } else if (jump == 2) {
            playerY += 8;
            if (playerY >= GROUND_Y) {
                playerY = GROUND_Y;
                jump = 0;
            }
        }

        obstacleX -= 5;
        if (obstacleX < -20) {
            obstacleX = SCREEN_W + rand() % 150;
            score++;
        }

        pspDebugScreenSetXY(0, 0);
        pspDebugScreenSetTextColor(0xFFFFFFFF);
        pspDebugScreenPrintf("RUNNER PSP - KAUA SOARES\n");
        pspDebugScreenPrintf("Pontuacao: %d\n\n", score);
        pspDebugScreenPrintf("Controles: X para pular\n\n");

        pspDebugScreenPrintf("                  [OBSTACULO]\n");
        pspDebugScreenPrintf("                Jogador: %s\n",
            playerY < GROUND_Y ? "PULANDO" : "CORRENDO");

        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
