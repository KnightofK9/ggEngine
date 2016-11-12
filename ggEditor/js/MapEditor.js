/**
 * Created by Knight of k9 on 12/11/2016.
 */
var MapEditor = function () {
    var tileSetSelect = $("#gg-map-tile-set-select");
    var tileSetList = $("#gg-map-tile-set-list");
    var tilePanel = $("#gg-map-tile-panel");
    var that = this;
    //<li role="presentation" ><a role="menuitem" tabindex="-1" href="#" >Map 1</a></li>


    this.reloadTileSetList = function () {
        tileSetList.html("");
        for (var key in Constant.TILE_SET_DICT) {
            if (Constant.TILE_SET_DICT.hasOwnProperty(key)) {
                var tileSet = Constant.TILE_SET_DICT[key];
                addTileSet(key, tileSet);
            }

        }
        reloadClickFunction();
    };

    this.selectTileSet = function (tileSetKey) {
        var tileSet = Constant.TILE_SET_DICT[tileSetKey];
        tilePanel.css("background", "url(" + Constant.TILE_SET_PATH + tileSet.name + ") no-repeat");
        tilePanel.css("width", tileSet.width);
        tilePanel.css("height", tileSet.height);

        drawTable(tileSetKey,tileSet);

    };


    /**
     * Private function
     */
    var drawTable = function (tileSetKey,tileSet) {
        var table = ('<table>');
        var gridWidth = tileSet.numberOfCellPerRow;
        var gridHeight = tileSet.numberOfCellPerColumn;
        var grid = [];
        for (var y = 0; y < gridHeight; y++) {
            table += ('<tr>');
            grid.push([]);
            for (var x = 0; x < gridWidth; x++) {
                table += ('<td onclick="handleClickTile(\''+tileSetKey+'\','+ (y*gridWidth+x) +')">');
                grid[y].push(0);
                table += ('</td>');
            }
            table += ('</tr>');
        }
        table += ('</table>');
        tilePanel.html(table);

        $("#gg-map-tile-panel td").css("width", tileSet.cellWidth);
        $("#gg-map-tile-panel td").css("height", tileSet.cellHeight);
    };

    var reloadClickFunction = function () {
        $("#gg-map-tile-set-list li").on('click', function () {
            var tileSetKey = $(this).text();
            that.selectTileSet(tileSetKey);
        });
    };

    var addTileSet = function (key, tileSet) {
        tileSetList.append('<li role="presentation" ><a role="menuitem"  >' + key + '</a></li>');
    };

    var init = function () {
        for (var key in Constant.TILE_SET_DICT) {
            if (Constant.TILE_SET_DICT.hasOwnProperty(key)) {
                initTileIdList(key);
            }
        }
    };

    var initTileIdList = function (key) {
        var tileSet = Constant.TILE_SET_DICT[key];
        tileSet.tileList = [];
        for(var y = 0;y<tileSet.numberOfCellPerColumn;y++){
            for(var x = 0;x<tileSet.numberOfCellPerRow;x++){
                var tile = new Tile();
                tile.width = tileSet.cellWidth;
                tile.height = tileSet.cellHeight;
                tile.x = x*tile.width;
                tile.y = y*tile.height;
                tileSet.tileList.push(tile);
            }
        }

        Constant.TILE_SET_DICT[key] = tileSet;
    };

    init();
    this.reloadTileSetList();


};

function handleClickTile(tileSet,id){
    sceneEditor.editState.pickTile(tileSet,id);
    //alert(JSON.stringify(Constant.TILE_SET_DICT[tileSet].tileList[id]));
}
function Tile(){
    this.x = 0;
    this.y = 0;
    this.width = 0;
    this.height = 0;
}