// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEquipment.h"
#include "PlayerCharacter.h"
#include "Engine.h"

APlayerEquipment::APlayerEquipment()
{
	PrimaryActorTick.bCanEverTick = false;
	mEquipped = false;
	bTheInteract = false;

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	EquipmentMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	EquipmentMesh->SetupAttachment(RootComponent);
}


void APlayerEquipment::BeginPlay()
{
	Super::BeginPlay();

	EnableCollision();
	beginPosition = FVector(0, 0, 0);
	beginRotation = FRotator(0, 0, 0);

}


void APlayerEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerEquipment::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isEquipped())
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (PlayerCharacter)
		{
			PlayerCharacter->EquipItem(this);
		}
	}
}

void APlayerEquipment::AttachToPlayer(USkeletalMeshComponent* Mesh, const FName &SocketName)
{
	/*if (Role == ROLE_Authority)
	{*/
		SetEquipped(true);
		DisableCollision();
		AttachToComponent(Mesh,
			FAttachmentTransformRules::KeepRelativeTransform,
			SocketName);
	/*}
	else
	{
		ServerAttachToPlayer(Mesh, SocketName);
	}*/
}


void APlayerEquipment::ServerAttachToPlayer_Implementation(USkeletalMeshComponent* Mesh,
	const FName &SocketName)
{
	AttachToPlayer(Mesh, SocketName);
}


bool APlayerEquipment::ServerAttachToPlayer_Validate(USkeletalMeshComponent* Mesh,
	const FName &SocketName)
{
	return true;
}


void APlayerEquipment::DetachFromPlayer(const FVector &NewLocation)
{
	if (Role == ROLE_Authority)
	{
		SetEquipped(false);
		EnableCollision();
		DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		SetActorLocation(NewLocation);
	}
	else
	{
		ServerDetachFromPlayer(NewLocation);
	}
}


void APlayerEquipment::ServerDetachFromPlayer_Implementation(const FVector &NewLocation)
{
	DetachFromPlayer(NewLocation);
}


bool APlayerEquipment::ServerDetachFromPlayer_Validate(const FVector &NewLocation)
{
	return true;
}


void APlayerEquipment::EnableCollision()
{
	if (BoxCollider != nullptr)
	{
		BoxCollider->SetSimulatePhysics(true);
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}


void APlayerEquipment::DisableCollision()
{
	if (BoxCollider != nullptr)
	{
		BoxCollider->SetSimulatePhysics(false);
		EquipmentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		EquipmentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		EquipmentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		BoxCollider->SetRelativeLocation(beginPosition);
		BoxCollider->SetRelativeRotation(beginRotation);
	}
}