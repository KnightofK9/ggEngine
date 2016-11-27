/**
 * Created by Knight of k9 on 12/11/2016.
 */
var Constant = new function(){
    //this.DEFAULT_URL = "http://localhost/ggEditor/";
    this.DEFAULT_URL = "";
    this.RESOURCE_PATH = this.DEFAULT_URL + "Resource/Resources/";
    this.TILE_SET_PATH = this.RESOURCE_PATH + "TileSet/";


    this.TILE_SET_DICT ={
        "level-2-tile-set":{
            name:"level-2-tile-set.png",
            json:"level-2-tile-set.json",
            width:64,
            height:192,
            cellWidth:16,
            cellHeight:16,
            numberOfCellPerRow:4,
            numberOfCellPerColumn:12
        },
        "level-3-tile-set":{
            name:"level-3-tile-set.png",
            json:"level-3-tile-set.json",
            width:128,
            height:288,
            cellWidth:16,
            cellHeight:16,
            numberOfCellPerRow:8,
            numberOfCellPerColumn:18
        }
    };
    this.CHARACTER_DICT = {
        "char-simon":{
            name:"Resource/Resources/Character/simon.png",
            type:"SpriteAnimation",
            width:45,
            height:50
        }
    };
    this.ENEMY_DICT = {
        "AxeKnight":{
            name:this.RESOURCE_PATH+"AxeKnight.png",
            frameWidth:16,
            frameHeight:32,
            numberOfFrame:3
        },
        "BatEnemy":{
            name:this.RESOURCE_PATH+"BatEnemy.png",
            frameWidth:16,
            frameHeight:16,
            numberOfFrame:4
        },
        "BonePillar":{
            name:this.RESOURCE_PATH+"BonePillar.png",
            frameWidth:16,
            frameHeight:16,
            numberOfFrame:4
        },
        "Boss":{
            name:this.RESOURCE_PATH+"Boss.png",
            frameWidth:32,
            frameHeight:32,
            numberOfFrame:4
        },
        "Ghost":{
            name:this.RESOURCE_PATH+"Ghost.png",
            frameWidth:16,
            frameHeight:16,
            numberOfFrame:2
        },
        "MedusaHead":{
            name:this.RESOURCE_PATH+"MedusaHead.png",
            frameWidth:32,
            frameHeight:16,
            numberOfFrame:2
        }

    };
    this.ITEM_DICT = {
        "Heart":{
            name:this.RESOURCE_PATH+"Heart1.png"
        },
        "BigHeart":{
            name:this.RESOURCE_PATH+"Heart2.png"
        },
        "HolyWater":{
            name:this.RESOURCE_PATH+"Holy_water.png"
        },
        "InvincibilityPotion":{
            name:this.RESOURCE_PATH+"invincibility_potion.png"
        },
        "MoneyBag100":{
            name:this.RESOURCE_PATH+"MoneyBag100.png"
        },
        "MoneyBag400":{
            name:this.RESOURCE_PATH+"MoneyBag400.png"
        },
        "MoneyBag700":{
            name:this.RESOURCE_PATH+"MoneyBag700.png"
        },
        "PotRoast":{
            name:this.RESOURCE_PATH+"PotRoast.png"
        },
        "StopWatch":{
            name:this.RESOURCE_PATH+"StopWatch.png"
        },
        "TripleShot":{
            name:this.RESOURCE_PATH+"TripleShot.png"
        },
        "WhipUpgrade":{
            name:this.RESOURCE_PATH+"WhipUpgrade.png"
        },
        "Axe":{
            name:this.RESOURCE_PATH+"Axe.png"
        },
        "Boomerang":{
            name:this.RESOURCE_PATH+"Boomerang.png"
        },
        "Cross":{
            name:this.RESOURCE_PATH+"Cross.png"
        },

        "Dagger":{
            name:this.RESOURCE_PATH+"Dagger.png"
        },
        "DoubleShot":{
            name:this.RESOURCE_PATH+"DoubleShot.png"
        }
    }
};