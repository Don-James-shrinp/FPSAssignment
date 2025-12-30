// Origin OvO CopyRight Reserved

#pragma once

#include "NativeGameplayTags.h"

/**
 * 
 */
namespace FPSGameplayTags
{
	/** Input Tags **/
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Rifle);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Rifle);
	
	/** Player Tags **/
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Rifle);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Rifle);

	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Rifle);

	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Rifle);
	FPSGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Rifle);
}