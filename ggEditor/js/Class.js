/**
 * Created by Knight of k9 on 13/11/2016.
 */
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


function StaticTile() {
    /**
     * Game object inheritance
     */

    this.type = "StaticTile";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileSetKey = "";
    this.tileId = -1;
    this.id = -1;

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
    this.width = 0;
    this.height = 0;
    this.id = -1;
    this.quadNodeIdList = [];
}

function Rect() {
    this.left = 0;
    this.top = 0;
    this.right = 0;
    this.bottom = 0;
}
function TileMap() {
    this.type = "TileMap";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.tileSetList = [];
    this.scale = new Vector(1, 1);
    this.isUsedQuadTree = false;
}
function Group() {
    this.type = "Group";
    this.x = 0;
    this.y = 0;
    this.objectList = [];
    this.scale = new Vector(1, 1);
    this.isUsedQuadTree = false;
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
