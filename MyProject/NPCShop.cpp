// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCShop.h"
#include "Engine.h"


ANPCShop::ANPCShop()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> temp(TEXT("DataTable'/Game/ShopTable'"));
	ItemsTables = temp.Object;

	bInteract = false;
}


void ANPCShop::BeginPlay()
{
	Super::BeginPlay();

	/*APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC && wInventoryUserWidget)
	{
		InventoryUserWidget = CreateWidget<UInventoryUserWidget>(PC, wInventoryUserWidget);
	}
	*/
}


void ANPCShop::OnGameObject(AActor* Target, FKey ButtonPressed)
{
	Super::OnGameObject(Target, ButtonPressed);

	/*if (!bInteract && ShopWidget)
	{
		//InventoryUserWidget->ShowShop();

		bInteract = true;
	}*/
}


void ANPCShop::OpenTheShop()
{

}


void ANPCShop::CloseTheShop()
{
	bInteract = false;
}