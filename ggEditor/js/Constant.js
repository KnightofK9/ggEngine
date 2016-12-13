/**
 * Created by Knight of k9 on 12/11/2016.
 */
var Constant = new function () {
    //this.DEFAULT_URL = "http://localhost/ggEditor/";
    this.exportWidthHeightForSprite = false;
    this.DEFAULT_URL = "";
    this.RESOURCE_PATH = this.DEFAULT_URL + "Resource/Resources/";
    this.TILE_SET_PATH = this.RESOURCE_PATH + "TileSet/";
    this.STATIC_TILE_PATH = this.RESOURCE_PATH + "TileObject/";

    this.TILE_SET_DICT = {
        "level-2": {
            name: this.TILE_SET_PATH + "level-2.png",
            json: "level-2.json",
            width: 64,
            height: 256,
            cellWidth: 16,
            cellHeight: 16,
            numberOfCellPerRow: 4,
            numberOfCellPerColumn: 16
        },
        "level-3": {
            name: this.TILE_SET_PATH + "level-3.png",
            json: "level-3.json",
            width: 64,
            height: 368,
            cellWidth: 16,
            cellHeight: 16,
            numberOfCellPerRow: 4,
            numberOfCellPerColumn: 23
        }
    };
    this.CHARACTER_DICT = {
        "char-simon": {
            name: "Resource/Resources/Character/simon.png",
            type: "SpriteAnimation",
            width: 45,
            height: 50
        }
    };
    this.STATIC_TILE_DICT = {
        "TileBrick": {
            name: this.STATIC_TILE_PATH + "TileBrick.png"
        },
        "TileLadderDownLeft": {
            name: this.STATIC_TILE_PATH + "TileLadderDownLeft.png"
        },
        "TileLadderUpRight": {
            name: this.STATIC_TILE_PATH + "TileLadderUpRight.png"
        },
        "TileLadderDownRight": {
            name: this.STATIC_TILE_PATH + "TileLadderDownRight.png"
        },
        "TileLadderUpLeft": {
            name: this.STATIC_TILE_PATH + "TileLadderUpLeft.png"
        }

    };
    this.ENEMY_DICT = {
        "AxeKnight": {
            name: this.RESOURCE_PATH + "AxeKnight.png",
            frameWidth: 16,
            frameHeight: 32,
            numberOfFrame: 3
        },
        "BatEnemy": {
            name: this.RESOURCE_PATH + "BatEnemy.png",
            frameWidth: 16,
            frameHeight: 16,
            numberOfFrame: 4
        },
        "BonePillar": {
            name: this.RESOURCE_PATH + "BonePillar.png",
            frameWidth: 16,
            frameHeight: 16,
            numberOfFrame: 4
        },
        "Boss": {
            name: this.RESOURCE_PATH + "Boss.png",
            frameWidth: 32,
            frameHeight: 32,
            numberOfFrame: 4
        },
        "Ghost": {
            name: this.RESOURCE_PATH + "Ghost.png",
            frameWidth: 16,
            frameHeight: 16,
            numberOfFrame: 2
        },
        "MedusaHead": {
            name: this.RESOURCE_PATH + "MedusaHead.png",
            frameWidth: 16,
            frameHeight: 16,
            numberOfFrame: 2
        },
          "AI6": {
            name: this.RESOURCE_PATH + "AI6.png",
            frameWidth: 32,
            frameHeight: 8,
            numberOfFrame: 1
        },
          "AI7": {
            name: this.RESOURCE_PATH + "AI7.png",
            frameWidth: 32,
            frameHeight: 64,
            numberOfFrame: 1
        },
        "Simon": {
            name: this.RESOURCE_PATH + "Character/simon.png",
            frameWidth: 45,
            frameHeight: 40,
            numberOfFrame: 25
        }

    };
    this.ITEM_DICT = {
        "Heart": {
            name: this.RESOURCE_PATH + "Heart1.png"
        },
        "BigHeart": {
            name: this.RESOURCE_PATH + "Heart2.png"
        },
        "HolyWater": {
            name: this.RESOURCE_PATH + "Holy_water.png"
        },
        "InvincibilityPotion": {
            name: this.RESOURCE_PATH + "invincibility_potion.png"
        },
        "MoneyBag100": {
            name: this.RESOURCE_PATH + "MoneyBag100.png"
        },
        "MoneyBag400": {
            name: this.RESOURCE_PATH + "MoneyBag400.png"
        },
        "MoneyBag700": {
            name: this.RESOURCE_PATH + "MoneyBag700.png"
        },
        "PotRoast": {
            name: this.RESOURCE_PATH + "PotRoast.png"
        },
        "StopWatch": {
            name: this.RESOURCE_PATH + "StopWatch.png"
        },
        "TripleShot": {
            name: this.RESOURCE_PATH + "TripleShot.png"
        },
        "WhipUpgrade": {
            name: this.RESOURCE_PATH + "WhipUpgrade.png"
        },
        "Axe": {
            name: this.RESOURCE_PATH + "Axe.png"
        },
        "Boomerang": {
            name: this.RESOURCE_PATH + "Boomerang.png"
        },
        "Cross": {
            name: this.RESOURCE_PATH + "Cross.png"
        },
        "Dagger": {
            name: this.RESOURCE_PATH + "Dagger.png"
        },
        "DoubleShot": {
            name: this.RESOURCE_PATH + "DoubleShot.png"
        }
    };
    this.ITEM_ANIMATION_DICT = {
        "MoneyBag1000": {
            name: this.RESOURCE_PATH + "MoneyBag1000.png",
            frameWidth: 14,
            frameHeight: 15,
            numberOfFrame: 3
        },
        "Stuff": {
            name: this.RESOURCE_PATH + "Stuff.png",
            frameWidth: 16,
            frameHeight: 16,
            numberOfFrame: 2
        },
        "Crown": {
            name: this.RESOURCE_PATH + "Crown.png",
            frameWidth: 15,
            frameHeight: 16,
            numberOfFrame: 3
        },
        "FireCandle": {
            name: this.RESOURCE_PATH + "FireCandle.png",
            frameWidth: 8,
            frameHeight: 16,
            numberOfFrame: 2
        }
    }
};