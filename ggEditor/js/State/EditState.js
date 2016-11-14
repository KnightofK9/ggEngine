/**
 * Created by Knight of k9 on 12/11/2016.
 */
var EditState = function(game,tileWidth, tileHeight, quadNodeWidth, quadNodeHeight) {
    var bgData = "data:image/jpeg;base64,iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAAABHNCSVQICAgIfAhkiAAAAFFJREFUWIXtzjERACAQBDFgMPOKzr8ScADFFlBsFKRX1WqfStLG68SNQcogZZAySBmkDFIGKYOUQcogZZAySBmkDFIGKYOUQcog9X1wJnl9ONrTcwPWLGFOywAAAABJRU5ErkJggg==";
    var backgroundSprite;
    var map;
    var layer1;
    var layer2;
    var layer3;
    var layerList = [];
    var layerKeyList = [];
    var enterPosition = [];
    var marker;
    var currentTile = 0;
    var currentLayer = null;
    var currentTileSetKey = "";
    var hierarchyObject = null;
    var cursors;
    var showLayersKey;
    var layer1Key;
    var layer2Key;
    var currentLayerIndex = 0;
    var manualSelectLayer = 0;
    var layer3Key;
    var isUsedQuadTree = false;


    var objectList = [];
    var quadId = 0;


    this.exportTileMap = function(){
        var state = [];

        var tileMap = initTileMapAsJson();
        var quadTree = createQuadTree();

        state.push(tileMap);
        state.push(quadTree);


        Helper.downloadJson(state,"ProtoTypeTileMap");
        quadId = 0;
        objectList = [];
    };

    this.preload = function(){
        //var iBg = new Image();
        //iBg.src = bgData;
        //game.cache.addImage('bg', bgData, iBg);

        for(var key in Constant.TILE_SET_DICT){
            if(Constant.TILE_SET_DICT.hasOwnProperty(key)){
                var tileSet = Constant.TILE_SET_DICT[key];
                game.load.image(key, Constant.TILE_SET_PATH + tileSet.name, tileSet.cellWidth,tileSet.cellHeight);
            }
        }

    };
    this.create = function(){
        ggConsole.log("Phaser load completed!");
        //backgroundSprite = game.add.tileSprite(0,0,game.width,game.height,'bg');
        //backgroundSprite.tileWidth = tileWidth;
        //backgroundSprite.tileHheight = tileHeight;
        game.stage.backgroundColor = "#4488AA";
        map = game.add.tilemap();
        map.tileWidth = tileWidth;
        map.tileHeight = tileHeight;
        map.width = game.width;
        map.height = game.height;
        map.callDestroy = function(){
            ggConsole.alertNotification("Error","Each state must have only 1 tile map.")
            return false;
        };
        hierarchyObject = hierarchyEditor.addObjectToHierarchy("tile-map",map);
        hierarchyEditor.updateHierarchy();
        //for(var key in Constant.TILE_SET_DICT){
        //    if(Constant.TILE_SET_DICT.hasOwnProperty(key)){
        //        map.addTilesetImage(key);
        //        if(currentTileSetKey!="") currentTileSetKey = key;
        //    }
        //}


        //layer1 = map.create('defaultLayer', game.width/tileWidth, game.height/tileHeight, tileWidth, tileHeight);
        //layer1.scrollFactorX = 0.5;
        //layer1.scrollFactorY = 0.5;
        ////  Resize the world
        //layer1.resizeWorld();

        showLayersKey = game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
        showLayersKey.onDown.add(changeLayer, this);
        game.input.addMoveCallback(updateMarker, this);

        cursors = game.input.keyboard.createCursorKeys();
        //  Our painting marker
        marker = game.add.graphics();
        marker.lineStyle(2, 0x000000, 1);
        marker.drawRect(0, 0, tileWidth, tileHeight);



    };

    var initTileMapAsJson = function(){
        var numberOfColumn = game.width/tileWidth;
        var numberOfRow = game.height/tileHeight;
        var tileList = [];
        var tileMap = new TileMap();
        tileMap.width = game.width;
        tileMap.height = game.height;
        tileMap.tileWidth = tileWidth;
        tileMap.tileHeight = tileHeight;
        tileMap.isUsedQuadTree = true;
        for(var i = 0;i<map.tilesets.length;i++){
            tileMap.tileSetList.push(map.tilesets[i].name);
        }
        for(var y = 0;y<numberOfRow;y++){
            for(var x = 0;x<numberOfColumn;x++){
                var tile = null;
                for(var l = 0; l<layerList.length;l++){
                    var t = map.getTile(x,y,layerList[l].name);
                    if(t !== null){
                        tile = new SingleTile();
                        tile.tileSetKey = layerList[l].name;
                        tile.tileId = t.index;
                        tile.x = x*tileWidth;
                        tile.y = y*tileHeight;
                    }
                }
                if(tile!=null){
                    tile.id = quadId;
                    objectList.push(tile);
                    tileList.push(tile);
                    quadId++;
                }
            }
        }
        tileMap.tileList = tileList;
        return tileMap;
    };

    function getBaseLog(x, y) {
        return Math.log(y) / Math.log(x);
    }
    function createQuadTree(){
        "use strict";
        var quadTree = new QuadTree();
        var width = 0;
        for(width = quadNodeWidth;width<=game.width;width*=2){

        }
        var height = 0;
        for(height = quadNodeHeight;height<=game.height;height*=2){

        }



        quadTree.width = width;
        quadTree.height = height;
        quadTree.leafWidth = quadNodeWidth;
        quadTree.leafHeight = quadNodeHeight;
        quadTree.totalLeafNodeSize = (quadTree.width/quadNodeWidth) * (quadTree.height/quadNodeHeight);
        var sum = 0;
        var cap = 1;
        var capLimit = Math.floor(getBaseLog(4,quadTree.totalLeafNodeSize));
        var lastSum = 0;
        while(cap<=capLimit){
            lastSum = sum;
            sum+= Math.pow(4,cap);
            cap++;
        }
        quadTree.totalNodeSize = sum;
        quadTree.indexOfFirstLeafNode = quadTree.totalNodeSize - quadTree.totalLeafNodeSize;
        quadTree.quadNodeList = new Array(quadTree.totalNodeSize);
        createQuadNode(0,0,0,quadTree.width,quadTree.height,quadTree);
        createQuadNode(1,quadTree.width/2,0,quadTree.width,quadTree.height,quadTree);
        createQuadNode(2,0,quadTree.height/2,quadTree.width,quadTree.height,quadTree);
        createQuadNode(3,quadTree.width/2,quadTree.height/2,quadTree.width,quadTree.height,quadTree);
        return quadTree;
    }
    function createQuadNode(nodeId, x, y, parentWidth, parentHeight, quadTree){
        var width = parentWidth / 2;
        var height = parentHeight / 2;
        var quadNode;
        if(width <= quadTree.leafWidth && height <= quadTree.leafHeight){
            quadNode = new LeafNode();
            quadNode.x = x;
            quadNode.y = y;
            quadNode.width = width;
            quadNode.height = height;
            quadNode.id = nodeId;


            quadNode.quadNodeIdList = [];


            quadTree.quadNodeList[nodeId] = quadNode;
        }
        else{
            quadNode = new QuadNode();

            quadNode.x = x;
            quadNode.y = y;
            quadNode.width = width;
            quadNode.height = height;
            quadNode.id = nodeId;

            quadNode.leftTop = (nodeId+1)*4;
            quadNode.rightTop = (nodeId+1)*4 + 1;
            quadNode.leftBottom = (nodeId+1)*4 + 2;
            quadNode.rightBottom = (nodeId+1)*4 + 3;

            quadTree.quadNodeList[nodeId] = quadNode;

            createQuadNode(quadNode.leftTop,quadNode.x,quadNode.y,quadNode.width,quadNode.height,quadTree);
            createQuadNode(quadNode.rightTop,quadNode.x + quadNode.width/2,quadNode.y,quadNode.width,quadNode.height,quadTree);
            createQuadNode(quadNode.leftBottom,quadNode.x,quadNode.y+quadNode.height/2,quadNode.width,quadNode.height,quadTree);
            createQuadNode(quadNode.rightBottom,quadNode.x+quadNode.width/2,quadNode.y+quadNode.height/2,quadNode.width,quadNode.height,quadTree);

        }



    }




    var changeLayer = function(key) {

        switch (key.keyCode)
        {
            case Phaser.Keyboard.SPACEBAR:
                for(var i = 0;i<layerList.length;i++){
                    layerList[i].alpha = 1;
                }
                break;

            default:
                var layerIndex = parseInt(key.event.key) -1;
                if(isNaN(layerIndex)){
                    break;
                }
                if(layerIndex>=layerList.length){
                    break;
                }

                for(var i = 0;i<layerList.length;i++){
                    if(i==layerIndex) layerList[i].alpha = 1;
                    else layerList[i].alpha = 0.3;
                }
                manualSelectLayer = layerIndex;
                //currentLayer = layerList[layerIndex];
                break;
        }

    };
    var addTileSet = function(tileSetKey){
        //if(layerList.length==1){
        //    ggConsole.showNotification("Error","You can not use multiple tile set for 1 tile map.");
        //    return false;
        //}
        map.addTilesetImage(tileSetKey);

    };
    var addLayer = function(tileSetKey){
        var layer = map.createBlankLayer(tileSetKey, game.width/tileWidth, game.height/tileHeight, tileWidth, tileHeight);
        layer.scrollFactorX = 0.5;
        layer.scrollFactorY = 0.5;
        layer.resizeWorld();
        layer.callDestroy = function(){
            for(var i = 0;i<layerList.length;i++){
                if(layerList[i].name === this.name){
                    layerList.splice(i,1);
                    break;
                }
            }
            for(i = 0;i<map.layers.length;i++){
                if(map.layers[i].name === this.name){
                    map.layers.splice(i,1);
                    break;
                }
            }
            this.destroy();
            if(layerList.length >= 1) {
                //currentTileSetKey = layerList[0].name;
                //changeMapTileSetArray(currentTileSetKey);
                currentTileSetKey = "";
                currentLayer = null;
            }
            else {
                currentTileSetKey = "";
                currentLayer = null;
            }
            return true;
        };
        //layer.loadTexture(tileSetKey);
        layerList.push(layer);
        hierarchyEditor.addObjectToHObject(tileSetKey,layer,hierarchyObject);
        hierarchyEditor.updateHierarchy();
        var lastIndex = layerList.length  - 1;
        var layerKey = game.input.keyboard.addKey((lastIndex+1).toString().charCodeAt(0));
        layerKey.onDown.add(changeLayer, this);
        layerKeyList.push(layerKey);
        enterPosition.push(tileSetKey);



        return layer;
    };
    this.pickTile = function(tileSetKey, tileId) {
        //if(currentTileSetKey !== tileSetKey){
        //    currentLayer.resetTilesetCache();
        //    map.addTilesetImage(tileSetKey);
        //    currentTileSetKey = tileSetKey;
        //}

        var tileSetIndex = map.getTilesetIndex(tileSetKey);
        if(tileSetIndex === null){
            addTileSet(tileSetKey)
        }
        var isLayerReady = false;
        for(var i = 0;i<layerList.length;i++){
            if(layerList[i].name === tileSetKey){
                isLayerReady = true;
                currentLayer = layerList[i];
                break;
            }
        }
        if(!isLayerReady){
            currentLayer = addLayer(tileSetKey);
        }

        if(currentTileSetKey != tileSetKey){
            changeMapTileSetArray(tileSetKey);
        }
        currentTileSetKey = tileSetKey;
        //var tile = Constant.TILE_SET_DICT[tileSetKey].tileList[tileId];
        //currentLayerIndex = enterPosition.indexOf(tileSetKey);
        //currentLayer = layerList[currentLayerIndex];
        //var tile = new Phaser.Tile(currentLayer,tileId,tile.x,tile.y,tile.width,tile.height);
        currentTile = tileId;
    };
    var changeMapTileSetArray = function(tileSetKey){
        map.tiles = [];
        var tileSet = Constant.TILE_SET_DICT[tileSetKey];
        var currentTileSetId = map.getTilesetIndex(tileSetKey);
        for(var i = 0;i<tileSet.tileList.length;i++){
            map.tiles.push([tileSet.tileList[i].x,tileSet.tileList[i].y,currentTileSetId]);
        }
    };
    var updateMarker = function() {

        if(currentLayer!=null){
            marker.x = currentLayer.getTileX(game.input.activePointer.worldX) * tileWidth;
            marker.y = currentLayer.getTileY(game.input.activePointer.worldY) * tileHeight;
            if (game.input.mousePointer.isDown)
            {
                map.putTile(currentTile, currentLayer.getTileX(marker.x), currentLayer.getTileY(marker.y), currentTileSetKey);
            }
        }



    }


};