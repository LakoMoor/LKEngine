#include "Discord.hpp"


void Discord::Init()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("<Enter your API>", &Handle, 1, NULL); //api
}

void Discord::Update()
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "Main Menu";
    discordPresence.details = "Playing in";
    discordPresence.startTimestamp = 1507665886;

    discordPresence.largeImageText = "LKEngine";
    discordPresence.largeImageKey = "logo";
    discordPresence.smallImageKey = "logo";
    discordPresence.smallImageText = "Rogue - Level 100";
    Discord_UpdatePresence(&discordPresence);
}