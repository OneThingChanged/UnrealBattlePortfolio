#pragma once

UENUM()
enum class ECharState : uint16
{
	None = 0,
	Idle = 1,
	Death = 3, 
	Jumping = 11, 
	Dash = 21,
	Hitting = 31,
	Groggy = 41,
	UltimateSkill = 101,
	NormalAttack = 111,
	Skill1 = 121,
};


UENUM()
enum class ECharAction : uint16
{
	None = 0,
	IdleWalkRun,
	Death,
	Jumping = 11,
	Dash = 21,
	BackDash = 22,
	HitReaction = 31,
	HitKnockDown = 32,
	HitKnockBack = 33,
	Groggy = 41,
	UltimateSkill = 101,
	NormalAttack1 = 111, 
	NormalAttack2 = 112, 
	NormalAttack3 = 113, 
	NormalAttack4 = 114, 
	Skill1 = 121,
	Skill2,
	Hitting1, //히트모션
	Hitting2, //넉백히트모션
	Hitting3, //넉다운히트모션
	End,
};

UENUM()
enum class ESkillType : uint16
{
	None = 0,
	Dash = 21,
	BackDash = 22,
	UltimateSkill = 101,
	NormalAttack01 = 111,
	NormalAttack02 = 112,
	NormalAttack03 = 113,
	NormalAttack04 = 114,
	NormalAttack05 = 115,
	NormalAttack06 = 116,
	NormalAttack07 = 117,
	NormalAttack08 = 118,
	NormalAttack09 = 119,
	Skill1 = 121,
	Skill2 = 131,
	Max,
};

UENUM()
enum class EEveSideType : uint16
{
	None = 0,
	Player = 1,
	Supporter = 2,
	Enemy = 3,
	Max,
};

UENUM()
enum class EEveCombatType : uint16
{
	None = 0,
	Fire = 1,
	Wind = 2,
	Lighting = 3,
	Water = 4,
	Physical = 5,
	Imaginary = 6,
	Max,
};

UENUM()
enum class EEveOriginType : uint16
{
	None = 0,
	Bio = 1,
	Mecha = 2,
	Source = 3,
	Max,
};

UENUM()
enum class EEveUnitType : uint16
{
	None = 0,
	Dual = 1,
	GreatSword = 2,
	Gunner = 3,
	Assassin = 4,
	Mage = 5,
	Katana = 6,
	Reira = 10,
	Pei = 11,
	Proto1 = 1001,
	ProtoBoss = 2001,
	Max,
};

UENUM()
enum class EEveStatType : uint16
{
	None = 0,
	Health = 1,
	Stamina = 3,
	Mana = 4,
	Armor = 101,
	Damage = 102,
	HitRecovery = 110,

	//Enemy
	CombatGauge = 201,
	CombatRecoveryTime = 202,
};

UENUM(BlueprintType)
enum class EDamageAreaType : uint8
{
	None = 0,
	Area = 1,
	Socket = 2,
	SectorForm = 3,
};

UENUM(BlueprintType)
enum class EEveCameraRotationMode : uint8
{
	None = 0,
	OrientToCamera = 1,
	HardLockEnemy = 2,
	DirectToMovement = 3,
};
UENUM()
enum class EEveControllerType : uint8
{
	None = 0,
	Player = 1,
	Enemy = 2,
};

UENUM(BlueprintType)
enum class EEveAIState : uint8
{
	Idle = 0,
	Chase = 1,
	Patrol = 2,
	Death = 3,
	NormalAttack = 4,
};

UENUM()
enum class EEveAIPatrolPathType : uint16
{
	None = 0,
	Path1 = 1,
	Path2 = 2,
	Path3 = 3,
	Path4 = 4,
	Path5 = 5,
	Path6 = 6,
	Path7 = 7,
	Path8 = 8,
	Path9 = 9,
	Path10 = 10,
	Path11 = 11,
};

UENUM()
enum class EEveDirectionType : uint8
{
	Forward = 0,
	Reverse = 1,
};

