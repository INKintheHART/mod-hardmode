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
			for (uint8 i = 0; i < 36; i++) //iterate each container slot
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
		player->AddItem(2512, 200); // arrows
		player->AddItem(117, 4); // food
		player->AddItem(6948, 1); // hearthstone
	}


	void OnLogin(Player* player) override
	{
		AdjustVanillaStats(player);
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
		//Vanilla Stats
		float adjustmentValue = -100.0f * (1.0f - 0.6);
		float adjustmentApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedAdjustment = player->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercent) : 0;
		float adjustmentHealingValue = -100.0f * (1.0f - 0.5);
		float adjustmentHealingApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedHealingAdjustment = player->GetLevel() > 10 ? (adjustmentHealingValue * adjustmentHealingApplyPercent) : 0;
		
		AdjustStats(player, computedAdjustment, computedHealingAdjustment);
		int32 bp0 = 0; // This would be the damage taken adjustment value, but we are already adjusting health
		auto bp1 = static_cast<int32>(computedAdjustment);
		auto bp1Healing = static_cast<int32>(computedHealingAdjustment);
		player->RemoveAura(89505);
		player->CastCustomSpell(player, 89505, &bp1, nullptr, nullptr, false);
		//float adjustmentApplyPercent = (float(playerLevel) - 10.0f) / 50.0f;
		//return playerLevel > 10 ? 1.0f - ((1.0f - configAdjustmentValue) * adjustmentApplyPercent) : 1;
	}


	void OnMapChanged(Player* player) override
	{
		AdjustVanillaStats(player);
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
		//Vanilla Stats
		float adjustmentValue = -100.0f * (1.0f - 0.6);
		float adjustmentApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedAdjustment = player->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercent) : 0;
		float adjustmentHealingValue = -100.0f * (1.0f - 0.5);
		float adjustmentHealingApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedHealingAdjustment = player->GetLevel() > 10 ? (adjustmentHealingValue * adjustmentHealingApplyPercent) : 0;
		
		AdjustStats(player, computedAdjustment, computedHealingAdjustment);
		int32 bp0 = 0; // This would be the damage taken adjustment value, but we are already adjusting health
		auto bp1 = static_cast<int32>(computedAdjustment);
		auto bp1Healing = static_cast<int32>(computedHealingAdjustment);
		player->RemoveAura(89505);
		player->CastCustomSpell(player, 89505, &bp1, nullptr, nullptr, false);
		//float adjustmentApplyPercent = (float(playerLevel) - 10.0f) / 50.0f;
		//return playerLevel > 10 ? 1.0f - ((1.0f - configAdjustmentValue) * adjustmentApplyPercent) : 1;
	}

	 void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
	{
		AdjustVanillaStats(player);
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
		//Vanilla Stats
		float adjustmentValue = -100.0f * (1.0f - 0.6);
		float adjustmentApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedAdjustment = player->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercent) : 0;
		float adjustmentHealingValue = -100.0f * (1.0f - 0.5);
		float adjustmentHealingApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedHealingAdjustment = player->GetLevel() > 10 ? (adjustmentHealingValue * adjustmentHealingApplyPercent) : 0;
		
		AdjustStats(player, computedAdjustment, computedHealingAdjustment);
		int32 bp0 = 0; // This would be the damage taken adjustment value, but we are already adjusting health
		auto bp1 = static_cast<int32>(computedAdjustment);
		auto bp1Healing = static_cast<int32>(computedHealingAdjustment);
		player->RemoveAura(89505);
		player->CastCustomSpell(player, 89505, &bp1, nullptr, nullptr, false);
		//float adjustmentApplyPercent = (float(playerLevel) - 10.0f) / 50.0f;
		//return playerLevel > 10 ? 1.0f - ((1.0f - configAdjustmentValue) * adjustmentApplyPercent) : 1;
	}

	void OnEquip(Player* player, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) override
	{
		AdjustVanillaStats(player);
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
		//Vanilla Stats
		float adjustmentValue = -100.0f * (1.0f - 0.6);
		float adjustmentApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedAdjustment = player->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercent) : 0;
		float adjustmentHealingValue = -100.0f * (1.0f - 0.5);
		float adjustmentHealingApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedHealingAdjustment = player->GetLevel() > 10 ? (adjustmentHealingValue * adjustmentHealingApplyPercent) : 0;
		
		AdjustStats(player, computedAdjustment, computedHealingAdjustment);
		int32 bp0 = 0; // This would be the damage taken adjustment value, but we are already adjusting health
		auto bp1 = static_cast<int32>(computedAdjustment);
		auto bp1Healing = static_cast<int32>(computedHealingAdjustment);
		player->RemoveAura(89505);
		player->CastCustomSpell(player, 89505, &bp1, nullptr, nullptr, false);
		//float adjustmentApplyPercent = (float(playerLevel) - 10.0f) / 50.0f;
		//return playerLevel > 10 ? 1.0f - ((1.0f - configAdjustmentValue) * adjustmentApplyPercent) : 1;
	}
	void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
	{
		AdjustVanillaStats(player);
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
		//Vanilla Stats
		float adjustmentValue = -100.0f * (1.0f - 0.6);
		float adjustmentApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedAdjustment = player->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercent) : 0;
		float adjustmentHealingValue = -100.0f * (1.0f - 0.5);
		float adjustmentHealingApplyPercent = (player->GetLevel() - 10.0f) / 50.0f;
		float computedHealingAdjustment = player->GetLevel() > 10 ? (adjustmentHealingValue * adjustmentHealingApplyPercent) : 0;
		
		AdjustStats(player, computedAdjustment, computedHealingAdjustment);
		int32 bp0 = 0; // This would be the damage taken adjustment value, but we are already adjusting health
		auto bp1 = static_cast<int32>(computedAdjustment);
		auto bp1Healing = static_cast<int32>(computedHealingAdjustment);
		player->RemoveAura(89505);
		player->CastCustomSpell(player, 89505, &bp1, nullptr, nullptr, false);
		//float adjustmentApplyPercent = (float(playerLevel) - 10.0f) / 50.0f;
		//return playerLevel > 10 ? 1.0f - ((1.0f - configAdjustmentValue) * adjustmentApplyPercent) : 1;
	}



	//Pet Adjustments
	void OnPetAddToWorld(Pet* pet) override
	{
		float adjustmentValue = -100.0f * (1.0f - sIndividualProgression->0.6);
        	float adjustmentApplyPercentPet = (pet->GetLevel() - 10.0f) / 50.0f;
        	float computedAdjustmentPet = pet->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercentPet) : 0;
        	float hpAdjustmentValue = -100.0f * (1.0f - sIndividualProgression->0.75);
        	float hpAdjustment = pet->GetLevel() > 10 ? (hpAdjustmentValue * adjustmentApplyPercentPet) : 0;
        	AdjustStats(pet, computedAdjustmentPet, hpAdjustment);
		
	}
};


// Add all scripts in one
void AddHardModePlayerScripts()
{
    new HardModePlayer();
}
