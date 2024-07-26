/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
// Add player scripts
class HardModePlayer : public PlayerScript
{
public:
    HardModePlayer() : PlayerScript("HardModePlayer") { }
    //OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) 
    void OnPlayerReleasedGhost(Player *player) override
    {		
	for (uint8 b= INVENTORY_SLOT_ITEM_START; b < INVENTORY_SLOT_ITEM_END; b++) // Iterate each backpack slot
	{
		player->DestroyItem(INVENTORY_SLOT_BAG_0, b, true); // Delete item
	}

	for  (uint8 c = INVENTORY_SLOT_BAG_START; c < INVENTORY_SLOT_BAG_END; c++) //iterate each equipped container
	{	
		for (uint8 i = INVENTORY_SLOT_START; i < MAX_BAG_SIZE; i++) //iterate each container slot
		{
			player->DestroyItem(c, i, true); // delete
		}
	}
	    // Equipment
        for (uint8 d= EQUIPMENT_SLOT_START; d < EQUIPMENT_SLOT_END; d++) //iterate each equipment slot
        {
                player->DestroyItem(INVENTORY_SLOT_BAG_0, d, true); // delete
	}

        player->SetMoney(0);
	// Add Items    
	player->AddItem(2092, 1); // dagger
        player->AddItem(148, 1); // shirt
        player->AddItem(147, 1); // pants
        player->AddItem(129, 1); // boots
        player->AddItem(159, 2); // water
        player->AddItem(2504, 1); // bow
        player->AddItem(2101, 1); // quiver
        player->AddItem(2512, 200); // arrows
        player->AddItem(117, 4); // food
        player->AddItem(6948, 1); // hearthstone
    }
};

// Add all scripts in one
void AddHardModePlayerScripts()
{
    new HardModePlayer();
}
