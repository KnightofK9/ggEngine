/**
 * Created by Knight of k9 on 12/11/2016.
 */
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
    var cursors;
    var showLayersKey;
    var layer1Key;
    var layer2Key;
    var currentLayerIndex = 0;
    var manualSelectLayer = 0;
    var layer3Key;
    this.preload = function(){
        //var iBg = new Image();
        //iBg.src = bgData;
        //game.cache.addImage('bg', bgData, iBg);

        for(var key in Constant.TILE_SET_DICT){
            if(Constant.TILE_SET_DICT.hasOwnProperty(key)){
                var tileSet = Constant.TILE_SET_DICT[key];
                game.load.spritesheet(key, Constant.TILE_SET_PATH + tileSet.name, tileSet.cellWidth,tileSet.cellHeight);
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
        if(layerList.length==1){
            ggConsole.showNotification("Error","You can not use multiple tile set for 1 tile map.");
            return false;
        }
        map.addTilesetImage(tileSetKey);
        var layer = map.createBlankLayer(tileSetKey, game.width/tileWidth, game.height/tileHeight, tileWidth, tileHeight);
        layer.scrollFactorX = 0.5;
        layer.scrollFactorY = 0.5;
        layer.resizeWorld();
        layerList.push(layer);
        var lastIndex = layerList.length  - 1;
        var layerKey = game.input.keyboard.addKey((lastIndex+1).toString().charCodeAt(0));
        layerKey.onDown.add(changeLayer, this);
        layerKeyList.push(layerKey);
        enterPosition.push(tileSetKey);
        return true;
    };
    this.pickTile = function(tileSetKey, tileId) {
        //if(currentTileSetKey !== tileSetKey){
        //    currentLayer.resetTilesetCache();
        //    map.addTilesetImage(tileSetKey);
        //    currentTileSetKey = tileSetKey;
        //}
        var tileSetIndex = map.getTilesetIndex(tileSetKey);
        if(tileSetIndex === null){
            if(!addTileSet(tileSetKey)) return;
        }
        currentLayerIndex = enterPosition.indexOf(tileSetKey);
        currentLayer = layerList[currentLayerIndex];
        currentTile = tileId;
    };

    var updateMarker = function() {

       if(currentLayer!=null){
           marker.x = currentLayer.getTileX(game.input.activePointer.worldX) * tileWidth;
           marker.y = currentLayer.getTileY(game.input.activePointer.worldY) * tileHeight;
           if (game.input.mousePointer.isDown)
           {
               map.putTile(currentTile, currentLayer.getTileX(marker.x), currentLayer.getTileY(marker.y), currentLayer);
           }
       }



    }


};