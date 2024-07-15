// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogZ, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSession, Log, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_CALLINFO_S(Category, Verbosity) UE_LOG(Category, Verbosity, TEXT("%s"), *LOG_CALLINFO)
#define Z_LOG(Category, Verbosity, Format, ...) UE_LOG(Category, Verbosity, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define Z_SCREEN_LOG(Time, Color, Format, ...) (GEngine->AddOnScreenDebugMessage(INDEX_NONE, Time, Color, *FString::Printf(Format, ##__VA_ARGS__)))
#define Z_LOG_NM(Category, Verbosity, Format, ...)\
FString Prefix = TEXT("server");\
if (GetWorld()->GetNetMode() == NM_Client)\
{\
if (GetWorld()->WorldType == EWorldType::Type::PIE)\
{\
Prefix = FString::Printf(TEXT("Client - %d"), GPlayInEditorID - 1);\
}\
else\
{\
Prefix = FString::Printf(TEXT("%s"), FPlatformProcess::GetCurrentProcessId());\
}\
} \
UE_LOG(Category, Verbosity, TEXT("%s (%s) : %s"), *LOG_CALLINFO, *Prefix, *FString::Printf(Format, ##__VA_ARGS__))\
