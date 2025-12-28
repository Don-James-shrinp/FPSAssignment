// Origin OvO CopyRight Reserved


#include "FPSGameplayTags.h"

namespace FPSGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Rifle, "InputTag.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Rifle, "InputTag.Unequip.Rifle");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Equip_Rifle, "Player.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Unequip_Rifle, "Player.Unequip.Rifle");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rifle, "Player.Weapon.Rifle");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Rifle, "Player.Event.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Rifle, "Player.Event.Unequip.Rifle");
}