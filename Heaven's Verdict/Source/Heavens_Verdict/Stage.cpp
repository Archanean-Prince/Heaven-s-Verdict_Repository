// Fill out your copyright notice in the Description page of Project Settings.

#include "Stage.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AStage::AStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Creates the root componenent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//Creates the hitbox component
	mCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionBox);

	//Creates the collision box to be of a specific size
	mCollisionBox->InitBoxExtent(FVector(100, 250, 20));
	//and places it in a specific area
	mCollisionBox->SetRelativeLocation(FVector(0, 0, 60));
	//This creates the static mesh component
	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	
	//Then attaches it to the root component. Order is done is still very important!
	myMesh->SetupAttachment(RootComponent);
	//Fetches the default cube object from my files
	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"))).Get());

	//Sets it's relative location to zero so it ligns up with everything else
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	//Moves it slightly downards to better fit it
	myMesh->SetRelativeLocation(FVector(0, 0, -15));

	//Stretches it accordingly to be more flat and better fit the whole "stage" idea
	myMesh->SetRelativeScale3D(FVector(2.0,5, 0.4));
	//Gives it the tag of floor so it's able to be recognized as such
	mCollisionBox->ComponentTags.Add(FName("Floor"));

	//Makes the root component equal to the collison box. This MUST go last.
	RootComponent = mCollisionBox;
}


// Called when the game starts or when spawned
void AStage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

