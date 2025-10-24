// test_game_loop_01.cpp

#include <catch2/catch_test_macros.hpp>

#include "Maelstrom_Globals.h"
#include "buttonlist.h"
#include "load.h"
#include "fastrand.h"
#include "checksum.h"

extern void PrintUsage(void);
extern void Message(const char *message);

extern int DrawText(int x, int y, const char *text, MFont *font, Uint8 style,
                    Uint8 R, Uint8 G, Uint8 B);

/* External functions used in this file */
extern int DoInitializations(Uint32 video_flags); /* init.cc */

extern void DrawMainScreen(void);
extern void RunPlayGame(void);
extern void RunQuitGame(void);

// Global variables set in this file...
extern int gStartLives;
extern int gStartLevel;
extern Bool gUpdateBuffer;
extern Bool gRunning;
extern int gNoDelay;

TEST_CASE("game_loop_01", "[game_loop]")
{
    /* Command line flags */
    int doprinthigh = 0;
    int speedtest = 0;
    Uint32 video_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

    /* Normal variables */
    SDL_Event event;
    const char *basePath = SDL_GetBasePath();
    // LibPath::SetExePath(argv[0]);
    LibPath::SetExePath(basePath);

    /* Seed the random number generator */
    SeedRandom(0L);
    /* Initialize the controls */
    LoadControls();

    /* Initialize game logic data structures */
    REQUIRE_FALSE(InitLogicData() < 0);

    /* Parse command line arguments */
    // removed code

    /* Do we just want the high scores? */
    // removed code

    /* Make sure we have a valid player list (netlogic) */
    REQUIRE_FALSE(InitLogic() < 0);

    /* Initialize everything. :) */
    REQUIRE_FALSE(DoInitializations(video_flags) < 0);

    gRunning = true;
    // sound->PlaySound(gNovaBoom, 5);
    // screen->Fade(); /* Fade-out */
    // Delay(SOUND_DELAY);
    gUpdateBuffer = true;
    // while (sound->Playing())
    // Delay(SOUND_DELAY);

#if 1

    /* Update the screen if necessary */
    if (gUpdateBuffer)
        DrawMainScreen();

    /* -- Get an event */
    // screen->WaitEvent(&event);
    extern int gNumPlayers;
    gNumPlayers = 0;
    RunPlayGame();

    RunQuitGame();

#endif

    Delay(60);
}
