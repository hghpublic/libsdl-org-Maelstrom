// DoInitializations.cpp


#define library(X)	(X)

#ifdef COMPUTE_VELTABLE
#include <math.h>
#endif
#include <signal.h>
#include <stdlib.h>

#include "Maelstrom_Globals.h"
#include "load.h"
#include "colortable.h"
#include "fastrand.h"


extern "C" void CleanUp(void);
extern void DoSplash(void);
extern void DoIntroScreen(void);
extern void BuildVelocityTable(void);
extern void InitStars(void);
extern void InitShots(void);

// Local functions used in this file.
/* static */ void DrawLoadBar(int first);
/* static */ int InitSprites(void);
/* static */ int LoadBlits(Mac_Resource *spriteres);
/* static */ int LoadCICNS(void);
/* static */ void BackwardsSprite(BlitPtr *theBlit, BlitPtr oldBlit);
/* static */ int LoadSprite(Mac_Resource *spriteres,
			BlitPtr *theBlit, int baseID, int numFrames);
/* static */ int LoadSmallSprite(Mac_Resource *spriteres,
			BlitPtr *theBlit, int baseID, int numFrames);

#if 1
/* ----------------------------------------------------------------- */
/* -- Perform some initializations and report failure if we choke */
int DoInitializations(Uint32 video_flags)
{
	LibPath library;
	int i;
	SDL_Surface *icon;

	/* Make sure we clean up properly at exit */
	Uint32 init_flags = (SDL_INIT_VIDEO|SDL_INIT_AUDIO);
#ifdef SDL_INIT_JOYSTICK
	init_flags |= SDL_INIT_JOYSTICK;
#endif
	if ( SDL_Init(init_flags) < 0 ) {
		init_flags &= ~SDL_INIT_JOYSTICK;
		if ( SDL_Init(init_flags) < 0 ) {
			error("Couldn't initialize SDL: %s\n", SDL_GetError());
			return(-1);
		}
	}
	atexit(CleanUp);
	signal(SIGSEGV, exit);

	// -- Initialize some variables
	gLastHigh = -1;

	// -- Create our scores file
	LoadScores();

#ifdef SDL_INIT_JOYSTICK
	/* Initialize the first joystick */
	if ( SDL_NumJoysticks() > 0 ) {
		if ( SDL_JoystickOpen(0) == NULL ) {
			error("Warning: Couldn't open joystick '%s' : %s\n",
				SDL_JoystickName(0), SDL_GetError());
		}
	}
#endif

	/* Load the Font Server */
	fontserv = new FontServ(library.Path("Maelstrom Fonts"));
	if ( fontserv->Error() ) {
		error("Fatal: %s\n", fontserv->Error());
		return(-1);
	}

	/* Load the Sound Server and initialize sound */
	sound = new Sound(library.Path("Maelstrom Sounds"), gSoundLevel);
	if ( sound->Error() ) {
		error("Fatal: %s\n", sound->Error());
		return(-1);
	}

	/* Load the Maelstrom icon */
	icon = SDL_LoadBMP(library.Path("icon.bmp"));
	if ( icon == NULL ) {
		error("Fatal: Couldn't load icon: %s\n", SDL_GetError());
		return(-1);
	}

	/* Initialize the screen */
	screen = new FrameBuf;
	if (screen->Init(SCREEN_WIDTH, SCREEN_HEIGHT, video_flags,
					colors[gGammaCorrect], icon) < 0){
		error("Fatal: %s\n", screen->Error());
		return(-1);
	}
	screen->SetCaption("Maelstrom");
	atexit(CleanUp);		// Need to reset this under X11 DGA
	SDL_FreeSurface(icon);

	/* -- We want to access the FULL screen! */
	SetRect(&gScrnRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gStatusLine = (gScrnRect.bottom - gScrnRect.top - STATUS_HEIGHT);
	gScrnRect.bottom -= STATUS_HEIGHT;
	gTop = 0;
	gLeft = 0;
	gBottom = gScrnRect.bottom - gScrnRect.top;
	gRight = gScrnRect.right - gScrnRect.left;

	gClipRect.x = gLeft+SPRITES_WIDTH;
	gClipRect.y = gTop+SPRITES_WIDTH;
	gClipRect.w = gRight-gLeft-2*SPRITES_WIDTH;
	gClipRect.h = gBottom-gTop-2*SPRITES_WIDTH+STATUS_HEIGHT;
	screen->ClipBlit(&gClipRect);

	/* Do the Ambrosia Splash screen */
	screen->Clear();
	screen->Update();
	screen->Fade();
	DoSplash();
	screen->Fade();
	for ( i=0; i<5; ++i ) {
		if ( DropEvents() ) {
			break;
		}
		Delay(60);
	}

	/* -- Throw up our intro screen */
	screen->Fade();
	DoIntroScreen();
	sound->PlaySound(gPrizeAppears, 1);
	screen->Fade();

	/* -- Load in our sprites and other needed resources */
	{
		Mac_Resource spriteres(library.Path("Maelstrom Sprites"));

		if ( spriteres.Error() ) {
			error("%s\n", spriteres.Error());
			return(-1);
		}
		if ( LoadBlits(&spriteres) < 0 ) {
			return(-1);
		}
	}

	/* -- Create the shots array */
	InitShots();

	/* -- Initialize the sprite manager - after we load blits and shots! */
	if ( InitSprites() < 0 )
		return(-1);

	/* -- Load in the prize CICN's */
	if ( LoadCICNS() < 0 )
		return(-1);

	/* -- Create the stars array */
	InitStars();

	/* -- Set up the velocity tables */
	BuildVelocityTable();

	return(0);
}	/* -- DoInitializations */
#endif
