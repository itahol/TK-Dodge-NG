#include "AnimationEvents.h"
#include "Hooks.h"
#include "InputEvents.h"
#include "TKRE.h"

namespace TKDodge
{
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\TK Dodge RE.ini"

	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
			Settings::readSettings();
			InputEventHandler::Register();
			animEventHandler::RegisterForPlayer();
			// TODO Port sprinting dodge
			// Hooks::install();
		}
	}
}