// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicalTarget.generated.h"

UCLASS()
class HEAVENS_VERDICT_API APhysicalTarget : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APhysicalTarget();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent *myMesh;

	UPROPERTY(EditAnywhere)
		class USphereComponent* mCollisionSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
};
