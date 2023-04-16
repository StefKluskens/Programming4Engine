#pragma once
#pragma warning(push)
#pragma warning(disable: 6340)
#include <steam_api.h>
#pragma warning(pop)

#include "Achievement.h"
#include "CSteamAchievements.h"

	// Defining our achievements
	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
	};

	// Achievement array which will hold data about the achievements and their state
	extern Achievement_t g_Achievements[];

	// Global access to Achievements object
	extern dae::CSteamAchievements* g_SteamAchievements;