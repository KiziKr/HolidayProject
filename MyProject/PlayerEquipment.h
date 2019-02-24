// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameObject.h"
#include "PlayerEquipment.generated.h"

/**
*/

UCLASS()
class MYPROJECT_API APlayerEquipment : public AGameObject
{
	GENERATED_BODY()

	bool mEquipped;
	FVector beginPosition;
	FRotator beginRotation;

public:
	// Sets default values for this actor's properties
	APlayerEquipment();

	UFUNCTION()
	void AttachToPlayer(USkeletalMeshComponent* Mesh, const FName &SocketName);

	UFUNCTION()
	void DetachFromPlayer(const FVector &NewLocation);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAttachToPlayer(USkeletalMeshComponent* Mesh, const FName &SocketName);

	virtual void ServerAttachToPlayer_Implementation(USkeletalMeshComponent* Mesh, const FName &SocketName);
	virtual bool ServerAttachToPlayer_Validate(USkeletalMeshComponent* Mesh, const FName &SocketName);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDetachFromPlayer(const FVector &NewLocation);

	virtual void ServerDetachFromPlayer_Implementation(const FVector &NewLocation);
	virtual bool ServerDetachFromPlayer_Validate(const FVector &NewLocation);

	bool isEquipped() const { return mEquipped; }
	void SetEquipped(bool value) { mEquipped = value; }

	UFUNCTION(BlueprintCallable, category=Item)
	FTableRowInventory GetInfosItem()
	{
		return Item;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	void SetInfosItem(const FTableRowInventory& NewItemInfos)
	{ 
		Item = NewItemInfos; 
	}

	UFUNCTION(BlueprintCallable, category = Item)
	int32 GetIdItem()
	{
		return Item.ItemData.id;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	FString GetNameItem()
	{
		return Item.ItemData.name;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	UTexture2D* GetSpriteItem()
	{
		return Item.ItemData.sprite;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	TEnumAsByte<ItemCategory> GetCategoryItem()
	{
		return Item.ItemData.category;
	}

	UFUNCTION(BlueprintCallable, category = Item)
	int32 GetWeightItem()
	{
		return Item.ItemData.weight;
	}

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Equipment")
	FTableRowInventory Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	void EnableCollision();

	UFUNCTION()
	virtual void DisableCollision();

	bool bTheInteract;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
