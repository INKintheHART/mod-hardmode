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
					player->LearnSpell(133); //Fireball (Mage)
					player->LearnSpell(348); //Immolate (Warlock)
					player->LearnSpell(403); //Lightning Bolt (Shaman)
					player->LearnSpell(635); // Holy Light (pally)
					player->LearnSpell(2050); //Lesser Heal (Priest)
					player->LearnSpell(5185); //Healing Touch (Druid)
					player->LearnSpell(331); //Healing Wave (Shaman)
					player->LearnSpell(585); //Smite (Priest)
					player->LearnSpell(2973); //Raptor Strike (Hunter)
					player->LearnSpell(5176); //Wrath (Druid)
					player->LearnSpell(686); //Shadowbolt (Warlock)
					//AddSpell{1804}, // Pick Lock (Rogue)
					//AddSpell{75}, //Auto Shot (hunter)
                    		}
                	}
                	break;
			
                	case 4:
                	{
                    		if (oldLevel < 4)
                    		{
                			player->LearnSpell(20271); // Judgement of Light (Paladin)
                			player->LearnSpell(8071); // Stoneskin Totem (Shaman)
					player->LearnSpell(172); // Corruption (Warlock)
					player->LearnSpell(116); //Frostbolt (Mage)
					player->LearnSpell(1978); //Serpent Sting (hunter)
					player->LearnSpell(2052); //Lesser Heal Rank 2 (Priest)
					player->LearnSpell(8921); //Moonfire (Druid)
					player->LearnSpell(774); //Rejuvenation (Druid)
					player->LearnSpell(8042); //Earth Shock (Shaman)
					player->LearnSpell(589); //Shadow Word: Pain (Priest)
					player->LearnSpell(2484); //Earthbind Totem (Shaman)
                    		}
                	}
                	break;

                	case 6:
                	{
                    		if (oldLevel < 6)
                    		{
					player->LearnSpell(1454); // Life Tap (Warlock)
              				player->LearnSpell(639); // Holy Light Rank 2 (Paladin)
					player->LearnSpell(1130); // Hunter's Mark (Hunter)
					player->LearnSpell(17); // Power Word Shield (Priest)
					player->LearnSpell(695); // Shadowbolt Rank 2 (Warlock)
					player->LearnSpell(332); // Healing Wave Rank 2 (Shaman)
					player->LearnSpell(591); // Smite Rank 2 (Priest)
					player->LearnSpell(2136); // Fire Blast (Mage)
					player->LearnSpell(143); //Fireball rank 2 (mage)
					player->LearnSpell(5177); //Wrath rank 2 (druid)
					player->LearnSpell(3044); //Arcane Shot (hunter)
                    		}
                	}
                	break;
			
                	case 8:
                	{
                    		if (oldLevel < 8)
                    		{
					player->LearnSpell(586); // Fade (Priest)
					player->LearnSpell(139); // Renew (Priest)
					player->LearnSpell(1152); // Purify (Paladin)
					player->LearnSpell(5730; // Stoneclaw Totem (Shaman)
					player->LearnSpell(118); // Polymorph (mage)
					player->LearnSpell(205); // Frostbolt rank 2 (mage)
					player->LearnSpell(853); // Hammer of Justice (Paladin) // 1 min cooldown - Stuns the target for 3 sec and interrupts non-player spellcasting for 3 sec.
					player->LearnSpell(529); // Lightning Bolt Rank 2 (Shaman)
					player->LearnSpell(5116); // Concussive Shot (Hunter)
					player->ALearnSpell(5186); // Healing Touch Rank 2(Druid)
					player->LearnSpell(8044); // Earth Shock Rank 2 (Shaman)
					player->LearnSpell(5782); // Fear (warlock)
					player->LearnSpell(5143); //Qrcane Missiles (mage)
					player->LearnSpell(14260); //Raptor Strike Rank 2 (hunter)
					player->LearnSpell(339); //Entangling Roots (Druid)
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
					player->LearnSpell(5487); // Bear Form (Druid)
					player->LearnSpell(1120); // Drain Soul (Warlock)
					player->LearnSpell(355); // Taunt (Warrior)
					player->LearnSpell(1058); // Rejuvernation Rank 2 (Druid)
					player->LearnSpell(2053); // LEsser Heal Rank 3 (Priest)
					player->LearnSpell(8050); // Flame Shock (Shaman)
					player->LearnSpell(122); // Frost Nova (Mage)
					player->LearnSpell(594); // Shadow Word: Pain Rank 2 (priest)
					player->LearnSpell(6795); // Growl (Taunt - Druid)
					player->LearnSpell(8092); // Mind Blast (Priest)
					player->LearnSpell(707); // Immolate rank 2 (Warlock)
					player->LearnSpell(8924); // Moonfire rank 2 (druid)
					player->LearnSpell(2006); // Resurrection (priest)
					player->LearnSpell(2641); // Dismiss Pet (hunter)
					player->LearnSpell(3599); // Searing Totem (Shaman)
					player->LearnSpell(6807); // Maul (Druid) - Bear Form
					player->LearnSpell(99); // Demoralizing Roar (Druid) Bear form
					player->LearnSpell(13549); //Serpent Sting Rank 2 (Hunter)
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

