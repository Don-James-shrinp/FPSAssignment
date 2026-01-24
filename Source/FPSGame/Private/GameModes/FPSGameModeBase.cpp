// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/FPSGameModeBase.h"

AFPSGameModeBase::AFPSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
