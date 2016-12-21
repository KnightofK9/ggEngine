/**
 * Created by Knight of k9 on 13/11/2016.
 */
var my = {};

my.hierarchy = null;
my.hierarchyIdDict = [];
my.hierarchyIdCount = 0;
my.isPutEnemyToQuadTree = false;

var  hierarchyId = 0;
var inheritsFrom = function (child, parent) {
    child.prototype = Object.create(parent.prototype);
    // child.prototype.export = function(){
    //     var result = {};
    //     for(var key in this){
    //         if(this.hasOwnProperty(key)){
    //             result[key] = this[key];
    //         }
    //     }
    //     return result;
    // }
};
function HierarchyObject(){
    this._name = "";
    this._hierarchyId = my.hierarchyIdCount;
    my.hierarchyIdCount+=1;
    my.hierarchyIdDict[this._hierarchyId] = this;
    this._parent = null;
    this._childList = [];
    this._level = 0;
    this._item = null;
    this._add = function(hObject){
        hObject._level = this._level + 1;
        hObject._parent = this;
        this._childList.push(hObject);
    };
    this._remove = function(hObject){
        for(var i = 0;i<this._childList.length;i++){
            if(this._childList[i] === hObject){
                this._childList.splice(i,1);
                break;
            }
        }
    };
    this._destroy = function(){
        if(this.parent != null) {
            for (var i = 0; i < this.parent._childList.length; i++) {
                if (this.parent._childList[i] === this) {
                    this.parent._childList.splice(i, 1);
                    break;
                }
            }
        }
    }
}
function GameObjectInfo() {
    this.type = "";
    this.info = {};
}
function Vector(x, y) {
    if (x) this.x = x;
    else this.x = 0;
    if (y) this.y = y;
    else this.y = 0;
}
function GameObject() {
    this.position = new Vector();
    this.scale = new Vector();
    this.opacity = 255;
    this.isCollidedObject = false;
    this.width = 0;
    this.height = 0;
}


function SingleTile() {
    /**
     * Game object inheritance
     */

    this.type = "SingleTile";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileSetKey = "";
    this.tileId = -1;
    this.id = -1;

}



function TileSet() {
    this.id = "";
    this.width = 0;
    this.height = 0;
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.numberOfCell = 0;
    this.numberOfCellPerColumn = 0;
    this.numberOfCellPerRow = 0;
}



function AnimationTile() {
    /**
     * Game object inheritance
     */
    this.position = new Vector();
    this.opacity = 255;
    this.isCollidedObject = false;
    this.width = 0;
    this.height = 0;

    this.animationList = [];
}
function Brick() {
    /**
     * Game object inheritance
     */
    this.position = new Vector();
    this.opacity = 255;
    this.isCollidedObject = true;
    this.width = 0;
    this.height = 0;
}

function QuadTree() {
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.leafWidth = 0;
    this.leafHeight = 0;
    this.totalLeafNodeSize = 0;
    this.indexOfFirstLeafNode = 0;
    this.totalObjectSize = 0;
    this.totalNodeSize = 0;
    this.quadNodeList = new Array(this.totalNodeSize);
}
function QuadNode() {
    this.type = "QuadNode";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.id = -1;

    this.leftTop = -1;
    this.rightTop = -1;
    this.leftBottom = -1;
    this.rightBottom = -1;
}
function LeafNode() {
    this.type = "LeafNode";
    this.x = 0;
    this.y = 0;
    this.quadNodeIdList = [];
}

function Rect() {
    this.left = 0;
    this.top = 0;
    this.right = 0;
    this.bottom = 0;
}
function StaticTile() {
    this._name = "";
    this._hierarchyId = my.hierarchyIdCount;
    my.hierarchyIdCount+=1;
    my.hierarchyIdDict[this._hierarchyId] = this;
    this._parent = null;
    this._childList = [];
    this._item = null;
    this._level = 0;
    this._add = function(hObject){
        hObject._level = this._level + 1;
        hObject._parent = this;
        this._childList.push(hObject);
    };
    this._remove = function(hObject){
        if(this._parent==null) return;
        for(var i = 0;i<this._parent._childList.length;i++){
            if(this._parent._childList[i] === hObject){
                this._parent._childList.splice(i,1);
                break;
            }
        }
    };
    this._destroy = function(){
        my.hierarchyIdDict[this._hierarchyId] = null;
        delete my.hierarchyIdDict[this._hierarchyId];
        if(this.parent != null) {
            for (var i = 0; i < this.parent._childList.length; i++) {
                if (this.parent._childList[i] === this) {
                    this.parent._childList.splice(i, 1);
                    break;
                }
            }
        }
        for(var i = 0; i<this._childList.length;i++){
            this._childList[i].callDestroy();
        }
    };
    // this.prototype = new HierarchyObject();
    /**
     * Game object inheritance
     */

    // HierarchyObject.apply(this);
    this.type = "StaticTile";
    // this.prototype._name = this.type + this.prototype._hierarchyId;
    this._name = this.type;
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileSetKey = "";
    this.tileId = -1;
    this.id = -1;

    this.idX = -1;
    this.idY = -1;
    this.layer = null;
    this.getName = function(){
        var space = "";
        for(var i = 0;i<this._level;i++){
            space+="&nbsp;&nbsp;";
        }
        return space + this._name +"-" +this._hierarchyId;
    };
    this.callDestroy = function(){
        var tileMap = this.parent._item;
        var tile = tileMap.getTile(this.idX,this.idY,this.layer);
        if(tile!=null){
            tile.debug = false;
        }
        this._remove(this);
        return true;
    };
    this.exportAsJson = function(){
        return{
            type:this.type,
            name:this.name,
            idX:this.idX,
            idY:this.idY
        }
    };

}
function TileMap() {
    this._name = "";
    this._hierarchyId = my.hierarchyIdCount;
    my.hierarchyIdCount+=1;
    my.hierarchyIdDict[this._hierarchyId] = this;
    this._parent = null;
    this._childList = [];
    this._item = null;
    this._level = 0;
    this._add = function(hObject){
        this._childList.push(hObject);
        hObject._parent = this;
        hObject._level = this._level + 1;
    };
    this._remove = function(hObject){
        for(var i = 0;i<this._childList.length;i++){
            if(this._childList[i] === hObject){
                hObject.callDestroy();
                this._childList.splice(i,1);
                break;
            }
        }
    };
    this._destroy = function(){
        my.hierarchyIdDict[this._hierarchyId] = null;
        delete my.hierarchyIdDict[this._hierarchyId];
        if(this._parent != null) {
            for (var i = 0; i < this._parent._childList.length; i++) {
                if (this._parent._childList[i] === this) {
                    this._parent._childList.splice(i, 1);
                    break;
                }
            }
        }
        for(var i = 0; i<this._childList.length;i++){
            this._childList[i].callDestroy();
        }
    };
    // HierarchyObject.apply(this);
    // this.prototype = new HierarchyObject();
    this.type = "TileMap";
    // this.prototype._name = this.type + this.prototype._hierarchyId;
    this._name = this.type;
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.tileSetList = [];
    this.scale = new Vector(1, 1);
    this.isUsedQuadTree = false;


    this.getName = function(){
        var space = "";
        for(var i = 0;i<this._level;i++){
            space+="&nbsp;&nbsp;";
        }
        return space + this._name +"-" +this._hierarchyId;
    };
    this.addTypeTile = function(hTile){
        //TO DO: put tile into game here
        var tileMap = this._item;
        switch(hTile.type){
            case "StaticTile":
                var tile = tileMap.getTile(hTile.idX, hTile.idY, hTile.layer);
                if(tile == null) return false;
                if(tile.debug) return false;
                tile.debug = true;
                break;
            default:
                return false;
        }
        this._add(hTile);
        return true;
    };
    this.callDestroy = function(){
        ggConsole.alertNotification("Error","Each state must have only 1 tile map.");
        sceneEditor.editState.currentLayer.dirty = true;
        return false;
    }
}

function Group() {
    /**
     * HierarchyObject
     */
    this._name = "";
    this._hierarchyId = my.hierarchyIdCount;
    my.hierarchyIdCount+=1;
    my.hierarchyIdDict[this._hierarchyId] = this;
    this._parent = null;
    this._childList = [];
    this._item = null;
    this._level = 0;
    this._add = function(hObject){
        this._childList.push(hObject);
        hObject._parent = this;
        hObject._level = this._level + 1;
    };
    this._remove = function(hObject){
        for(var i = 0;i<this._childList.length;i++){
            if(this._childList[i] === hObject){
                this._childList.splice(i,1);
                break;
            }
        }
    };
    this._destroy = function(){
        my.hierarchyIdDict[this._hierarchyId] = null;
        delete my.hierarchyIdDict[this._hierarchyId];
        if(this._parent != null) {
            for (var i = 0; i < this._parent._childList.length; i++) {
                if (this._parent._childList[i] === this) {
                    this._parent._childList.splice(i, 1);
                    break;
                }
            }
        }
        for(var i = 0; i<this._childList.length;i++){
            this._childList[i].callDestroy();
        }
        $("#hierarchy-" + this._hierarchyId).remove();
    };
    this.getName = function(){
        var space = "";
        for(var i = 0;i<this._level;i++){
            space+="&nbsp;&nbsp;";
        }
        return space + this._name +"-" +this._hierarchyId;
    };
    /**
     * End HierarchyObject
     */
    this.type = "Group";
    this.x = 0;
    this.y = 0;
    this.callDestroy = function(){
        var that = this;
        var cloneList = this._childList.slice();
        for(var i = 0; i < cloneList.length; i++){
            cloneList[i].callDestroy();
        }
        // this._destroy();
        // that._item.destroy();
        return false;
    };
    this.addObject = function(sprite){
        var hSprite = new Sprite();
        hSprite._item = sprite;
        hSprite._name = sprite._type;
        hSprite.type = sprite._type;
        hSprite.x = sprite.x;
        hSprite.y = sprite.y;
        this._add(hSprite);
        return hSprite;
    };
    this.exportAsJson = function(useQuadTree){
        var json =  {
            type:this.type,
            name:this.name,
            x:this.x,
            y:this.y,
            itemList:[]
        };
        for(var i = 0;i<this._childList.length;i++){
            var item = this._childList[i];
            var sprite = {};
            sprite.type = item.type;
            sprite.name = item.name;
            sprite.x = item._item.x;
            sprite.y = item._item.y;
            if(Constant.exportWidthHeightForSprite)
            {
                sprite.width = item._item.width;
                sprite.height = item._item.height;
            }
            if(Constant.EXPORT_WIDTH_HEIGHT_DICT.hasOwnProperty(sprite.type)){
                sprite.width = item._item.width;
                sprite.height = item._item.height;
            }
            if(Constant.BREAKABLE_DROP_DICT.hasOwnProperty(sprite.type)){
                sprite.extraInfo.dropType.name = sprite.extraInfo.dropType.type;
                sprite.extraInfo.dropType.x = sprite.x;
                sprite.extraInfo.dropType.y = sprite.y;
            }
            // if(useQuadTree){
            //     if(Constant.ENEMY_DICT.hasOwnProperty(sprite.type) && !my.isPutEnemyToQuadTree ){
            //         sprite.quadTreeId = -1;
            //     }
            //     else{
            //         sprite.quadTreeId = my.getQuadTreeId(sprite);
            //     }
            // }
            json.itemList.push(sprite);
        }
        return json;
    };

}
function Sprite(){
    /**
     * HierarchyObject
     */
    this._name = "";
    this._hierarchyId = my.hierarchyIdCount;
    my.hierarchyIdCount+=1;
    my.hierarchyIdDict[this._hierarchyId] = this;
    this._parent = null;
    this._childList = [];
    this._item = null;
    this._level = 0;
    this._add = function(hObject){
        this._childList.push(hObject);
        hObject._parent = this;
        hObject._level = this._level + 1;
    };
    this._remove = function(hObject){
        for(var i = 0;i<this._childList.length;i++){
            if(this._childList[i] === hObject){
                this._childList.splice(i,1);
                break;
            }
        }
    };
    this._destroy = function(){
        my.hierarchyIdDict[this._hierarchyId] = null;
        delete my.hierarchyIdDict[this._hierarchyId];
        if(this._parent != null) {
            for (var i = 0; i < this._parent._childList.length; i++) {
                if (this._parent._childList[i] === this) {
                    this._parent._childList.splice(i, 1);
                    break;
                }
            }
            for(var i = 0; i<this._childList.length;i++){
                this._childList[i].callDestroy();
            }
        }
        $("#hierarchy-" + this._hierarchyId).remove();
    };
    this.getName = function(){
        var space = "";
        for(var i = 0;i<this._level;i++){
            space+="&nbsp;&nbsp;";
        }
        return space + this._name +"-" +this._hierarchyId;
    };
    /**
     * End HierarchyObject
     */
    this.type = "";
    this.x = 0;
    this.y = 0;
    this.callDestroy = function(){
        this._item.destroy();
        this._destroy();
        return true;
    }
}

function State() {
    this.type = "State";
    this.name = "";
    this.width = 0;
    this.height = 0;
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.camera = null;
    this.preloadList = [];
    this.stageList = [];
    this.groupList = [];
    this.quadTree = null;
}
function Camera() {
    this.type = "Camera";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;

}


// void Font(std::string fontKey, std::string fontName, int fontSize, bool isItalic = false, int fontWeight = FW_NORMAL);
// void Font(std::string fontKey, std::string fontName, std::string fontPath , int fontSize, bool isItalic = false, int fontWeight = FW_NORMAL);
// void Texture(std::string textureKey, std::string texturePath);
// void Atlas(std::string atlasName, std::string atlasPath, std::string atlasDefPath, AtlasDefType type = AtlasDefTypeXML);
// void Audio(std::string audioKey, std::string audioPath);
// void TileSet(std::string tileSetPath, std::string tileSetJsonPath);


function PreFontMemory() {
    this.type = "PreFontMemory";
    this.fontKey = "";
    this.fontName = "";
    this.fontSize = 0;
    this.isItalic = false;
    this.fontWeight = 400;
}
function PreFontFile() {
    this.type = "PreFontFile";
    this.fontKey = "";
    this.fontName = "";
    this.fontPath = "";
    this.fontSize = 0;
    this.isItalic = false;
    this.fontWeight = 400;
}
function PreTexture() {
    this.type = "PreTexture";
    this.textureKey = "";
    this.texturePath = "";
}
function PreAtlas() {
    this.type = "PreAtlas";
    this.atlasName = "";
    this.atlasPath = "";
    this.atlasDefPath = "";
    this.type = 1; //0 XML, 1 Json
}
function PreAudio() {
    this.type = "PreAudio";
    this.audioKey = "";
    this.audioPath = "";
}
function PreTileSet() {
    this.type = "PreTileSet";
    this.tileSetPath = "";
    this.tileSetJsonPath = "";
}
// TileMap.prototype  = Object.create(HierarchyObject.prototype);
// StaticTile.prototype  = Object.create(HierarchyObject.prototype);
// TileMap.prototype  = new HierarchyObject();
// TileMap.prototype.constructor = TileMap;
// StaticTile.prototype  = new HierarchyObject();
// StaticTile.prototype.constructor = StaticTile;
// inheritsFrom(StaticTile,HierarchyObject);
// inheritsFrom(Group,HierarchyObject);
// inheritsFrom(TileMap,HierarchyObject);
Phaser.QuadTree.prototype.export = function(){
    var quadTreeJson = {};
    quadTreeJson.type = "QuadTree";
    quadTreeJson.maxLevels = this.maxLevels;
    quadTreeJson.maxObjects = this.maxObjects;
    quadTreeJson.level = this.level;
    quadTreeJson.bounds = this.bounds;
    quadTreeJson.objects = [];
    for(var i = 0; i <this.objects.length;i++){
        var sprite = {};
        var item = this.objects[i].sprite.hObject;
        sprite.type = item.type;
        sprite.name = item.name;
        if(Constant.exportWidthHeightForSprite){
            sprite.width = item._item.width;
            sprite.height = item._item.height;
        }

        // sprite.x = item.x + sprite.width;
        // sprite.y = item.y + sprite.height;
        sprite.x = this.objects[i].x;
        sprite.y = this.objects[i].y;
        if(Constant.EXPORT_WIDTH_HEIGHT_DICT.hasOwnProperty(sprite.type)){
            sprite.width = this.objects[i].width;
            sprite.height = this.objects[i].height;
        }
        // switch(sprite.type){
        //     case "TileBrick":
        //         sprite.width = this.objects[i].width;
        //         sprite.height = this.objects[i].height;
        //         break;
        // }
        if(isNotNull(item._item.extraInfo)){
            sprite.extraInfo = item._item.extraInfo;
            if(Constant.BREAKABLE_DROP_DICT.hasOwnProperty(sprite.type)){
                sprite.extraInfo.dropType.name = sprite.extraInfo.dropType.type;
                sprite.extraInfo.dropType.x = sprite.x;
                sprite.extraInfo.dropType.y = sprite.y;
            }
        }

        quadTreeJson.objects.push(sprite);
    }
    quadTreeJson.nodes = [];
    if (this.nodes[0] != null){
        for(var i = 0; i < 4;i++){
            quadTreeJson.nodes.push(this.nodes[i].export());
        }
    }
    return quadTreeJson;

};
function CVBlock(){
    this.type = "CVBlock";
    this.name = "Block";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.simonPosition = {x:0,y:0};
    this.cameraPosition = {x:0,y:0};
}
function CVStage(){
    this.type = "CVStage";
    this.number = -1;
    this.blockList = [];
}