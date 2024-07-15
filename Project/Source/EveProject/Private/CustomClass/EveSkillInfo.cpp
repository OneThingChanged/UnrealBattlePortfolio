// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomClass/InfoClass/EveSkillInfo.h"

#include "Data/FCharacterSkillTable.h"

void UEveSkillInfo::EveTick(float DeltaTime)
{
	if (AbleToUseSkill)
		return;

	CurCoolTime -= DeltaTime;
	if (CurCoolTime <= 0)
	{
		CurCoolTime = 0;
		AbleToUseSkill = true;
		FOnSetAbleToUseSkillAction.Broadcast(this);
	}
	FOnSkillTickAction.Broadcast(this);
}

void UEveSkillInfo::SetData(FCharacterSkillTable* SkillInfo)
{
	MaxCoolTime = SkillInfo->CoolTime;
	AbleToUseSkill = true;
	Data = SkillInfo;
}
