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
    }
};