// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hitbox.generated.h"

UCLASS()
class HEAVENS_VERDICT_API AHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitbox();
	UPROPERTY(EditAnywhere)
		class UBoxComponent* mCollisionBox;

	//Hitbox duration
	int hitboxDuration = 100;

	FTimerHandle countdownTimerHandle;

	void AdvanceTimer();

	void CountdownHasFinished();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
