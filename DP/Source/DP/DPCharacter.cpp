// Copyright Epic Games, Inc. All Rights Reserved.

#include "DPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////
// ADPCharacter

ADPCharacter::ADPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	Inventory = CreateDefaultSubobject<UDPInventoryComponent>(TEXT("Inventory"));
	Inventory->Capacity = 20;
	
	Health = 100.f;
	 
	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	collectionRange->AttachTo(RootComponent);
	collectionRange->SetSphereRadius(100.0f);
}

void ADPCharacter::UseItem(class UItem* Item)
{
	if(Item)
	{
		Item->Use(this);
		Item->OnUse(this);
	}
}

void ADPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(wielded)
	{
		wielded->SetActorHiddenInGame(true);
	}

	//// Init MyBag Widget
	//FString WidgetMyBagLoadPath = FString(TEXT("/Game/UI/MyBag.MyBag_C"));

	//TSubclassOf<UMyBagWidget> MyBagWidgetClass = LoadClass<UMyBagWidget>(NULL, *WidgetMyBagLoadPath);
	//MyBagUI = CreateWidget<UMyBagWidget>(GetWorld(), MyBagWidgetClass);

	// Add HealthBar Widget
	FString WidgetHealthBarLoadPath = FString(TEXT("/Game/UI/Health_Widget.Health_Widget_C"));
	TSubclassOf<UHealthWidget> HealthBarWidgetClass = LoadClass<UHealthWidget>(NULL, *WidgetHealthBarLoadPath);
	HealthBarUI = CreateWidget<UHealthWidget>(GetWorld(), HealthBarWidgetClass);
	HealthBarUI->AddToViewport();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ADPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADPCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADPCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADPCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADPCharacter::OnResetVR);

	//PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ADPCharacter::Interact);
	
	//PlayerInputComponent->BindAction("OpenBag", IE_Pressed, this, &ADPCharacter::OpenBag);
}


void ADPCharacter::Interact()
{
	//TArray<AActor*> inRangeItems;
	//collectionRange->GetOverlappingActors(inRangeItems);

	//for(int i = 0; i < inRangeItems.Num(); i++)
	//{
	//	AMyItemPickup* const item = Cast<AMyItemPickup>(inRangeItems[i]);
	//	if(item && item->GetActive())
	//	{
	//		item->Interacted();
	//		if(wielded)
	//		{
	//			wielded->SetActorHiddenInGame(false);
	//		}
	//	}
	//}
}

void ADPCharacter::OpenBag()
{
	//if (MyBagUI != nullptr)
	//{
	//	if(MyBagUI->IsInViewport() == false){
	//		MyBagUI->AddToViewport();
	//	}
	//	
	//	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//	//playerController->SetInputMode()
	//	playerController->bShowMouseCursor = true;
	//}
}

void ADPCharacter::OnResetVR()
{
	// If DP is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in DP.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADPCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADPCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADPCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADPCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
