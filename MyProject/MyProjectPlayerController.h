// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, category=test)
	bool MouseIsMoving();
};
