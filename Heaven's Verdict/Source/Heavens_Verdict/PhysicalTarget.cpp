// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicalTarget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
// Sets default values
APhysicalTarget::APhysicalTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	//Creates the hitbox component
	mCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionSphere);

	mCollisionSphere->InitSphereRadius(50);

	mCollisionSphere->SetRelativeLocation(FVector(0, 0, 0));

	//This creates the static mesh component

	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	myMesh->SetupAttachment(RootComponent);

	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid"))).Get());


	//Sets it's relative location to zero so it ligns up with everything else
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	myMesh->SetRelativeLocation(FVector(0, 0, -50));

	mCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APhysicalTarget::OnOverlapBegin);

	RootComponent = mCollisionSphere;

	mCollisionSphere->ComponentTags.Add(FName("Target"));
}

// Called when the game starts or when spawned
void APhysicalTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicalTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicalTarget::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Hitbox")) {
		UE_LOG(LogTemp, Warning, TEXT("Got punched!"));
		Destroy();
	}
}
