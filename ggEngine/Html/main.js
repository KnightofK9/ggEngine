/**
 * Created by Phan on 10/24/2016.
 */

function downloadJson(json,name){
    var dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(json));
    var dlAnchorElem = document.getElementById('downloadAnchorElem');
    dlAnchorElem.setAttribute("href",     dataStr     );
    dlAnchorElem.setAttribute("download", name + ".json");
    dlAnchorElem.click();
}
function getBaseLog(x, y) {
    return Math.log(y) / Math.log(x);
}
function createQuadTree(){
    "use strict";
    var quadTree = {};
    quadTree.width = 512;
    quadTree.height = 512;
    quadTree.leafWidth = 32;
    quadTree.leafHeight = 32;
    quadTree.totalLeafNodeSize = 16*16;
    var sum = 0;
    var cap = 1;
    var capLimit = Math.floor(getBaseLog(4,quadTree.totalLeafNodeSize));
    while(cap<=capLimit){
        sum+= Math.pow(4,cap);
        cap++;
    }
    quadTree.totalNodeSize = sum;
    quadTree.quadNodeList = new Array(quadTree.totalNodeSize);
    createQuadNode(0,quadTree.width,quadTree.height,quadTree);
    createQuadNode(1,quadTree.width,quadTree.height,quadTree);
    createQuadNode(2,quadTree.width,quadTree.height,quadTree);
    createQuadNode(3,quadTree.width,quadTree.height,quadTree);
    return quadTree;
}
function createQuadNode(nodeId,parentWidth,parentHeight, quadTree){
    var quadNode = {};
    var width = parentWidth / 2;
    var height = parentHeight / 2;
    quadNode.width = width;
    quadNode.height = height;
    quadNode.id = nodeId;

    if(width <= quadTree.leafWidth && height <= quadTree.leafHeight){
        quadNode.tileList = [];
        var tileInfo;
        tileInfo = createTileInfo("scene",randomInRangeInt(1,40));
        var tileType = createTileType("singleTile",tileInfo);
        quadNode.tileList.push(tileType);
        quadTree.quadNodeList[nodeId] = quadNode;
        return;
    }
    quadNode.leftTop = (nodeId+1)*4;

    quadNode.rightTop = (nodeId+1)*4 + 1;
    quadNode.leftBottom = (nodeId+1)*4 + 2;
    quadNode.rightBottom = (nodeId+1)*4 + 3;
    quadNode.tileList = "";

    quadTree.quadNodeList[nodeId] = quadNode;

    createQuadNode(quadNode.leftTop,quadNode.width,quadNode.height,quadTree);
    createQuadNode(quadNode.rightTop,quadNode.width,quadNode.height,quadTree);
    createQuadNode(quadNode.leftBottom,quadNode.width,quadNode.height,quadTree);
    createQuadNode(quadNode.rightBottom,quadNode.width,quadNode.height,quadTree);

    return;
}
function createTileType(type,value){
    var tileType = {};
    tileType.type = type;
    tileType.value = value;
    return tileType;
}
function createTileInfo(tileMapKey,tileId){
    var tileInfo = {};
    tileInfo.tileMapKey = tileMapKey;
    tileInfo.tileId = tileId;
    return tileInfo;
}
function createRandomTileAnimation(){
    var tileAnimationList = [];
    var random = randomInRangeInt(1,5);
    for(var i = 0;i<random;i++){
        var tileInfo = createTileInfo("scene",randomInRangeInt(1,40));
        tileAnimationList.push(tileInfo);
    }
    var tileType = createTileType("animationTile",tileAnimationList);
    return tileAnimationList;
}
function randomInRangeInt(min,max){
    return Math.floor(Math.random()*(max-min)+min);
}
function main(){
    var quadTree = createQuadTree();
    downloadJson(quadTree,"scene");
}
main();