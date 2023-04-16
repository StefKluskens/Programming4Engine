#pragma once
#include "Achievement.h"

#pragma warning(push)
#pragma warning(disable: 6340)
#include <steam_api.h>
#pragma warning(pop)

#include "Singleton.h"

namespace dae
{
	class CSteamAchievements : public dae::Singleton< CSteamAchievements>
	{
	public:
		CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
		~CSteamAchievements();

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);
		STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);
		STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);

	private:
		int64 m_iAppID; // Our current AppID
		Achievement_t* m_pAchievements; // Achievements data
		int m_iNumAchievements; // The number of Achievements
		bool m_bInitialized; // Have we called Request stats and received the callback?
	};
}