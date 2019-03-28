// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stage.generated.h"

UCLASS()
class HEAVENS_VERDICT_API AStage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//The Mesh component that is seen by the playe
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* myMesh;

	//The Hitbox that is invisible to the player that I care about
	UPROPERTY(EditAnywhere)
	class UBoxComponent* mCollisionBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
