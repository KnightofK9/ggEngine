/**
 * Created by knightofk9 on 11/20/2016.
 */
var ObjectList = function(){
    var panel = $("#gg-tool-object-list");
    var navTab = $("#gg-tool-object-list-nav-tab");
    var that = this;
    //<li role="presentation" ><a role="menuitem" tabindex="-1" href="#" >Map 1</a></li>

    var objectSelect = $("#gg-object-tile");
    var charSelect = $("#gg-object-character");
    var tileSelect = $("#gg-object-tile");

    var itemOption = $("#gg-object-item-picker");
    var charOption = $("#gg-object-char-picker");
    var tileOption = $("#gg-object-tile-picker");

    this.setActive = function(isActive){
        if(isActive){
            panel.css("display","block");
            navTab.addClass("active");
        }else{
            panel.css("display","none");
            navTab.removeClass("active");
        }
    };
    var initOption = function(key,name){
        // <option data-img-src="Resource/Resources/Boomerang.png" data-img-class="first" data-img-alt="StaticTile" data-img-label="StaticTile" value="0">   </option>
        var div = ' <option data-img-src="'+ name +'" data-img-class="first" data-img-alt="'+ key + '" data-img-label="'+ key + '" value="0">   </option>';
        return div;
    };

    var initEnemyList = function(){
        charOption.html("");
        for(var key in Constant.ENEMY_DICT){
            if(Constant.ENEMY_DICT.hasOwnProperty(key)){
                charOption.append( initOption(key, Constant.ENEMY_DICT[key].name));
            }
        }
    };
    var initObjectList = function(){
        itemOption.html("");
        for(var key in Constant.ITEM_DICT){
            if(Constant.ITEM_DICT.hasOwnProperty(key)){
                itemOption.append( initOption(key, Constant.ITEM_DICT[key].name));
            }
        }
    };
    var handleClicked = function(select, picker_option, event){
        var type = select.node[0].textContent;
        switch(this[0].id){
            case "gg-object-tile-picker":
                sceneEditor.editState.pickTypeTile(type);
                break;
            case "gg-object-item-picke":
                break;
            case "gg-object-char-picker":
                break;
        }
    };
    var init = function(){
        initEnemyList();
        initObjectList();
        objectSelect.css("display","none");
        charSelect.css("display","none");
        tileSelect.css("display","none");
        $("select").imagepicker({
            show_label:true,
            clicked:handleClicked
            // function(select, picker option, event){...}
        });
    };
    init();
};