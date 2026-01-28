#pragma once
UENUM()
enum class EFPSSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EFPSConfirmType : uint8
{
	Yes,
	No
};

UENUM(BlueprintType)
enum class ECompetitionGameState : uint8
{
	BeforeSpawningNewWave,  //  生成下一波前，用于进行一些准备工作
	SpawningWave,	//  生成新一波的敌人
	InBattle,   //  生成完后处于战斗状态
	WaveComplete,  //  当前波次结束
	AllWaveDone,	//  所有波次结束
	PlayerDied
};