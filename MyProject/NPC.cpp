// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Engine.h"

ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlayerInteract = nullptr;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC && wInventoryUserWidget)
	{
		InventoryUserWidget = CreateWidget<UInventoryUserWidget>(PC, wInventoryUserWidget);
		InventoryUserWidget->SetOwnerInventory(this);
	}
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC::OnGameObject(AActor * Target, FKey ButtonPressed)
{
	Super::OnGameObject(Target, ButtonPressed);

	/* if (!PlayerInteract && InventoryUserWidget)
	{
		PlayerInteract = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}*/
}