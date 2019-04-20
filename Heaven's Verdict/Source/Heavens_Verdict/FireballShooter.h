// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireballShooter.generated.h"

UCLASS()
class HEAVENS_VERDICT_API AFireballShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireballShooter();
	
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent *myMesh;

	UPROPERTY(EditAnywhere)
		class USphereComponent* mCollisionSphere;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AFireBall> toSpawn;

	UPROPERTY(EditAnywhere)
		FVector targetLocation;

	UPROPERTY(EditAnywhere)
		FVector fireballSpawnPoint;

	//Checks to see if the fireball is dead.
	bool fireballDead;

	//Meant to mimic how the fireball timer works
	int fireballLifeSpan = 200;

	FTimerHandle countdownTimerHandle;

	void AdvanceTimer();

	void CountdownHasFinished();

	bool GetFireballStatus();

	//Some filler variable to save me some time.
	float defaultValue = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void shootFireball();

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

};