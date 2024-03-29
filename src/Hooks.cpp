#include "Hooks.h"
#include "InputEvents.h"
#include "TKRE.h"
#include <DKUtil/Logger.hpp>

namespace Hooks
{
	void install()
	{
		INFO("Hooking...");

		SprintHandlerHook::Hook();

		INFO("...success");
	}
	static bool bStoppingSprint = false;
	//static float heldDownTimeOffset = 0.f;

	void SprintHandlerHook::ProcessButton(RE::SprintHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data)
	{
		if (Settings::EnableSprintKeyDodge) {
			auto playerCharacter = RE::PlayerCharacter::GetSingleton();
			auto userEvent = a_event->QUserEvent();
			auto userEvents = RE::UserEvents::GetSingleton();

			if (userEvent == userEvents->sprint) {
				if (a_event->IsDown() && (playerCharacter->GetPlayerRuntimeData().playerFlags.isSprinting)) {  // stopping sprint
					DEBUG("key pressesd while pc is sprinting - stopping sprint");
					bStoppingSprint = true;
				} else if (a_event->HeldDuration() < Settings::SprintingPressDuration) {  //TODO:ADD THIS to settings
					if (a_event->IsUp()) {
						DEBUG("key lifted and was pressed less then SprintingPressDuration - dodging");
						TKRE::dodge();
						bStoppingSprint = false;
					}
					return;
				} else if (playerCharacter && (!playerCharacter->GetPlayerRuntimeData().playerFlags.isSprinting && !bStoppingSprint)) {
					DEBUG("player not sprinting and StoopingSprint flag is false - ressetting heldDownSecs to 0");
					a_event->GetRuntimeData().heldDownSecs = 0.f;
				} else if (a_event->IsUp()) {
					DEBUG("key lifted - resuming sprint");
					bStoppingSprint = false;
				}
			}
		}

		_ProcessButton(a_this, a_event, a_data);
	}
}
