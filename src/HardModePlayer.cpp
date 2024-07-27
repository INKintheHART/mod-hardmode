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
		// Remove the 15% built-in ranged haste that was added to hunters in WotLK
		// This lets us add haste spells back to quivers
		player->RemoveAura(89507);
		player->CastSpell(player, 89507, false);

	}
	void OnMapChanged(Player* player) override
	{

		// Remove the 15% built-in ranged haste that was added to hunters in WotLK
		// This lets us add haste spells back to quivers
		player->RemoveAura(89507);
		player->CastSpell(player, 89507, false);
		
	}
	void OnEquip(Player* player, Item* /*it*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) override
	{
		// Remove the 15% built-in ranged haste that was added to hunters in WotLK
		// This lets us add haste spells back to quivers
		player->RemoveAura(89507);
		player->CastSpell(player, 89507, false);
		
	}
	void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
	{
		// Remove the 15% built-in ranged haste that was added to hunters in WotLK
		// This lets us add haste spells back to quivers
		player->RemoveAura(89507);
		player->CastSpell(player, 89507, false);
		
	}

	//void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
    	void OnLevelChanged(Player* player, uint8 oldLevel) override
	{

		// Remove the 15% built-in ranged haste that was added to hunters in WotLK
		// This lets us add haste spells back to quivers
		player->RemoveAura(89507);
		player->CastSpell(player, 89507, false);

		uint8 level = player->GetLevel();

            	switch (level)
            	{
                	case 2:
                	{
                    		if (oldLevel < 2)
                    		{
					player->learnSpell(133); //Fireball (Mage)
					player->learnSpell(348); //Immolate (Warlock)
					player->learnSpell(403); //Lightning Bolt (Shaman)
					player->learnSpell(635); // Holy Light (pally)
					player->learnSpell(2050); //Lesser Heal (Priest)
					player->learnSpell(5185); //Healing Touch (Druid)
					player->learnSpell(331); //Healing Wave (Shaman)
					player->learnSpell(585); //Smite (Priest)
					player->learnSpell(2973); //Raptor Strike (Hunter)
					player->learnSpell(5176); //Wrath (Druid)
					player->learnSpell(686); //Shadowbolt (Warlock)
					//AddSpell{1804}, // Pick Lock (Rogue)
					//AddSpell{75}, //Auto Shot (hunter)
                    		}
                	}
                	break;
			
                	case 4:
                	{
                    		if (oldLevel < 4)
                    		{
                			player->learnSpell(20271); // Judgement of Light (Paladin)
                			player->learnSpell(8071); // Stoneskin Totem (Shaman)
					player->learnSpell(172); // Corruption (Warlock)
					player->learnSpell(116); //Frostbolt (Mage)
					player->learnSpell(1978); //Serpent Sting (hunter)
					player->learnSpell(2052); //Lesser Heal Rank 2 (Priest)
					player->learnSpell(8921); //Moonfire (Druid)
					player->learnSpell(774); //Rejuvenation (Druid)
					player->learnSpell(8042); //Earth Shock (Shaman)
					player->learnSpell(589); //Shadow Word: Pain (Priest)
					player->learnSpell(2484); //Earthbind Totem (Shaman)
                    		}
                	}
                	break;

                	case 6:
                	{
                    		if (oldLevel < 6)
                    		{
					player->learnSpell(1454); // Life Tap (Warlock)
              				player->learnSpell(639); // Holy Light Rank 2 (Paladin)
					player->learnSpell(1130); // Hunter's Mark (Hunter)
					player->learnSpell(17); // Power Word Shield (Priest)
					player->learnSpell(695); // Shadowbolt Rank 2 (Warlock)
					player->learnSpell(332); // Healing Wave Rank 2 (Shaman)
					player->learnSpell(591); // Smite Rank 2 (Priest)
					player->learnSpell(2136); // Fire Blast (Mage)
					player->learnSpell(143); //Fireball rank 2 (mage)
					player->learnSpell(5177); //Wrath rank 2 (druid)
					player->learnSpell(3044); //Arcane Shot (hunter)
                    		}
                	}
                	break;
			
                	case 8:
                	{
                    		if (oldLevel < 8)
                    		{
					player->learnSpell(586); // Fade (Priest)
					player->learnSpell(139); // Renew (Priest)
					player->learnSpell(1152); // Purify (Paladin)
					player->learnSpell(5730; // Stoneclaw Totem (Shaman)
					player->learnSpell(118); // Polymorph (mage)
					player->learnSpell(205); // Frostbolt rank 2 (mage)
					player->learnSpell(853); // Hammer of Justice (Paladin) // 1 min cooldown - Stuns the target for 3 sec and interrupts non-player spellcasting for 3 sec.
					player->learnSpell(529); // Lightning Bolt Rank 2 (Shaman)
					player->learnSpell(5116); // Concussive Shot (Hunter)
					player->lLearnSpell(5186); // Healing Touch Rank 2(Druid)
					player->learnSpell(8044); // Earth Shock Rank 2 (Shaman)
					player->learnSpell(5782); // Fear (warlock)
					player->learnSpell(5143); //Qrcane Missiles (mage)
					player->learnSpell(14260); //Raptor Strike Rank 2 (hunter)
					player->learnSpell(339); //Entangling Roots (Druid)
                    		}
                	}
                	break;

                	case 10:
                	{
                    		if (oldLevel < 10)
                    		{
		        		//AddSpell{6991}, // Feed Pet (Hunter)
					//AddSpell{1515}, // Tame Beast (Hunter)
					//AddSpell{883}, // Call Pet (Hunter)
					//AddSpell{982}, // Revive Pet (Hunter)
					player->learnSpell(5487); // Bear Form (Druid)
					player->learnSpell(1120); // Drain Soul (Warlock)
					player->learnSpell(355); // Taunt (Warrior)
					player->learnSpell(1058); // Rejuvernation Rank 2 (Druid)
					player->learnSpell(2053); // LEsser Heal Rank 3 (Priest)
					player->learnSpell(8050); // Flame Shock (Shaman)
					player->learnSpell(122); // Frost Nova (Mage)
					player->learnSpell(594); // Shadow Word: Pain Rank 2 (priest)
					player->learnSpell(6795); // Growl (Taunt - Druid)
					player->learnSpell(8092); // Mind Blast (Priest)
					player->learnSpell(707); // Immolate rank 2 (Warlock)
					player->learnSpell(8924); // Moonfire rank 2 (druid)
					player->learnSpell(2006); // Resurrection (priest)
					player->learnSpell(2641); // Dismiss Pet (hunter)
					player->learnSpell(3599); // Searing Totem (Shaman)
					player->learnSpell(6807); // Maul (Druid) - Bear Form
					player->learnSpell(99); // Demoralizing Roar (Druid) Bear form
					player->learnSpell(13549); //Serpent Sting Rank 2 (Hunter)
					//AddSpell{633}, //Lay on Hands(Paladin)
                    		}
                	}
                	break;

		}
	}

	void OnFirstLogin(Player* player) override
    	{
	player->AddItem(5175, 1); // Earth Totem
	player->AddItem(5176, 1); // Fire Totem
	player->AddItem(5177, 1); // Water Totem
	player->AddItem(5178, 1); // Air Totem
	}
    
};
  
// Add all scripts in one
void AddHardModePlayerScripts()
{
    new HardModePlayer();
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

