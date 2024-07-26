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
    	Item* pItem = GetItemByPos(bag, slot);
    	if (pItem)
    	{
		LOG_DEBUG("entities.player.items", "STORAGE: DestroyItem bag = {}, slot = {}, item = {}", bag, slot, pItem->GetEntry());
       		// Also remove all contained items if the item is a bag.
	        // This if () prevents item saving crashes if the condition for a bag to be empty before being destroyed was bypassed somehow.
	        if (pItem->IsNotEmptyBag())
 	           for (uint8 i = 0; i < MAX_BAG_SIZE; ++i)
   	             DestroyItem(slot, i, update);
 
   	     if (pItem->HasFlag(ITEM_FIELD_FLAGS, ITEM_FIELD_FLAG_WRAPPED))
   	     {
    	        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GIFT);
        	    stmt->SetData(0, pItem->GetGUID().GetCounter());
	            CharacterDatabase.Execute(stmt);
	     }
		RemoveEnchantmentDurations(pItem);
		RemoveItemDurations(pItem);
 
        	pItem->SetNotRefundable(this);
        	pItem->ClearSoulboundTradeable(this);
        	RemoveTradeableItem(pItem);
 
        	ItemTemplate const* proto = pItem->GetTemplate();
        	for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            		if (proto->Spells[i].SpellTrigger == ITEM_SPELLTRIGGER_ON_NO_DELAY_USE && proto->Spells[i].SpellId > 0) // On obtain trigger
                		RemoveAurasDueToSpell(proto->Spells[i].SpellId);
 
        	ItemRemovedQuestCheck(pItem->GetEntry(), pItem->GetCount());
 
        	sScriptMgr->OnItemRemove(this, pItem);
 
		if (bag == INVENTORY_SLOT_BAG_0)
		{
			SetGuidValue(PLAYER_FIELD_INV_SLOT_HEAD + (slot * 2), ObjectGuid::Empty);
			
			// equipment and equipped bags can have applied bonuses
			if (slot < INVENTORY_SLOT_BAG_END)
			{
				ItemTemplate const* pProto = pItem->GetTemplate();
				
				// item set bonuses applied only at equip and removed at unequip, and still active for broken items
				if (pProto && pProto->ItemSet)
					RemoveItemsSetItem(this, pProto);
				_ApplyItemMods(pItem, slot, false);
			}
			if (slot < EQUIPMENT_SLOT_END)
			{
				// remove item dependent auras and casts (only weapon and armor slots)
				RemoveItemDependentAurasAndCasts(pItem);
				
				// update expertise and armor penetration - passive auras may need it
				switch (slot)
				{
					case EQUIPMENT_SLOT_MAINHAND:
					case EQUIPMENT_SLOT_OFFHAND:
					case EQUIPMENT_SLOT_RANGED:
						RecalculateRating(CR_ARMOR_PENETRATION);
					default:
						break;
				}
				
				if (slot == EQUIPMENT_SLOT_MAINHAND)
					UpdateExpertise(BASE_ATTACK);
				else if (slot == EQUIPMENT_SLOT_OFFHAND)
					UpdateExpertise(OFF_ATTACK);
				
				// equipment visual show
				SetVisibleItemSlot(slot, nullptr);
			}
			
			m_items[slot] = nullptr;
		}
	        else if (Bag* pBag = GetBagByPos(bag))
	            pBag->RemoveItem(slot, update);
	 
	        // Xinef: item is removed, remove loot from storage if any
	        if (proto->Flags & ITEM_FLAG_HAS_LOOT)
	            sLootItemStorage->RemoveStoredLoot(pItem->GetGUID());
	 
	        if (IsInWorld() && update)
	        {
	            pItem->RemoveFromWorld();
	            pItem->DestroyForPlayer(this);
	        }
 
	        //pItem->SetOwnerGUID(0);
	        pItem->SetGuidValue(ITEM_FIELD_CONTAINED, ObjectGuid::Empty);
	        pItem->SetSlot(NULL_SLOT);
	        pItem->SetState(ITEM_REMOVED, this);
	    }
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
