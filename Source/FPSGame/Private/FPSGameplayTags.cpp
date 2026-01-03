// Origin OvO CopyRight Reserved


#include "FPSGameplayTags.h"

namespace FPSGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Fire, "InputTag.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Rifle, "InputTag.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Rifle, "InputTag.Unequip.Rifle");

	/** Player Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rifle, "Player.Ability.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Rifle, "Player.Ability.Unequip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_DryFire_Rifle, "Player.Ability.DryFire.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AimFire_Rifle, "Player.Ability.AimFire.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Aim_Rifle, "Player.Ability.Aim.Rifle");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rifle, "Player.Weapon.Rifle");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Rifle, "Player.Event.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Rifle, "Player.Event.Unequip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Bullet_Hit, "Player.Event.Bullet.Hit");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Aim, "Player.Status.Aim");
}