// Fill out your copyright notice in the Description page of Project Settings.


#include "ListenerPawn.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"
#include "ROSIntegration/Public/geometry_msgs/Twist.h"
#include "C:/Users/josip/Documents/Unreal Projects/Spaceship/Source/Spaceship/SpaceshipPawn.h"
// Sets default values
AListenerPawn::AListenerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AListenerPawn::BeginPlay()
{
	Super::BeginPlay();
	//LISTENER
	// Initialize a topic
	UTopic* ExampleTopicSub = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinstSub = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	ExampleTopicSub->Init(rosinstSub->ROSIntegrationCore, TEXT("/key_vel"), TEXT("geometry_msgs/Twist"));

	// Create a std::function callback object
	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [](TSharedPtr<FROSBaseMsg> msg) -> void
	{
		auto Concrete = StaticCastSharedPtr<ROSMessages::geometry_msgs::Twist>(msg);
		if (Concrete.IsValid())
		{
			for (TObjectIterator<ASpaceshipPawn> Itr; Itr; ++Itr)
			{
				if (Itr->IsA(ASpaceshipPawn::StaticClass()))
				{
					ASpaceshipPawn* actorClass = *Itr;
					actorClass->MoveUpInput(Concrete->linear.x);
					actorClass->MoveRightInput(-1*(Concrete->angular.z));
				}
			}
			//UE_LOG(LogTemp, Log, TEXT("Linear: %f %f %f"), Concrete->linear.x, Concrete->linear.y, Concrete->linear.z);
			//UE_LOG(LogTemp, Log, TEXT("Angular: %f %f %f"), Concrete->angular.x, Concrete->angular.y, Concrete->angular.z);
		}
		return;
	};

	// Subscribe to the topic
	ExampleTopicSub->Subscribe(SubscribeCallback);
	
}

// Called every frame
void AListenerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AListenerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

