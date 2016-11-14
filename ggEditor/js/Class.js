/**
 * Created by Knight of k9 on 13/11/2016.
 */
function GameObjectInfo(){
    this.type = "";
    this.info = {};
}
function Vector(x,y){
    if(x) this.x = x;
    else this.x = 0;
    if(y) this.y = y;
    else this.y = 0;
}
function GameObject(){
    this.position = new Vector();
    this.scale = new Vector();
    this.opacity = 255;
    this.isCollidedObject = false;
    this.width = 0;
    this.height = 0;
}

function TileMap(){
    this.type = "TileMap";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.tileWidth = 0;
    this.tileHeight = 0;
    this.tileSetList = [];
    this.isUsedQuadTree = false;
}
function SingleTile(){
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

function StaticTile(){
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
function AnimationTile(){
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
function Brick(){
    /**
     * Game object inheritance
     */
    this.position = new Vector();
    this.opacity = 255;
    this.isCollidedObject = true;
    this.width = 0;
    this.height = 0;
}

function QuadTree(){
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.leafWidth = 0;
    this.leafHeight = 0;
    this.totalLeafNodeSize = 0;
    this.totalNodeSize = 0;
    this.indexOfFirstLeafNode = 0;
    this.quadNodeList = new Array(this.totalNodeSize);
}
function QuadNode(){
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
function LeafNode(){
    this.type = "LeafNode";
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
    this.id = -1;
    this.quadNodeIdList = [];
}
function QuadTree(){
    this.type = "QuadTree";
    this.width = 0;
    this.height = 0;
    this.leafWidth = 0;
    this.leafHeight = 0;
    this.totalLeafNodeSize = 0;
    this.totalNodeSize = 0;
    this.quadNodeList = null;
}



function Rect(){
    this.left = 0;
    this.top = 0;
    this.right = 0;
    this.bottom = 0;
}
