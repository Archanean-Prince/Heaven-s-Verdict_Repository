// Fill out your copyright notice in the Description page of Project Settings.

#include "WinArea.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
AWinArea::AWinArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	//Creates the hitbox component
	mCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionSphere);

	mCollisionSphere->InitSphereRadius(80);

	mCollisionSphere->SetRelativeLocation(FVector(0, 0, 0));

	//This creates the static mesh component

	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	myMesh->SetupAttachment(RootComponent);

	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"))).Get());


	//Sets it's relative location to zero so it ligns up with everything else
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	myMesh->SetRelativeLocation(FVector(0, 0, -50));

	mCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWinArea::OnOverlapBegin);

	RootComponent = mCollisionSphere;

	mCollisionSphere->ComponentTags.Add(FName("Win!"));
}

// Called when the game starts or when spawned
void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AWinArea::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Player")) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerCollided"));
		UWorld* currentWorld=GetWorld();
		FString currentWorldName = currentWorld->GetMapName();
		//UE_LOG(LogTemp, Warning, TEXT("%s"),*currentWorldName);
		if (currentWorldName=="UEDPIE_0_BasicMovement") {
			UE_LOG(LogTemp, Warning, TEXT("We in world one"));
			UGameplayStatics::OpenLevel(GetWorld(),"/Game/StarterContent/Maps/BasicMovement2.umap");
		}
	}
}

