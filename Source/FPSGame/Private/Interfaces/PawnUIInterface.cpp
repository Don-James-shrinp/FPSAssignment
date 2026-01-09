// Origin OvO CopyRight Reserved


#include "Interfaces/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UPawnUIComponent* IPawnUIInterface::GetPawnUIComponent() const
{
	return nullptr;
}

UPlayerUIComponent* IPawnUIInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}


