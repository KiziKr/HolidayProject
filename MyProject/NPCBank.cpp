// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCBank.h"
#include "Engine.h"


ANPCBank::ANPCBank()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> temp(TEXT("DataTable'/Game/Miscellaneous/DataTable/BankTable'"));
	ItemsTables = temp.Object;
}

void ANPCBank::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCBank::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "je passe");
	if (!PlayerInteract && InventoryUserWidget)
	{
		PlayerInteract = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (PlayerInteract)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "je passe bien la aussi");
			InventoryUserWidget->SetOwnerInventory(this);

			if (!OpensTheAccountOf(PlayerInteract->GetPlayerName()))
			{

			}
		}
	}
}

void ANPCBank::OpeningAnAccount(const FString &PlayerName, float price)
{
	if (!OpensTheAccountOf(PlayerName) && price > 100)
	{
		//FTableRowBank InitBank;
		//ItemsTables->AddRow(FName(*PlayerName), InitBank);

		//if (OpensTheAccountOf(PlayerName))
		//{
			//Retire largent au joueur
		//}
	}
}

bool ANPCBank::OpensTheAccountOf(const FString &PlayerName)
{	
	if (!ItemsTables || !InventoryUserWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "merde");
		return false;
	}

	if (TableInventoryBank = ItemsTables->FindRow<FTableRowBank>(FName(*PlayerName), FString()))
	{
		InventoryUserWidget->ShowInventoryUniform(TableInventoryBank->BankMap, 6);
		InventoryUserWidget->AddToViewport();
		return true;
	}

	return false;
}

void ANPCBank::RefreshAccount()
{
	if (TableInventoryBank && InventoryUserWidget)
	{
		InventoryUserWidget->ShowInventoryUniform(TableInventoryBank->BankMap, 6);
	}
}

void ANPCBank::GiveObjectToPlayer(int32 IDItem)
{
	if (!TableInventoryBank || IDItem < 0 || TableInventoryBank->BankMap.Num() < IDItem)
		return;

	if (ABagPlayer* BagPlayer = PlayerInteract->GetCarryingBag())
	{
		FTableRowInventory& Item = TableInventoryBank->BankMap[IDItem];

		if (BagPlayer->AddItem(Item, 1))
		{
			(Item.Quantity <= 1) ?
				TableInventoryBank->BankMap.RemoveAt(IDItem) :
				Item.Quantity--;

			if (BagPlayer->IsOpen())
			{
				BagPlayer->RefreshBag();
			}
		}
	}
}

void ANPCBank::CloseAccount()
{
	InventoryUserWidget->SetOwnerInventory(nullptr);
	InventoryUserWidget->RemoteInventory();
	PlayerInteract = nullptr;
	TableInventoryBank = nullptr;
}


/*ANPCBank::AddItem(const FTableRowInventory &item)
{

}*/
