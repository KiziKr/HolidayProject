// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObject.h"
#include "Engine.h"


AGameObject::AGameObject()
{
	bInteract = false;

	PrimaryActorTick.bCanEverTick = false;
	OnReleased.AddDynamic(this, &AGameObject::OnGameObject);
	OnBeginCursorOver.AddDynamic(this, &AGameObject::CustomOnBeginMouseOver);
	OnEndCursorOver.AddDynamic(this, &AGameObject::CustomOnEndMouseOver);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));
	BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BoxCollider->bGenerateOverlapEvents = true;
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AGameObject::OnPlayerEnterPickupBox);
	RootComponent = BoxCollider;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMeshComponent"));
	SkeletalMesh->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("Arrow Component"));
	ArrowComponent->SetupAttachment(RootComponent);
}


void AGameObject::BeginPlay()
{
	Super::BeginPlay();
	
}


void AGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGameObject::OnGameObject(AActor* Target, FKey ButtonPressed)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "KOI ?");
}


void AGameObject::CustomOnBeginMouseOver(AActor* TouchedComponent)
{
	if (EquipmentMesh != nullptr)
	{
		EquipmentMesh->SetRenderCustomDepth(true);
	}

	if (SkeletalMesh != nullptr)
	{
		SkeletalMesh->SetRenderCustomDepth(true);
	}
}


void AGameObject::CustomOnEndMouseOver(AActor* TouchedComponent)
{
	if (EquipmentMesh != nullptr)
	{
		EquipmentMesh->SetRenderCustomDepth(false);
	}

	if (SkeletalMesh != nullptr)
	{
		SkeletalMesh->SetRenderCustomDepth(false);
	}

}


void AGameObject::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, OtherActor->GetClass()->GetFName().ToString());
	}
}

