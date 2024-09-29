// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealGroqBPLibrary.generated.h"

UENUM(BlueprintType)
enum class EGroqModel : uint8
{
	Gemma7bIt UMETA(DisplayName = "gemma-7b-it"),
	Gemma2_9bIt UMETA(DisplayName = "gemma-2-9b-it")
};

// Declare delegates for callbacks
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccess, const FString&, Result);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFailure, const FString&, ErrorMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnProgress, float, Progress);

UCLASS()
class UUnrealGroqBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "UnrealGroq sample test testing"), Category = "UnrealGroqTesting")
	static float UnrealGroqSampleFunction(float Param);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Chat Message To Groq", Keywords = "UnrealGroq chat message"), Category = "UnrealGroq")
	static FString SendChatMessageToGroq(const FString& ApiKey, const FString& UserMessage, EGroqModel Model, FOnSuccess OnSuccess, FOnFailure OnFailure, FOnProgress OnProgress);
};
