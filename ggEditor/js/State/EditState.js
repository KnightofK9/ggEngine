/**
 * Created by Knight of k9 on 12/11/2016.
 */
var EditState = function (name, game, tileWidth, tileHeight, quadTreeMaxObject, quadTreeMaxLevel, json) {

    this.arrayTile = [];
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
    var that = this;
    var updateGroup = null;
    var objectList = [];
    var quadId = 0;
    var remaingTileToupdate = [];
    var currentTileType = "";
    var currentPickName = "";
    var groupList = [];
    var hierachyGrouplist = [];
    var currentPickTile = "";
    var mouseSprite = null;
    var quadTreeHGroup = null;
    var enemyHGroup = null;
    var isBlockingClick = false;

    var wasMouseButtonDown = false;

    var currentSelectHGroup = null;

    var phaserQuadTree;

    var mouseGroup = null;

    var pickRectCompleted = false;

    var currentPickRect = null;
    var currentPickRectPos = {x:0,y:0};

    var tileMapGroup = null;
    var resetCurrentPickRect = function(){
        currentPickRect = new Phaser.Rectangle();
    };
    this.getCurrentLayer = function () {
        return currentLayer;
    };
    var createGroup = function (groupName) {
        return hierarchyEditor.add.group(groupName);

    };

    var initGroupListAsJson = function(useQuadTree){
        var groupList = [];
        for(var i = 0;i<my.hierarchy._childList.length;i++){
            var item = my.hierarchy._childList[i];
            switch(item.type){
                case "Group":
                    var groupJson = item.exportAsJson(useQuadTree);
                    groupList.push(groupJson);
                    break;
                default:
                    break;
            }
        }
        return groupList;
    };

    this.showCreateGroup = function () {
        BootstrapDialog.show({
            closable: true,
            title: "Create group",
            message: 'Name <input id="dialog-name" type="text" class="form-control">'
            ,
            onshow: function (dialogRef) {
                dialogRef.getModalBody().find('#dialog-name').val("Group");
            },
            buttons: [{
                label: 'Create',
                action: function (dialogRef) {
                    var name = dialogRef.getModalBody().find('#dialog-name').val();
                    dialogRef.close();
                    createGroup(name);
                }
            }]
        });
    };
    this.importState = function (stateJson) {
        for (var i = 0; i < stateJson.groupList.length; i++) {
            var group = stateJson.groupList[i];
            switch (group.type) {
                case "TileMap":
                    var tileMap = new TileMap();
                    tileWidth = group.tileWidth;
                    tileHeight = group.tileHeight;
                    isUsedQuadTree = group.isUsedQuadTree;
                    for (var d = 0; d < group.tileSetList.length; d++) {
                        //var tileSetKey = group.tileSetList[d];
                        //addTileSet(tileSetKey);
                        //currentLayer = addLayer(tileSetKey);
                        //currentTileSetKey = tileSetKey;
                    }
                    //changeMapTileSetArray(currentTileSetKey);
                    for (var t = 0; t < group.tileList.length; t++) {
                        var tile = group.tileList[t];
                        switch (tile.type) {
                            case  "SingleTile":
                                //if(currentTileSetKey !== tile.tileSetKey){
                                //    for(var layer in layerList){
                                //        if(layer.name === tile.tileSetKey){
                                //            currentTileSetKey = tile.tileSetKey;
                                //            changeMapTileSetArray(currentTileSetKey);
                                //            break;
                                //        }
                                //    }
                                //}
                                //if(tile.tileSetKey === "level-3-tile-set") {
                                //    break;
                                //}

                                //that.pickTile(tile.tileSetKey,tile.tileId);
                                //map.putTile(currentTile, currentLayer.getTileX(tile.x), currentLayer.getTileY(tile.y), currentTileSetKey);
                                //window.setTimeout(function(){
                                //    that.pickTile(tile.tileSetKey,tile.tileId);
                                //    map.putTile(currentTile, currentLayer.getTileX(tile.x), currentLayer.getTileY(tile.y), currentTileSetKey);
                                //},100);
                                remaingTileToupdate.push(tile);
                                //game.time.events.add(1000 , function(tile){
                                //    that.pickTile(tile.tileSetKey,tile.tileId);
                                //    map.putTile(currentTile, currentLayer.getTileX(tile.x), currentLayer.getTileY(tile.y), currentTileSetKey);
                                //}, this,tile);

                                break;
                            default:
                                console.log("No supported tile type " + tile.type);
                                break;
                        }
                    }


                    break;
                default:
                    console.log("No supported group type " + group.type);
                    break;
            }
        }

    };
    var resetPick = function () {
        $("#picker-filed > .btn").removeClass("active");
        currentTileType = "";
        currentPickTile = "";
        currentPickName = "";
        if (mouseSprite != null) mouseSprite.destroy();
        mouseSprite = null;
        // currentLayer = null;
        pickRectCompleted = false;
        currentPickRectPos = {x:0,y:0};
        currentTile = null;
        resetCurrentPickRect();
        clearArrayTile()
    };
    var initPreloadList = function () {
        var preloadList = [];
        if (layerList.length > 0) {
            for (var i = 0; i < layerList.length; i++) {
                var preTileSet = new PreTileSet();
                var key = layerList[i].name;
                preTileSet.tileSetPath = Constant.TILE_SET_PATH + Constant.TILE_SET_DICT[key].name;
                preTileSet.tileSetJsonPath = Constant.TILE_SET_PATH + Constant.TILE_SET_DICT[key].json;
                preloadList.push(preTileSet);
            }
        }
        return preloadList;
    };

    this.exportTileMap = function () {
        isUsedQuadTree = stateInfo.isUsedQuadTree();
        my.isPutEnemyToQuadTree = stateInfo.isPutEnemyToQuadTree();
        var state = new State();
        state.name = name;
        state.width = game.width;
        state.height = game.height;
        state.tileWidth = tileWidth;
        state.tileHeight = tileHeight;

        my.quadTreeId = 0;
        if(isUsedQuadTree){
            my.quadTreeObjectList = [];
            my.getQuadTreeId = function(object){
                my.quadTreeObjectList.push(object);
                return my.quadTreeId++;
            }
        }


        var tileMap = initTileMapAsJson(isUsedQuadTree);
        state.groupList.push(tileMap);
        var groupList = initGroupListAsJson(isUsedQuadTree);
        state.groupList = state.groupList.concat(groupList);
        if (isUsedQuadTree) {
            var quadTree = createQuadTree();
            state.quadTree = quadTree;
        }
        else {
        }
        var preloadList = initPreloadList();
        state.preloadList = preloadList;
        if (isUsedQuadTree) state.quadTree = quadTree;


        Helper.downloadJson(state, state.name);
        quadId = 0;
        objectList = [];
    };
    this.preload = function () {
        //var iBg = new Image();
        //iBg.src = bgData;
        //game.cache.addImage('bg', bgData, iBg);

        for(var key in Constant.STATIC_TILE_DICT){
            if(Constant.STATIC_TILE_DICT.hasOwnProperty(key)){
                game.load.image(key,Constant.STATIC_TILE_DICT[key].name);
            }
        }

        for (var key in Constant.TILE_SET_DICT) {
            if (Constant.TILE_SET_DICT.hasOwnProperty(key)) {
                var tileSet = Constant.TILE_SET_DICT[key];
                game.load.image(key, tileSet.name, tileSet.cellWidth, tileSet.cellHeight);
            }
        }

        for (var key in Constant.ITEM_DICT) {
            if (Constant.ITEM_DICT.hasOwnProperty(key)) {
                game.load.image(key, Constant.ITEM_DICT[key].name);
            }
        }
        for (var key in Constant.ENEMY_DICT) {
            if (Constant.ENEMY_DICT.hasOwnProperty(key)) {
                game.load.spritesheet(key, Constant.ENEMY_DICT[key].name, Constant.ENEMY_DICT[key].frameWidth, Constant.ENEMY_DICT[key].frameHeight, Constant.ENEMY_DICT[key].numberOfFrame);
            }
        }

    };
    this.refresh = function(){
        wasMouseButtonDown = false;
        clearArrayTile();
        resetCurrentPickRect();
        phaserQuadTree.clear();
        phaserQuadTree.populate(quadTreeHGroup._item);
    };
    this.create = function () {
        ggConsole.log("Phaser load completed!");
        game.physics.startSystem(Phaser.Physics.ARCADE);
        //backgroundSprite = game.add.tileSprite(0,0,game.width,game.height,'bg');
        //backgroundSprite.tileWidth = tileWidth;
        //backgroundSprite.tileHheight = tileHeight;
        tileMapGroup = game.add.group();
        phaserQuadTree = new Phaser.QuadTree(0, 0, game.width, game.height, quadTreeMaxObject, quadTreeMaxLevel, 0);

        var updateGroup = game.add.group();
        updateGroup.update = function () {
            if (remaingTileToupdate.length > 0) {
                var tile = remaingTileToupdate.pop();
                that.pickTile(tile.tileSetKey, tile.tileId);
                map.putTile(currentTile, currentLayer.getTileX(tile.x), currentLayer.getTileY(tile.y), currentTileSetKey);
            } else {
                this.destroy();
            }
        };
        game.stage.backgroundColor = "#4488AA";
        map = hierarchyEditor.add.tilemap()._item;
        map.tileWidth = tileWidth;
        map.tileHeight = tileHeight;
        map.width = game.width;
        map.height = game.height;
        map.callDestroy = function () {
            ggConsole.alertNotification("Error", "Each state must have only 1 tile map.")
            return false;
        };
        // hierarchyObject = hierarchyEditor.addObjectToHierarchy("tile-map",map);
        // hierarchyEditor.updateHierarchy();
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


        if (json) this.importState(json);


        mouseGroup = game.add.group();


        /**
         * Add quad tree group and enemy group
         */
        quadTreeHGroup =  createGroup("QuadTree");
        enemyHGroup = createGroup("Enemy");
        resetCurrentPickRect();

    };

    this.render = function(){
        game.debug.reset();
        if(stateInfo.isRenderStaticBody()) {
            for(var i = 0; i < quadTreeHGroup._childList.length; i++){
                game.debug.body(quadTreeHGroup._childList[i]._item);
            }
        }
        if(stateInfo.isRenderQuadTree()){
            game.debug.quadTree(phaserQuadTree,"#003815");
        }
        switch(currentPickTile){
            case "SelectPick":
                game.debug.geom(currentPickRect,null,false);
                break;
            default:
                break;
        }


    };
    var initTileMapAsJson = function (useQuadTre) {
        var numberOfColumn = game.width / tileWidth;
        var numberOfRow = game.height / tileHeight;
        var tileList = [];
        var tileMap = {};
        tileMap.type = "TileMap";
        tileMap.name = "Background";
        tileMap.width = game.width;
        tileMap.height = game.height;
        tileMap.tileWidth = tileWidth;
        tileMap.tileHeight = tileHeight;
        tileMap.isUsedQuadTree = useQuadTre;
        tileMap.tileSetList = [];
        for (var i = 0; i < map.tilesets.length; i++) {
            tileMap.tileSetList.push(map.tilesets[i].name);
        }
        for (var y = 0; y < numberOfRow; y++) {
            for (var x = 0; x < numberOfColumn; x++) {
                var tile = null;
                for (var l = 0; l < layerList.length; l++) {
                    var t = map.getTile(x, y, layerList[l].name);
                    if (t !== null) {
                        tile = {};
                        if (t.debug) {
                            tile.type = "StaticTile";
                            // tile = new StaticTile();
                        }
                        else {
                            tile.type = "SingleTile";
                            // tile = new SingleTile();
                        }
                        tile.idX = x;
                        tile.idY = y;
                        tile.x = x * tileWidth;
                        tile.y = y * tileHeight;
                        tile.width = tileWidth;
                        tile.height = tileHeight;
                        tile.tileSetKey = layerList[l].name;
                        tile.tileId = t.index;
                        if(useQuadTre){
                            tile.quadTreeId = my.getQuadTreeId(tile);
                        }
                    }
                }
                if (tile != null) {
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

    var getBaseLog = function (x, y) {
        return Math.log(y) / Math.log(x);
    };
    var createQuadTree = function () {
        "use strict";
        var quadTree = new QuadTree();
        var width = 0;
        for (width = quadNodeWidth; width <= game.width; width *= 2) {

        }
        var height = 0;
        for (height = quadNodeHeight; height <= game.height; height *= 2) {

        }


        quadTree.width = width;
        quadTree.height = height;
        quadTree.leafWidth = quadNodeWidth;
        quadTree.leafHeight = quadNodeHeight;
        quadTree.totalObjectSize = objectList.length;
        quadTree.numberOfLeafNodePerRow = quadTree.width / quadNodeWidth;
        quadTree.numberOfLeafNodePerColumn = quadTree.height/quadNodeHeight;
        quadTree.totalLeafNodeSize = quadTree.numberOfLeafNodePerRow * quadTree.numberOfLeafNodePerColumn;
        var sum = 0;
        var cap = 1;
        var capLimit = Math.floor(getBaseLog(4, quadTree.totalLeafNodeSize));
        var lastSum = 0;
        while (cap <= capLimit) {
            lastSum = sum;
            sum += Math.pow(4, cap);
            cap++;
        }
        quadTree.totalNodeSize = sum;
        quadTree.indexOfFirstLeafNode = quadTree.totalNodeSize - quadTree.totalLeafNodeSize;
        quadTree.quadNodeList = initLeafNodeListNew(quadTree);
        // createQuadNode(0, 0, 0, quadTree.width, quadTree.height, quadTree);
        // createQuadNode(1, quadTree.width / 2, 0, quadTree.width, quadTree.height, quadTree);
        // createQuadNode(2, 0, quadTree.height / 2, quadTree.width, quadTree.height, quadTree);
        // createQuadNode(3, quadTree.width / 2, quadTree.height / 2, quadTree.width, quadTree.height, quadTree);
        //
        // initLeafNodeList(quadTree);

        return quadTree;
    };
    var initLeafNodeListNew = function(quadTree){
        var twoDArray = new Array(quadTree.numberOfLeafNodePerColumn);
        for(var idY = 0;idY<twoDArray.length;idY++){
            twoDArray[idY] = new Array(quadTree.numberOfLeafNodePerRow);
        }
        for(var idY = 0;idY<quadTree.numberOfLeafNodePerColumn;idY++) {
            for (var idX = 0; idX < quadTree.numberOfLeafNodePerRow; idX++) {
                var leafNode = new LeafNode();
                leafNode.x = idX * quadTree.leafWidth;
                leafNode.y = idY * quadTree.leafHeight;
                leafNode.quadNodeIdList = [];
                twoDArray[idY][idX] = leafNode;
            }
        }
        twoDArray = initReferToObject(twoDArray,quadTree.leafWidth,quadTree.leafHeight);
        return twoDArray;
    };
    var initReferToObject = function(twoDArray,leafWidth,leafHeight){
        var objectList = my.quadTreeObjectList;
        for(var i = 0;i<objectList.length;i++){
            var item = objectList[i];
            if(item.type === "SingleTile" || item.type ==="StaticTile"){
                twoDArray[item.idY][item.idX].quadNodeIdList.push(i);
                continue;
            }

            var idX = Math.floor(item.x / leafWidth);
            var idY = Math.floor(item.y/ leafHeight);
            var endIdX = Math.floor((item.x +item.width )/ leafWidth);
            var endIdY = Math.floor((item.y + item.height)/ leafHeight);
            for(var y = idY;y <= endIdY;y++){
                for(var x = idX;x<=endIdX;x++){
                    twoDArray[y][x].quadNodeIdList.push(i);
                }
            }
        }
        return twoDArray;
    };

    var createQuadNode = function (nodeId, x, y, parentWidth, parentHeight, quadTree) {
        var width = parentWidth / 2;
        var height = parentHeight / 2;
        var quadNode;
        if (width <= quadTree.leafWidth && height <= quadTree.leafHeight) {
            quadNode = new LeafNode();
            quadNode.x = x;
            quadNode.y = y;
            quadNode.width = width;
            quadNode.height = height;
            quadNode.id = nodeId;


            quadNode.quadNodeIdList = [];


            quadTree.quadNodeList[nodeId] = quadNode;
        }
        else {
            quadNode = new QuadNode();

            quadNode.x = x;
            quadNode.y = y;
            quadNode.width = width;
            quadNode.height = height;
            quadNode.id = nodeId;

            quadNode.leftTop = (nodeId + 1) * 4;
            quadNode.rightTop = (nodeId + 1) * 4 + 1;
            quadNode.leftBottom = (nodeId + 1) * 4 + 2;
            quadNode.rightBottom = (nodeId + 1) * 4 + 3;

            quadTree.quadNodeList[nodeId] = quadNode;

            createQuadNode(quadNode.leftTop, quadNode.x, quadNode.y, quadNode.width, quadNode.height, quadTree);
            createQuadNode(quadNode.rightTop, quadNode.x + quadNode.width / 2, quadNode.y, quadNode.width, quadNode.height, quadTree);
            createQuadNode(quadNode.leftBottom, quadNode.x, quadNode.y + quadNode.height / 2, quadNode.width, quadNode.height, quadTree);
            createQuadNode(quadNode.rightBottom, quadNode.x + quadNode.width / 2, quadNode.y + quadNode.height / 2, quadNode.width, quadNode.height, quadTree);

        }


    };

    var initLeafNodeList = function (quadTree) {
        var allNodeList = Array(quadTree.quadNodeList.length);
        var l = quadTree.quadNodeList.length;
        while (l--) allNodeList[l] = quadTree.quadNodeList[l];
        //var leafNodeList = quadTree.quadNodeList.splice(quadTree.indexOfFirstLeafNode);
        var numberOfCellPerRow = quadTree.width / quadTree.leafWidth;
        var numberOfCellPerColumn = quadTree.height / quadTree.leafHeight;
        var leafWidth = quadTree.leafWidth;
        var leafHeight = quadTree.leafHeight;


        for (var i = 0; i < objectList.length; i++) {
            var object = objectList[i];
            for (var y = object.y / leafHeight; y * leafHeight <= object.y + object.width; y += 1) {
                for (var x = object.x / leafWidth; x * leafWidth <= object.x + object.height; x += 1) {
                    quadTree.quadNodeList[y * numberOfCellPerRow + x + quadTree.indexOfFirstLeafNode].quadNodeIdList.push(object.id);
                }
            }
        }

    };


    var changeLayer = function (key) {

        switch (key.keyCode) {
            case Phaser.Keyboard.SPACEBAR:
                for (var i = 0; i < layerList.length; i++) {
                    layerList[i].alpha = 1;
                }
                break;

            default:
                var layerIndex = parseInt(key.event.key) - 1;
                if (isNaN(layerIndex)) {
                    break;
                }
                if (layerIndex >= layerList.length) {
                    break;
                }

                for (var i = 0; i < layerList.length; i++) {
                    if (i == layerIndex) layerList[i].alpha = 1;
                    else layerList[i].alpha = 0.3;
                }
                manualSelectLayer = layerIndex;
                //currentLayer = layerList[layerIndex];
                break;
        }

    };
    var addTileSet = function (tileSetKey) {
        //if(layerList.length==1){
        //    ggConsole.showNotification("Error","You can not use multiple tile set for 1 tile map.");
        //    return false;
        //}
        map.addTilesetImage(tileSetKey);

    };
    var addLayer = function (tileSetKey) {
        var layer = map.createBlankLayer(tileSetKey, game.width / tileWidth, game.height / tileHeight, tileWidth, tileHeight);
        tileMapGroup.add(layer);
        layer.scrollFactorX = 0.5;
        layer.scrollFactorY = 0.5;
        layer.resizeWorld();
        layer.callDestroy = function () {
            for (var i = 0; i < layerList.length; i++) {
                if (layerList[i].name === this.name) {
                    layerList.splice(i, 1);
                    break;
                }
            }
            for (i = 0; i < map.layers.length; i++) {
                if (map.layers[i].name === this.name) {
                    map.layers.splice(i, 1);
                    break;
                }
            }
            this.destroy();
            if (layerList.length >= 1) {
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
        // hierarchyEditor.addObjectToHObject(tileSetKey,layer,hierarchyObject);
        // hierarchyEditor.updateHierarchy();
        var lastIndex = layerList.length - 1;
        //var layerKey = game.input.keyboard.addKey((lastIndex+1).toString().charCodeAt(0));
        //layerKey.onDown.add(changeLayer, this);
        //layerKeyList.push(layerKey);
        enterPosition.push(tileSetKey);


        return layer;
    };
    this.reset = function () {
        hierarchyId = 0;
    };

    var changeMapTileSetArray = function (tileSetKey) {
        map.tiles = [];
        var tileSet = Constant.TILE_SET_DICT[tileSetKey];
        var currentTileSetId = map.getTilesetIndex(tileSetKey);
        for (var i = 0; i < tileSet.tileList.length; i++) {
            map.tiles.push([tileSet.tileList[i].x, tileSet.tileList[i].y, currentTileSetId]);
        }
    };


    this.pickItem = function (itemKey) {
        resetPick();
        currentPickTile = "ItemPick";
        currentPickName = itemKey;
        mouseSprite = game.add.sprite(game.input.activePointer.worldX, game.input.activePointer.worldY, itemKey);
        if (Constant.ENEMY_DICT.hasOwnProperty(itemKey)) {
            var walk = mouseSprite.animations.add('walk');
            mouseSprite.animations.play('walk', 24, true);
        }

    };
    this.pickTypeTile = function (type) {
        resetPick();
        currentPickTile = "TilePick";
        currentTileType = type;
    };
    this.pickRemove = function(){
        resetPick();
        currentPickTile = "RemovePick";
    };
    this.pickMove = function(){
        resetPick();
        currentPickTile = "MovePick";
    };
    this.pickSelect = function(){
        resetPick();
        currentPickTile = "SelectPick";
    };
    this.selectGroup = function (hGroup) {
        currentSelectHGroup = hGroup;
    };
    this.pickTile = function (tileSetKey, tileId) {
        resetPick();
        //if(currentTileSetKey !== tileSetKey){
        //    currentLayer.resetTilesetCache();
        //    map.addTilesetImage(tileSetKey);
        //    currentTileSetKey = tileSetKey;
        //}
        currentPickTile = "TilePick";
        currentTileType = "BackgroundTile";
        var tileSetIndex = map.getTilesetIndex(tileSetKey);
        if (tileSetIndex === null) {
            addTileSet(tileSetKey)
        }
        var isLayerReady = false;
        for (var i = 0; i < layerList.length; i++) {
            if (layerList[i].name === tileSetKey) {
                isLayerReady = true;
                currentLayer = layerList[i];
                break;
            }
        }
        if (!isLayerReady) {
            currentLayer = addLayer(tileSetKey);
        }

        if (currentTileSetKey != tileSetKey) {
            changeMapTileSetArray(tileSetKey);
        }
        currentTileSetKey = tileSetKey;
        //var tile = Constant.TILE_SET_DICT[tileSetKey].tileList[tileId];
        //currentLayerIndex = enterPosition.indexOf(tileSetKey);
        //currentLayer = layerList[currentLayerIndex];
        //var tile = new Phaser.Tile(currentLayer,tileId,tile.x,tile.y,tile.width,tile.height);
        currentTile = tileId;
    };
    var isUnQuadTreeObject = function(type){
        return Constant.ENEMY_DICT.hasOwnProperty(type);
    };

    this.createSpriteAt = function(posX,posY,type){
        var hGroup = quadTreeHGroup;
        var isUnQuadTree = isUnQuadTreeObject(type);
        if( isUnQuadTree ){
            hGroup = enemyHGroup;
        }
        var sprite = game.add.sprite(posX, posY, type, 0, hGroup._item);
        sprite._type = type;
        sprite.inputEnabled = true;
        sprite.events.onInputOver.add(function(item){
            switch(currentPickTile) {
                case  "RemovePick":
                case "MovePick":
                    item.alpha = 0.5;
                default:
                    break;
            }
        },this);

        sprite.events.onInputOut.add(function(item){
            switch(currentPickTile) {
                case  "RemovePick":
                case "MovePick":
                    item.alpha = 1;
                default:
                    break;
            }

        },this);
        sprite.events.onInputDown.add(function(item){
            switch(currentPickTile){
                case  "RemovePick":
                    var hObjectId = item.hObject._hierarchyId;
                    if(item.hObject.callDestroy()){
                        // $("#hierarchy-" + hObjectId).remove();
                    }
                    break;
                case "MovePick":
                    sprite.input.enableDrag(true);
                    //    item.x = game.input.activePointer.worldX - item.width/2;
                    //    item.y = game.input.activePointer.worldY - item.height/2;
                    break;
                default:
                    break;
            }

        },this);
        sprite.events.onInputUp.add(function(item){
            switch(currentPickTile){
                case  "RemovePick":
                    break;
                case "MovePick":
                    if( Constant.STATIC_TILE_DICT.hasOwnProperty(sprite._type)){
                        sprite.x = marker.x ;
                        sprite.y = marker.y ;
                    }
                    sprite.input.enableDrag(false);
                    //    item.x = game.input.activePointer.worldX - item.width/2;
                    //    item.y = game.input.activePointer.worldY - item.height/2;
                    break;
                default:
                    break;
            }

        },this);
        /**
         * Use quad tree
         */
        sprite._quadTree = null;
        if(!isUnQuadTree){
            game.physics.enable(sprite, Phaser.Physics.ARCADE);
            sprite.body.allowGravity  = false;
            sprite.body.immovable   = true;
            phaserQuadTree.insert(sprite);
            sprite._quadTree = phaserQuadTree;

        }

        if (Constant.ENEMY_DICT.hasOwnProperty(type)) {
            var info = Constant.ENEMY_DICT[type];
            var walk = sprite.animations.add('walk');
            sprite.animations.play('walk', 24, true);
            sprite.x -= info.frameWidth;
            sprite.y -= info.frameHeight;
        } else {
            sprite.x -= sprite.width;
            sprite.y -= sprite.height;
        }



        hierarchyEditor.add.sprite(sprite, hGroup);



    };
    var layOutMarker = function(){
        marker.x = Math.floor(game.input.activePointer.worldX/tileWidth) * tileWidth;
        marker.y = Math.floor(game.input.activePointer.worldY/tileHeight) * tileHeight;
    };

    var handleMouseUp = function(event){
        switch (currentPickTile){
            case "SelectPick":
                if(pickRectCompleted){
                    currentPickRectPos.x = currentPickRectPos.y = 0;
                }
                else{
                    if(currentPickRect.x !== 0 && currentPickRect.y !== 0 && currentPickRect.width !==0 && currentPickRect.height != 0){
                        // updatePickRect();

                        pickRectCompleted = true;
                    }
                }

                // resetCurrentPickRect();
                break;
            default:
                break;
        }
    };
    var updatePickRect = function(){
        if(currentLayer != null){

            var rectX = Math.floor(currentPickRect.x/tileWidth);
            var rectY = Math.floor(currentPickRect.y/tileWidth);
            var width = Math.floor(currentPickRect.width/tileWidth) + 1;
            var height = Math.floor(currentPickRect.height/tileWidth) + 1;
            clearArrayTile();
            // that.arrayTile = new Array(height);
            // for(var y = 0; y < height; y++){
            //     that.arrayTile[y] = new Array(width);
            //     for(var x = 0; x < width; x++){
            //         that.arrayTile[y][x] = null;
            //     }
            // }
            //
            // map.forEach(function(tile){
            //     var tileX = tile.x - rectX;
            //     var tileY = tile.y - rectY;
            //     that.arrayTile[tileY][tileX] = tile;
            // },this,rectX,rectY,width,height,currentLayer);
            that.arrayTile = map.copy(rectX,rectY,width,height,currentLayer);

            for(var i = 0;i<that.arrayTile.length;i++){
                var tile = that.arrayTile[i];
                tile.debug = true;
            }
            currentLayer.dirty = true;
        }
    };
    this.deleteTileInRect = function(){
        if(!pickRectCompleted) return;
        var rectX = Math.floor(currentPickRect.x/tileWidth);
        var rectY = Math.floor(currentPickRect.y/tileWidth);
        var width = Math.floor(currentPickRect.width/tileWidth) + 1;
        var height = Math.floor(currentPickRect.height/tileWidth) + 1;

        map.forEach(function(tile){
            map.putTile(-1, tile.x, tile.y, currentLayer);
            // map.removeTile(tile.x,tile.y,currentLayer);
        },this,rectX,rectY,width,height,currentLayer);
    };
    this.copyTileInRect = function(){
        if(!pickRectCompleted) return;
        updatePickRect();
        // ggConsole.showNotification("Success", "Tiles in rect has been copied!");

    };
    this.pasteTileInRect = function(){
        if(!pickRectCompleted || that.arrayTile.length <= 0) return;
        var rectX = Math.floor(currentPickRect.x/tileWidth);
        var rectY = Math.floor(currentPickRect.y/tileWidth);
        var width = Math.floor(currentPickRect.width/tileWidth) + 1;
        var height = Math.floor(currentPickRect.height/tileWidth) + 1;

        map.paste(rectX,rectY,that.arrayTile,currentLayer);
        // ggConsole.showNotification("Success", "Tiles has been pasted!");

    };
    var clearArrayTile = function(){
        for(var i = 0;i<that.arrayTile.length;i++){
            var tile = that.arrayTile[i];
            tile.debug = false;
        }
        if(currentLayer!=null) currentLayer.dirty = true;
        that.arrayTile = [];
    };
    var putTileArrayAt = function(x,y,width,height){
        x = Math.floor(x/tileWidth);
        y = Math.floor(y/tileWidth);
        width = Math.round(width/tileWidth);
        height = Math.round(height/tileWidth);
    };
    var updateMarker = function (pointer, event) {
        switch (currentPickTile) {
            case "ItemPick":
                if(Constant.STATIC_TILE_DICT.hasOwnProperty(currentPickName)){
                    layOutMarker();
                    mouseSprite.x = marker.x;
                    mouseSprite.y = marker.y;
                }else{
                    mouseSprite.x = game.input.activePointer.worldX - mouseSprite.width;
                    mouseSprite.y = game.input.activePointer.worldY - mouseSprite.height;
                }

                break;
            case "SelectPick":

                break;
            case "TilePick":
            default:
                layOutMarker();
        }

        if (game.input.mousePointer.isDown) {
            wasMouseButtonDown = true;
            if (isBlockingClick) return;
            switch (currentPickTile) {
                case "SelectPick":
                    var posX = game.input.activePointer.worldX;
                    var posY = game.input.activePointer.worldY;

                    if(currentPickRect.top === 0 && currentPickRect.left === 0){
                        clearArrayTile();
                        pickRectCompleted = false;
                        currentPickRect.left = posX;
                        currentPickRect.top = posY;
                    }else{
                        if(pickRectCompleted){
                            if(currentPickRectPos.x === 0 && currentPickRectPos.y === 0){
                                currentPickRectPos.x = posX;
                                currentPickRectPos.y = posY;
                            }else{
                                currentPickRect.x += posX - currentPickRectPos.x;
                                currentPickRect.y += posY - currentPickRectPos.y;
                                currentPickRectPos.x = posX;
                                currentPickRectPos.y = posY;
                            }
                        }else{
                            currentPickRect.right = posX;
                            currentPickRect.bottom = posY;
                        }
                    }

                    break;
                case  "RemovePick":
                    break;
                case "ItemPick":
                    isBlockingClick = true;
                    var posX = game.input.activePointer.worldX;
                    var posY = game.input.activePointer.worldY;
                    var setSprite = function () {
                        if(Constant.STATIC_TILE_DICT.hasOwnProperty(currentPickName)){
                            that.createSpriteAt(marker.x+tileWidth,marker.y+tileHeight,currentPickName);
                        }
                        else{
                            that.createSpriteAt(posX,posY,currentPickName);
                        }
                        isBlockingClick = false;
                    };
                    window.setTimeout(setSprite, 50);
                    break;
                case "TilePick":
                    switch (currentTileType){
                        case "BackgroundTile":
                            if (currentLayer != null) {
                                var tile = map.putTile(currentTile, currentLayer.getTileX(marker.x), currentLayer.getTileY(marker.y), currentTileSetKey);
                                tile._type = "Tile";
                            }
                            break;
                        default:
                            // isBlockingClick = true;
                            // var setStaticTile = function () {
                            //     that.createSpriteAt(marker.x ,marker.y,currentTileType);
                            //     isBlockingClick = false;
                            // };
                            // window.setTimeout(setStaticTile, 150);
                            break;
                    }
                    break;
                default:
                    break;
            }

        }else{
            if(wasMouseButtonDown){
                wasMouseButtonDown = false;
                handleMouseUp();
            }
        }


    }


};