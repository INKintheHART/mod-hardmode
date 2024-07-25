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
    //OnPlayerKilledByCreature
    void OnPlayerReleasedGhost(Creature* /*killer*/, Player* player) override	
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
    }
    void OnPlayerReleasedGhost(Player *player) override	
    {
        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
        {
            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
            if (item)
            {
                // Remove the equipped item
                player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
                sLog->outDebug(LOG_FILTER_SERVER_LOADING, "Removed equipped item: %u", item->GetEntry());
            }
        }
	    
        // Iterate over all inventory slots (bag slots 19 to 39)
        for (uint8 bagSlot = INVENTORY_SLOT_BAG_START; bagSlot < INVENTORY_SLOT_BAG_END; ++bagSlot)
        {
            for (uint8 slot = 0; slot < MAX_BAG_SIZE; ++slot)
            {
                Item* item = player->GetItemByPos(bagSlot, slot);
                if (item)
                {
                    // Remove the item from the inventory
                    player->DestroyItem(bagSlot, slot, true);
                    sLog->outDebug(LOG_FILTER_SERVER_LOADING, "Removed inventory item: %u", item->GetEntry());
                }
            }
        }

        player->SendBroadcastMessage("All equipped items and inventory items have been removed.");  
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
