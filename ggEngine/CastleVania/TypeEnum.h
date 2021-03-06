#pragma once
enum ObjectType {
	ObjectType_Normal = 0, ObjectType_Static,
	ObjectType_Door, ObjectType_AI6, ObjectType_AI7,
	ObjectType_LadderDownLeft, ObjectType_LadderUpLeft, ObjectType_LadderDownRight, ObjectType_LadderUpRight,
	ObjectType_Candle, ObjectType_BreakableTileBrick,
	ObjectType_LevelTwoBrick ,ObjectType_Item, ObjectType_Simon , ObjectType_Weapon, 
	ObjectType_Enemy,
	ObjectType_SubWeapon};

enum FacingDirection { FacingDirection_Left, FacingDirection_Right};