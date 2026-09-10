// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EmotionData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEmotionLine
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	USoundBase* Sound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	FText Subtitle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	float VolumeMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	float PitchMultiplier = 1.0f;
};

USTRUCT(BlueprintType)
struct FSingleEmotion
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	TArray<FEmotionLine> Lines;
};

UCLASS()
class SOUND_API UEmotionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion")
	TArray<FSingleEmotion> SingleEmotions;
};
