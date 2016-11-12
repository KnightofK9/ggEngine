/**
 * Created by Knight of k9 on 12/11/2016.
 */
var Constant = new function(){
    this.DEFAULT_URL = "http://localhost/ggEditor/";
    this.RESOURCE_PATH = this.DEFAULT_URL + "Resource/Resources/";
    this.TILE_SET_PATH = this.DEFAULT_URL + "Resource/Resources/" + "TileSet/";


    this.TILE_SET_DICT ={
        "level-2-tile-set":{
            name:"lv2.png",
            width:64,
            height:192,
            cellWidth:16,
            cellHeight:16,
            numberOfCellPerRow:4,
            numberOfCellPerColumn:12
        },
        "level-3-tile-set":{
            name:"lv3.png",
            width:128,
            height:288,
            cellWidth:16,
            cellHeight:16,
            numberOfCellPerRow:8,
            numberOfCellPerColumn:18
        }
    }
};