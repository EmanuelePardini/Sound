// Fill out your copyright notice in the Description page of Project Settings.

#include "Sound/Public/EmotionComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEmotionComponent::UEmotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SetSubtitlesEnabled(true);
	ScheduleNext();
}


// Called every frame
void UEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEmotionComponent::ScheduleNext()
{
	const float Delay = FMath::FRandRange(MinInterval, MaxInterval);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UEmotionComponent::TimerFired, Delay);
}

void UEmotionComponent::TimerFired()
{
	TriggerRandomEmotion();
	ScheduleNext();
}

void UEmotionComponent::TriggerRandomEmotion()
{
	if (!EmotionData || EmotionData->SingleEmotions.IsEmpty())
		return;
	
	TArray<FSingleEmotion> Emotions = EmotionData->SingleEmotions;
	const FSingleEmotion Emotion = Emotions[FMath::RandRange(0, Emotions.Num() - 1)];
	const FEmotionLine Line = Emotion.Lines[FMath::RandRange(0, Emotion.Lines.Num() - 1)];
	
	if (!Line.Sound) return;
	
	if (USoundWave* Wave = Cast<USoundWave>(Line.Sound))
	{
		Wave->Subtitles.Empty();
		
		FSubtitleCue Cue;
		Cue.Text = Line.Subtitle;
		Cue.Time = 0.f;
		Wave->Subtitles.Add(Cue);
	}
	
	// if (Fire)
	// {
	// 	UGameplayStatics::PlaySound2D(this, Line.Sound, Line.VolumeMultiplier, Line.PitchMultiplier);
	// }
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "Entered");
	StopCurrentLine();
	
	ActiveVoice = UGameplayStatics::SpawnSound2D(this, Line.Sound, Line.VolumeMultiplier, Line.PitchMultiplier,
		0.f, nullptr, false, false);
	
	ActiveVoice->OnAudioFinished.AddDynamic(this, &UEmotionComponent::StopCurrentLine);
	
	
}

void UEmotionComponent::StopCurrentLine()
{
	if (ActiveVoice)
	{
		ActiveVoice->OnAudioFinished.RemoveDynamic(this, &UEmotionComponent::StopCurrentLine);
		ActiveVoice->Stop();
		ActiveVoice->DestroyComponent();
	}
	
	ActiveVoice = nullptr;
}

