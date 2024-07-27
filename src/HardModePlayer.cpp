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
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
	}
	void OnMapChanged(Player* player) override
	{
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
	}
	void OnEquip(Player* player, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) override
	{
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
	}
	void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
	{
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		
	}

	//Pet Adjustments
//	void OnPetAddToWorld(Pet* pet) override
//	{
//		float adjustmentValue = -100.0f * (1.0f - sIndividualProgression->0.6);
//        	float adjustmentApplyPercentPet = (pet->GetLevel() - 10.0f) / 50.0f;
//        	float computedAdjustmentPet = pet->GetLevel() > 10 ? (adjustmentValue * adjustmentApplyPercentPet) : 0;
//        	float hpAdjustmentValue = -100.0f * (1.0f - sIndividualProgression->0.75);
//        	float hpAdjustment = pet->GetLevel() > 10 ? (hpAdjustmentValue * adjustmentApplyPercentPet) : 0;
//        	AdjustStats(pet, computedAdjustmentPet, hpAdjustment);
//		
//	}

	void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
	{
		if (player->getClass() == CLASS_HUNTER)
		{
			// Remove the 15% built-in ranged haste that was added to hunters in WotLK
			// This lets us add haste spells back to quivers
			player->RemoveAura(89507);
			player->CastSpell(player, 89507, false);
		}
		if (player->GetLevel() == 2
		{
			player->AddSpell(133); //Fireball (Mage)
			player->AddSpell(348); //Immolate (Warlock)
			player->AddSpell(403); //Lightning Bolt (Shaman)
			player->AddSpell(635); // Holy Light (pally)
			player->AddSpell(2050); //Lesser Heal (Priest)
			player->AddSpell(5185); //Healing Touch (Druid)
			player->AddSpell(331); //Healing Wave (Shaman)
			player->AddSpell(585); //Smite (Priest)
			player->AddSpell(2973); //Raptor Strike (Hunter)
			player->AddSpell(5176); //Wrath (Druid)
			player->AddSpell(686); //Shadowbolt (Warlock)
			//AddSpell{1804}, // Pick Lock (Rogue)
			//AddSpell{75}, //Auto Shot (hunter)
		

		{
		if (player->GetLevel() == 4
		{
                	player->AddSpell(20271); // Judgement of Light (Paladin)
                	player->AddSpell(8071); // Stoneskin Totem (Shaman)
			player->AddSpell(172); // Corruption (Warlock)
			player->AddSpell(116); //Frostbolt (Mage)
			player->AddSpell(1978); //Serpent Sting (hunter)
			player->AddSpell(2052); //Lesser Heal Rank 2 (Priest)
			player->AddSpell(8921); //Moonfire (Druid)
			player->AddSpell(774); //Rejuvenation (Druid)
			player->AddSpell(8042); //Earth Shock (Shaman)
			player->AddSpell(589); //Shadow Word: Pain (Priest)
			player->AddSpell(2484); //Earthbind Totem (Shaman)
		}
		if (player->GetLevel() == 6
		{
			player->AddSpell(1454); // Life Tap (Warlock)
              		player->AddSpell(639); // Holy Light Rank 2 (Paladin)
			player->AddSpell(1130); // Hunter's Mark (Hunter)
			player->AddSpell(17); // Power Word Shield (Priest)
			player->AddSpell(695); // Shadowbolt Rank 2 (Warlock)
			player->AddSpell(332); // Healing Wave Rank 2 (Shaman)
			player->AddSpell(591); // Smite Rank 2 (Priest)
			player->AddSpell(2136); // Fire Blast (Mage)
			player->AddSpell(143); //Fireball rank 2 (mage)
			player->AddSpell(5177); //Wrath rank 2 (druid)
			player->AddSpell(3044); //Arcane Shot (hunter)
		}
		if (player->GetLevel() == 8
		{
			player->AddSpell(586); // Fade (Priest)
			player->AddSpell(139); // Renew (Priest)
			player->AddSpell(1152); // Purify (Paladin)
			player->AddSpell(5730; // Stoneclaw Totem (Shaman)
			player->AddSpell(118); // Polymorph (mage)
			player->AddSpell(205); // Frostbolt rank 2 (mage)
			player->AddSpell(853); // Hammer of Justice (Paladin) // 1 min cooldown - Stuns the target for 3 sec and interrupts non-player spellcasting for 3 sec.
			player->AddSpell(529); // Lightning Bolt Rank 2 (Shaman)
			player->AddSpell(5116); // Concussive Shot (Hunter)
			player->AddSpell(5186); // Healing Touch Rank 2(Druid)
			player->AddSpell(8044); // Earth Shock Rank 2 (Shaman)
			player->AddSpell(5782); // Fear (warlock)
			player->AddSpell(5143); //Qrcane Missiles (mage)
			player->AddSpell(14260); //Raptor Strike Rank 2 (hunter)
			player->AddSpell(339); //Entangling Roots (Druid)
		}
		if (player->GetLevel() == 10
		{
		        //AddSpell{6991}, // Feed Pet (Hunter)
			//AddSpell{1515}, // Tame Beast (Hunter)
			//AddSpell{883}, // Call Pet (Hunter)
			//AddSpell{982}, // Revive Pet (Hunter)
			player->AddSpell(5487); // Bear Form (Druid)
			player->AddSpell(1120); // Drain Soul (Warlock)
			player->AddSpell(355); // Taunt (Warrior)
			player->AddSpell(1058); // Rejuvernation Rank 2 (Druid)
			player->AddSpell(2053); // LEsser Heal Rank 3 (Priest)
			player->AddSpell(8050); // Flame Shock (Shaman)
			player->AddSpell(122); // Frost Nova (Mage)
			player->AddSpell(594); // Shadow Word: Pain Rank 2 (priest)
			player->AddSpell(6795); // Growl (Taunt - Druid)
			player->AddSpell(8092); // Mind Blast (Priest)
			player->AddSpell(707); // Immolate rank 2 (Warlock)
			player->AddSpell(8924); // Moonfire rank 2 (druid)
			player->AddSpell(2006); // Resurrection (priest)
			player->AddSpell(2641); // Dismiss Pet (hunter)
			player->AddSpell(3599); // Searing Totem (Shaman)
			player->AddSpell(6807); // Maul (Druid) - Bear Form
			player->AddSpell(99); // Demoralizing Roar (Druid) Bear form
			player->AddSpell(13549); //Serpent Sting Rank 2 (Hunter)
			//AddSpell{633}, //Lay on Hands(Paladin) - 20 min CD - Heals a friendly target for an amount equal to the Paladin's maximum health.  If used on self, the Paladin cannot be targeted by Divine Shield, Divine Protection, Hand of Protection, or self-targeted Lay on Hands again for 2 min.  Also cannot be used on self within 30 sec of using Avenging Wrath.
		}
	}
};

   
    
  
// Add all scripts in one
void AddHardModePlayerScripts()
{
    new HardModePlayer();
}
