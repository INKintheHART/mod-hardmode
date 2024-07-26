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
        for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        {
		// Delete player items
             if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
             {
                  if (pItem->GetTemplate())
                      continue;
                  uint8 slot = pItem->GetSlot();
                  // ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
                  player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);   

              }
		
        }
	for (uint8 b= INVENTORY_SLOT_ITEM_START; b < INVENTORY_SLOT_ITEM_END; b++)
	{
		player->DestroyItem(INVENTORY_SLOT_BAG_0, b, true);
	}
	for  (uint8 c = INVENTORY_SLOT_BAG_START; c < INVENTORY_SLOT_BAG_END; c++)
	{	
		for (uint8 i = INVENTORY_SLOT_BAG_START; i < MAX_BAG_SIZE i++)
		{
			player->DestroyItem(c, i, true);
		}
	}	
        player->SetMoney(0);
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
