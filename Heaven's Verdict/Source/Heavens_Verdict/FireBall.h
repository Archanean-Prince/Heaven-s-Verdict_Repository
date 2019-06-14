// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

UCLASS()
class HEAVENS_VERDICT_API AFireBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireBall();

	//The current velocity of the fireball
	FVector currentVelocity;

	//Some filler variable to save me some time.
	float defaultValue = 1;

	bool fireballDead;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The Mesh Component 
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent *myMesh;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* mCollisionBox;

	int fireballLifeSpan = 200;

	void AdvanceTimer();

	void CountDownHasFinished();

	FTimerHandle countdownTimerHandle;

	bool isActive = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetFireballStatus();

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
};
