// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EmotionData.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "EmotionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOUND_API UEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEmotionComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Emotion")
	UEmotionData* EmotionData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Emotion")
	float MinInterval = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Emotion")
	float MaxInterval = 9.f;
	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Emotion")
	bool Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Emotion")
	UAudioComponent* ActiveVoice;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void ScheduleNext();
	UFUNCTION()
	void TimerFired();
	UFUNCTION()
	void TriggerRandomEmotion();
	UFUNCTION()
	void StopCurrentLine();
};
