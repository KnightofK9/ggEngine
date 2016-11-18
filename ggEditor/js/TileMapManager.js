/**
 * Created by Knight of k9 on 11/11/2016.
 */
var TileMap = function(width,height,cellWidth,cellHeight,tileSetKey,tileSetNumberOfCell){
    var tileMap = {};
    var gameObjectList = [];
    var quadTree = [];

    var currentX = 0;
    var currentY = 0;

    var brickId = 1;

    var numberOfRandomElement = (width/cellWidth)*(height/cellHeight);

    var quadTree;

    var useQuadTree = false;

    this.createTileMap = function(){
        initRandomGameObject();
    };
    this.initQuadTree = function(){
        useQuadTree = true;
        initQuadTree();
    };
    this.exportToJson = function(){
        var tileMap = {};
        tileMap.gameObjectList = gameObjectList;
        Helper.downloadJson(tileMap,"TestQuadTree");
    };


    /**
     * Private function section
     */
    var initRandomGameObject = function(){
        for(var i = 0;i<numberOfRandomElement;i++){
            createRandomGameObject();
        }
    };

    var initQuadTree = function(){
        quadTree = new QuadTree();

        quadTree.width = 512;
        quadTree.height = 512;
        quadTree.leafWidth = 32;
        quadTree.leafHeight = 32;
        quadTree.totalLeafNodeSize = 16*16;
        var sum = 0;
        var cap = 1;
        var capLimit = Math.floor(Helper.getBaseLog(4,quadTree.totalLeafNodeSize));
        while(cap<=capLimit){
            sum+= Math.pow(4,cap);
            cap++;
        }
        quadTree.totalNodeSize = sum;
        quadTree.quadNodeList = new Array(quadTree.totalNodeSize);
        createQuadNode(0,0,0,quadTree.width,quadTree.height,quadTree);
        createQuadNode(1,quadTree.width/2,0,quadTree.width,quadTree.height,quadTree);
        createQuadNode(2,0,quadTree.height/2,quadTree.width,quadTree.height,quadTree);
        createQuadNode(3,quadTree.width/2,quadTree.height/2,quadTree.width,quadTree.height,quadTree);

    };


    var createQuadNode = function(nodeId, x, y, parentWidth, parentHeight, quadTree){
        var quadNode = {};
        var width = parentWidth / 2;
        var height = parentHeight / 2;
        quadNode.x = x;
        quadNode.y = y;
        quadNode.width = width;
        quadNode.height = height;
        quadNode.id = nodeId;

        if(width <= quadTree.leafWidth && height <= quadTree.leafHeight){
            quadNode.objectIdList = getAnyIntersectObjectId(quadNode.x,quadNode.y,quadNode.x+quadNode.width,quadNode.y+quadNode.height);
            quadTree.quadNodeList[nodeId] = quadNode;
            return;
        }
        quadNode.leftTop = (nodeId+1)*4;

        quadNode.rightTop = (nodeId+1)*4 + 1;
        quadNode.leftBottom = (nodeId+1)*4 + 2;
        quadNode.rightBottom = (nodeId+1)*4 + 3;
        quadNode.objectIdList = [];

        quadTree.quadNodeList[nodeId] = quadNode;

        createQuadNode(quadNode.leftTop,quadNode.x,quadNode.y,quadNode.width,quadNode.height,quadTree);
        createQuadNode(quadNode.rightTop,quadNode.x + quadNode.width/2,quadNode.y,quadNode.width,quadNode.height,quadTree);
        createQuadNode(quadNode.leftBottom,quadNode.x,quadNode.y+quadNode.height/2,quadNode.width,quadNode.height,quadTree);
        createQuadNode(quadNode.rightBottom,quadNode.x+quadNode.width/2,quadNode.y+quadNode.height/2,quadNode.width,quadNode.height,quadTree);
    };
    var getAnyIntersectObjectId = function(left, top,right,bottom){
        var idList = [];
<<<<<<< HEAD
=======
        var quadNodeRect = new Rect();
        quadNodeRect.left = left;
        quadNodeRect.top = top;
        quadNodeRect.right = right;
        quadNodeRect.bottom = bottom;
>>>>>>> 8af77554377c4c3da7f646992b14f23eb4652998
        //TO DO: get intersect object here
        return idList;
    };
    var createRandomGameObject = function(){
        var gameObjectInfo = new GameObjectInfo();
        //var random = Helper.getRandomIntInRange(0,2);
        var random = 0;
        switch (random){
            case 0:
                gameObjectInfo.type = "SingleTile";
                gameObjectInfo.info = getRandomSingleTile();
                break;
            case 1:
                gameObjectInfo.type = "AnimationTile";
                gameObjectInfo.info = getRandomAnimationTile();
                break;
            case 2:
                gameObjectInfo.type = "Brick";
                gameObjectInfo.info = getRandomBrick();
        }
        gameObjectList.push(gameObjectInfo);
        return gameObjectInfo;

    };

    var getRandomAnimationTile = function(){
        var info = new AnimationTile();
        info.position = getNextPosition();
        var n = Helper.getRandomIntInRange(1,4);
        for(var i = 0;i<n;i++){
            var sprite = {};
            sprite.tileSetKey = tileSetKey;
            sprite.tileId = getRandomTileId();
            info.animationList.push(sprite);
        }
    };

    var getRandomSingleTile = function(){
        var info = new SingleTile();
        info.position = getNextPosition();
        info.tileSetKey = tileSetKey;
        info.tileId = getRandomTileId();
        return info;
    };

    var getRandomBrick = function(){
        var info = new Brick();
        info.position = getNextPosition();
        info.isCollidedObject = true;
        info.tileId = brickId();
        return info;
    };

    var getRandomTileId = function(){
        return Helper.getRandomIntInRange(1,tileSetNumberOfCell);
    };

    var getNextPosition = function(){
        var position = new Vector();
        position.x = currentX;
        position.y = currentY;
        currentX+=cellWidth;
        if(currentX>=width){
            currentX = 0;
            currentY += cellHeight;
        }
        return position;
    };
};
<<<<<<< HEAD
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
function SingleTile(){
    /**
     * Game object inheritance
     */
    this.position = new Vector();
    this.opacity = 255;
    this.isCollidedObject = false;
    this.width = 0;
    this.height = 0;

    this.tileSetKey = "";
    this.tileId = null;

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

    this.width = 0;
    this.height = 0;
    this.leafWidth = 0;
    this.leafHeight = 0;
    this.totalLeafNodeSize = 0;
    this.totalNodeSize = 0;
    this.quadNodeList = new Array(this.totalNodeSize);
}
=======
>>>>>>> 8af77554377c4c3da7f646992b14f23eb4652998
