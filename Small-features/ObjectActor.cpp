// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AObjectActor::AObjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AObjectActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayEffect();
}

void AObjectActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpInfo, GetActorLocation());
}

// Called every frame
void AObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) {
		PlayEffect();
		MyCharacter->bIsCarry = true;
		Destroy();
	}
	
}

