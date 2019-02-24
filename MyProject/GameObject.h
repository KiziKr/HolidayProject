// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameObject.generated.h"

UCLASS()
class MYPROJECT_API AGameObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Bag, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(Category = SkeletalMesh, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(Category = Bag, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	UPROPERTY(Category = Bag, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;

	bool bInteract;

	UFUNCTION()
	virtual void OnGameObject(AActor* Target, FKey ButtonPressed);

	UFUNCTION()
	virtual void CustomOnBeginMouseOver(AActor* TouchedComponent);

	UFUNCTION()
	virtual void CustomOnEndMouseOver(AActor* TouchedComponent);

	UFUNCTION()
	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
