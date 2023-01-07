// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SpaceObject.generated.h"

UCLASS()
class ASTRAX_API ASpaceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collider)
		USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
		float MovementSpeed;

	FORCEINLINE void SetMovementDirection(FVector direction)
	{
		m_MovementDirection = direction;
	}

	FORCEINLINE void SetXBorder(float xBorder)
	{
		m_XBorder = xBorder;
	}

	FORCEINLINE void SetYBorder(float yBorder)
	{
		m_YBorder = yBorder;
	}

private:
	FVector m_MovementDirection;
	float m_XBorder;
	float m_YBorder;
};
